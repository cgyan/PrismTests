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
	int singleValue;

	void SetUp() {
		numElements = 5;
		singleValue = 10;
	}
};

TEST_F(NewVector,
InitialisedWithFiveLotsOfValueOfTen) {
	PVector<int> v(numElements, singleValue);

	ASSERT_TRUE(10 == v.at(0));
	ASSERT_TRUE(10 == v.at(1));
	ASSERT_TRUE(10 == v.at(2));
	ASSERT_TRUE(10 == v.at(3));
	ASSERT_TRUE(10 == v.at(4));
}

TEST_F(NewVector,
InitialisedWithFiveLotsOfValueOfTenHasSizeOfFive) {
	PVector<int> v(numElements, singleValue);
	int expectedSize = 5;

	ASSERT_TRUE(expectedSize == v.size());
}

TEST_F(NewVector,
InitialisedWithValuesHasCapacityEqualToSize) {
	PVector<int> v(numElements, singleValue);
	int expectedCapacity = 5;

	ASSERT_TRUE(expectedCapacity == v.capacity());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










