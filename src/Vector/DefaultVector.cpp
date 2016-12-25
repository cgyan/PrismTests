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
		ArbitraryValue = 500;
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
	v.append(ArbitraryValue);

	ASSERT_FALSE(v.empty());
}

TEST_F(DefaultVector,
HasSizeOfZero) {
	ASSERT_EQ(0, v.size());
}

TEST_F(DefaultVector,
HasSizeOfFiveWhenResizingToPositiveFive) {
	v.resize(5);

	ASSERT_EQ(5, v.size());
}

TEST_F(DefaultVector,
HasSizeOfThreeAfterAddingThreeElements) {
	v.append(1);
	v.append(2);
	v.append(3);
	int expectedSize = 3;
	int actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
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
	int expectedOccurrences = 0;
	int actualOcurrences = v.count(SomeValueNotInVector);

	ASSERT_EQ(expectedOccurrences, actualOcurrences);
}

TEST_F(DefaultVector,
AnswersFalseWhenAskedIfTheFirstElementEqualsValue) {
	ASSERT_FALSE(v.startsWith(ArbitraryValue));
}

TEST_F(DefaultVector,
AnswersFalseWhenAskedIfTheLastElementEqualsValue) {
	ASSERT_FALSE(v.endsWith(ArbitraryValue));
}

TEST_F(DefaultVector,
AnswersIndexNotFoundForFirstIndexOfValue) {
	ASSERT_EQ(IndexNotFound, v.indexOf(SomeValueNotInVector));
}

TEST_F(DefaultVector,
AnswersIndexNotFoundForLastIndexOfValue) {
	ASSERT_EQ(IndexNotFound, v.lastIndexOf(SomeValueNotInVector));
}

TEST_F(DefaultVector,
InsertsValueAtIndexZero) {
	int IndexZero = 0;
	v.insert(IndexZero, ArbitraryValue);

	ASSERT_TRUE(v.at(IndexZero) == ArbitraryValue);
}

TEST_F(DefaultVector,
HasSizeOfOneAfterSingleElementAdded) {
	v.append(ArbitraryValue);

	ASSERT_EQ(1, v.size());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










