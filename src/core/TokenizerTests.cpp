#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <string>

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

};
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
    int count{0};
    int currentToken{0};
};

Tokenizer::Tokenizer(const std::string& str) {
    tokenize(str);
}

const bool
Tokenizer::hasNext() const {
    if (currentToken >= count) return false;
    return true;
}

Token
Tokenizer::next() {
    if (!hasNext())
        throw NonExistentException();
    ++currentToken;
    return Token();
}

int
Tokenizer::numTokens() const {
    return count;
}

void
Tokenizer::tokenize(const std::string& str) {
    count = str.size();
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

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
