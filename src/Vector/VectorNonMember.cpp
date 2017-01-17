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
	PVector<int> original;
	PVector<int> originalCopy;
	PVector<int> unequal;

	VectorNonMember()
	: original({1,2,3,4,5}),
	  originalCopy(original),
	  unequal({6,7,8})
	{}
};

TEST_F(VectorNonMember,
ReturnsTrueWhenTwoEmptyVectorsAreCompared) {
	ASSERT_EQ(PVector<int>(), PVector<int>());
}

TEST_F(VectorNonMember,
ReturnsTrueWhenVectorsAreEqual) {
	ASSERT_TRUE(originalCopy == original);
}

TEST_F(VectorNonMember,
ReturnsFalseWhenVectorsAreUnequal) {
	ASSERT_FALSE(unequal == original);
}

TEST_F(VectorNonMember,
ReturnsTrueWhenVectorsAreUnequal) {
	ASSERT_TRUE(unequal != original);
}

TEST_F(VectorNonMember,
ReturnsFalseWhenVectorsAreEqual) {
	ASSERT_FALSE(originalCopy != original);
}

PRISM_END_PRIVATE_NAMESPACE
PRISM_END_NAMESPACE


















