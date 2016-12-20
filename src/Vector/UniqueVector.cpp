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
// The vector contains the values: { 1, 2, 3, 4, 5 }
//=============================================================================
class UniqueVector : public Test {
public:
	UniqueVector()
	: 	InvalidNegativeIndex(-1),
		InvalidPositiveIndex(15),
		InvalidNegativeSize(-1),
		SomeValueNotInVector(8),
		IndexNotFound(-1),
		IndexZero(0),
		IndexOne(1),
		IndexTwo(2),
		IndexThree(3),
		IndexFour(4)
		{}

	void SetUp() {
		setCapacityToTen();
		addFiveElements_intsOneToFive();
	}

	void setCapacityToTen() {
		v.reserve(10);
	}

	void addFiveElements_intsOneToFive() {
		v.append(1);
		v.append(2);
		v.append(3);
		v.append(4);
		v.append(5);
	}

	PVector<int> v;
	int InvalidNegativeIndex;
	int InvalidPositiveIndex;
	int InvalidNegativeSize;
	int SomeValueNotInVector;
	int IndexNotFound;
	int IndexZero;
	int IndexOne;
	int IndexTwo ;
	int IndexThree;
	int IndexFour;
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
	ASSERT_EQ(3, v.at(IndexTwo));
}

TEST_F(UniqueVector,
ModifiesElementAtSpecifiedIndexByReference) {
	v.at(2) = 10;

	ASSERT_EQ(10, v.at(IndexTwo));
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

	ASSERT_TRUE(v.size() == 4);
}

TEST_F(UniqueVector,
HasSizeOfZeroAfterRemovingAllElements) {
	v.clear();

	ASSERT_TRUE(v.size() == 0);
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

	ASSERT_TRUE(arbitraryValue == v.at(IndexZero));
	ASSERT_TRUE(arbitraryValue == v.at(IndexOne));
	ASSERT_TRUE(arbitraryValue == v.at(IndexTwo));
	ASSERT_TRUE(arbitraryValue == v.at(IndexThree));
	ASSERT_TRUE(arbitraryValue == v.at(IndexFour));
}

TEST_F(UniqueVector,
AnswersTrueWhenCheckingIfValueOfOneExists) {
	int valueToFind = 1;
	ASSERT_TRUE(v.contains(valueToFind));
}

TEST_F(UniqueVector,
AnswersTrueWhenCheckingIfValueOfTwoExists) {
	int valueToFind = 2;
	ASSERT_TRUE(v.contains(valueToFind));
}

TEST_F(UniqueVector,
AnswersTrueWhenCheckingIfValueOfThreeExists) {
	int valueToFind = 3;
	ASSERT_TRUE(v.contains(valueToFind));
}

TEST_F(UniqueVector,
AnswersTrueWhenCheckingIfValueOfFourExists) {
	int valueToFind = 4;
	ASSERT_TRUE(v.contains(valueToFind));
}

TEST_F(UniqueVector,
AnswersTrueWhenCheckingIfValueOfFiveExists) {
	int valueToFind = 5;
	ASSERT_TRUE(v.contains(valueToFind));
}

TEST_F(UniqueVector,
AnswersFalseWhenCheckingIfNonExistentValueExists) {
	ASSERT_FALSE(v.contains(SomeValueNotInVector));
}

TEST_F(UniqueVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfOne) {
	ASSERT_TRUE(1 == v.count(1));
}

TEST_F(UniqueVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfTwo) {
	ASSERT_TRUE(1 == v.count(2));
}

TEST_F(UniqueVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfThree) {
	ASSERT_TRUE(1 == v.count(3));
}

TEST_F(UniqueVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfFour) {
	ASSERT_TRUE(1 ==v.count(4));
}

TEST_F(UniqueVector,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfFive) {
	ASSERT_TRUE(1 ==v.count(5));
}

TEST_F(UniqueVector,
AnswersCountOfTwoForNumberOfOccurrencesOfValueOfOneAfterAddingAnotherValueOfOne) {
	v.append(1);
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
AnswersFirstIndexOfValue) {
	ASSERT_EQ(IndexZero, v.indexOf(1));
	ASSERT_EQ(IndexOne, v.indexOf(2));
	ASSERT_EQ(IndexTwo, v.indexOf(3));
	ASSERT_EQ(IndexThree, v.indexOf(4));
	ASSERT_EQ(IndexFour, v.indexOf(5));
}

TEST_F(UniqueVector,
AnswersLastIndexOfValue) {
	ASSERT_EQ(IndexZero, v.lastIndexOf(1));
	ASSERT_EQ(IndexOne, v.lastIndexOf(2));
	ASSERT_EQ(IndexTwo, v.lastIndexOf(3));
	ASSERT_EQ(IndexThree, v.lastIndexOf(4));
	ASSERT_EQ(IndexFour, v.lastIndexOf(5));
}

TEST_F(UniqueVector,
AnswersFirstIndexNotFoundForNonExistentValue) {
	ASSERT_EQ(IndexNotFound, v.indexOf(SomeValueNotInVector));
}

TEST_F(UniqueVector,
AnswersLastIndexNotFoundForNonExistentValue) {
	ASSERT_EQ(IndexNotFound, v.lastIndexOf(SomeValueNotInVector));
}

TEST_F(UniqueVector,
IsEqualToVectorWithSameElementsInSameOrder) {
	PVector<int> other;
	other.append(1);
	other.append(2);
	other.append(3);
	other.append(4);
	other.append(5);

	ASSERT_TRUE(v == other);
}

TEST_F(UniqueVector,
IsNotEqualToVectorWithDifferentElements) {
	PVector<int> other;
	other.append(15);
	other.append(16);
	other.append(17);
	other.append(18);
	other.append(19);

	ASSERT_TRUE(v != other);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE















