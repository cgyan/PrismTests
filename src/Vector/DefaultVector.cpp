/*
 * DefaultVector.cpp
 *
 *  Created on: 12 Dec 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/PVector>
#include <prism/OutOfBoundsException>
using namespace ::testing;
using namespace prism;

class DefaultVector : public Test {
public:
	PVector<int> v;
	int ArbitraryValue;
	int InvalidNegativeSize;
	int PositiveSize;

	DefaultVector()
	: ArbitraryValue(10),
	  InvalidNegativeSize(-1),
	  PositiveSize(5)
	{}
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
HasSizeZero) {
	ASSERT_EQ(0, v.size());
}

TEST_F(DefaultVector,
HasSizeOneAfterElementAdded) {
	v.append(ArbitraryValue);

	ASSERT_EQ(1, v.size());
}

TEST_F(DefaultVector,
HasNonZeroSizeWhenResizingToPositiveSize) {
	v.resize(PositiveSize);

	ASSERT_EQ(PositiveSize, v.size());
}

TEST_F(DefaultVector,
ThrowsWhenResizingToNegativeSize) {
	ASSERT_THROW(v.resize(InvalidNegativeSize), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
HasZeroCapacity) {
	ASSERT_EQ(0, v.capacity());
}

TEST_F(DefaultVector,
HasNonZeroCapacityAfterReservingMemory) {
	v.reserve(PositiveSize);

	ASSERT_EQ(PositiveSize, v.capacity());
}

TEST_F(DefaultVector,
ThrowsWhenReservingNegativeSizeOfMemory) {
	ASSERT_ANY_THROW(v.reserve(InvalidNegativeSize));
}












