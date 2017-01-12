/*
 * NewVector.cpp
 * v0.*
 *
 *  Created on: 23 Dec 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/PVector>
#include <prism/global>

using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class NewVector : public Test {
public:
	PVector<int> defaultVector;
	PVector<int> fillVector;
	PVector<int> initializerListVector;
	PVector<int> rangeVector;
	PVector<int> copiedVector;
	PVector<int> copyAssignmentVector;

	NewVector()
	: defaultVector(),
	  fillVector(3, 123),
	  initializerListVector({1,2,3,4,5}),
	  rangeVector(initializerListVector.cbegin(), initializerListVector.cend()),
	  copiedVector(rangeVector),
	  copyAssignmentVector()
	{}
};

TEST_F(NewVector,
DefaultVectorHasSizeZero) {
	ASSERT_EQ(0, defaultVector.size());
}

TEST_F(NewVector,
DefaultVectorHasCapacityZero) {
	ASSERT_EQ(0, defaultVector.capacity());
}

TEST_F(NewVector,
DefaultVectorIsEmpty) {
	ASSERT_TRUE(defaultVector.empty());
}

TEST_F(NewVector,
FilledVectorHasSizeThree) {
	ASSERT_EQ(3, fillVector.size());
}

TEST_F(NewVector,
FilledVectorHasCapacityThree) {
	ASSERT_EQ(3, fillVector.capacity());
}

TEST_F(NewVector,
FilledVectorIsNotEmpty) {
	ASSERT_FALSE(fillVector.empty());
}

TEST_F(NewVector,
FilledVectorHasEachElementEqualToValue) {
	ASSERT_EQ(123, fillVector.at(0));
	ASSERT_EQ(123, fillVector.at(1));
	ASSERT_EQ(123, fillVector.at(2));
}

TEST_F(NewVector,
InitializerListVectorHasSizeFive) {
	ASSERT_EQ(5, initializerListVector.size());
}

TEST_F(NewVector,
InitializerListVectorHasCapacityFive) {
	ASSERT_EQ(5, initializerListVector.capacity());
}

TEST_F(NewVector,
InitializerListVectorHasElementsAtIndexs) {
	ASSERT_EQ(1, initializerListVector[0]);
	ASSERT_EQ(2, initializerListVector[1]);
	ASSERT_EQ(3, initializerListVector[2]);
	ASSERT_EQ(4, initializerListVector[3]);
	ASSERT_EQ(5, initializerListVector[4]);
}

TEST_F(NewVector,
InitializerListVectorIsNotEmpty) {
	ASSERT_FALSE(initializerListVector.empty());
}

TEST_F(NewVector,
RangeVectorHasSizeFive) {
	ASSERT_EQ(5, rangeVector.size());
}

TEST_F(NewVector,
RangeVectorHasCapacityFive) {
	ASSERT_EQ(5, rangeVector.capacity());
}

TEST_F(NewVector,
RangeVectorHasElementsAtIndexs) {
	ASSERT_EQ(1, rangeVector[0]);
	ASSERT_EQ(2, rangeVector[1]);
	ASSERT_EQ(3, rangeVector[2]);
	ASSERT_EQ(4, rangeVector[3]);
	ASSERT_EQ(5, rangeVector[4]);
}

TEST_F(NewVector,
CopyConstructedVectorHasSameSizeAsOriginalVector) {
	int expectedSize = 5;
	int actualSize = copiedVector.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(NewVector,
CopyConstructedVectorHasCapacityEqualToSize) {
	ASSERT_EQ(copiedVector.capacity(), copiedVector.size());
}

TEST_F(NewVector,
CopyConstructedVectorHasSameElementsAsOriginalVector) {
	ASSERT_EQ(rangeVector[0], copiedVector[0]);
	ASSERT_EQ(rangeVector[1], copiedVector[1]);
	ASSERT_EQ(rangeVector[2], copiedVector[2]);
	ASSERT_EQ(rangeVector[3], copiedVector[3]);
	ASSERT_EQ(rangeVector[4], copiedVector[4]);
}

TEST_F(NewVector,
CopyAssignedVectorHasSameSizeAsOriginalVector) {
	copyAssignmentVector = initializerListVector;
	int expectedSize = 5;
	int actualSize = copyAssignmentVector.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(NewVector,
CopyAssignedVectorHasCapacityEqualToOriginalVector) {
	copyAssignmentVector = initializerListVector;
	int expectedCapacity = initializerListVector.capacity();
	int actualCapacity = copyAssignmentVector.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(NewVector,
CopyAssignedVectorHasSameElementsAsOriginalVector) {
	copyAssignmentVector = initializerListVector;

	ASSERT_EQ(copyAssignmentVector[0], initializerListVector[0]);
	ASSERT_EQ(copyAssignmentVector[1], initializerListVector[1]);
	ASSERT_EQ(copyAssignmentVector[2], initializerListVector[2]);
	ASSERT_EQ(copyAssignmentVector[3], initializerListVector[3]);
	ASSERT_EQ(copyAssignmentVector[4], initializerListVector[4]);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










