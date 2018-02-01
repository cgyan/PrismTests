#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonArray>
#include <prism/JsonValue>
#include <prism/OutOfBoundsException>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonArrayTests, DefaultIsEmpty) {
    JsonArray ja;
    ASSERT_TRUE(ja.empty());
}

TEST(JsonArrayTests, DefaultHasSizeZero) {
    JsonArray ja;
    ASSERT_EQ(0, ja.size());
}

TEST(JsonArrayTests, IsNotEmptyAfterAddingValue) {
    JsonArray ja;
    ja.append("value");
    ASSERT_FALSE(ja.empty());
}

TEST(JsonArrayTests, HasSizeOneAfterAddingValue) {
    JsonArray ja = { 3.14 };
    ASSERT_EQ(1, ja.size());
}

TEST(JsonArrayTests, HasSizeZeroAfterRemovingLastValue) {
    JsonArray ja = { true };
    ja.removeAt(0);
    ASSERT_EQ(0, ja.size());
}

TEST(JsonArrayTests, IsEmptyAfterRemovingLastValue) {
    JsonArray ja = { "value" };
    ja.erase(ja.begin());
    ASSERT_TRUE(ja.empty());
}

TEST(JsonArrayTests, CanInsertNewValueAtFront) {
    JsonArray ja = { 6.28, 9.56 };
    ja.prepend(3.14);
    JsonArray expected = { 3.14, 6.28, 9.56 };
    ASSERT_EQ(expected, ja);
}

TEST(JsonArrayTests, CopiedArrayIsIndependentFromOriginalArray) {
    JsonArray ja = { true };
    JsonArray copy = ja;
    copy[0] = false;
    ASSERT_EQ(JsonArray({true}), ja);
    ASSERT_EQ(JsonArray({false}), copy);
}

TEST(JsonArrayTests, AssignedArrayIsIndependentFromOriginalArray) {
    JsonArray ja = { true };
    JsonArray copy;
    copy = ja;
    copy.at(0) = false;
    ASSERT_EQ(JsonArray({true}), ja);
    ASSERT_EQ(JsonArray({false}), copy);
}

TEST(JsonArrayTests, ThrowsWhenAccessingIndexOutOfBounds) {
    JsonArray ja = { "value1", "value2", "value3" };
    ASSERT_THROW(ja.at(3), prism::OutOfBoundsException);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
