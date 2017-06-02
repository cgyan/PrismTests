/*
 * Time.cpp
 * v0.*
 *
 *  Created on: 15 Mar 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/Time>

using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

struct TimeConstructions : public Test {

};

TEST_F(TimeConstructions, CanBeCopyConstructed) {
	Time original(12,34,56,789);
	Time copy = original;
	ASSERT_EQ(original, copy);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE


