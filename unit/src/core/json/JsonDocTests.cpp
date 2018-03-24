#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonDoc>
#include <prismtests/FakeJsonObject>
#include <prismtests/FakeJsonArray>
#include <prismtests/FakeJsonValue>
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
    std::string jsonWithTwoRootObjects = R"({"num":1}{"pi":3.14})";
    JsonDoc doc(jsonWithTwoRootObjects);
    EXPECT_FALSE(doc.valid());
}

TEST(JsonDocTests, WhenParsingStringWithMoreThanOneRootObjectExpectDocToBeEmpty) {
    std::string jsonWithTwoRootObjects = R"({"num":1}{"pi":3.14})";
    JsonDoc doc(jsonWithTwoRootObjects);
    EXPECT_TRUE(doc.empty());
}

TEST(JsonDocTests, WhenParsingStringWithMoreThanOneRootObjectExpectConversionStringToBeEmpty) {
    std::string emptyConversionString = "";
    JsonDoc doc(emptyConversionString);
    EXPECT_EQ(emptyConversionString, doc.toJson());
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

TEST(JsonDocTests, WhenMoveConstructingThenConvertingOriginalDocToJsonExpectStringOfEmptyObject) {
    JsonDoc originalDoc("{\"pi\":3.14}");
    JsonDoc movedToDoc = std::move(originalDoc);
    EXPECT_EQ("{}", originalDoc.toJson());
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

TEST(JsonDocTests, WhenMoveAssigningThenConvertingOriginalDocToJsonExpectStringOfEmptyObject) {
    std::string json = "{\"pi\":3.14}";
    JsonDoc originalDoc(json);
    JsonDoc movedToDoc;
    movedToDoc = std::move(originalDoc);
    EXPECT_EQ("{}", originalDoc.toJson());
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
    std::string jsonWithObjectValueWithMultipleMembers = R"({"employee":{"active":true,"department":"legal","name":"Ken"}})";
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

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValueOfStrings) {
    std::string jsonWithArrayOfStrings = R"({"array":["str1","str2"]})";
    JsonDoc doc(jsonWithArrayOfStrings);
    EXPECT_EQ(jsonWithArrayOfStrings, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValueOfDoubles) {
    std::string jsonWithArrayOfDoubles = R"({"array":[3.14,6.28]})";
    JsonDoc doc(jsonWithArrayOfDoubles);
    EXPECT_EQ(jsonWithArrayOfDoubles, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValueOfBools) {
    std::string jsonWithArrayOfBools = R"({"array":[true,false]})";
    JsonDoc doc(jsonWithArrayOfBools);
    EXPECT_EQ(jsonWithArrayOfBools, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValueOfNulls) {
    std::string jsonWithArrayOfNulls = R"({"array":[null,null]})";
    JsonDoc doc(jsonWithArrayOfNulls);
    EXPECT_EQ(jsonWithArrayOfNulls, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValueOfArrays) {
    std::string jsonWithArrayOfArrays = R"({"array":[[],[]]})";
    JsonDoc doc(jsonWithArrayOfArrays);
    EXPECT_EQ(jsonWithArrayOfArrays, doc.toJson());
}

TEST(JsonDocTests,
WhenInitializingDocWithStringThenConvertingDocToJsonExpectStringContainingArrayValueOfObjects) {
    std::string jsonWithArrayOfObjects = R"({"array":[{},{}]})";
    JsonDoc doc(jsonWithArrayOfObjects);
    EXPECT_EQ(jsonWithArrayOfObjects, doc.toJson());
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
