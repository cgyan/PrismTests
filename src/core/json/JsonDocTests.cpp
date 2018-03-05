//==============================================================================
// JsonDocImpl
//==============================================================================
#include <prism/global>
#include <prism/JsonObject>
#include <prism/JsonArray>
#include <prism/JsonToken>
#include <prism/JsonStringBuilder>
#include <prism/JsonLexer>
#include <prism/JsonLexerException>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <iostream>

PRISM_BEGIN_NAMESPACE

class JsonParserException : public Exception {
public:
    JsonParserException(const std::string& msg)
    : Exception{msg}
    {}
};

enum class JsonSymbol {
    // non-terminal symbols
    NT_S,
    NT_T,
    NT_M,
    NT_P,
    NT_Q,
    NT_V,
    NT_R,
    NT_E,
    NT_F,
    // terminal symbols
    T_LeftBrace,
    T_RightBrace,
    T_LeftBracket,
    T_RightBracket,
    T_String,
    T_Colon,
    T_Comma,
    T_Number,
    T_Bool,
    T_Null
};

const bool equivalent(JsonSymbol symbol, JsonToken::Type type) {
    if (symbol == JsonSymbol::T_LeftBrace && type == JsonToken::Type::LeftBrace) return true;
    else if (symbol == JsonSymbol::T_RightBrace && type == JsonToken::Type::RightBrace) return true;
    else if (symbol == JsonSymbol::T_String && type == JsonToken::Type::String) return true;
    else if (symbol == JsonSymbol::T_Colon && type == JsonToken::Type::Colon) return true;
    else if (symbol == JsonSymbol::T_Comma && type == JsonToken::Type::Comma) return true;
    else if (symbol == JsonSymbol::T_Number && type == JsonToken::Type::Number) return true;
    else if (symbol == JsonSymbol::T_Bool && type == JsonToken::Type::BoolLiteral) return true;
    else if (symbol == JsonSymbol::T_Null && type == JsonToken::Type::NullLiteral) return true;
    else if (symbol == JsonSymbol::T_LeftBracket && type == JsonToken::Type::LeftBracket) return true;
    else if (symbol == JsonSymbol::T_RightBracket && type == JsonToken::Type::RightBracket) return true;
    return false;
}

class JsonDocImpl {
public:
    JsonDocImpl() = default;

    JsonDocImpl(const std::string& json) {
        try {
            parseJson(json);
        }
        catch (const JsonParserException& ex) {
            m_valid = false;
        }
    }

    JsonDocImpl(const JsonObject& object)
    : m_object{object}
    {}

    JsonDocImpl(const JsonDocImpl& copy)
    : m_valid{copy.m_valid}, m_object{copy.m_object}
    {}

    void parseJson(const std::string& json) {
        using SymbolStack = std::stack<JsonSymbol, std::vector<JsonSymbol>>;
        SymbolStack ss;
        ss.push(JsonSymbol::NT_S);

        using ObjectStack = std::stack<JsonObject, std::vector<JsonObject>>;
        ObjectStack objectStack;

        using KeyStack = std::stack<std::string, std::vector<std::string>>;
        KeyStack keyStack;

        using ArrayStack = std::stack<JsonArray, std::vector<JsonArray>>;
        ArrayStack arrayStack;

        using ParseTable = std::map<JsonSymbol, std::map<JsonToken::Type, int>>;
        ParseTable table;
        table[JsonSymbol::NT_S][JsonToken::Type::LeftBrace] = 1;
        table[JsonSymbol::NT_T][JsonToken::Type::RightBrace] = 2;
        table[JsonSymbol::NT_T][JsonToken::Type::String] = 3;
        table[JsonSymbol::NT_M][JsonToken::Type::String] = 4;
        table[JsonSymbol::NT_P][JsonToken::Type::String] = 5;
        table[JsonSymbol::NT_V][JsonToken::Type::Number] = 6;
        table[JsonSymbol::NT_Q][JsonToken::Type::RightBrace] = 7; // duplicate of case 2
        table[JsonSymbol::NT_V][JsonToken::Type::BoolLiteral] = 8;
        table[JsonSymbol::NT_V][JsonToken::Type::NullLiteral] = 9;
        table[JsonSymbol::NT_V][JsonToken::Type::String] = 10;
        table[JsonSymbol::NT_V][JsonToken::Type::LeftBracket] = 11;
        table[JsonSymbol::NT_R][JsonToken::Type::LeftBracket] = 12;
        table[JsonSymbol::NT_E][JsonToken::Type::Number] = 13;
        table[JsonSymbol::NT_F][JsonToken::Type::RightBracket] = 14; // duplicate of case 2
        table[JsonSymbol::NT_Q][JsonToken::Type::RightBracket] = 15; // duplicate of case 2
        table[JsonSymbol::NT_E][JsonToken::Type::RightBracket] = 16; // duplicate of case 2
        table[JsonSymbol::NT_F][JsonToken::Type::Comma] = 17;
        table[JsonSymbol::NT_V][JsonToken::Type::LeftBrace] = 18;
        table[JsonSymbol::NT_Q][JsonToken::Type::Comma] = 19;
        table[JsonSymbol::NT_E][JsonToken::Type::String] = 20; // duplicate of case 13
        table[JsonSymbol::NT_E][JsonToken::Type::LeftBracket] = 21; // duplicate of case 13

        JsonLexer lexer(json);
        JsonToken token = lexer.getNextToken();

        int currentTokenIndex = 1;

        while (!ss.empty()) {
            if (equivalent(ss.top(), token.type)) {
                ss.pop();
                token = lexer.getNextToken();
                ++currentTokenIndex;
            }
            else {
                switch(table[ss.top()][token.type]) {
                    case 1: // S => {T}
                    {// std::cout << "Rule 1" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::T_RightBrace);
                        ss.push(JsonSymbol::NT_T);
                        ss.push(JsonSymbol::T_LeftBrace);
                        break;
                    }
                    case 2: // remove T
                    {// std::cout << "Rule 2" << std::endl;
                        ss.pop();
                        break;
                    }
                    case 3: // T => M
                    {// std::cout << "Rule 3" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::NT_M);
                        break;
                    }
                    case 4: // M => PQ
                    {// std::cout << "Rule 4" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::NT_Q);
                        ss.push(JsonSymbol::NT_P);
                        break;
                    }
                    case 5: // P => String:V
                    {// std::cout << "Rule 5" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::NT_V);
                        ss.push(JsonSymbol::T_Colon);
                        ss.push(JsonSymbol::T_String);
                        break;
                    }
                    case 6: // V => Number
                    // std::cout << "Rule 6" << std::endl;
                    {   ss.pop();
                        ss.push(JsonSymbol::T_Number);
                        break;
                    }
                    case 7: // remove Q
                    {// std::cout << "Rule 7" << std::endl;
                        ss.pop();
                        break;
                    }
                    case 8: // V => Bool
                    {// std::cout << "Rule 8" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::T_Bool);
                        break;
                    }
                    case 9: // V => Null
                    {// std::cout << "Rule 9" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::T_Null);
                        break;
                    }
                    case 10: // V => String
                    {// std::cout << "Rule 10" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::T_String);
                        break;
                    }
                    case 11: // V => R
                    {// std::cout << "Rule 11" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::NT_R);
                        break;
                    }
                    case 12: // R => [E]
                    {// std::cout << "Rule 12" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::T_RightBracket);
                        ss.push(JsonSymbol::NT_E);
                        ss.push(JsonSymbol::T_LeftBracket);
                        break;
                    }
                    case 13: // E => VF
                    {// std::cout << "Rule 13" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::NT_F);
                        ss.push(JsonSymbol::NT_V);
                        break;
                    }
                    case 14: // remove F
                    {// std::cout << "Rule 14" << std::endl;
                        ss.pop();
                        break;
                    }
                    case 15: // remove Q
                    {// std::cout << "Rule 15" << std::endl;
                        ss.pop();
                        break;
                    }
                    case 16: // remove E
                    {// std::cout << "Rule 16" << std::endl;
                        ss.pop();
                        break;
                    }
                    case 17: // F => ,E
                    {// std::cout << "Rule 17" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::NT_E);
                        ss.push(JsonSymbol::T_Comma);
                        break;
                    }
                    case 18: // V => S
                    {// std::cout << "Rule 18" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::NT_S);
                        break;
                    }
                    case 19: // Q => ,M
                    {// std::cout << "Rule 19" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::NT_M);
                        ss.push(JsonSymbol::T_Comma);
                        break;
                    }
                    case 20: // E => VF
                    {// std::cout << "Rule 20" << std::endl;
                        ss.pop();
                        ss.push(JsonSymbol::NT_F);
                        ss.push(JsonSymbol::NT_V);
                        break;
                    }
                    case 21: // E => VF
                    {
                        ss.pop();
                        ss.push(JsonSymbol::NT_F);
                        ss.push(JsonSymbol::NT_V);
                        break;
                    }
                    default:
                    {
                        std::stringstream ss;
                        ss << "Parser error at token " << currentTokenIndex;
                        throw JsonParserException(ss.str());
                    }
                }
            }
        }

        // JsonObject obj = objectStack.top().toObject();
        // objectStack.pop();
        // m_object = obj;
    }

    const bool docIsEmpty() const {
        return m_object.empty();
    }

    const bool docIsValid() const {
        return m_valid;
    }

    const std::string invalidDocToString() const {
        return std::string("");
    }

    const std::string convertDocToJson() const {
        if (docIsValid()) {
            JsonStringBuilder sb;
            sb.appendObject(m_object);
            return sb.toString();
        }
        return invalidDocToString();
    }

    JsonObject object() const {
        return m_object;
    }

    const bool operator==(const JsonDocImpl& rhs) const {
        if (m_valid == rhs.m_valid && m_object == rhs.m_object) {
            return true;
        }
        else return false;
    }
private:
    bool m_valid{true};
    JsonObject m_object{};
};
//==============================================================================
// JsonDoc
//==============================================================================
class JsonDoc {
public:
    JsonDoc();
    JsonDoc(const std::string& json);
    JsonDoc(const JsonObject& object);
    JsonDoc(const JsonDoc& copy);
    JsonDoc(JsonDoc&& rhs);
    JsonDoc& operator=(const JsonDoc& rhs);
    JsonDoc& operator=(JsonDoc&& rhs);
    ~JsonDoc();

    const bool valid() const;
    const bool empty() const;
    const std::string toJson() const;
    void swap(JsonDoc& other);
    void clear();
    JsonObject object() const;
private:
    friend const bool operator==(const JsonDoc& lhs, const JsonDoc& rhs);
    friend const bool operator!=(const JsonDoc& lhs, const JsonDoc& rhs);
private:
    std::shared_ptr<JsonDocImpl> m_impl;
};

JsonDoc::JsonDoc()
: m_impl{new JsonDocImpl}
{}

JsonDoc::JsonDoc(const std::string& json)
: m_impl{new JsonDocImpl(json)}
{}

JsonDoc::JsonDoc(const JsonObject& object)
: m_impl{new JsonDocImpl(object)}
{}

JsonDoc::JsonDoc(const JsonDoc& copy)
: m_impl{new JsonDocImpl(*copy.m_impl)}
{}

JsonDoc::JsonDoc(JsonDoc&& rhs)
: m_impl{new JsonDocImpl(*rhs.m_impl)}
{
    rhs.clear();
}

JsonDoc&
JsonDoc::operator=(const JsonDoc& rhs) {
    m_impl.reset(new JsonDocImpl(*rhs.m_impl));
    return *this;
}

JsonDoc&
JsonDoc::operator=(JsonDoc&& rhs) {
    *this = rhs;
    rhs.clear();
    return *this;
}

JsonDoc::~JsonDoc()
{}

const bool
JsonDoc::valid() const {
    return m_impl->docIsValid();
}

const bool
JsonDoc::empty() const {
    return m_impl->docIsEmpty();
}

const std::string
JsonDoc::toJson() const {
    return m_impl->convertDocToJson();
}

void
JsonDoc::swap(JsonDoc& other) {
    std::swap(this->m_impl, other.m_impl);
}

void
JsonDoc::clear() {
    m_impl.reset(new JsonDocImpl);
}

JsonObject
JsonDoc::object() const {
    return m_impl->object();
}

const bool
operator==(const JsonDoc& lhs, const JsonDoc& rhs) {
    return *(lhs.m_impl) == *(rhs.m_impl);
}

const bool
operator!=(const JsonDoc& lhs, const JsonDoc& rhs) {
    return !(lhs == rhs);
}

std::ostream&
operator<<(std::ostream& out, const JsonDoc& doc) {
    out << doc.toJson();
    return out;
}

// if (json == "") m_valid = false;
// else if (json == "}") m_valid = false;
// else if (json == "{") m_valid = false;
// else if (json == "{:3.14}") m_valid = false;
// else if (json == "{\"pi\":}") m_valid = false;
// else if (json == "{\"pi\"3.14}") m_valid = false;
// else if (json == "{3.14:null}") m_valid = false;
// else if (json == "{true:null}") m_valid = false;
// else if (json == "{false:null}") m_valid = false;
// else if (json == "{null:3.14}") m_valid = false;
// else if (json == "{{}:3.14}") m_valid = false;
// else if (json == "{[]:3.14}") m_valid = false;
// else if (json == R"({"pi":3.14"twopi":6.28})") m_valid = false;
// else if (json == "{\"nums\":1,2]}") m_valid = false;
// else if (json == "{\"nums\":[1,2}") m_valid = false;
// else if (json == "{\"nums\":[1 2]}") m_valid = false;
// else if (json == "{\"num\":1}{\"pi\":3.14}") m_valid = false;
// else if (json == R"({"pi":3.14":twopi":6.28})") m_valid = false;
// else if (json == "{\"nums\":[1:2]}") m_valid = false;
// else if (json == "[1,2,3]") {
//     m_valid = false;
// }
// else if (json == "{}") {
//     m_valid = true;
// }
// else if (json == "{\"pi\":3.14}") {
//     m_object.insert("pi", JsonValue(3.14));
// }
// else if (json == "{\"valid\":true}") m_object.insert("valid",true);
// else if (json == "{\"valid\":false}") m_object.insert("valid",false);
// else if (json == "{\"valid\":null}") m_object.insert("valid",JsonValue());
// else if (json == "{\"student\":{\"current\":true}}") {
//     std::pair<std::string, JsonValue> pair = std::make_pair("current", true);
//     JsonObject obj({pair});
//     m_object.insert("student", obj);
// }
// else if (json == "{\"pi multiples\":[3.14,6.28,9.56]}") {
//     m_object.insert("pi multiples",JsonArray({3.14,6.28,9.56}));
// }
// else if (json == "{\"nyc\":\"new york city\"}") {
//     m_object.insert("nyc",std::string("new york city"));
// }
// else {
//     m_valid = true;
// }

// Rule 1
// Rule 3
// Rule 4
// Rule 5
// Rule 8
// Rule 9

/*
    Q}
    token = }
*/

PRISM_END_NAMESPACE
//==============================================================================
// JsonDocTests
//==============================================================================
#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FakeJsonObject>
#include <prism/FakeJsonArray>
#include <prism/FakeJsonValue>
#include <string>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonDocTests, WhenDefaultDocIsCreatedExpectItToBeValid) {
    JsonDoc doc;
    EXPECT_TRUE(doc.valid());
}

TEST(JsonDocTests, WhenDefaultDocIsCreatedExpectDocToBeEmpty) {
    JsonDoc doc;
    EXPECT_TRUE(doc.empty());
}

TEST(JsonDocTests, WhenConvertingDefaultDocToJsonExpectStringOfEmptyObject) {
    JsonDoc doc;
    EXPECT_EQ("{}", doc.toJson());
}

TEST(JsonDocTests, WhenDocIsInvalidExpectConversionStringToBeEmpty) {
    std::string invalidJson = "[1,2,3]";
    std::string expectedConversionString = "";
    JsonDoc doc(invalidJson);
    EXPECT_FALSE(doc.valid());
    EXPECT_EQ(expectedConversionString, doc.toJson());
}

TEST(JsonDocTests, WhenDocIsInitializedWithEmptyStringExpectDocToBeInvalid) {
    std::string emptyString = "";
    JsonDoc doc(emptyString);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenDocIsInitializedWithEmptyObjectStringExpectDocToBeEmpty) {
    std::string emptyObjectJson = "{}";
    JsonDoc doc(emptyObjectJson);
    EXPECT_TRUE(doc.empty());
}

TEST(JsonDocTests, WhenDocIsInitializedWithNonEmptyObjectStringExpectDocToBeNotEmpty) {
    std::string jsonWithSingleMember = "{\"pi\":3.14}";
    JsonDoc doc(jsonWithSingleMember);
    EXPECT_FALSE(doc.empty());
}

TEST(JsonDocTests, WhenStringObjectIsMissingLeftBraceExpectDocToBeInvalid) {
    std::string jsonWithMissingLeftBrace = "}";
    JsonDoc doc(jsonWithMissingLeftBrace);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringIsMissingRightBraceExpectDocToBeInvalid) {
    std::string jsonWithMissingRightBrace = "{";
    JsonDoc doc(jsonWithMissingRightBrace);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringIsMissingKeyNameExpectDocToBeInvalid) {
    std::string jsonWithMissingKeyName = "{:3.14}";
    JsonDoc doc(jsonWithMissingKeyName);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringIsMissingValueExpectDocToBeInvalid) {
    std::string jsonWithMissingValue = R"({"pi":})";
    JsonDoc doc(jsonWithMissingValue);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringIsMissingColonBetweenKeyAndValueExpectDocToBeInvalid) {
    std::string jsonWithMissingColonBetweenKeyAndValue = R"({"pi"3.14})";
    JsonDoc doc(jsonWithMissingColonBetweenKeyAndValue);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringHasDoubleTypeAsKeyExpectDocToBeInvalid) {
    std::string jsonWithDoubleAsKey = "{3.14:null}";
    JsonDoc doc(jsonWithDoubleAsKey);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringHasLiteralTrueAsKeyExpectDocToBeInvalid) {
    std::string jsonWithBoolAsKey = "{true:null}";
    JsonDoc doc(jsonWithBoolAsKey);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringHasLiteralFalseAsKeyExpectDocToBeInvalid) {
    std::string jsonWithBoolAsKey = "{false:null}";
    JsonDoc doc(jsonWithBoolAsKey);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringHasLiteralNullAsKeyExpectDocToBeInvalid) {
    std::string jsonWithNullAsKey = "{null:3.14}";
    JsonDoc doc(jsonWithNullAsKey);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringHasObjectAsKeyExpectDocToBeInvalid) {
    std::string jsonWithObjectAsKey = "{{}:3.14}";
    JsonDoc doc(jsonWithObjectAsKey);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringHasArrayAsKeyExpectDocToBeInvalid) {
    std::string jsonWithArrayAsKey = "{[]:3.14}";
    JsonDoc doc(jsonWithArrayAsKey);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringIsMissingCommaBetweenMembersExpectDocToBeInvalid) {
    std::string jsonWithMissingCommaBetweenObjectMembers = R"({"pi":3.14"twopi":6.28})";
    JsonDoc doc(jsonWithMissingCommaBetweenObjectMembers);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenJsonStringDoesNotUseCommaBetweenMembersExpectDocToBeInvalid) {
    std::string jsonWithInvalidColonBetweenObjectMembers = R"({"pi":3.14":twopi":6.28})";
    JsonDoc doc(jsonWithInvalidColonBetweenObjectMembers);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenArrayInJsonStringIsMissingLeftBracketExpectDocToBeInvalid) {
    std::string jsonWithArrayMissingLeftBracket = "{\"nums\":1,2]}";
    JsonDoc doc(jsonWithArrayMissingLeftBracket);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenArrayInJsonStringIsMissingRightBracketExpectDocToBeInvalid) {
    std::string jsonWithArrayMissingRightBracket = "{\"nums\":[1,2}";
    JsonDoc doc(jsonWithArrayMissingRightBracket);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenArrayInJsonStringIsMissingCommaBetweenValuesExpectDocToBeInvalid) {
    std::string jsonWithArrayMissingComma = "{\"nums\":[1 2]}";
    JsonDoc doc(jsonWithArrayMissingComma);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenArrayInJsonStringDoesNotUseCommaBetweenValuesExpectDocToBeInvalid) {
    std::string jsonWithInvalidColonBetweenArrayValues = "{\"nums\":[1:2]}";
    JsonDoc doc(jsonWithInvalidColonBetweenArrayValues);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenParsingStringWithMoreThanOneRootObjectExpectDocToBeInvalid) {
    std::string jsonWithTwoRootObjects = "{\"num\":1}{\"pi\":3.14}";
    JsonDoc doc(jsonWithTwoRootObjects);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenSwappingTwoDocsExpectTheContentsOfEachDocToTransferToTheOtherDoc) {
    JsonDoc doc1("{}");
    JsonDoc doc2("{\"pi\":3.14}");
    doc1.swap(doc2);
    EXPECT_EQ(JsonDoc("{\"pi\":3.14}"), doc1);
    EXPECT_EQ(JsonDoc("{}"), doc2);
}

TEST(JsonDocTests, WhenResettingDocExpectDocToBeEmpty) {
    JsonDoc doc("{\"pi\":3.14}");
    doc.clear();
    EXPECT_TRUE(doc.empty());
}

TEST(JsonDocTests, WhenResettingDocExpectDocToBeValid) {
    JsonDoc doc("{\"pi\":3.14}");
    doc.clear();
    EXPECT_TRUE(doc.valid());
}

TEST(JsonDocTests, WhenConvertingResetDocToJsonExpectStringOfEmptyObject) {
    JsonDoc doc("{\"pi\":3.14}");
    doc.clear();
    EXPECT_EQ("{}", doc.toJson());
}

TEST(JsonDocTests, WhenModifyingCopyOfDocExpectOriginalDocToRetainState) {
    std::string json = "{\"pi\":3.14}";
    JsonDoc originalDoc(json);
    JsonDoc copyOfDoc = originalDoc;
    copyOfDoc.clear();
    EXPECT_NE(originalDoc, copyOfDoc);
}

TEST(JsonDocTests, WhenCreatingCopyOfDocExpectBothDocsToContainSameState) {
    std::string json = "{\"pi\":3.14}";
    JsonDoc originalDoc(json);
    JsonDoc copyOfDoc = originalDoc;
    EXPECT_EQ(originalDoc, copyOfDoc);
}

TEST(JsonDocTests, WhenModifyingCopyAssignedDocExpectOriginalDocToRetainState) {
    std::string json = "{\"pi\":3.14}";
    JsonDoc doc1{json};
    JsonDoc doc2;
    doc2 = doc1;
    doc2.clear();
    EXPECT_NE(doc1, doc2);
}

TEST(JsonDocTests, WhenCopyAssigningExpectBothDocsToContainSameState) {
    std::string json = "{\"pi\":3.14}";
    JsonDoc thisDoc;
    JsonDoc otherDoc(json);
    thisDoc = otherDoc;
    EXPECT_EQ(thisDoc, otherDoc);
}

TEST(JsonDocTests, WhenMoveConstructingExpectOriginalDocToBeEmptyAfterwards) {
    JsonDoc originalDoc("{\"pi\":3.14}");
    JsonDoc movedToDoc(std::move(originalDoc));
    EXPECT_TRUE(originalDoc.empty());
}

TEST(JsonDocTests, WhenMoveConstructingExpectOriginalDocToBeValidAfterwards) {
    JsonDoc originalDoc("{\"pi\":3.14}");
    JsonDoc movedToDoc(std::move(originalDoc));
    EXPECT_TRUE(originalDoc.valid());
}

TEST(JsonDocTests, WhenMoveConstructingExpectStateOfOriginalDocToMoveToNewDoc) {
    std::string json = "{\"pi\":3.14}";
    JsonDoc originalDoc(json);
    JsonDoc movedToDoc(std::move(originalDoc));
    EXPECT_EQ(JsonDoc(json), movedToDoc);
}

TEST(JsonDocTests, WhenMoveAssigningExpectOriginalDocToBeEmptyAfterwards) {
    JsonDoc originalDoc("{\"pi\":3.14}");
    JsonDoc movedToDoc;
    movedToDoc = std::move(originalDoc);
    EXPECT_TRUE(originalDoc.empty());
}

TEST(JsonDocTests, WhenMoveAssigningExpectOriginalDocToBeValidAfterwards) {
    JsonDoc originalDoc("{\"pi\":3.14}");
    JsonDoc movedToDoc;
    movedToDoc = std::move(originalDoc);
    EXPECT_TRUE(originalDoc.valid());
}

TEST(JsonDocTests, WhenMoveAssigningExpectStateOfOriginalDocToMoveToNewDoc) {
    std::string json = "{\"pi\":3.14}";
    JsonDoc originalDoc(json);
    JsonDoc movedToDoc;
    movedToDoc = std::move(originalDoc);
    EXPECT_EQ(JsonDoc(json), movedToDoc);
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingEmptyObject) {
    std::string json = "{}";
    JsonDoc doc(json);
    EXPECT_EQ(json , doc.toJson())
        << "Returned string should contain an empty object - {}";
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingDoubleValue) {
    std::string json = "{\"pi\":3.14}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson())
        << "--------> Returned string should contain a member with a double value <--------";
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingLiteralTrueValue) {
    std::string json = "{\"valid\":true}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson())
        << "Returned string should contain a member with a value of true";
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingLiteralFalseValue) {
    std::string json = "{\"valid\":false}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson())
        << "Returned string should contain a member with a value of false";
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingLiteralNullValue) {
    std::string json = "{\"valid\":null}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson())
        << "Returned string should contain a member with a value of null";
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingStringValue) {
    std::string json = "{\"nyc\":\"new york city\"}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingObjectValueWithNoMembers) {
    std::string jsonWithObjectValueWithNoMembers = "{\"key\":{}}";
    JsonDoc doc(jsonWithObjectValueWithNoMembers);
    EXPECT_EQ(jsonWithObjectValueWithNoMembers, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingObjectValueWithOneMember) {
    std::string jsonWithObjectValueWithOneMember = "{\"employee\":{\"name\":\"Bob\"}}";
    JsonDoc doc(jsonWithObjectValueWithOneMember);
    EXPECT_EQ(jsonWithObjectValueWithOneMember, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingObjectValueWithMultipleMembers) {
    std::string jsonWithObjectValueWithMultipleMembers = "{\"employee\":{\"name\":\"Bob\",\"aardvark\":\"ken\",\"department\":\"legal\"}}";
    JsonDoc doc(jsonWithObjectValueWithMultipleMembers);
    EXPECT_EQ(jsonWithObjectValueWithMultipleMembers, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValueWithNoElements) {
    std::string jsonWithArrayValue = "{\"empty array\":[]}";
    JsonDoc doc(jsonWithArrayValue);
    EXPECT_EQ(jsonWithArrayValue, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValueWithOneElement) {
    std::string jsonWithArrayValue = "{\"nums\":[3.14]}";
    JsonDoc doc(jsonWithArrayValue);
    EXPECT_EQ(jsonWithArrayValue, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValueWithMultipleElements) {
    std::string jsonWithArrayValue = "{\"pi multiples\":[3.14,6.28]}";
    JsonDoc doc(jsonWithArrayValue);
    EXPECT_EQ(jsonWithArrayValue, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValueWithStringNumberBoolNullObjectAndArrayElements) {
    std::string jsonWithEveryValueType = R"({"array":["string",[],3.14,{},true,null]})";
    JsonDoc doc(jsonWithEveryValueType);
    EXPECT_EQ(jsonWithEveryValueType, doc.toJson());
}

TEST(JsonDocTests, WhenInitializingDocWithEmptyObjectExpectDocToBeValid) {
    JsonObject fakeObject = make_fake_json_object();
    JsonDoc doc(fakeObject);
    EXPECT_TRUE(doc.valid());
}

TEST(JsonDocTests, WhenInitializingDocWithEmptyObjectExpectDocToBeEmpty) {
    JsonObject fakeObject = make_fake_json_object();
    JsonDoc doc(fakeObject);
    EXPECT_TRUE(doc.empty());
}

TEST(JsonDocTests, WhenInitializingDocWithNonEmptyObjectExpectDocToBeNotEmpty) {
    JsonObject fakeObject = make_fake_json_object("pi", 3.14);
    JsonDoc doc(fakeObject);
    EXPECT_FALSE(doc.empty());
}

TEST(JsonDocTests, WhenInitializingDocWithEmptyObjectThenConvertingDocToJsonExpectEmptyObjectString) {
    JsonObject emptyFakeObject = make_fake_json_object();
    JsonDoc doc(emptyFakeObject);
    EXPECT_EQ("{}", doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithObjectThenConvertingDocToJsonExpectStringContainingDoubleValue) {
    JsonObject fakeObjectWithDoubleValue = make_fake_json_object("pi", 3.14);
    JsonDoc doc(fakeObjectWithDoubleValue);
    std::string expected = "{\"pi\":3.14}";
    EXPECT_EQ(expected, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithObjectThenConvertingDocToJsonExpectStringContainingLiteralTrueValue) {
    JsonObject fakeObjectWithTrueValue = make_fake_json_object("valid", true);
    JsonDoc doc(fakeObjectWithTrueValue);
    std::string expected = "{\"valid\":true}";
    EXPECT_EQ(expected, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithObjectThenConvertingDocToJsonExpectStringContainingLiteralFalseValue) {
    JsonObject fakeObjectWithFalseValue = make_fake_json_object("valid", false);
    JsonDoc doc(fakeObjectWithFalseValue);
    std::string expected = "{\"valid\":false}";
    EXPECT_EQ(expected, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithObjectThenConvertingDocToJsonExpectStringContainingLiteralNullValue) {
    JsonValue nullValue = make_fake_json_value();
    JsonObject fakeObjectWithNullValue = make_fake_json_object("valid", nullValue);
    JsonDoc doc(fakeObjectWithNullValue);
    std::string expected = "{\"valid\":null}";
    EXPECT_EQ(expected, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithObjectThenConvertingDocToJsonExpectStringContainingStringValue) {
    JsonObject fakeObjectWithStringValue = make_fake_json_object("nyc", "new york city");
    JsonDoc doc(fakeObjectWithStringValue);
    EXPECT_EQ("{\"nyc\":\"new york city\"}", doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithObjectThenConvertingDocToJsonExpectStringContainingArrayValue) {
    JsonValue fakeArrayValue = make_fake_json_array({3.14,6.28,9.56});
    JsonObject fakeObjectWithArrayValue = make_fake_json_object("pi multiples", fakeArrayValue);
    JsonDoc doc(fakeObjectWithArrayValue);
    std::string expected = R"({"pi multiples":[3.14,6.28,9.56]})";
    EXPECT_EQ(expected, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithObjectThenConvertingDocToJsonExpectStringContainingObjectValue) {
    JsonObject fakeObjectValue = make_fake_json_object("nyc", "new york city");
    JsonObject fakeObjectWithObjectValue = make_fake_json_object("cities", fakeObjectValue);
    JsonDoc doc(fakeObjectWithObjectValue);
    std::string expected = R"({"cities":{"nyc":"new york city"}})";
    EXPECT_EQ(expected, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithObjectThenConvertingDocToJsonExpectStringContainingCommaSeperatingMembers) {
    JsonObject fakeObj = make_fake_json_object();
    fakeObj.insert("jfk", "john f kennedy");
    fakeObj.insert("lhr", "london heathrow");
    JsonDoc doc(fakeObj);
    std::string expected = R"({"jfk":"john f kennedy","lhr":"london heathrow"})";
    EXPECT_EQ(expected, doc.toJson());
}

TEST(JsonDocTests, WhenInitializingDocWithInvalidStringExpectReturnedObjectToBeEmpty) {
    std::string invalidJson = "";
    JsonDoc doc(invalidJson);
    JsonObject emptyObject;
    EXPECT_EQ(emptyObject, doc.object());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

/*
    {}
    {"pi",3.14}
    {"key": ["string", [], 3.14, {}, true, null]}
                        _
    ]F]Q}

    obj         key         arr         arr
    rootObj     root        arr         obj
    ======      ======      ======      =======
    object      key         array       value
    ======      ======      ======      =======


*/

/* TODO

Error handling messages

WhenMoveConstructingThenConvertingOriginalDocToJsonExpectStringOfEmptyObject
WhenMoveAssigningThenConvertingOriginalDocToJsonExpectStringOfEmptyObject
WhenInitializingDocWithStringExpectReturnedObjectToBeEmpty
WhenInitializingDocWithStringExpectReturnedObjectToContainOneMemberWithDoubleValue
WhenInitializingDocWithStringExpectReturnedObjectToContainOneMemberWithStringValue
WhenInitializingDocWithStringExpectReturnedObjectToContainOneMemberWithLiteralTrueValue
WhenInitializingDocWithStringExpectReturnedObjectToContainOneMemberWithLiteralFalseValue
WhenInitializingDocWithStringExpectReturnedObjectToContainOneMemberWithLiteralNullValue
WhenInitializingDocWithStringExpectReturnedObjectToContainOneMemberWithObjectValue
WhenInitializingDocWithStringExpectReturnedObjectToContainOneMemberWithArrayValue

WhenConvertingDocToJsonWhenInitializedWithEmptyJsonObjectExpectEmptyObjectString
WhenDocInitializedWithJsonReturnsObjectExpectItToContainOneMemberWithDoubleValue
WhenDocInitializedWithJsonReturnsObjectExpectItToContainOneMemberWithLiteralTrueValue
WhenDocInitializedWithJsonReturnsObjectExpectItToContainOneMemberWithLiteralFalseValue
WhenDocInitializedWithJsonReturnsObjectExpectItToContainOneMemberWithLiteralNullValue

//------------

WhenDocIsCreatedWithNonEmptyObjectArgumentExpectDocToBeNotEmpty

WhenDocIsInitializedWithEmptyJsonObjectExpectDocToBeEmpty
WhenDocIsInitializedWithEmptyJsonObjectExpectDocToBeValid
WhenConvertingDocToJsonWhenInitializedWithEmptyJsonObjectExpectEmptyObjectString
WhenConvertingDocToJsonWhenInitializedWithEmptyJsonObjectExpectEmptyObjectString
WhenDocInitializedWithJsonReturnsObjectExpectItToContainOneMemberWithDoubleValue
WhenDocInitializedWithJsonReturnsObjectExpectItToContainOneMemberWithLiteralTrueValue
WhenDocInitializedWithJsonReturnsObjectExpectItToContainOneMemberWithLiteralFalseValue
WhenDocInitializedWithJsonReturnsObjectExpectItToContainOneMemberWithLiteralNullValue

DocIsNotValidWhenParsingStringWithNestedObjectMissingLeftBrace
DocIsNotValidWhenParsingStringWithNestedObjectMissingRightBrace
DocIsNotValidWhenParsingStringWithNestedObjectMissingKeyName
DocIsNotValidWhenParsingStringWithNestedObjectMissingValue
WhenParsingStringWithNestedObjectMissingColonBetweenKeyAndValueExpectDocToBeInvalid
WhenParsingStringWithNestedObjectNotUsingColonAsKeyValueSeperatorExpectDocToBeInvalid
DocIsNotValidWhenParsingStringWithNestedObjectUsingDoubleTypeAsKey
DocIsNotValidWhenParsingStringWithNestedObjectUsingLiteralTrueAsKey
DocIsNotValidWhenParsingStringWithNestedObjectUsingLiteralFalseAsKey
DocIsNotValidWhenParsingStringWithNestedObjectUsingLiteralNullAsKey
DocIsNotValidWhenParsingStringWithNestedObjectUsingObjectTypeAsKey
DocIsNotValidWhenParsingStringWithNestedObjectUsingArrayTypeAsKey
DocIsNotValidWhenParsingStringWithNestedObjectMissingCommaBetweenMembers

*/
