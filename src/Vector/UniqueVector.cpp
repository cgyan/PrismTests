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

//=============================================================================
// UniqueVector is a test vector that contains unique elements
// (i.e. no duplicates)
//=============================================================================
class UniqueVector : public Test {
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

TEST_F(UniqueVector,
IsEmptyWhenSizeIsZero) {
	v.clear();

	ASSERT_TRUE(v.empty());
}

TEST_F(UniqueVector,
IsNotEmptyWhenSizeIsNonZero) {
	ASSERT_FALSE(v.empty());
}

TEST_F(UniqueVector,
AnswersWithElementAtSpecifiedIndex) {
	ASSERT_EQ(3, v.at(2));
}

TEST_F(UniqueVector,
ModifiesElementAtSpecifiedIndexByReference) {
	v.at(2) = 10;

	ASSERT_EQ(10, v.at(2));
}

TEST_F(UniqueVector,
ThrowsWhenAccessingNegativeIndex) {
	ASSERT_THROW(v.at(InvalidNegativeIndex), prism::OutOfBoundsException);
}

TEST_F(UniqueVector,
ThrowsWhenAccessingIndexGreaterThanNumberOfElements) {
	ASSERT_THROW(v.at(InvalidPositiveIndex), prism::OutOfBoundsException);
}

TEST_F(UniqueVector,
ThrowsWhenResizingToNegativeSize) {
	ASSERT_THROW(v.resize(InvalidNegativeSize), prism::OutOfBoundsException);
}

TEST_F(UniqueVector,
ThrowsWhenReservingNegativeAmountOfMemory) {
	ASSERT_ANY_THROW(v.reserve(InvalidNegativeSize));
}

TEST_F(UniqueVector,
HasSizeOfFourAfterRemovingSingleElement) {
	v.removeLast();

	ASSERT_EQ(4, v.size());
}

TEST_F(UniqueVector,
HasSizeOfZeroAfterRemovingAllElements) {
	v.clear();

	ASSERT_EQ(0, v.size());
}

TEST_F(UniqueVector,
CapacityRemainsUnchangedAfterRemovingAllElements) {
	int capacityBeforeRemovals = v.capacity();

	v.clear();
	int capacityAfterRemovals = v.capacity();

	ASSERT_EQ(capacityBeforeRemovals, capacityAfterRemovals);
}

TEST_F(UniqueVector,
CapacityRemainsUnchangedWhenTryingToReserveZeroMemory) {
	int capacityBeforeReserve = v.capacity();
	v.reserve(0);
	int capacityAfterReserve = v.capacity();

	ASSERT_EQ(capacityBeforeReserve, capacityAfterReserve);
}

TEST_F(UniqueVector,
SetsEachElementEqualToSpecifiedValue) {
	int arbitraryValue = 23;

	v.fill(arbitraryValue);

	ASSERT_TRUE(arbitraryValue == v.at(0));
	ASSERT_TRUE(arbitraryValue == v.at(1));
	ASSERT_TRUE(arbitraryValue == v.at(2));
	ASSERT_TRUE(arbitraryValue == v.at(3));
	ASSERT_TRUE(arbitraryValue == v.at(4));
}

TEST_F(UniqueVector,
AnswersTrueWhenCheckingIfValueOfOneExists) {
	ASSERT_TRUE(v.contains(1));
}

TEST_F(UniqueVector,
AnswersTrueWhenCheckingIfValueOfTwoExists) {
	ASSERT_TRUE(v.contains(2));
}

TEST_F(UniqueVector,
AnswersTrueWhenCheckingIfValueOfThreeExists) {
	ASSERT_TRUE(v.contains(3));
}

TEST_F(UniqueVector,
AnswersTrueWhenCheckingIfValueOfFourExists) {
	ASSERT_TRUE(v.contains(4));
}

TEST_F(UniqueVector,
AnswersTrueWhenCheckingIfValueOfFiveExists) {
	ASSERT_TRUE(v.contains(5));
}

TEST_F(UniqueVector,
AnswersFalseWhenCheckingIfValueOfSixExists) {
	ASSERT_FALSE(v.contains(6));
}

TEST_F(UniqueVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfOne) {
	ASSERT_EQ(1, v.count(1));
}

TEST_F(UniqueVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfTwo) {
	ASSERT_EQ(1, v.count(2));
}

TEST_F(UniqueVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfThree) {
	ASSERT_EQ(1, v.count(3));
}

TEST_F(UniqueVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfFour) {
	ASSERT_EQ(1, v.count(4));
}

TEST_F(UniqueVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfFive) {
	ASSERT_EQ(1, v.count(5));
}

TEST_F(UniqueVector,
AnswersCountOfTwoForNumberOfOccurrencesOfValueOfOneAfterAddingAnotherValueOfOne) {
	v.addAtEnd(1);
	int numOccurrencesOfValueOfOne = v.count(1);

	ASSERT_EQ(2, numOccurrencesOfValueOfOne);
}

TEST_F(UniqueVector,
AnswersTrueIfTheLastElementEqualsFive) {
	bool lastElementEqualsFive = v.endsWith(5);

	ASSERT_TRUE(lastElementEqualsFive);
}

TEST_F(UniqueVector,
AnswersFalseIfTheLastElementDoesNotEqualFive) {
	bool lastElementEqualsOne = v.endsWith(1);

	ASSERT_FALSE(lastElementEqualsOne);
}

TEST_F(UniqueVector,
AnswersTrueIfTheFirstElementEqualsOne) {
	bool firstElementEqualsOne = v.startsWith(1);

	ASSERT_TRUE(firstElementEqualsOne);
}

TEST_F(UniqueVector,
AnswersFalseIfTheFirstElementDoesNotEqualOne) {
	bool firstElementEqualsFive = v.startsWith(5);

	ASSERT_FALSE(firstElementEqualsFive);
}

TEST_F(UniqueVector,
AnswersIndexZeroWhenSearchingForwardFromIndexZeroForValueOfOne) {
	int indexZero = 0;
	int valueToFind = 1;
	int returnedIndex = v.indexOf(valueToFind);

	ASSERT_EQ(indexZero, returnedIndex);
}

TEST_F(UniqueVector,
AnswersIndexOneWhenSearchingForwardFromIndexZeroForValueOfTwo) {
	int indexZero = 0;
	int valueToFind = 1;
	int returnedIndex = v.indexOf(valueToFind);

	ASSERT_EQ(indexZero, returnedIndex);
}

TEST_F(UniqueVector,
AnswersIndexTwoWhenSearchingForwardFromIndexZeroForValueOfThree) {
	int indexZero = 0;
	int valueToFind = 1;
	int returnedIndex = v.indexOf(valueToFind);

	ASSERT_EQ(indexZero, returnedIndex);
}

TEST_F(UniqueVector,
AnswersIndexThreeWhenSearchingForwardFromIndexZeroForValueOfFour) {
	int indexZero = 0;
	int valueToFind = 1;
	int returnedIndex = v.indexOf(valueToFind);

	ASSERT_EQ(indexZero, returnedIndex);
}

TEST_F(UniqueVector,
AnswersIndexFourWhenSearchingForwardFromIndexZeroForValueOfFive) {
	int indexZero = 0;
	int valueToFind = 1;
	int returnedIndex = v.indexOf(valueToFind);

	ASSERT_EQ(indexZero, returnedIndex);
}

TEST_F(UniqueVector,
AnswersIndexZeroWhenSearchingForLastValueOfOne) {
	int lastIndexThatContainsValueOfOne = 0;

	ASSERT_EQ(lastIndexThatContainsValueOfOne, v.lastIndexOf(1));
}

TEST_F(UniqueVector,
AnswersIndexOneWhenSearchingForLastValueOfTwo) {
	int lastIndexThatContainsValueOfTwo = 1;

	ASSERT_EQ(lastIndexThatContainsValueOfTwo, v.lastIndexOf(2));
}

TEST_F(UniqueVector,
AnswersIndexTwoWhenSearchingForLastValueOfThree) {
	int lastIndexThatContainsValueOfThree = 2;

	ASSERT_EQ(lastIndexThatContainsValueOfThree, v.lastIndexOf(3));
}

TEST_F(UniqueVector,
AnswersIndexThreeWhenSearchingForLastValueOfFour) {
	int lastIndexThatContainsValueOfFour = 3;

	ASSERT_EQ(lastIndexThatContainsValueOfFour, v.lastIndexOf(4));
}

TEST_F(UniqueVector,
AnswersIndexFourWhenSearchingForLastValueOfFive) {
	int lastIndexThatContainsValueOfFive = 4;

	ASSERT_EQ(lastIndexThatContainsValueOfFive, v.lastIndexOf(5));
}

TEST_F(UniqueVector,
AnswersIndexNotFoundWhenSearchingForwardFromIndexZeroForElementNotFound) {
	int indexNotFound = -1;
	int valueNotInVector = 50;

	ASSERT_EQ(indexNotFound, v.indexOf(valueNotInVector));
}

TEST_F(UniqueVector,
AnswersIndexNotFoundWhenSearchingBackwardFromIndexFourForElementNotFound) {
	int indexNotFound = -1;
	int valueNotInVector = 50;

	ASSERT_EQ(indexNotFound, v.lastIndexOf(valueNotInVector));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE















