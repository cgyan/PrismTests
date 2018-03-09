#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonStringBuilder>
#include <prism/FakeJsonObject>
#include <prism/FakeJsonArray>
#include <prism/FakeJsonValue>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonStringBuilderTests, WhenDefaultBuilderIsCreatedExpectItToBeEmpty) {
    JsonStringBuilder jsb;
    EXPECT_TRUE(jsb.empty());
}

TEST(JsonStringBuilderTests, WhenDefaultBuilderIsCreatedExpectSizeToBeZero) {
    JsonStringBuilder jsb;
    const int expectedSize = 0;
    EXPECT_EQ(expectedSize, jsb.size());
}

TEST(JsonStringBuilderTests, WhenAppendedToExpectBuilderSizeToMatchArgumentLength) {
    JsonStringBuilder jsb;
    jsb.append(3.14);
    const int expectedSize = 4;
    EXPECT_EQ(expectedSize, jsb.size());
}

TEST(JsonStringBuilderTests, WhenAppendedToExpectBuilderNotToBeEmpty) {
    JsonStringBuilder jsb;
    jsb.append(3.14);
    EXPECT_FALSE(jsb.empty());
}

TEST(JsonStringBuilderTests, WhenLiteralStringIsAppendedExpectConversionStringToContainString) {
    const char * s = "nyc";
    JsonStringBuilder jsb;
    jsb.append(s);
    EXPECT_EQ(R"("nyc")", jsb.toString());
}

TEST(JsonStringBuilderTests, WhenStdStringIsAppendedExpectConversionStringToContainString) {
    std::string s = "nyc";
    JsonStringBuilder jsb;
    jsb.append(s);
    std::string expectedString = R"("nyc")";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenLiteralTrueIsAppendedExpectConversionStringToContainBool) {
    JsonStringBuilder jsb;
    jsb.append(true);
    EXPECT_EQ("true", jsb.toString());
}

TEST(JsonStringBuilderTests, WhenLiteralFalseIsAppendedExpectConversionStringToContainBool) {
    JsonStringBuilder jsb;
    jsb.append(false);
    EXPECT_EQ("false", jsb.toString());
}

TEST(JsonStringBuilderTests, WhenIntegerIsAppendedExpectConversionStringToContainInt) {
    JsonStringBuilder jsb;
    jsb.append(1);
    EXPECT_EQ("1", jsb.toString());
}

TEST(JsonStringBuilderTests, WhenDoubleIsAppendedExpectConversionStringToContainNumber) {
    JsonStringBuilder jsb;
    jsb.append(3.14);
    EXPECT_EQ("3.14", jsb.toString());
}

TEST(JsonStringBuilderTests, WhenEmptyObjectIsAppendedExpectConversionStringToContainEmptyObject) {
    JsonStringBuilder jsb;
    jsb.append(make_fake_json_object());
    const std::string expectedString = "{}";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenObjectWithDoubleValueIsAppendedExpectConversionStringToContainObject) {
    JsonObject fakeObj = make_fake_json_object("pi", 3.14);
    JsonStringBuilder jsb;
    jsb.append(fakeObj);
    const std::string expectedString = R"({"pi":3.14})";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenObjectWithStringValueIsAppendedExpectConversionStringToContainObject) {
    JsonObject fakeObj = make_fake_json_object("nyc", "new york city");
    JsonStringBuilder jsb;
    jsb.append(fakeObj);
    const std::string expectedString = R"({"nyc":"new york city"})";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenObjectWithLiteralTrueValueIsAppendedExpectConversionStringToContainObject) {
    JsonObject fakeObj = make_fake_json_object("valid", true);
    JsonStringBuilder jsb;
    jsb.append(fakeObj);
    const std::string expectedString = R"({"valid":true})";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenObjectWithLiteralFalseValueIsAppendedExpectConversionStringToContainObject) {
    JsonObject fakeObj = make_fake_json_object("valid", false);
    JsonStringBuilder jsb;
    jsb.append(fakeObj);
    const std::string expectedString = R"({"valid":false})";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenObjectWithLiteralNullValueIsAppendedExpectConversionStringToContainObject) {
    JsonObject fakeObj = make_fake_json_object("valid", make_fake_json_value());
    JsonStringBuilder jsb;
    jsb.append(fakeObj);
    const std::string expectedString = R"({"valid":null})";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenObjectWithEmptyObjectValueIsAppendedExpectConversionStringToContainEmptyObject) {
    JsonObject fakeObj = make_fake_json_object("empty obj", make_fake_json_object());
    JsonStringBuilder jsb;
    jsb.append(fakeObj);
    const std::string expectedString = R"({"empty obj":{}})";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenObjectWithObjectValueIsAppendedExpectConversionStringToContainObject) {
    JsonObject fakeObj = make_fake_json_object("cities", make_fake_json_object("nyc", "new york city"));
    JsonStringBuilder jsb;
    jsb.append(fakeObj);
    const std::string expectedString = R"({"cities":{"nyc":"new york city"}})";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenEmptyArrayIsAppendedExpectConversionStringToContainEmptyArray) {
    JsonArray fakeArray = make_fake_json_array();
    JsonStringBuilder jsb;
    jsb.append(fakeArray);
    std::string expectedString = "[]";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenArrayWithDoubleValueIsAppendedExpectConversionStringToContainArray) {
    JsonArray fakeArray = make_fake_json_array({3.14});
    JsonStringBuilder jsb;
    jsb.append(fakeArray);
    std::string expectedString = "[3.14]";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenArrayWithStringValueIsAppendedExpectConversionStringToContainArray) {
    JsonArray fakeArray = make_fake_json_array({"nyc"});
    JsonStringBuilder jsb;
    jsb.append(fakeArray);
    std::string expectedString = R"(["nyc"])";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenArrayWithLiteralTrueValueIsAppendedExpectConversionStringToContainArray) {
    JsonArray fakeArray = make_fake_json_array({true});
    JsonStringBuilder jsb;
    jsb.append(fakeArray);
    std::string expectedString = R"([true])";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenArrayWithLiteralFalseValueIsAppendedExpectConversionStringToContainArray) {
    JsonArray fakeArray = make_fake_json_array({false});
    JsonStringBuilder jsb;
    jsb.append(fakeArray);
    std::string expectedString = R"([false])";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenArrayWithLiteralNullValueIsAppendedExpectConversionStringToContainArray) {
    JsonArray fakeArray = make_fake_json_array({make_fake_json_value()});
    JsonStringBuilder jsb;
    jsb.append(fakeArray);
    std::string expectedString = R"([null])";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenArrayWithEmptyArrayValueIsAppendedExpectConversionStringToContainArray) {
    JsonArray fakeArray = make_fake_json_array({make_fake_json_array()});
    JsonStringBuilder jsb;
    jsb.append(fakeArray);
    std::string expectedString = R"([[]])";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenArrayWithEmptyObjectValueIsAppendedExpectConversionStringToContainArray) {
    JsonArray fakeArray = make_fake_json_array({make_fake_json_object()});
    JsonStringBuilder jsb;
    jsb.append(fakeArray);
    std::string expectedString = R"([{}])";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenArrayWithObjectValueIsAppendedExpectConversionStringToContainArray) {
    JsonArray fakeArray = make_fake_json_array({make_fake_json_object("pi", 3.14)});
    JsonStringBuilder jsb;
    jsb.append(fakeArray);
    std::string expectedString = R"([{"pi":3.14}])";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenArrayOfDoublesIsAppendedExpectConversionStringToContainArrayElements) {
    JsonArray fakeArray = make_fake_json_array({3.14,6.28,9.56});
    JsonStringBuilder jsb;
    jsb.append(fakeArray);
    const std::string expectedString = R"([3.14,6.28,9.56])";
    EXPECT_EQ(expectedString, jsb.toString());
}

TEST(JsonStringBuilderTests, WhenObjectWithMultipleMembersIsAppendedExpectConversionStringToContainObject) {
    JsonObject fakeObj = make_fake_json_object();
    fakeObj.insert("la", "los angeles");
    fakeObj.insert("nyc", "new york city");
    JsonStringBuilder jsb;
    jsb.append(fakeObj);
    std::string expectedString = R"({"la":"los angeles","nyc":"new york city"})";
    EXPECT_EQ(expectedString, jsb.toString());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
