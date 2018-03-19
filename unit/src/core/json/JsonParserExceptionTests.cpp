#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonParserException>
#include <prism/JsonSymbols>
#include <string>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonParserExceptionTests, WhenJsonSymbolIsSExpectErrorMessageToExpectLeftBrace) {
    std::string invalidString = "#";
    JsonParserException ex(JsonSymbol::NT_S, invalidString);
    std::string expectedMessage = "Error: parse error - expecting '{', got '#'";
    EXPECT_EQ(expectedMessage, ex.errorMsg());
}

TEST(JsonParserExceptionTests, WhenJsonSymbolIsTExpectErrorMessageToExpectStringOrRightBrace) {
    std::string invalidString = "#";
    JsonParserException ex(JsonSymbol::NT_T, invalidString);
    std::string expectedMessage = "Error: parse error - expecting 'String', '}', got '#'";
    EXPECT_EQ(expectedMessage, ex.errorMsg());
}

TEST(JsonParserExceptionTests, WhenJsonSymbolIsMExpectErrorMessageToExpectString) {
    std::string invalidString = "#";
    JsonParserException ex(JsonSymbol::NT_M, invalidString);
    std::string expectedMessage = "Error: parse error - expecting 'String', got '#'";
    EXPECT_EQ(expectedMessage, ex.errorMsg());
}

TEST(JsonParserExceptionTests, WhenJsonSymbolIsPExpectErrorMessageToExpectString) {
    std::string invalidString = "#";
    JsonParserException ex(JsonSymbol::NT_P, invalidString);
    std::string expectedMessage = "Error: parse error - expecting 'String', got '#'";
    EXPECT_EQ(expectedMessage, ex.errorMsg());
}

TEST(JsonParserExceptionTests, WhenJsonSymbolIsQExpectErrorMessageToExpectCommaOrRightBraceOrRightBracket) {
    std::string invalidString = "#";
    JsonParserException ex(JsonSymbol::NT_Q, invalidString);
    std::string expectedMessage = "Error: parse error - expecting ',', '}', ']', got '#'";
    EXPECT_EQ(expectedMessage, ex.errorMsg());
}

TEST(JsonParserExceptionTests, WhenJsonSymbolIsRExpectErrorMessageToExpectLeftBracket) {
    std::string invalidString = "#";
    JsonParserException ex(JsonSymbol::NT_R, invalidString);
    std::string expectedMessage = "Error: parse error - expecting '[', got '#'";
    EXPECT_EQ(expectedMessage, ex.errorMsg());
}

TEST(JsonParserExceptionTests, WhenJsonSymbolIsEExpectErrorMessageToExpectLeftBraceOrLeftBracketOrRightBracketOrStringOrNumberOrBoolOrNull) {
    std::string invalidString = "#";
    JsonParserException ex(JsonSymbol::NT_E, invalidString);
    std::string expectedMessage = "Error: parse error - expecting '{', '[', ']', 'String', 'Number', 'Bool', 'Null', got '#'";
    EXPECT_EQ(expectedMessage, ex.errorMsg());
}

TEST(JsonParserExceptionTests, WhenJsonSymbolIsFExpectErrorMessageToExpectRightBracketOrComma) {
    std::string invalidString = "#";
    JsonParserException ex(JsonSymbol::NT_F, invalidString);
    std::string expectedMessage = "Error: parse error - expecting ']', ',', got '#'";
    EXPECT_EQ(expectedMessage, ex.errorMsg());
}

TEST(JsonParserExceptionTests, WhenJsonSymbolIsVExpectErrorMessageToExpectLeftBraceOrLeftBracketOrStringOrNumberOrBoolOrNull) {
    std::string invalidString = "#";
    JsonParserException ex(JsonSymbol::NT_V, invalidString);
    std::string expectedMessage = "Error: parse error - expecting '{', '[', 'String', 'Number', 'Bool', 'Null', got '#'";
    EXPECT_EQ(expectedMessage, ex.errorMsg());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
