/*
 * algorithm_test.cpp
 * v0.*
 *
 *  Created on: 28 Jan 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/algorithm>
#include <prism/PVector>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class algorithm_test : public Test {

};

TEST_F(algorithm_test,
MoveRange) {
	PVector<int> original = {1,2,3,4,5,6};
	PVector<int> destination(6);

	prism::move(original.cbegin(), original.cend(), destination.begin());

	ASSERT_EQ(6, destination.size());
	ASSERT_EQ(1, destination[0]);
	ASSERT_EQ(2, destination[1]);
	ASSERT_EQ(3, destination[2]);
	ASSERT_EQ(4, destination[3]);
	ASSERT_EQ(5, destination[4]);
	ASSERT_EQ(6, destination[5]);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE












