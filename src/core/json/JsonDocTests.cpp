#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/JsonDoc>
#include <prism/FakeJsonObjectImpl>
#include <prism/FakeJsonArrayImpl>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonDocTests, DefaultDocisValid) {
    JsonDoc doc;
    ASSERT_TRUE(doc.isValid());
}

TEST(JsonDocTests, DocInitializedWithObjectIsValid) {
    JsonDoc doc(make_fake_json_object("pi", 3.14));
    ASSERT_TRUE(doc.isValid());
}

TEST(JsonDocTests, DocInitializedFromIncorrectJsonisInvalid) {
    std::string invalidJson = "{ 1 # false }";
    JsonDoc doc(invalidJson);
    ASSERT_FALSE(doc.isValid());
}

TEST(JsonDocTests, DocInitializedFromValidJsonStringIsValid) {
    std::string validJson = R"({ "key" : "value" })";
    JsonDoc doc(validJson);
    ASSERT_TRUE(doc.isValid());
}

TEST(JsonDocTests, DefaultDocConvertedToJsonOutputsEmptyObject) {
    JsonDoc doc;
    std::string expected = "{}";
    ASSERT_EQ(expected, doc.toJson());
}

TEST(JsonDocTests, DocInitializedWithObjectOutputsObjectConvertedToJson) {
    JsonObject fakeObj = make_fake_json_object("pi", 3.14);
    JsonDoc doc = JsonDoc::fromObject(fakeObj);
    ASSERT_EQ(R"({ "pi" : 3.14 })", doc.toJson());
}

TEST(JsonDocTests, DocInitializedWithObjectContainingArrayOutputsRootObjectConvertedToJson) {
    JsonArray fakeArray = make_fake_json_array({3.14, 6.28, 9.56});
    JsonObject fakeObject = make_fake_json_object("pi multiples", fakeArray);
    JsonDoc doc = JsonDoc::fromObject(fakeObject);
    ASSERT_EQ(R"({ "pi multiples" : [ 3.14, 6.28, 9.56 ] })", doc.toJson());
}

TEST(JsonDocTests, DocInitializedWithObjectContainingSubObjectOutputsRootObjectConvertedToJson) {
    JsonObject fakeSubObject = make_fake_json_object("pi", 3.14);
    JsonObject fakeMainObject = make_fake_json_object("key", fakeSubObject);
    JsonDoc doc = JsonDoc::fromObject(fakeMainObject);
    std::string expected = R"({ "key" : { "pi" : 3.14 } })";
    ASSERT_EQ(expected, doc.toJson());
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
    JsonObject fakeObj = make_fake_json_object("pi", 3.14);
    JsonDoc doc(fakeObj);
    ASSERT_EQ(fakeObj.size(), doc.numKeys());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
