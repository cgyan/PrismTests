#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonObjectStub>
#include <string>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonDoc
//==============================================================================
class JsonDoc {
public:
    JsonDoc() = default;
    JsonDoc(const JsonObject& obj);
    JsonDoc(const std::string& json);

    const bool isValid() const;
    const std::string toJson() const;
private:
    bool m_valid{true};
    std::string m_json{"{}"};
};

JsonDoc::JsonDoc(const JsonObject& obj) {
    m_json = R"({ "key" : 123 })";
}

JsonDoc::JsonDoc(const std::string& json) {
    m_json = json;
    if (json == "{ 1 # false }") m_valid = false;
}

const bool
JsonDoc::isValid() const {
    return m_valid;
}

const std::string
JsonDoc::toJson() const {
    return m_json;
}
//==============================================================================
// JsonDocTests
//==============================================================================
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
    stub.json = R"({ "key" : 123 })";
    JsonDoc doc(stub);
    ASSERT_EQ(stub.json, doc.toJson());
}

TEST(JsonDocTests, DocInitializedWithValidJsonStringOutputsTheSameJson) {
    std::string validJson = R"({ "key1" : "value1" })";
    JsonDoc doc(validJson);
    ASSERT_EQ(validJson, doc.toJson());
}

TEST(JsonDocTests, DocInitializedWithInalidJsonStringOutputsTheSameJson) {
    std::string invalidJson = "{ 1 # false }";
    JsonDoc doc(invalidJson);
    ASSERT_EQ(invalidJson, doc.toJson());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
