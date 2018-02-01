#include <gtest/gtest.h>
#include <prism/JsonObject>
#include <prism/JsonValue>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(JsonObjectTests, DefaultIsEmpty) {
    JsonObject jo;
    ASSERT_TRUE(jo.empty());
}

TEST(JsonObjectTests, DefaultHasSizeZero) {
    JsonObject jo;
    ASSERT_EQ(0, jo.size());
}

TEST(JsonObjectTests, HasSizeOneAfterAddingNewMember) {
    std::string key = "key";
    std::string value = "value";
    JsonObject jo({{key, value}});
    ASSERT_EQ(1, jo.size());
}

TEST(JsonObjectTests, IsNotEmptyAfterAddingNewMember) {
    std::string key = "key";
    std::string value = "value";
    JsonObject jo = { {key, value} };
    ASSERT_FALSE(jo.empty());
}

TEST(JsonObjectTests, DefaultDoesNotContainAnyKeys) {
    JsonObject jo;
    ASSERT_FALSE(jo.contains("nonexistent key"));
}

TEST(JsonObjectTests, CanAddMember) {
    std::string key = "key";
    std::string value = "value";
    JsonObject jo;
    jo.insert(key, value);
    ASSERT_EQ(value, jo[key]);
}

TEST(JsonObjectTests, CanAlterValueDirectly) {
    std::string pi = "pi";
    double value = 3.14;
    double newValue = 6.28;
    JsonObject jo = { {pi, value} };
    jo[pi] = newValue;
    ASSERT_EQ(newValue, jo[pi]);
}

TEST(JsonObjectTests, CanConfirmThatInsertedKeyIsContainedInObject) {
    std::string key = "key";
    const double value = 123;
    JsonObject jo({{key, value}});
    ASSERT_TRUE(jo.contains(key));
}

TEST(JsonObjectTests, UnusedKeyIsNotContainedInEmptyObject) {
    std::string unusedKey = "unused key";
    JsonObject jo;
    ASSERT_FALSE(jo.contains(unusedKey));
}

TEST(JsonObjectTests, UnusedKeyIsNotContainedInInitializedObject) {
    std::string unusedKey = "unused key";
    JsonObject jo = { {"key1", "value1"}, {"key2", "value2"} };
    ASSERT_FALSE(jo.contains(unusedKey));
}

TEST(JsonObjectTests, CanReturnAllKeyNames) {
    JsonObject jo = { {"key1","value1"}, {"key2","value2"}, {"key3", "value3"} };
    std::list<std::string> expected = { "key1", "key2", "key3" };
    ASSERT_EQ(expected, jo.keys());
}

TEST(JsonObjectTests, SizeIsOneLessAfterRemovingMember) {
    JsonObject jo = { {"key1", true}, {"key2", false} };
    jo.remove("key1");
    const int expectedSize = 1;
    ASSERT_EQ(expectedSize, jo.size());
}

TEST(JsonObjectTests, OnlyOneMemberRemainsAfterRemovingMember) {
    using Member = std::pair<std::string, JsonValue>;
    Member member1 = {"key1", true};
    Member member2 = {"key2", 3.14};
    JsonObject jo = { member1, member2 };

    jo.remove("key1");

    JsonObject expected = { member2 };
    ASSERT_EQ(expected, jo);
}

TEST(JsonObjectTests, IsEmptyAfterRemovingLastMember) {
    using Member = std::pair<std::string, JsonValue>;
    Member member1 = {"key1", 6.28};
    JsonObject jo = { member1 };
    JsonObject::iterator it = jo.begin();
    jo.erase(it);
    ASSERT_TRUE(jo.empty());
}

TEST(JsonObjectTests, CanFindMemberUsingKey) {
    using Member = std::pair<const std::string, JsonValue>;
    Member member1 = {"pi", 3.14};
    Member member2 = {"twopi", 6.28};
    Member member3 = {"threepi", 9.56};
    JsonObject jo = { member1, member2, member3 };
    JsonObject::iterator it = jo.find("twopi");
    ASSERT_EQ(member2, *it);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
