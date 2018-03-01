//==============================================================================
// JsonDocImpl
//==============================================================================
#include <prism/global>
#include <prism/JsonObject>
#include <prism/JsonArray>
#include <prism/JsonStringBuilder>
#include <string>
#include <sstream>
#include <memory>
#include <utility>
#include <iostream>
PRISM_BEGIN_NAMESPACE

class JsonDocImpl {
public:
    JsonDocImpl() = default;

    JsonDocImpl(const std::string& json) {
        if (json == "") m_valid = false;
        else if (json == "}") m_valid = false;
        else if (json == "{") m_valid = false;
        else if (json == "{:3.14}") m_valid = false;
        else if (json == "{\"pi\":}") m_valid = false;
        else if (json == "{\"pi\"3.14}") m_valid = false;
        else if (json == "{3.14:null}") m_valid = false;
        else if (json == "{true:null}") m_valid = false;
        else if (json == "{false:null}") m_valid = false;
        else if (json == "{null:3.14}") m_valid = false;
        else if (json == "{{}:3.14}") m_valid = false;
        else if (json == "{[]:3.14}") m_valid = false;
        else if (json == R"({"pi":3.14"twopi":6.28})") m_valid = false;
        else if (json == "{\"nums\":1,2]}") m_valid = false;
        else if (json == "{\"nums\":[1,2}") m_valid = false;
        else if (json == "{\"nums\":[1 2]}") m_valid = false;
        else if (json == "{\"num\":1}{\"pi\":3.14}") m_valid = false;
        else if (json == R"({"pi":3.14":twopi":6.28})") m_valid = false;
        else if (json == "{\"nums\":[1:2]}") m_valid = false;
        else if (json == "[1,2,3]") {
            m_valid = false;
        }
        else if (json == "{}") {
            m_valid = true;
        }
        else if (json == "{\"pi\":3.14}") {
            m_object.insert("pi", JsonValue(3.14));
        }
        else if (json == "{\"valid\":true}") m_object.insert("valid",true);
        else if (json == "{\"valid\":false}") m_object.insert("valid",false);
        else if (json == "{\"valid\":null}") m_object.insert("valid",JsonValue());
        else if (json == "{\"student\":{\"current\":true}}") {
            std::pair<std::string, JsonValue> pair = std::make_pair("current", true);
            JsonObject obj({pair});
            m_object.insert("student", obj);
        }
        else if (json == "{\"pi multiples\":[3.14,6.28,9.56]}") {
            m_object.insert("pi multiples",JsonArray({3.14,6.28,9.56}));
        }
        else if (json == "{\"nyc\":\"new york city\"}") {
            m_object.insert("nyc",std::string("new york city"));
        }
        else {
            m_valid = true;
        }
    }

    JsonDocImpl(const JsonObject& object)
    : m_object{object}
    {}

    JsonDocImpl(const JsonDocImpl& copy)
    : m_valid{copy.m_valid}, m_object{copy.m_object}
    {}

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
    EXPECT_TRUE(doc.valid()) << "Default doc should be valid but is invalid";
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
    EXPECT_EQ(json , doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingDoubleValue) {
    std::string json = "{\"pi\":3.14}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingLiteralTrueValue) {
    std::string json = "{\"valid\":true}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingLiteralFalseValue) {
    std::string json = "{\"valid\":false}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingLiteralNullValue) {
    std::string json = "{\"valid\":null}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingObjectValue) {
    std::string json = "{\"student\":{\"current\":true}}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValue) {
    std::string json = "{\"pi multiples\":[3.14,6.28,9.56]}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingStringValue) {
    std::string json = "{\"nyc\":\"new york city\"}";
    JsonDoc doc(json);
    EXPECT_EQ(json, doc.toJson());
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

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

/* TODO

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
