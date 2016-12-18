/*
 * VectorSizeFiveCapacityTen.cpp
 * v0.*
 *
 *  Created on: 16 Dec 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/PVector>
#include <prism/h/global.h>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class PopulatedVector : public Test {
public:
	void SetUp() {
		setCapacityToTen();
		addFiveElements_intsOneToFive();
	}

	void setCapacityToTen() {
		v.reserve(10);
	}

	void addFiveElements_intsOneToFive() {
		v.addAtEnd(1);
		v.addAtEnd(2);
		v.addAtEnd(3);
		v.addAtEnd(4);
		v.addAtEnd(5);
	}

	PVector<int> v;
	static const int InvalidNegativeIndex = -1;
	static const int InvalidPositiveIndex = 15;
	static const int InvalidNegativeSize = -1;
};

TEST_F(PopulatedVector,
IsEmptyWhenSizeIsZero) {
	v.clear();

	ASSERT_TRUE(v.empty());
}

TEST_F(PopulatedVector,
IsNotEmptyWhenSizeIsNonZero) {
	ASSERT_FALSE(v.empty());
}

TEST_F(PopulatedVector,
AnswersWithElementAtSpecifiedIndex) {
	ASSERT_EQ(3, v.at(2));
}

TEST_F(PopulatedVector,
ModifiesElementAtSpecifiedIndexByReference) {
	v.at(2) = 10;

	ASSERT_EQ(10, v.at(2));
}

TEST_F(PopulatedVector,
ThrowsWhenAccessingNegativeIndex) {
	ASSERT_THROW(v.at(InvalidNegativeIndex), prism::OutOfBoundsException);
}

TEST_F(PopulatedVector,
ThrowsWhenAccessingIndexGreaterThanNumberOfElements) {
	ASSERT_THROW(v.at(InvalidPositiveIndex), prism::OutOfBoundsException);
}

TEST_F(PopulatedVector,
ThrowsWhenResizingToNegativeSize) {
	ASSERT_THROW(v.resize(InvalidNegativeSize), prism::OutOfBoundsException);
}

TEST_F(PopulatedVector,
ThrowsWhenReservingNegativeAmountOfMemory) {
	ASSERT_ANY_THROW(v.reserve(InvalidNegativeSize));
}

TEST_F(PopulatedVector,
HasSizeOfFourAfterRemovingSingleElement) {
	v.removeLast();

	ASSERT_EQ(4, v.size());
}

TEST_F(PopulatedVector,
HasSizeOfZeroAfterRemovingAllElements) {
	v.clear();

	ASSERT_EQ(0, v.size());
}

TEST_F(PopulatedVector,
CapacityRemainsUnchangedAfterRemovingAllElements) {
	int capacityBeforeRemovals = v.capacity();

	v.clear();
	int capacityAfterRemovals = v.capacity();

	ASSERT_EQ(capacityBeforeRemovals, capacityAfterRemovals);
}

TEST_F(PopulatedVector,
CapacityRemainsUnchangedWhenTryingToReserveZeroMemory) {
	int capacityBeforeReserve = v.capacity();
	v.reserve(0);
	int capacityAfterReserve = v.capacity();

	ASSERT_EQ(capacityBeforeReserve, capacityAfterReserve);
}

TEST_F(PopulatedVector,
SetsEachElementEqualToSpecifiedValue) {
	int arbitraryValue = 23;

	v.fill(arbitraryValue);

	ASSERT_TRUE(arbitraryValue == v.at(0));
	ASSERT_TRUE(arbitraryValue == v.at(1));
	ASSERT_TRUE(arbitraryValue == v.at(2));
	ASSERT_TRUE(arbitraryValue == v.at(3));
	ASSERT_TRUE(arbitraryValue == v.at(4));
}

TEST_F(PopulatedVector,
AnswersTrueWhenCheckingIfValueOfOneExists) {
	ASSERT_TRUE(v.contains(1));
}

TEST_F(PopulatedVector,
AnswersTrueWhenCheckingIfValueOfTwoExists) {
	ASSERT_TRUE(v.contains(2));
}

TEST_F(PopulatedVector,
AnswersTrueWhenCheckingIfValueOfThreeExists) {
	ASSERT_TRUE(v.contains(3));
}

TEST_F(PopulatedVector,
AnswersTrueWhenCheckingIfValueOfFourExists) {
	ASSERT_TRUE(v.contains(4));
}

TEST_F(PopulatedVector,
AnswersTrueWhenCheckingIfValueOfFiveExists) {
	ASSERT_TRUE(v.contains(5));
}

TEST_F(PopulatedVector,
AnswersFalseWhenCheckingIfValueOfSixExists) {
	ASSERT_FALSE(v.contains(6));
}

TEST_F(PopulatedVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfOne) {
	ASSERT_EQ(1, v.count(1));
}

TEST_F(PopulatedVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfTwo) {
	ASSERT_EQ(1, v.count(2));
}

TEST_F(PopulatedVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfThree) {
	ASSERT_EQ(1, v.count(3));
}

TEST_F(PopulatedVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfFour) {
	ASSERT_EQ(1, v.count(4));
}

TEST_F(PopulatedVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfFive) {
	ASSERT_EQ(1, v.count(5));
}

TEST_F(PopulatedVector,
AnswersCountOfTwoForNumberOfOccurrencesOfValueOfOneAfterAddingAnotherValueOfOne) {
	v.addAtEnd(1);
	int numOccurrencesOfValueOfOne = v.count(1);

	ASSERT_EQ(2, numOccurrencesOfValueOfOne);
}

TEST_F(PopulatedVector,
AnswersTrueIfTheLastElementEqualsFive) {
	bool lastElementEqualsFive = v.endsWith(5);

	ASSERT_TRUE(lastElementEqualsFive);
}

TEST_F(PopulatedVector,
AnswersFalseIfTheLastElementDoesNotEqualFive) {
	bool lastElementEqualsOne = v.endsWith(1);

	ASSERT_FALSE(lastElementEqualsOne);
}

TEST_F(PopulatedVector,
AnswersTrueIfTheFirstElementEqualsOne) {
	bool firstElementEqualsOne = v.startsWith(1);

	ASSERT_TRUE(firstElementEqualsOne);
}

TEST_F(PopulatedVector,
AnswersFalseIfTheFirstElementDoesNotEqualOne) {
	bool firstElementEqualsFive = v.startsWith(5);

	ASSERT_FALSE(firstElementEqualsFive);
}

TEST_F(PopulatedVector,
AnswersZeroWhenSearchingForTheFirstIndexContainingTheValueOfOne) {
	int firstIndexContainingValueOfOne = v.indexOf(1);

	ASSERT_EQ(0, firstIndexContainingValueOfOne);
}

TEST_F(PopulatedVector,
AnswersOneWhenSearchingForTheFirstIndexContainingTheValueOfTwo) {
	int firstIndexContainingValueOfTwo = v.indexOf(2);

	ASSERT_EQ(1, firstIndexContainingValueOfTwo);
}

TEST_F(PopulatedVector,
AnswersTwoWhenSearchingForTheFirstIndexContainingTheValueOfThree) {
	int firstIndexContainingValueOfThree = v.indexOf(3);

	ASSERT_EQ(2, firstIndexContainingValueOfThree);
}

TEST_F(PopulatedVector,
AnswersThreeWhenSearchingForTheFirstIndexContainingTheValueOfFour) {
	int firstIndexContainingValueOfFour = v.indexOf(4);

	ASSERT_EQ(3, firstIndexContainingValueOfFour);
}

TEST_F(PopulatedVector,
AnswersFourWhenSearchingForTheFirstIndexContainingTheValueOfFive) {
	int firstIndexContainingValueOfFive = v.indexOf(5);

	ASSERT_EQ(4, firstIndexContainingValueOfFive);
}

TEST_F(PopulatedVector,
AnswersIndexZeroWhenSearchingForLastValueOfOne) {
	int lastIndexThatContainsValueOfOne = 0;

	ASSERT_EQ(lastIndexThatContainsValueOfOne, v.lastIndexOf(1));
}

TEST_F(PopulatedVector,
AnswersIndexOneWhenSearchingForLastValueOfTwo) {
	int lastIndexThatContainsValueOfTwo = 1;

	ASSERT_EQ(lastIndexThatContainsValueOfTwo, v.lastIndexOf(2));
}

TEST_F(PopulatedVector,
AnswersIndexTwoWhenSearchingForLastValueOfThree) {
	int lastIndexThatContainsValueOfThree = 2;

	ASSERT_EQ(lastIndexThatContainsValueOfThree, v.lastIndexOf(3));
}

TEST_F(PopulatedVector,
AnswersIndexThreeWhenSearchingForLastValueOfFour) {
	int lastIndexThatContainsValueOfFour = 3;

	ASSERT_EQ(lastIndexThatContainsValueOfFour, v.lastIndexOf(4));
}

TEST_F(PopulatedVector,
AnswersIndexFourWhenSearchingForLastValueOfFive) {
	int lastIndexThatContainsValueOfFive = 4;

	ASSERT_EQ(lastIndexThatContainsValueOfFive, v.lastIndexOf(5));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE















