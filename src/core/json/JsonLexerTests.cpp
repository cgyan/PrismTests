#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonLexer>
#include <prism/JsonLexerException>
#include <prism/JsonToken>
#include <prism/EmptyException>
#include <string>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonLexerTests, ThrowsWhenInitializedWithInvalidInput) {
    std::string invalidInput = "?&£";
    JsonLexer lex{invalidInput};
    ASSERT_THROW(lex.getNextToken(), prism::JsonLexerException);
}

TEST(JsonLexerTests, LexerHasOneTokenAfterGivenValidInput) {
    JsonLexer lex("{");
    ASSERT_TRUE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, ReturnsCommaToken) {
    JsonLexer lex(",");
    ASSERT_EQ(JsonToken(JsonToken::Type::Comma), lex.getNextToken());
}

TEST(JsonLexerTests, ReturnsColonToken) {
    JsonLexer lex(":");
    ASSERT_EQ(JsonToken(JsonToken::Type::Colon), lex.getNextToken());
}

TEST(JsonLexerTests, ReturnsLeftBraceToken) {
    JsonLexer lex("{");
    ASSERT_EQ(JsonToken(JsonToken::Type::LeftBrace), lex.getNextToken());
}

TEST(JsonLexerTests, ReturnsRightBraceToken) {
    JsonLexer lex("}");
    ASSERT_EQ(JsonToken(JsonToken::Type::RightBrace), lex.getNextToken());
}

TEST(JsonLexerTests, ReturnsLeftBracketToken) {
    JsonLexer lex("[");
    ASSERT_EQ(JsonToken(JsonToken::Type::LeftBracket), lex.getNextToken());
}

TEST(JsonLexerTests, ReturnsRightBracketToken) {
    JsonLexer lex("]");
    ASSERT_EQ(JsonToken(JsonToken::Type::RightBracket), lex.getNextToken());
}

TEST(JsonLexerTests, ReturnsTrueConstantToken) {
    std::string input = "true";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::BoolLiteral, input), lex.getNextToken());
}

TEST(JsonLexerTests, ReturnsFalseConstantToken) {
    std::string input = "false";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::BoolLiteral, input), lex.getNextToken());
}

TEST(JsonLexerTests, ReturnsNullConstantToken) {
    std::string input = "null";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::NullLiteral), lex.getNextToken());
}

TEST(JsonLexerTests, ParsesEmptyString) {
    std::string input = R"("")";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::String, ""), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, ReturnsStringLiteralToken) {
    std::string input = R"("manhattan")";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::String, "manhattan"), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, ReturnsPositiveSingleDigitNumericalToken) {
    std::string input = "4";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.getNextToken());
}

TEST(JsonLexerTests, ReturnsPositiveMultiDigitNumericalToken) {
    std::string input = "479";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, ReturnsNegativSingleDigiteNumericalToken) {
    std::string input = "-1";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, ReturnsNegativeMultiDigitNumericalToken) {
    std::string input = "-132";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, ReturnsPositiveDecimalNumericalToken) {
    std::string input = "3.14";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, ReturnsNegativeDecimalNumericalToken) {
    std::string input = "-6.28";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, ReturnsPositiveExponentialNumericalToken) {
    std::string input1 = "1.23e15";
    std::string input2 = "1.23e+15";

    JsonLexer lex1(input1);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input1), lex1.getNextToken());
    ASSERT_FALSE(lex1.hasMoreTokens());

    JsonLexer lex2(input2);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input2), lex2.getNextToken());
    ASSERT_FALSE(lex2.hasMoreTokens());
}

TEST(JsonLexerTests, ReturnsNegativeExponentialNumericalToken) {
    std::string input = "-3.14E-15";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::Type::Number, input), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, TokenizesObject) {
    std::string input = R"({ "key" : "value" })";
    JsonLexer lex(input);
    using Type = JsonToken::Type;
    ASSERT_EQ(JsonToken(Type::LeftBrace), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::String, "key"), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::Colon), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::String, "value"), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::RightBrace), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, TokenizesObjectWithMultipleMembers) {
    std::string input = R"({ "key1" : "value1", "key2" : "value2" })";
    JsonLexer lex(input);
    using Type = JsonToken::Type;
    ASSERT_EQ(JsonToken(Type::LeftBrace), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::String, "key1"), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::Colon), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::String, "value1"), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::Comma), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::String, "key2"), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::Colon), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::String, "value2"), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::RightBrace), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

TEST(JsonLexerTests, TokenizesArray) {
    std::string input = R"([ 67891, "val" ])";
    JsonLexer lex(input);
    using Type = JsonToken::Type;
    ASSERT_EQ(JsonToken(Type::LeftBracket), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::Number, "67891"), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::Comma), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::String, "val"), lex.getNextToken());
    ASSERT_EQ(JsonToken(Type::RightBracket), lex.getNextToken());
    ASSERT_FALSE(lex.hasMoreTokens());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
