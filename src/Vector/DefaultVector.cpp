/*
 * DefaultVector.cpp
 *
 *  Created on: 12 Dec 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/PVector>
#include <prism/OutOfBoundsException>
#include <prism/h/global.h>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class DefaultVector : public Test {
public:
	void SetUp() {
		ArbitraryValue = 10;
		InvalidNegativeSize = -1;
		PositiveSize = 5;
		SomeValueToFindInVector = 34;
	}

	PVector<int> v;
	int ArbitraryValue;
	int InvalidNegativeSize;
	int PositiveSize;
	int SomeValueToFindInVector;
};

TEST_F(DefaultVector,
IsEmptyOnConstruction) {
	ASSERT_TRUE(v.empty());
}

TEST_F(DefaultVector,
IsNotEmptyAfterElementAdded) {
	v.addAtEnd(ArbitraryValue);

	ASSERT_FALSE(v.empty());
}

TEST_F(DefaultVector,
HasSizeOfZero) {
	ASSERT_EQ(0, v.size());
}

TEST_F(DefaultVector,
HasSizeOfOneAfterSingleElementAdded) {
	v.addAtEnd(ArbitraryValue);

	ASSERT_EQ(1, v.size());
}

TEST_F(DefaultVector,
HasSizeOfThreeAfterAddingThreeElements) {
	v.addAtEnd(1);
	v.addAtEnd(2);
	v.addAtEnd(3);

	ASSERT_EQ(3, v.size());
}

TEST_F(DefaultVector,
HasSizeOfFiveWhenResizingToPositiveFive) {
	v.resize(5);

	ASSERT_EQ(5, v.size());
}

TEST_F(DefaultVector,
ThrowsWhenResizingToNegativeSize) {
	ASSERT_THROW(v.resize(InvalidNegativeSize), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
HasCapacityOfZero) {
	ASSERT_EQ(0, v.capacity());
}

TEST_F(DefaultVector,
HasCapacityOfTenAfterReservingMemoryForTenElements) {
	v.reserve(10);

	ASSERT_EQ(10, v.capacity());
}

TEST_F(DefaultVector,
ThrowsWhenReservingNegativeAmountOfMemory) {
	ASSERT_ANY_THROW(v.reserve(InvalidNegativeSize));
}

TEST_F(DefaultVector,
AnswersFalseWhenCheckingIfElementExists) {
	bool vectorContainsValue = v.contains(SomeValueToFindInVector);

	ASSERT_FALSE(vectorContainsValue);
}

TEST_F(DefaultVector,
AnswersZeroToNumberOfOccurrencesOfElement) {
	ASSERT_EQ(0, v.count(SomeValueToFindInVector));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










