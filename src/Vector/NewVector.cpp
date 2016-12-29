/*
 * NewVector.cpp
 * v0.*
 *
 *  Created on: 23 Dec 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <list>
#include <prism/PVector>
#include <prism/global>

using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class NewVector : public Test {
public:
	PVector v_default;
	PVector v_size_value;

	NewVector()
	: v_default(),
	  v_size_value(3, 123)
	{}
};

TEST_F(NewVector,
VDefaultHasSizeZero) {
	ASSERT_EQ(0, v_default.size());
}

TEST_F(NewVector,
VDefaultHasCapacityZero) {
	ASSERT_EQ(0, v_default.capacity());
}

TEST_F(NewVector,
VDefaultIsEmpty) {
	ASSERT_TRUE(v_default.empty());
}

TEST_F(NewVector,
VSizeValueHasSizeThree) {
	ASSERT_EQ(3, v_size_value.size());
}

TEST_F(NewVector,
VSizeValueHasCapacityThree) {
	ASSERT_EQ(3, v_size_value.capacity());
}

TEST_F(NewVector,
VSizeValueIsNotEmpty) {
	ASSERT_FALSE(v_size_value.empty());
}

TEST_F(NewVector,
VSizeValueHasEachElementEqualToValue) {
	ASSERT_EQ(123, v_size_value.at(0));
	ASSERT_EQ(123, v_size_value.at(1));
	ASSERT_EQ(123, v_size_value.at(2));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










