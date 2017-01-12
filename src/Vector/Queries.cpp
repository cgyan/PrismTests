/*
 * Queries.cpp
 * v0.*
 *
 *  Created on: 8 Jan 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/PVector>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class Queries : public Test {
public:
	PVector<int> v;
	int expectedIndex;
	int actualIndex;

	enum {
		NonExistentValue = 500
	};

	Queries()
	: v({1,2,3,4,5,3})
	{}
};

TEST_F(Queries,
ReturnsFalseForContainsNonExistentValue) {
	ASSERT_FALSE(v.contains(NonExistentValue));
}

TEST_F(Queries,
ReturnsTrueForContainsValue) {
	ASSERT_TRUE(v.contains(1));
	ASSERT_TRUE(v.contains(2));
	ASSERT_TRUE(v.contains(3));
	ASSERT_TRUE(v.contains(4));
	ASSERT_TRUE(v.contains(5));
}

TEST_F(Queries,
ReturnsZeroForCountOfNonExistentValue) {
	int expectedCount = 0;
	int actualCount = v.count(NonExistentValue);

	ASSERT_EQ(expectedCount, actualCount);
}

TEST_F(Queries,
ReturnsTwoForCountOfValue) {
	int valueToCount = 3;
	int expectedCount = 2;
	int actualCount = v.count(valueToCount);

	ASSERT_EQ(expectedCount, actualCount);
}

TEST_F(Queries,
ReturnsTrueWhenEndsWithValue) {
	int value = 3;

	ASSERT_TRUE(v.endsWith(value));
}

TEST_F(Queries,
ReturnsFalseWhenDoesNotEndWithValue) {
	ASSERT_FALSE(v.endsWith(NonExistentValue));
	ASSERT_FALSE(v.endsWith(5));
}

TEST_F(Queries,
ReturnsFalseWhenEmptyVectorDoesNotEndWithValue) {
	PVector<int> vec;
	int value = 500;
	ASSERT_FALSE(vec.endsWith(value));
}

TEST_F(Queries,
ReturnsTrueWhenStartsWithValue) {
	int value = 1;

	ASSERT_TRUE(v.startsWith(value));
}

TEST_F(Queries,
ReturnsFalseWhenDoesNotStartWithValue) {
	ASSERT_FALSE(v.startsWith(NonExistentValue));
}

TEST_F(Queries,
ReturnsFalseWhenEmptyVectorDoesNotStartWithValue) {
	PVector<int> vec;

	ASSERT_FALSE(vec.startsWith(500));
}

TEST_F(Queries,
ReturnsIndexNotFoundForFirstIndexOfNonExistentValue) {
	int valueToFind = NonExistentValue;

	ASSERT_EQ(PVector<int>::IndexNotFound, v.indexOf(valueToFind));
}

TEST_F(Queries,
ReturnsFirstIndexMatchingValue) {
	int valueToFind = 3;
	int expectedIndex = 2;
	int actualIndex = v.indexOf(valueToFind);

	ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(Queries,
ReturnsFirstIndexMatchingValueSearchingFromIndex) {
	int valueToFind = 3;
	int indexToSearchFrom = 3;
	expectedIndex = 5;
	actualIndex = v.indexOf(valueToFind, indexToSearchFrom);

	ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(Queries,
ReturnsIndexNotFoundForLastIndexOfNonExistentValue) {
	int valueToFind = NonExistentValue;

	ASSERT_EQ(PVector<int>::IndexNotFound, v.lastIndexOf(valueToFind));
}

TEST_F(Queries,
ReturnsLastIndexMatchingValue) {
	int valueToFind = 3;
	expectedIndex = 5;
	actualIndex = v.lastIndexOf(valueToFind);

	ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(Queries,
ReturnsLastIndexMatchingValueSearchingFromIndex) {
	int valueToFind = 3;
	int indexToSearchFrom = 4;
	expectedIndex = 2;
	actualIndex = v.lastIndexOf(valueToFind, indexToSearchFrom);

	ASSERT_EQ(expectedIndex, actualIndex);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE


