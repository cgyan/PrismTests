#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/FakeJsonArray>
#include <prism/FakeJsonValue>
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
    ja.append(make_fake_json_value(3.14));
    ASSERT_FALSE(ja.empty());
}

TEST(JsonArrayTests, HasSizeOneAfterAddingValue) {
    JsonArray ja = { make_fake_json_value(3.14) };
    ASSERT_EQ(1, ja.size());
}

TEST(JsonArrayTests, HasSizeZeroAfterRemovingLastValue) {
    JsonArray ja = { make_fake_json_value(3.14) };
    ja.removeAt(0);
    ASSERT_EQ(0, ja.size());
}

TEST(JsonArrayTests, IsEmptyAfterRemovingLastValue) {
    JsonArray ja = { make_fake_json_value(3.14) };
    ja.remove(ja.begin());
    ASSERT_TRUE(ja.empty());
}

TEST(JsonArrayTests, CanInsertNewValueAtFront) {
    JsonArray ja = {
        make_fake_json_value(6.28),
        make_fake_json_value(9.56)
    };
    ja.prepend(make_fake_json_value(3.14));
    JsonArray expected = {
        make_fake_json_value(3.14),
        make_fake_json_value(6.28),
        make_fake_json_value(9.56)
    };
    ASSERT_EQ(expected, ja);
}

TEST(JsonArrayTests, CanInsertNewValueInMiddleOfExistingElementsByIterator) {
    JsonArray ja = {
        make_fake_json_value(3.14),
        make_fake_json_value(9.56)
    };
    ja.insert(ja.end() - 1, make_fake_json_value(6.28));
    JsonArray expected = {
        make_fake_json_value(3.14),
        make_fake_json_value(6.28),
        make_fake_json_value(9.56)
    };
    ASSERT_EQ(expected, ja);
}

TEST(JsonArrayTests, CanInsertNewValueInMiddleOfExistingElementsByIndex) {
    JsonArray ja = {
        make_fake_json_value(3.14),
        make_fake_json_value(9.56)
    };
    const int insertIndex = 1;
    ja.insert(insertIndex, make_fake_json_value(6.28));
    JsonArray expected = {
        make_fake_json_value(3.14),
        make_fake_json_value(6.28),
        make_fake_json_value(9.56) };
    ASSERT_EQ(expected, ja);
}

TEST(JsonArrayTests, CanConfirmArrayContainsElement) {
    JsonArray ja = {
        make_fake_json_value(3.14),
        make_fake_json_value(6.28),
        make_fake_json_value(9.56)
    };
    ASSERT_TRUE(ja.contains(make_fake_json_value(3.14)));
    ASSERT_FALSE(ja.contains("non existent value"));
}

TEST(JsonArrayTests, CopiedArrayIsIndependentFromOriginalArray) {
    JsonArray ja = {
        make_fake_json_value(3.14)
    };
    JsonArray copy = ja;
    copy[0] = make_fake_json_value(6.28);
    ASSERT_EQ(JsonArray({make_fake_json_value(3.14)}), ja);
    ASSERT_EQ(JsonArray({make_fake_json_value(6.28)}), copy);
}

TEST(JsonArrayTests, AssignedArrayIsIndependentFromOriginalArray) {
    JsonArray ja = {
        make_fake_json_value(3.14)
    };
    JsonArray copy;
    copy = ja;
    copy.at(0) = make_fake_json_value(6.28);
    ASSERT_EQ(JsonArray({make_fake_json_value(3.14)}), ja);
    ASSERT_EQ(JsonArray({make_fake_json_value(6.28)}), copy);
}

TEST(JsonArrayTests, ThrowsWhenAccessingIndexOutOfBounds) {
    JsonArray ja = {
        make_fake_json_value(3.14),
        make_fake_json_value(6.28),
        make_fake_json_value(9.56)
    };
    ASSERT_THROW(ja.at(3), prism::OutOfBoundsException);
}

TEST(JsonArrayTests, CanSwapContentsOfTwoArrays) {
    JsonArray ja1 = {
        make_fake_json_value(1.23),
        make_fake_json_value(2.34),
        make_fake_json_value(3.45)
    };
    JsonArray ja2 = {
        make_fake_json_value(9.87),
        make_fake_json_value(8.76),
        make_fake_json_value(7.65)
    };
    JsonArray copyOfJa1 = ja1;
    JsonArray copyOfJa2 = ja2;
    ja1.swap(ja2);
    ASSERT_EQ(copyOfJa2, ja1);
    ASSERT_EQ(copyOfJa1, ja2);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
