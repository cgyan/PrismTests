#include <gtest/gtest.h>
#include <prism/JsonObject>
#include <prism/JsonValue>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class JsonValueStub : public JsonValue {
public:
    bool b{};
    double d{};
};

TEST(JsonObjectTests, DefaultIsEmpty) {
    JsonObject jo;
    ASSERT_TRUE(jo.empty());
}

TEST(JsonObjectTests, DefaultHasSizeZero) {
    JsonObject jo;
    ASSERT_EQ(0, jo.size());
}

TEST(JsonObjectTests, HasSizeOneAfterAddingNewMember) {
    JsonValueStub stub;
    JsonObject jo({{"key", stub}});
    ASSERT_EQ(1, jo.size());
}

TEST(JsonObjectTests, IsNotEmptyAfterAddingNewMember) {
    JsonValueStub stub;
    JsonObject jo = { {"key", stub} };
    ASSERT_FALSE(jo.empty());
}

TEST(JsonObjectTests, DefaultDoesNotContainAnyKeys) {
    JsonObject jo;
    ASSERT_FALSE(jo.contains("nonexistent key"));
}

TEST(JsonObjectTests, CanAddMember) {
    JsonObject jo;
    JsonValueStub stub;
    jo.insert("key", stub);
    ASSERT_EQ(stub, jo["key"]);
}

TEST(JsonObjectTests, CanAlterValueDirectly) {
    JsonValueStub stub;
    stub.d = 3.14;
    JsonObject jo = { {"pi", stub} };
    jo["pi"] = 6.28;
    ASSERT_EQ(6.28, jo["pi"]);
}

TEST(JsonObjectTests, CanConfirmThatInsertedKeyIsContainedInObject) {
    JsonValueStub stub;
    JsonObject jo({{"key", stub}});
    ASSERT_TRUE(jo.contains("key"));
}

TEST(JsonObjectTests, UnusedKeyIsNotContainedInEmptyObject) {
    JsonObject jo;
    ASSERT_FALSE(jo.contains("unused key"));
}

TEST(JsonObjectTests, UnusedKeyIsNotContainedInInitializedObject) {
    JsonObject jo = { {"key1", JsonValueStub()}, {"key2", JsonValueStub()} };
    ASSERT_FALSE(jo.contains("unused key"));
}

TEST(JsonObjectTests, CanReturnAllKeyNames) {
    JsonObject jo = {
        {"key1", JsonValueStub()},
        {"key2", JsonValueStub()},
        {"key3", JsonValueStub()}
    };
    std::list<std::string> expected = { "key1", "key2", "key3" };
    ASSERT_EQ(expected, jo.keys());
}

TEST(JsonObjectTests, SizeIsOneLessAfterRemovingMember) {
    JsonObject jo = {
        {"key1", JsonValueStub()},
        {"key2", JsonValueStub()}
    };
    jo.remove("key1");
    const int expectedSize = 1;
    ASSERT_EQ(expectedSize, jo.size());
}

TEST(JsonObjectTests, OnlyOneMemberRemainsAfterRemovingMember) {
    JsonObject jo = {
        {"key1", JsonValueStub()},
        {"key2", JsonValueStub()}
    };

    jo.remove("key1");
    JsonObject expected = {
        {"key2", JsonValueStub()}
    };

    ASSERT_EQ(expected, jo);
}

TEST(JsonObjectTests, IsEmptyAfterRemovingLastMember) {
    JsonObject jo = {
        {"key", JsonValueStub()}
    };

    JsonObject::iterator it = jo.begin();
    jo.erase(it);

    ASSERT_TRUE(jo.empty());
}

TEST(JsonObjectTests, CanFindMemberUsingKey) {
    JsonObject jo = {
        {"pi", JsonValueStub()},
        {"twopi", JsonValueStub()},
        {"threepi", JsonValueStub()}
    };
    JsonObject::iterator it = jo.find("twopi");
    ASSERT_EQ("twopi", (*it).first);
}

TEST(JsonObjectTests, CopiedObjectIsIndependentOfOriginalObject) {
    JsonValueStub trueStub;
    trueStub.b = true;
    JsonValueStub falseStub;
    falseStub.b = false;

    JsonObject jo = {
        {"key1", trueStub}
    };
    JsonObject copy = jo;
    copy["key1"] = falseStub;

    ASSERT_EQ(JsonObject({{"key1",trueStub}}), jo);
    ASSERT_EQ(JsonObject({{"key1",falseStub}}), copy);
}

TEST(JsonObjectTests, AssignedObjectIsIndependentOfOriginalObject) {
    JsonValueStub trueStub;
    trueStub.b = true;
    JsonValueStub falseStub;
    falseStub.b = false;

    JsonObject jo = { {"key1", trueStub} };
    JsonObject copy;
    copy = jo;
    copy["key1"] = falseStub;

    ASSERT_EQ(JsonObject({{"key1",trueStub}}), jo);
    ASSERT_EQ(JsonObject({{"key1",falseStub}}), copy);
}

TEST(JsonObjectTests, InsertingNewMemberWithDuplicateKeyOverwritesExistingAssociatedValue) {
    JsonValueStub stubPi;
    stubPi.d = 3.14;
    JsonValueStub stubTwoPi;
    stubTwoPi.d = 6.28;
    JsonValueStub stubHalfPi;
    stubTwoPi.d = 1.57;

    JsonObject jo = {
        {"pi", stubPi},
        {"twopi", stubTwoPi}
    };
    jo.insert("pi", stubHalfPi);

    JsonObject expected = {
        {"pi",stubHalfPi},
        {"twopi",stubTwoPi}
    };
    ASSERT_EQ(expected, jo);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
