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

class VectorSizeFiveCapacityTen : public Test {
public:
	void SetUp() {
		setCapacityToTen();
		addElementsOneToFive();
	}

	void setCapacityToTen() {
		v.reserve(10);
	}

	void addElementsOneToFive() {
		v.addAtEnd(1);
		v.addAtEnd(2);
		v.addAtEnd(3);
		v.addAtEnd(4);
		v.addAtEnd(5);
	}

	PVector<int> v;
	static const int InvalidNegativeIndex = -1;
	static const int InvalidPositiveIndex = 5;
};

TEST_F(VectorSizeFiveCapacityTen,
AnswersWithElementAtSpecifiedIndex) {
	ASSERT_EQ(3, v.at(2));
}

TEST_F(VectorSizeFiveCapacityTen,
ModifiesElementAtSpecifiedIndexByReference) {
	v.at(2) = 10;

	ASSERT_EQ(10, v.at(2));
}

TEST_F(VectorSizeFiveCapacityTen,
ThrowsWhenAccessingNegativeIndex) {
	ASSERT_THROW(v.at(InvalidNegativeIndex), prism::OutOfBoundsException);
}

TEST_F(VectorSizeFiveCapacityTen,
ThrowsWhenAccessingIndexGreaterThanNumberOfElements) {
	ASSERT_THROW(v.at(InvalidPositiveIndex), prism::OutOfBoundsException);
}

TEST_F(VectorSizeFiveCapacityTen,
HasSizeOfFourAfterRemovingSingleElement) {
	v.removeLast();

	ASSERT_EQ(4, v.size());
}

TEST_F(VectorSizeFiveCapacityTen,
HasSizeOfZeroAfterRemovingAllElements) {
	v.clear();

	ASSERT_EQ(0, v.size());
}

TEST_F(VectorSizeFiveCapacityTen,
CapacityRemainsUnchangedAfterRemovingAllElements) {
	int capacityBeforeRemovals = v.capacity();

	v.clear();
	int capacityAfterRemovals = v.capacity();

	ASSERT_EQ(capacityBeforeRemovals, capacityAfterRemovals);
}

TEST_F(VectorSizeFiveCapacityTen,
IsNotEmptyWhenSizeIsNonZero) {
	ASSERT_FALSE(v.empty());
}

TEST_F(VectorSizeFiveCapacityTen,
IsEmptyWhenSizeIsZero) {
	v.clear();

	ASSERT_TRUE(v.empty());
}

TEST_F(VectorSizeFiveCapacityTen,
SetsEachElementEqualToSpecifiedValue) {
	int arbitraryValue = 23;

	v.fill(arbitraryValue);

	ASSERT_TRUE(arbitraryValue == v.at(0));
	ASSERT_TRUE(arbitraryValue == v.at(1));
	ASSERT_TRUE(arbitraryValue == v.at(2));
	ASSERT_TRUE(arbitraryValue == v.at(3));
	ASSERT_TRUE(arbitraryValue == v.at(4));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersTrueWhenCheckingIfValueOfOneExists) {
	ASSERT_TRUE(v.contains(1));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersTrueWhenCheckingIfValueOfTwoExists) {
	ASSERT_TRUE(v.contains(2));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersTrueWhenCheckingIfValueOfThreeExists) {
	ASSERT_TRUE(v.contains(3));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersTrueWhenCheckingIfValueOfFourExists) {
	ASSERT_TRUE(v.contains(4));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersTrueWhenCheckingIfValueOfFiveExists) {
	ASSERT_TRUE(v.contains(5));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersFalseWhenCheckingIfValueOfSixExists) {
	ASSERT_FALSE(v.contains(6));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfOne) {
	ASSERT_EQ(1, v.count(1));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfTwo) {
	ASSERT_EQ(1, v.count(2));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfThree) {
	ASSERT_EQ(1, v.count(3));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfFour) {
	ASSERT_EQ(1, v.count(4));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersCountOfOneForNumberOfOccurrencesOfValueOfFive) {
	ASSERT_EQ(1, v.count(5));
}

TEST_F(VectorSizeFiveCapacityTen,
AnswersCountOfTwoForNumberOfOccurrencesOfValueOfOne) {
	v.addAtEnd(1);
	int numOccurrencesOfValueOfOne = v.count(1);

	ASSERT_EQ(2, numOccurrencesOfValueOfOne);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE















