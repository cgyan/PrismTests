#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonValue>
#include <prism/FakeJsonObjectImpl>
#include <prism/FakeJsonArrayImpl>
#include <prism/InvalidConversionException>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonValueTests, DefaultIsNull) {
    JsonValue jv;
    ASSERT_TRUE(jv.isNull());
}

TEST(JsonValueTests, IsNotNullWhenInitializedWithValue) {
    ASSERT_FALSE(JsonValue(3.14).isNull());
    ASSERT_FALSE(JsonValue(false).isNull());
    ASSERT_FALSE(JsonValue("string value").isNull());
    ASSERT_FALSE(JsonValue(make_fake_json_object("pi", 3.14)).isNull());
    ASSERT_FALSE(JsonValue(make_fake_json_array({3.14, 6.28})).isNull());
}

TEST(JsonValueTests, ThrowsWhenConvertingDoubleToNonDoubleType) {
    const double doubleValue = 6.28;
    JsonValue jv(doubleValue);
    ASSERT_NO_THROW(jv.toDouble());
    ASSERT_THROW(jv.toBool(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toString(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toObject(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toArray(), prism::InvalidConversionException);
}

TEST(JsonValueTests, ThrowsWhenConvertingBoolToNonBoolType) {
    const bool boolValue = true;
    JsonValue jv(boolValue);
    ASSERT_NO_THROW(jv.toBool());
    ASSERT_THROW(jv.toDouble(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toString(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toObject(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toArray(), prism::InvalidConversionException);
}

TEST(JsonValueTests, ThrowsWhenConvertingStringToNonStringType) {
    const std::string stringValue = "nyc";
    JsonValue jv(stringValue);
    ASSERT_NO_THROW(jv.toString());
    ASSERT_THROW(jv.toBool(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toDouble(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toObject(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toArray(), prism::InvalidConversionException);
}

TEST(JsonValueTests, ThrowsWhenConvertingObjectToNonObjectType) {
    JsonValue jv(make_fake_json_object("pi", 3.14));
    ASSERT_NO_THROW(jv.toObject());
    ASSERT_THROW(jv.toDouble(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toBool(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toString(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toArray(), prism::InvalidConversionException);
}

TEST(JsonValueTests, ThrowsWhenConvertingArrayToNonArrayType) {
    JsonValue jv(make_fake_json_array({3.14, 6.28, 9.56}));
    ASSERT_NO_THROW(jv.toArray());
    ASSERT_THROW(jv.toDouble(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toObject(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toBool(), prism::InvalidConversionException);
    ASSERT_THROW(jv.toString(), prism::InvalidConversionException);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
