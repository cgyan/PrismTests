#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonLexer>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cerrno>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

//TODO: graceful error handling for invalid input

TEST(JsonLexerTests, DefaultLexerIsEmpty) {
    JsonLexer lex;
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, DefaultLexerThrowsWhenAccessingTokens) {
    JsonLexer lex;
    ASSERT_THROW(lex.next(), prism::EmptyException);
}

TEST(JsonLexerTests, LexerHasZeroTokensAfterProcessingUnrecognizedInput) {
    JsonLexer lex("?&£"); // lexer doesn't know how to tokenize this input
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, LexerHasOneTokenAfterGivenValidInput) {
    JsonLexer lex("{}");
    ASSERT_TRUE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsCommaToken) {
    JsonLexer lex(",");
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::COMMA), lex.next());
}

TEST(JsonLexerTests, ReturnsColonToken) {
    JsonLexer lex(":");
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::COLON), lex.next());
}

TEST(JsonLexerTests, ReturnsLeftBraceToken) {
    JsonLexer lex("{");
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::LEFT_BRACE), lex.next());
}

TEST(JsonLexerTests, ReturnsRightBraceToken) {
    JsonLexer lex("}");
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::RIGHT_BRACE), lex.next());
}

TEST(JsonLexerTests, ReturnsLeftBracketToken) {
    JsonLexer lex("[");
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::LEFT_BRACKET), lex.next());
}

TEST(JsonLexerTests, ReturnsRightBracketToken) {
    JsonLexer lex("]");
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::RIGHT_BRACKET), lex.next());
}

TEST(JsonLexerTests, ReturnsTrueConstantToken) {
    std::string input = "true";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::BOOL_LITERAL, input), lex.next());
}

TEST(JsonLexerTests, ReturnsFalseConstantToken) {
    std::string input = "false";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::BOOL_LITERAL, input), lex.next());
}

TEST(JsonLexerTests, ReturnsNullConstantToken) {
    std::string input = "null";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NULL_LITERAL), lex.next());
}

TEST(JsonLexerTests, ParsesEmptyString) {
    std::string input = R"("")";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::STRING, ""), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsStringLiteralToken) {
    std::string input = R"("manhattan")";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::STRING, "manhattan"), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsPositiveSingleDigitNumericalToken) {
    std::string input = "4";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NUMBER, input), lex.next());
}

TEST(JsonLexerTests, ReturnsPositiveMultiDigitNumericalToken) {
    std::string input = "479";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NUMBER, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsNegativSingleDigiteNumericalToken) {
    std::string input = "-1";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NUMBER, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsNegativeMultiDigitNumericalToken) {
    std::string input = "-132";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NUMBER, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsPositiveDecimalNumericalToken) {
    std::string input = "3.14";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NUMBER, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsNegativeDecimalNumericalToken) {
    std::string input = "-6.28";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NUMBER, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ReturnsPositiveExponentialNumericalToken) {
    std::string input1 = "1.23e15";
    std::string input2 = "1.23e+15";

    JsonLexer lex1(input1);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NUMBER, input1), lex1.next());
    ASSERT_FALSE(lex1.hasNext());

    JsonLexer lex2(input2);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NUMBER, input2), lex2.next());
    ASSERT_FALSE(lex2.hasNext());
}

TEST(JsonLexerTests, ReturnsNegativeExponentialNumericalToken) {
    std::string input = "-3.14E-15";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NUMBER, input), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ParsesObject) {
    std::string input = R"({ "key" : "value" })";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::LEFT_BRACE), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::STRING, "key"), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::COLON), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::STRING, "value"), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::RIGHT_BRACE), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ParsesObjectWithMultiplePairs) {
    std::string input = R"({ "key1" : "value1", "key2" : "value2" })";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::LEFT_BRACE), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::STRING, "key1"), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::COLON), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::STRING, "value1"), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::COMMA), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::STRING, "key2"), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::COLON), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::STRING, "value2"), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::RIGHT_BRACE), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

TEST(JsonLexerTests, ParsesArray) {
    std::string input = R"([ 67891, "val" ])";
    JsonLexer lex(input);
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::LEFT_BRACKET), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::NUMBER, "67891"), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::COMMA), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::STRING, "val"), lex.next());
    ASSERT_EQ(JsonToken(JsonToken::LexemeType::RIGHT_BRACKET), lex.next());
    ASSERT_FALSE(lex.hasNext());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
