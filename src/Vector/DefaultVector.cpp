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
	}

	PVector<int> v;
	int ArbitraryValue;
	int InvalidNegativeSize;
	int PositiveSize;

};

TEST_F(DefaultVector,
IsEmptyOnConstruction) {
	ASSERT_TRUE(v.empty());
}

TEST_F(DefaultVector,
IsNotEmptyAfterElementAdded) {
	v.add(ArbitraryValue);

	ASSERT_FALSE(v.empty());
}

TEST_F(DefaultVector,
HasSizeOfZero) {
	ASSERT_EQ(0, v.size());
}

TEST_F(DefaultVector,
HasSizeOfOneAfterSingleElementAdded) {
	v.add(ArbitraryValue);

	ASSERT_EQ(1, v.size());
}

TEST_F(DefaultVector,
HasSizeOfThreeAfterAddingThreeElements) {
	v.add(1);
	v.add(2);
	v.add(3);

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
	v.reserve(5);

	ASSERT_EQ(5, v.capacity());
}

TEST_F(DefaultVector,
ThrowsWhenReservingNegativeAmountOfMemory) {
	ASSERT_ANY_THROW(v.reserve(InvalidNegativeSize));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










