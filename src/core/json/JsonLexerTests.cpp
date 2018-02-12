#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonLexer>
#include <prism/EmptyException>
#include <string>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonLexerTests, ThrowsWhenInitializedWithInvalidInput) {
    std::string invalidInput = "?&£";
    ASSERT_THROW(JsonLexer lex(invalidInput), prism::JsonLexerException);
}

TEST(JsonLexerTests, LexerHasOneTokenAfterGivenValidInput) {
    JsonLexer lex("{}");
    ASSERT_TRUE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsCommaToken) {
    JsonLexer lex(",");
    ASSERT_EQ(JsonToken(JsonToken::Type::Comma), lex.next());
}

TEST(JsonLexerTests, ReturnsColonToken) {
    JsonLexer lex(":");
    ASSERT_EQ(JsonToken(JsonToken::Type::Colon), lex.next());
}

TEST(JsonLexerTests, ReturnsLeftBraceToken) {
    JsonLexer lex("{");
    ASSERT_EQ(JsonToken(JsonToken::Type::LeftBrace), lex.next());
}

TEST(JsonLexerTests, ReturnsRightBraceToken) {
    JsonLexer lex("}");
    ASSERT_EQ(JsonToken(JsonToken::Type::RightBrace), lex.next());
}

TEST(JsonLexerTests, ReturnsLeftBracketToken) {
    JsonLexer lex("[");
    ASSERT_EQ(JsonToken(JsonToken::Type::LeftBracket), lex.next());
}

TEST(JsonLexerTests, ReturnsRightBracketToken) {
    JsonLexer lex("]");
    ASSERT_EQ(JsonToken(JsonToken::Type::RightBracket), lex.next());
}

TEST(JsonLexerTests, ReturnsTrueConstantToken) {
    std::string input = "true";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::BoolLiteral, input), lex.next());
}

TEST(JsonLexerTests, ReturnsFalseConstantToken) {
    std::string input = "false";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::BoolLiteral, input), lex.next());
}

TEST(JsonLexerTests, ReturnsNullConstantToken) {
    std::string input = "null";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::NullLiteral), lex.next());
}

TEST(JsonLexerTests, ParsesEmptyString) {
    std::string input = R"("")";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::String, ""), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsStringLiteralToken) {
    std::string input = R"("manhattan")";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::String, "manhattan"), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsPositiveSingleDigitNumericalToken) {
    std::string input = "4";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.next());
}

TEST(JsonLexerTests, ReturnsPositiveMultiDigitNumericalToken) {
    std::string input = "479";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsNegativSingleDigiteNumericalToken) {
    std::string input = "-1";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsNegativeMultiDigitNumericalToken) {
    std::string input = "-132";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsPositiveDecimalNumericalToken) {
    std::string input = "3.14";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsNegativeDecimalNumericalToken) {
    std::string input = "-6.28";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsPositiveExponentialNumericalToken) {
    std::string input1 = "1.23e15";
    std::string input2 = "1.23e+15";

    JsonLexer lex1(input1);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input1), lex1.next());
    ASSERT_FALSE(lex1.hasNext());

    JsonLexer lex2(input2);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input2), lex2.next());
    ASSERT_FALSE(lex2.hasNext());
}

TEST(JsonLexerTests, ReturnsNegativeExponentialNumericalToken) {
    std::string input = "-3.14E-15";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, TokenizesObject) {
    std::string input = R"({ "key" : "value" })";
    JsonLexer lex(input);
    using Type = JsonToken::Type;
    ASSERT_EQ(JsonToken(Type::LeftBrace), lex.next());
    ASSERT_EQ(JsonToken(Type::String, "key"), lex.next());
    ASSERT_EQ(JsonToken(Type::Colon), lex.next());
    ASSERT_EQ(JsonToken(Type::String, "value"), lex.next());
    ASSERT_EQ(JsonToken(Type::RightBrace), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, TokenizesObjectWithMultipleMembers) {
    std::string input = R"({ "key1" : "value1", "key2" : "value2" })";
    JsonLexer lex(input);
    using Type = JsonToken::Type;
    ASSERT_EQ(JsonToken(Type::LeftBrace), lex.next());
    ASSERT_EQ(JsonToken(Type::String, "key1"), lex.next());
    ASSERT_EQ(JsonToken(Type::Colon), lex.next());
    ASSERT_EQ(JsonToken(Type::String, "value1"), lex.next());
    ASSERT_EQ(JsonToken(Type::Comma), lex.next());
    ASSERT_EQ(JsonToken(Type::String, "key2"), lex.next());
    ASSERT_EQ(JsonToken(Type::Colon), lex.next());
    ASSERT_EQ(JsonToken(Type::String, "value2"), lex.next());
    ASSERT_EQ(JsonToken(Type::RightBrace), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, TokenizesArray) {
    std::string input = R"([ 67891, "val" ])";
    JsonLexer lex(input);
    using Type = JsonToken::Type;
    ASSERT_EQ(JsonToken(Type::LeftBracket), lex.next());
    ASSERT_EQ(JsonToken(Type::Number, "67891"), lex.next());
    ASSERT_EQ(JsonToken(Type::Comma), lex.next());
    ASSERT_EQ(JsonToken(Type::String, "val"), lex.next());
    ASSERT_EQ(JsonToken(Type::RightBracket), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
