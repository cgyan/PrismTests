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

//=============================================================================
// NewVector is a fixture that tests the vector's various constructors
//=============================================================================
class NewVector : public Test {
public:
	int numElements;
	int value;

	void SetUp() {
		numElements = 5;
		value = 10;
	}
};

TEST_F(NewVector,
InitialisedWithFiveLotsOfValueOfTen) {
	PVector<int> v(numElements, value);

	ASSERT_TRUE(value == v.at(0));
	ASSERT_TRUE(value == v.at(1));
	ASSERT_TRUE(value == v.at(2));
	ASSERT_TRUE(value == v.at(3));
	ASSERT_TRUE(value == v.at(4));
}

TEST_F(NewVector,
InitialisedWithCountAmountOfValueHasSizeEqualToCount) {
	PVector<int> v(numElements, value);
	int expectedSize = 5;
	int actualSize = v.size();

	ASSERT_TRUE(expectedSize == actualSize);
}

TEST_F(NewVector,
InitialisedWithCountAmountOfValueHasCapacityEqualToSize) {
	PVector<int> v(numElements, value);
	int actualSize = v.size();
	int expectedCapacity = actualSize;

	ASSERT_TRUE(expectedCapacity == actualSize);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










