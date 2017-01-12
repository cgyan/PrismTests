/*
 * NonMember.cpp
 * v0.*
 *
 *  Created on: 8 Jan 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/PVector>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class VectorNonMember : public Test {
public:
	PVector<int> v;

	VectorNonMember()
	: v({1,2,3,4,5})
	{}
};

TEST_F(VectorNonMember,
ReturnsTrueWhenTwoEmptyVectorsAreComparedForEquality) {
	PVector<int> emptyvec1;
	PVector<int> emptyvec2;

	ASSERT_EQ(emptyvec1, emptyvec2);
}

TEST_F(VectorNonMember,
ReturnsTrueWhenVectorsAreEqual) {
	PVector<int> otherVec({1,2,3,4,5});

	ASSERT_TRUE(otherVec == v);
}

TEST_F(VectorNonMember,
ReturnsFalseWhenVectorsAreUnequal) {
	PVector<int> otherVec({1,2,3});

	ASSERT_FALSE(otherVec == v);
}

TEST_F(VectorNonMember,
ReturnsTrueWhenVectorsAreUnequal) {
	PVector<int> otherVec({1,2,3});

	ASSERT_TRUE(otherVec != v);
}

TEST_F(VectorNonMember,
ReturnsFalseWhenVectorsAreEqual) {
	PVector<int> otherVec({1,2,3,4,5});

	ASSERT_FALSE(otherVec != v);
}

PRISM_END_PRIVATE_NAMESPACE
PRISM_END_NAMESPACE


















