// // {
// //     "city" : "nyc",
// //     "visited" : true,
// //     "subway lines" : [
// //         "lettered" : [ "A", "C", "E", "B", "D", "F", "M" ],
// //         "numbered" : [ 1, 2, 3, 4, 5, 6, 7 ]
// //     ],
// //     "year visited" : 2017,
// //     "hotel" : {
// //         "street" : "West 55th St",
// //         "area" : "midtown"
// //     },
// //     "wifi" : null
// // }
//
#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonObject>
#include <string>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE
//==============================================================================
// JsonObjectTests
//==============================================================================
TEST(JsonObjectTests, DefaultIsEmpty) {
    JsonObject jo;
    ASSERT_TRUE(jo.empty());
}

TEST(JsonObjectTests, DefaultIsNotEmptyAfterInsertion) {
    JsonObject jo;
    jo.insert("key", "stringvalue");
    ASSERT_FALSE(jo.empty());
}

TEST(JsonObjectTests, DefaultHasZeroMembers) {
    JsonObject jo;
    ASSERT_EQ(0, jo.count());
}

TEST(JsonObjectTests, HasSizeOneAfterInsertion) {
    JsonObject jo;
    jo.insert("key", "stringvalue");
    ASSERT_EQ(1, jo.size());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
