//==============================================================================
// JsonParser
//==============================================================================
#include <prism/global>
#include <prism/JsonLexer>
#include <prism/JsonToken>
#include <prism/Vector>
#include <prism/Exception>

PRISM_BEGIN_NAMESPACE

class JsonParserException : public Exception {

};

class JsonTree {

};

class JsonTreeEmptyObjectStub : public JsonTree {

};

const bool operator==(const JsonTreeEmptyObjectStub& lhs, const JsonTree& rhs) {
    return true;
}

class JsonLexerInvalidStreamStub : public JsonLexer {
public:
    JsonLexerInvalidStreamStub() : JsonLexer{""} {}
    JsonToken next() override {
        return tokens[0];
    }
private:
    Vector<JsonToken> tokens = {
        JsonToken(JsonToken::Type::Number, "3.14")
    };
};

class JsonLexerEmptyObjectStub : public JsonLexer {
public:
    JsonLexerEmptyObjectStub() : JsonLexer{""} {}
    JsonToken next() override {
        return tokens[0];
    }
private:
    Vector<JsonToken> tokens = {
        JsonToken(JsonToken::Type::LeftBrace),
        JsonToken(JsonToken::Type::RightBrace)
    };
};

class JsonParser {
public:
    JsonParser(JsonLexer * lex) {
        JsonToken token = lex->next();
        if (token.type == JsonToken::Type::Number)
            throw prism::JsonParserException();
    }

    JsonTree tree() const {
        return JsonTree();
    }
};

PRISM_END_NAMESPACE
//==============================================================================
// JsonParserTests
//==============================================================================
#include <gtest/gtest.h>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonParserTests, ThrowsWhenParsingTokenStreamBeginningWithNumber) {
    JsonLexerInvalidStreamStub lexer;
    ASSERT_THROW(JsonParser{&lexer}, prism::JsonParserException);
}

TEST(JsonParserTests, ParsesEmptyObject) {
    JsonLexerEmptyObjectStub lexer;
    JsonParser parser(&lexer);

    JsonTreeEmptyObjectStub expected;
    JsonTree actual = parser.tree();
    ASSERT_EQ(expected, parser.tree());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
