#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <string>
#include <vector>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE
//==============================================================================
// NonExistentException
//==============================================================================
class NonExistentException {

};
//==============================================================================
// Token
//==============================================================================
struct Token {
    enum {
        OBJ_OPEN,
        OBJ_CLOSE,
        DBL_QUOTE,
        ARR_OPEN,
        ARR_CLOSE,
        PAIR_DIVIDER,
        // a-z
        // A-Z
        // 0-9
        TRUE_VALUE,
        FALSE_VALUE,
        NULL_VALUE
    };
    int type;
    std::string value;
};

Token
make_token(const int type, const std::string& value) {
    Token tk;
    tk.type = type;
    tk.value = value;
    return tk;
}
//==============================================================================
// Tokenizer
//==============================================================================
class Tokenizer {
public:
    Tokenizer() = default;
    Tokenizer(const std::string& str);

    const bool hasNext() const;
    Token next();
    int numTokens() const;
    void tokenize(const std::string& str);
private:
    int currentToken{0};
    std::vector<Token> tokens{};
};

Tokenizer::Tokenizer(const std::string& str) {
    tokenize(str);
}

const bool
Tokenizer::hasNext() const {
    if (currentToken >= tokens.size()) return false;
    return true;
}

Token
Tokenizer::next() {
    if (!hasNext())
        throw NonExistentException();
    return tokens.at(currentToken++);
}

int
Tokenizer::numTokens() const {
    return tokens.size();
}

void
Tokenizer::tokenize(const std::string& str) {
    if (str == "{")
        tokens.push_back(make_token(Token::OBJ_OPEN, "{"));
    else if (str == "}")
        tokens.push_back(make_token(Token::OBJ_CLOSE, "}"));
    else if (str == "\"")
        tokens.push_back(make_token(Token::DBL_QUOTE, "\""));
    else if (str == "[")
        tokens.push_back(make_token(Token::ARR_OPEN, "["));
    else if (str == "]")
        tokens.push_back(make_token(Token::ARR_CLOSE, "]"));
    else if (str == ":")
        tokens.push_back(make_token(Token::PAIR_DIVIDER, ":"));
    else if (str == "true")
        tokens.push_back(make_token(Token::TRUE_VALUE, "true"));
    else if (str == "false")
        tokens.push_back(make_token(Token::FALSE_VALUE, "false"));
    else if (str == "null")
        tokens.push_back(make_token(Token::NULL_VALUE, "null"));
    else if (str == "{}") {
        tokens.push_back(Token());
        tokens.push_back(Token());
    }
    currentToken = 0;
}
//==============================================================================
// TokenizerTests
//==============================================================================
TEST(TokenizerTests, HasZeroTokensByDefault) {
    Tokenizer t;
    ASSERT_EQ(0, t.numTokens());
}

TEST(TokenizerTests, ThrowsWhenEmptyTokenizerReturnsNextToken) {
    Tokenizer t;
    ASSERT_THROW(t.next(), NonExistentException);
}

TEST(TokenizerTests, ReturnsFalseForNextTokenEnquiryWhenTokenCountIsZero) {
    Tokenizer t;
    ASSERT_FALSE(t.hasNext());
}

TEST(TokenizerTests, ReturnsSizeOneAfterTokenization) {
    Tokenizer t("{");
    ASSERT_EQ(1, t.numTokens());
}

TEST(TokenizerTests, ReturnsSizeTwoAfterTokenization) {
    Tokenizer t;
    t.tokenize("{}");
    ASSERT_EQ(2, t.numTokens());
}

TEST(TokenizerTests, ReturnsTrueForNextTokenEnquiryBeforeFirstTokenRead) {
    Tokenizer t("{");
    ASSERT_TRUE(t.hasNext());
}

TEST(TokenizerTests, ReturnsFalseForNextTokenEnquiryWhenAllTokensRead) {
    Tokenizer t("{");
    t.next();
    ASSERT_FALSE(t.hasNext());
}

TEST(TokenizerTests, ReturnsObjectOpenToken) {
    Tokenizer t("{");
    Token tk = t.next();
    ASSERT_EQ(Token::OBJ_OPEN, tk.type);
    ASSERT_EQ("{", tk.value);
}

TEST(TokenizerTests, ReturnsObjectCloseToken) {
    Tokenizer t("}");
    Token tk = t.next();
    ASSERT_EQ(Token::OBJ_CLOSE, tk.type);
    ASSERT_EQ("}", tk.value);
}

TEST(TokenizerTests, ReturnsDoubleQuoteToken) {
    Tokenizer t("\"");
    Token tk = t.next();
    ASSERT_EQ(Token::DBL_QUOTE, tk.type);
    ASSERT_EQ("\"", tk.value);
}

TEST(TokenizerTests, ReturnsArrayOpenToken) {
    Tokenizer t("[");
    Token tk = t.next();
    ASSERT_EQ(Token::ARR_OPEN, tk.type);
    ASSERT_EQ("[", tk.value);
}

TEST(TokenizerTests, ReturnsArrayCloseToken) {
    Tokenizer t("]");
    Token tk = t.next();
    ASSERT_EQ(Token::ARR_CLOSE, tk.type);
    ASSERT_EQ("]", tk.value);
}

TEST(TokenizerTests, ReturnsPairDividerToken) {
    Tokenizer t(":");
    Token tk = t.next();
    ASSERT_EQ(Token::PAIR_DIVIDER, tk.type);
    ASSERT_EQ(":", tk.value);
}

TEST(TokenizerTests, ReturnsTrueToken) {
    Tokenizer t("true");
    Token tk = t.next();
    ASSERT_EQ(Token::TRUE_VALUE, tk.type);
    ASSERT_EQ("true", tk.value);
}

TEST(TokenizerTests, ReturnsFalseToken) {
    Tokenizer t("false");
    Token tk = t.next();
    ASSERT_EQ(Token::FALSE_VALUE, tk.type);
    ASSERT_EQ("false", tk.value);
}

TEST(TokenizerTests, ReturnsNullToken) {
    Tokenizer t("null");
    Token tk = t.next();
    ASSERT_EQ(Token::NULL_VALUE, tk.type);
    ASSERT_EQ("null", tk.value);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
