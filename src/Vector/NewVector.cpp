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
	PVector v1;
	PVector v2;
	PVector v3;
	PVector v4;

	NewVector()
	: v1(),
	  v2(3, 123),
	  v3({1,2,3,4,5}),
	  v4(v3.data(), v3.data()+v3.size())
	{}
};

TEST_F(NewVector,
V1HasSizeZero) {
	ASSERT_EQ(0, v1.size());
}

TEST_F(NewVector,
V1HasCapacityZero) {
	ASSERT_EQ(0, v1.capacity());
}

TEST_F(NewVector,
V1IsEmpty) {
	ASSERT_TRUE(v1.empty());
}

TEST_F(NewVector,
V2HasSizeThree) {
	ASSERT_EQ(3, v2.size());
}

TEST_F(NewVector,
V2HasCapacityThree) {
	ASSERT_EQ(3, v2.capacity());
}

TEST_F(NewVector,
V2IsNotEmpty) {
	ASSERT_FALSE(v2.empty());
}

TEST_F(NewVector,
V2HasEachElementEqualToValue) {
	ASSERT_EQ(123, v2.at(0));
	ASSERT_EQ(123, v2.at(1));
	ASSERT_EQ(123, v2.at(2));
}

TEST_F(NewVector,
V3HasSizeFive) {
	ASSERT_EQ(5, v3.size());
}

TEST_F(NewVector,
V3HasCapacityFive) {
	ASSERT_EQ(5, v3.capacity());
}

TEST_F(NewVector,
V3HasElementsAtIndexs) {
	ASSERT_EQ(1, v3[0]);
	ASSERT_EQ(2, v3[1]);
	ASSERT_EQ(3, v3[2]);
	ASSERT_EQ(4, v3[3]);
	ASSERT_EQ(5, v3[4]);
}

TEST_F(NewVector,
V3IsNotEmpty) {
	ASSERT_FALSE(v3.empty());
}

TEST_F(NewVector,
V4HasSizeFive) {
	ASSERT_EQ(5, v4.size());
}

TEST_F(NewVector,
V4HasCapacityFive) {
	ASSERT_EQ(5, v4.capacity());
}

TEST_F(NewVector,
V4HasElementsAtIndexs) {
	ASSERT_EQ(1, v4[0]);
	ASSERT_EQ(2, v4[1]);
	ASSERT_EQ(3, v4[2]);
	ASSERT_EQ(4, v4[3]);
	ASSERT_EQ(5, v4[4]);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










