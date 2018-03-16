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
#include <prism/Vector>

// #include "../../inc/prism/h/DynamicNumber.h"
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

using NumberType = int;
using Container = prism::Vector<NumberType>;

class AlgorithmTestBase : public Test {
public:
	Container original{1,2,3,4,5,6};
};

class AlgorithmMove : public AlgorithmTestBase
{};

TEST_F(AlgorithmMove,
DestinationRangeHasMovedElements) {
	Container destination(original.size());
	prism::move(original.cbegin(), original.cend(), destination.begin());

	const unsigned expectedSize = 6;
	ASSERT_EQ(expectedSize, destination.size());
	ASSERT_EQ(NumberType(1), destination[0]);
	ASSERT_EQ(NumberType(2), destination[1]);
	ASSERT_EQ(NumberType(3), destination[2]);
	ASSERT_EQ(NumberType(4), destination[3]);
	ASSERT_EQ(NumberType(5), destination[4]);
	ASSERT_EQ(NumberType(6), destination[5]);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
