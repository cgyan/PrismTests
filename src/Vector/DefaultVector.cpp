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

//=============================================================================
// DefaultVector is a test class that owns a vector with size and capacity of
// zero. It has just been instantiated and no actions have been performed on it.
//=============================================================================
class DefaultVector : public Test {
public:
	void SetUp() {
		ArbitraryValue = 10;
		PositiveSize = 5;
		SomeValueNotInVector = 34;
		IndexNotFound = -1;
	}

	PVector<int> v;
	int ArbitraryValue;
	int PositiveSize;
	int SomeValueNotInVector;
	int IndexNotFound;
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
HasSizeOfFiveWhenResizingToPositiveFive) {
	v.resize(5);

	ASSERT_EQ(5, v.size());
}

TEST_F(DefaultVector,
HasSizeOfThreeAfterAddingThreeElements) {
	v.addAtEnd(1);
	v.addAtEnd(2);
	v.addAtEnd(3);

	ASSERT_EQ(3, v.size());
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
AnswersFalseWhenCheckingIfElementExists) {
	bool vectorContainsValue = v.contains(SomeValueNotInVector);

	ASSERT_FALSE(vectorContainsValue);
}

TEST_F(DefaultVector,
AnswersCountOfZeroForNumberOfOccurrencesOfElement) {
	int numOcurrencesInVector = v.count(SomeValueNotInVector);
	ASSERT_EQ(0, numOcurrencesInVector);
}

TEST_F(DefaultVector,
AnswersFalseWhenAskedIfTheFirstElementEqualsSpecifiedValue) {
	ASSERT_FALSE(v.startsWith(ArbitraryValue));
}

TEST_F(DefaultVector,
AnswersFalseWhenAskedIfTheLastElementEqualsSpecifiedValue) {
	ASSERT_FALSE(v.endsWith(ArbitraryValue));
}

TEST_F(DefaultVector,
AnswersIndexNotFoundForFirstIndexOfValue) {
	ASSERT_EQ(IndexNotFound, v.indexOf(SomeValueNotInVector));
}

TEST_F(DefaultVector,
AnswersIndexNotFoundForLastIndexOfValue) {
	ASSERT_EQ(IndexNotFound, v.lastIndexOf(ArbitraryValue));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










