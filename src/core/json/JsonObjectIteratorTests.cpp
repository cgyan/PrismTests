#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/JsonValue>
#include <prism/JsonObject>
#include <prism/Vector>
#include <prism/Pair>
#include <map>
#include <string>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class JsonObjectIteratorTests : public Test {
public:
    using JsonObjectPair = std::pair<const std::string,JsonValue>;
    using iterator = JsonObject::iterator;
    prism::Vector<std::string> keyOrder;
    std::map<std::string, JsonValue> map;
    int currentIndex{0};

    void SetUp() {
        keyOrder << "one" << "two" << "three";
        map["one"] = 1;
        map["two"] = 2;
        map["three"] = 3;
    }
};

TEST_F(JsonObjectIteratorTests, WhenDereferencedExpectPairContainingKeyAndValue) {
    iterator it(&keyOrder, &map, currentIndex);

    JsonObjectPair expected("one", 1);
    JsonObjectPair actual = *it;
    EXPECT_EQ(expected, actual);
}

TEST_F(JsonObjectIteratorTests, WhenDereferencingPostIncrementedIterExpectReturnedPairToContainFirstPair) {
    iterator it(&keyOrder, &map, currentIndex);
    JsonObjectPair expected("one", 1);
    EXPECT_EQ(expected, *it++);
}

TEST_F(JsonObjectIteratorTests, WhenDereferencingPreIncrementedIterExpectReturnedPairToContainSecondPair) {
    iterator it(&keyOrder, &map, currentIndex);
    JsonObjectPair expected("two", 2);
    EXPECT_EQ(expected, *++it);
}

TEST_F(JsonObjectIteratorTests, WhenDereferencingIterExpectReturnedPairToContainThirdPair) {
    iterator it(&keyOrder, &map, currentIndex);

    it += 2;

    EXPECT_EQ(JsonObjectPair("three",3), *it);
}

TEST_F(JsonObjectIteratorTests, WhenPostDecrementingIterExpectReturnedIterToEqualEndIter) {
    currentIndex = map.size();
    iterator it(&keyOrder, &map, currentIndex);
    iterator expected = it;
    iterator actual = it--;

    EXPECT_TRUE(actual == expected);
}

TEST_F(JsonObjectIteratorTests, WhenDereferencingPreIncrementedIterExpectReturnedPairToContainLastPair) {
    currentIndex = map.size();

    iterator it(&keyOrder, &map, currentIndex);
    EXPECT_EQ(JsonObjectPair("three",3), *--it);
}

TEST_F(JsonObjectIteratorTests, WhenDereferencingIterExpectReturnedPairToContainFirstPair) {
    currentIndex = map.size();
    iterator it(&keyOrder, &map, currentIndex);

    it -= 3;

    EXPECT_EQ(JsonObjectPair("one",1), *it);
}

TEST_F(JsonObjectIteratorTests, WhenAddingOneToIterExpectDereferencedPairToContainSecondPair) {
    iterator it(&keyOrder, &map, currentIndex);

    it = it + 1;

    EXPECT_EQ(JsonObjectPair("two",2), *it);
}

TEST_F(JsonObjectIteratorTests, WhenSubtractingOneFromIterExpectDereferencedPairToContainLastPair) {
    currentIndex = map.size();
    iterator it(&keyOrder, &map, currentIndex);

    it = it - 1;

    EXPECT_EQ(JsonObjectPair("three",3), *it);
}

TEST_F(JsonObjectIteratorTests, WhenSubtractingOneIterFromAnotherExpectDistanceToEqualTwo) {
    currentIndex = map.size();
    iterator endIter(&keyOrder, &map, currentIndex);
    currentIndex = 0;
    iterator itPointingAtFirstPair(&keyOrder, &map, currentIndex);

    const int distanceBetweenIters = endIter - itPointingAtFirstPair;
    const int expected = map.size();
    EXPECT_EQ(expected, distanceBetweenIters);
}

TEST_F(JsonObjectIteratorTests, WhenIncrementingIterExpectDereferencePairNotToMatchFirstPairAnymore) {
    iterator it(&keyOrder, &map, currentIndex);

    ++it;

    iterator itToFirstPair(&keyOrder, &map, currentIndex);
    EXPECT_TRUE(itToFirstPair != it);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
