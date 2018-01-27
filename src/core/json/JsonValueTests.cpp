#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonValue>
#include <prism/JsonObject>
#include <prism/InvalidConversionException>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonValueTests, DefaultIsNull) {
    JsonValue jv;
    ASSERT_TRUE(jv.isNull());
}

TEST(JsonValueTests, IsNotNullWhenInitializedWithValue) {
    ASSERT_FALSE(JsonValue(3.14).isNull());
    ASSERT_FALSE(JsonValue("string value").isNull());
    ASSERT_FALSE(JsonValue(false).isNull());
    ASSERT_FALSE(JsonValue(JsonObject()).isNull());
    ASSERT_FALSE(JsonValue(JsonArray()).isNull());
}

TEST(JsonValueTests, CanExtractDouble) {
    const double pi = 3.14;
    JsonValue jv(pi);
    ASSERT_EQ(pi, jv.toDouble());
}

TEST(JsonValueTests, CanExtractBool) {
    const bool b = false;
    JsonValue jv(b);
    ASSERT_EQ(b, jv.toBool());
}

TEST(JsonValueTests, CanExtractString) {
    const std::string str = "manhattan";
    JsonValue jv(str);
    ASSERT_EQ(str, jv.toString());
}

TEST(JsonValueTests, CanExtractObject) {
    JsonObject jo;
    JsonValue jv(jo);
    ASSERT_EQ(jo, jv.toObject());
}

TEST(JsonValueTests, CanExtractArray) {
    JsonArray ja;
    JsonValue jv(ja);
    ASSERT_EQ(ja, jv.toArray());
}

TEST(JsonValueTests, ThrowsWhenConvertingDoubleToNonDoubleType) {
    const double doubleValue = 6.28;
    JsonValue jv(doubleValue);
    ASSERT_NO_THROW(jv.toDouble());
    ASSERT_THROW(jv.toString(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toArray(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toObject(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toBool(), prism::InvalidConversionException);
}

TEST(JsonValueTests, ThrowsWhenConvertingBoolToNonBoolType) {
    const bool boolValue = true;
    JsonValue jv(boolValue);
    ASSERT_NO_THROW(jv.toBool());
    ASSERT_THROW(jv.toDouble(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toString(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toArray(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toObject(), prism::InvalidConversionException);
}

TEST(JsonValueTests, ThrowsWhenConvertingStringToNonStringType) {
    const std::string stringValue = "nyc";
    JsonValue jv(stringValue);
    ASSERT_NO_THROW(jv.toString());
    ASSERT_THROW(jv.toDouble(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toArray(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toObject(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toBool(), prism::InvalidConversionException);
}

TEST(JsonValueTests, ThrowsWhenConvertingObjectToNonObjectType) {
    JsonObject objectValue;
    JsonValue jv(objectValue);
    ASSERT_NO_THROW(jv.toObject());
    ASSERT_THROW(jv.toDouble(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toArray(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toBool(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toString(), prism::InvalidConversionException);
}

TEST(JsonValueTests, ThrowsWhenConvertingArrayToNonArrayType) {
    JsonArray arrayValue;
    JsonValue jv(arrayValue);
    ASSERT_NO_THROW(jv.toArray());
    ASSERT_THROW(jv.toDouble(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toObject(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toBool(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toString(), prism::InvalidConversionException);
}

TEST(JsonValueTests, TwoValuesAreEquivalent) {
    ASSERT_EQ(JsonValue(3.14), JsonValue(3.14));
    ASSERT_EQ(JsonValue(true), JsonValue(true));
    ASSERT_EQ(JsonValue("nyc"), JsonValue("nyc"));
    ASSERT_EQ(JsonValue(JsonObject()), JsonValue(JsonObject()));
    ASSERT_EQ(JsonValue(JsonArray()), JsonValue(JsonArray()));
}

TEST(JsonValueTests, TwoValuesAreNotEquivalent) {
    ASSERT_TRUE(JsonValue(3.14) != JsonValue(6.28));
    ASSERT_TRUE(JsonValue(true) != JsonValue(false));
    ASSERT_TRUE(JsonValue("") != JsonValue("manhattan"));
    //TODO: need to make JsonObject and JsonArray instances unique for this test
    ASSERT_TRUE(JsonValue(JsonObject()) != JsonValue(JsonObject()));
    ASSERT_TRUE(JsonValue(JsonArray()) != JsonValue(JsonArray()));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
