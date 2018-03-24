#include <gtest/gtest.h>
#include <prism/JsonObject>
#include <prismtests/FakeJsonValue>

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
    JsonObject jo({{
        "key", make_fake_json_value(3.14)
    }});
    ASSERT_EQ(1, jo.size());
}

TEST(JsonObjectTests, IsNotEmptyAfterAddingNewMember) {
    JsonObject jo = { {
        "key", make_fake_json_value(3.14)
    } };
    ASSERT_FALSE(jo.empty());
}

TEST(JsonObjectTests, DefaultDoesNotContainAnyKeys) {
    JsonObject jo;
    ASSERT_FALSE(jo.contains("nonexistent key"));
}

TEST(JsonObjectTests, CanAddMember) {
    JsonObject jo;
    jo.insert("key", make_fake_json_value(3.14));
    ASSERT_EQ(make_fake_json_value(3.14), jo["key"]);
}

TEST(JsonObjectTests, CanAlterValueDirectly) {
    JsonObject jo = { {
        "pi", make_fake_json_value(3.14)}
    };
    jo["pi"] = make_fake_json_value(6.28);
    ASSERT_EQ(make_fake_json_value(6.28), jo["pi"]);
}

TEST(JsonObjectTests, CanConfirmThatInsertedKeyIsContainedInObject) {
    JsonObject jo({{
        "key", make_fake_json_value(3.14)
    }});
    ASSERT_TRUE(jo.contains("key"));
}

TEST(JsonObjectTests, UnusedKeyIsNotContainedInEmptyObject) {
    JsonObject jo;
    ASSERT_FALSE(jo.contains("unused key"));
}

TEST(JsonObjectTests, UnusedKeyIsNotContainedInInitializedObject) {
    JsonObject jo = {        {
            "key1", make_fake_json_value(3.14)
        },
        {
            "key2", make_fake_json_value(6.28)
        }
    };
    ASSERT_FALSE(jo.contains("unused key"));
}

TEST(JsonObjectTests, CanReturnAllKeyNames) {
    JsonObject jo = {
        {
            "key1", make_fake_json_value(3.14)
        },
        {
            "key2", make_fake_json_value(6.28)
        },
        {
            "key3", make_fake_json_value(9.56)
        }
    };
    prism::Vector<std::string> expected = { "key1", "key2", "key3" };
    ASSERT_EQ(expected, jo.keys());
}

TEST(JsonObjectTests, SizeIsOneLessAfterRemovingMember) {
    JsonObject jo = {
        {
            "key1", make_fake_json_value(3.14)
        },
        {
            "key2", make_fake_json_value(6.28)
        }
    };
    jo.remove("key1");
    const int expectedSize = 1;
    ASSERT_EQ(expectedSize, jo.size());
}

TEST(JsonObjectTests, OnlyOneMemberRemainsAfterRemovingMember) {
    JsonObject jo = {
        {
            "key1", make_fake_json_value(3.14)
        },
        {
            "key2", make_fake_json_value(6.28)
        }
    };

    jo.remove("key1");
    JsonObject expected = {
        {
            "key2", make_fake_json_value(6.28)
        }
    };

    ASSERT_EQ(expected, jo);
}

TEST(JsonObjectTests, IsEmptyAfterRemovingLastMember) {
    JsonObject jo = {
        {
            "key", make_fake_json_value(3.14)
        }
    };

    JsonObject::iterator it = jo.begin();
    jo.erase(it);

    ASSERT_TRUE(jo.empty());
}

TEST(JsonObjectTests, CanFindMemberUsingKey) {
    JsonObject jo = {
        {
            "pi", make_fake_json_value(3.14)
        },
        {
            "twopi", make_fake_json_value(6.28)
        },
        {
            "threepi", make_fake_json_value(9.56)
        }
    };
    JsonObject::iterator it = jo.find("twopi");
    ASSERT_EQ("twopi", (*it).first);
    ASSERT_EQ(6.28, (*it).second);
}

TEST(JsonObjectTests, CopiedObjectIsIndependentOfOriginalObject) {
    JsonObject jo = {{
        "key", make_fake_json_value(3.14)
    }};
    JsonObject copy = jo;
    copy["key"] = make_fake_json_value(6.28);

    ASSERT_EQ(JsonObject({{"key", make_fake_json_value(3.14)}}), jo);
    ASSERT_EQ(JsonObject({{"key", make_fake_json_value(6.28)}}), copy);
}

TEST(JsonObjectTests, AssignedObjectIsIndependentOfOriginalObject) {
    JsonObject jo = { {
        "key", make_fake_json_value(3.14)}
    };
    JsonObject copy;
    copy = jo;
    copy["key"] = make_fake_json_value(6.28);

    ASSERT_EQ(JsonObject({{"key",make_fake_json_value(3.14)}}), jo);
    ASSERT_EQ(JsonObject({{"key",make_fake_json_value(6.28)}}), copy);
}

TEST(JsonObjectTests, InsertingNewMemberWithDuplicateKeyOverwritesExistingAssociatedValue) {
    JsonObject jo = {{
        "pi", make_fake_json_value(3.14)
    }};

    jo.insert("pi", make_fake_json_value(9.56));

    JsonObject expected = {{
        "pi", make_fake_json_value(9.56)
    }};
    ASSERT_EQ(expected, jo);
}

TEST(JsonObjectTests, WhenInsertingMembersExpectTheInsertionOrderToBePreserved) {
    JsonObject jo;
    jo.insert("name", "al");
    jo.insert("account", "123");
    jo.insert("department", "legal");
    JsonObject::const_iterator cit = jo.cbegin();

    EXPECT_EQ("name", (*cit).first);
    EXPECT_EQ("account", (*++cit).first);
    EXPECT_EQ("department", (*++cit).first);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
