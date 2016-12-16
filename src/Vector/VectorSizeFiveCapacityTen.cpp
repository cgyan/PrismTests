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
		v.add(1);
		v.add(2);
		v.add(3);
		v.add(4);
		v.add(5);
	}

	void removeAllElements() {
		for (int i=0; i<5; i++)
			v.removeLast();
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
	this->removeAllElements();

	ASSERT_EQ(0, v.size());
}

TEST_F(VectorSizeFiveCapacityTen,
CapacityRemainsUnchangedAfterRemovingAllElements) {
	int capacityBeforeRemovals = v.capacity();
	this->removeAllElements();

	ASSERT_EQ(capacityBeforeRemovals, v.capacity());
}

TEST_F(VectorSizeFiveCapacityTen,
IsNotEmptyWhenSizeIsNonZero) {
	ASSERT_FALSE(v.empty());
}

TEST_F(VectorSizeFiveCapacityTen,
IsEmptyWhenSizeIsZero) {
	this->removeAllElements();

	ASSERT_TRUE(v.empty());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE















