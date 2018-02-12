#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/JsonDoc>
#include <prism/JsonObjectStub>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonDocTests, DefaultDocisValid) {
    JsonDoc doc;
    ASSERT_TRUE(doc.isValid());
}

TEST(JsonDocTests, DocInitializedWithObjectIsValid) {
    JsonObjectStub stub;
    JsonDoc doc(stub);
    ASSERT_TRUE(doc.isValid());
}

TEST(JsonDocTests, DocInitializedFromIncorrectJsonisInvalid) {
    std::string invalidJson = "{ 1 # false }";
    JsonDoc doc(invalidJson);
    ASSERT_FALSE(doc.isValid());
}

TEST(JsonDocTests, DocInitializedFromValidJsonStringIsValid) {
    std::string validJson = R"({ "key1" : "value1" })";
    JsonDoc doc(validJson);
    ASSERT_TRUE(doc.isValid());
}

TEST(JsonDocTests, DefaultDocConvertedToJsonOutputsEmptyObject) {
    JsonDoc doc;
    std::string expected = "{}";
    ASSERT_EQ(expected, doc.toJson());
}

TEST(JsonDocTests, DocInitializedWithObjectOutputsObjectConvertedToJson) {
    JsonObjectStub stub;
    stub.json = R"({ "city" : "nyc" })";
    JsonDoc doc = JsonDoc::fromObject(stub);
    ASSERT_EQ(stub.json, doc.toJson());
}

TEST(JsonDocTests, DocInitializedWithObjectContainingArrayOutputsRootObjectConvertedToJson) {
    JsonObjectStub stub;
    stub.json = R"({
        "cities" : [
            "nyc",
            "boston",
            "london"
        ]
    })";
    JsonDoc doc = JsonDoc::fromObject(stub);
    ASSERT_EQ(stub.json, doc.toJson());
}

TEST(JsonDocTests, DocInitializedWithObjectContainingObjectOutputsRootObjectConvertedToJson) {
    JsonObjectStub stub;
    stub.json = R"({
        "cities" : {
            "new york" : "nyc",
            "boston" : "bst",
            "london" : "lon"
        }
    })";
    JsonDoc doc = JsonDoc::fromObject(stub);
    ASSERT_EQ(stub.json, doc.toJson());
}

TEST(JsonDocTests, DocInitializedWithValidJsonStringOutputsTheSameJson) {
    std::string validJson = R"({ "key" : 123 })";
    JsonDoc doc(validJson);
    ASSERT_EQ(validJson, doc.toJson());
}

TEST(JsonDocTests, DocInitializedWithInvalidJsonStringOutputsTheSameJson) {
    std::string invalidJson = "{ 1 # false }";
    JsonDoc doc = JsonDoc::fromJson(invalidJson);
    ASSERT_EQ(invalidJson, doc.toJson());
}

TEST(JsonDocTests, CanSwapTheContentsOfTwoDocs) {
    JsonDoc doc1 = JsonDoc::fromJson(R"({ "doc1key" : 123 })");
    JsonDoc doc2 = JsonDoc::fromJson(R"({ "doc2key" : 456 })");
    JsonDoc copyOfDoc1 = doc1;
    JsonDoc copyOfDoc2 = doc2;

    doc1.swap(doc2);

    ASSERT_EQ(copyOfDoc1, doc2);
    ASSERT_EQ(copyOfDoc2, doc1);
}

TEST(JsonDocTests, ReturnsTheNumberOfKeysInRootObject) {
    JsonObjectStub stub;
    stub.json = R"({ "on" : true, "in motion" : false })";
    JsonDoc doc(stub);
    ASSERT_EQ(2, doc.numKeys());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
