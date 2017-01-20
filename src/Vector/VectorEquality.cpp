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

class VectorEquality : public Test {
public:
	PVector<int> original;
	PVector<int> originalCopy;
	PVector<int> unequal;

	VectorEquality()
	: original({1,2,3,4,5}),
	  originalCopy(original),
	  unequal({6,7,8})
	{}
};

TEST_F(VectorEquality,
ReturnsTrueWhenTwoEmptyVectorsAreCompared) {
	ASSERT_EQ(PVector<int>(), PVector<int>());
}

TEST_F(VectorEquality,
ReturnsTrueWhenVectorsAreEqual) {
	ASSERT_TRUE(originalCopy == original);
}

TEST_F(VectorEquality,
ReturnsFalseWhenVectorsAreUnequal) {
	ASSERT_FALSE(unequal == original);
}

TEST_F(VectorEquality,
ReturnsTrueWhenVectorsAreUnequal) {
	ASSERT_TRUE(unequal != original);
}

TEST_F(VectorEquality,
ReturnsFalseWhenVectorsAreEqual) {
	ASSERT_FALSE(originalCopy != original);
}

class VectorLessThanComparision : public Test {
public:
	PVector<int> equalRange1;
	PVector<int> equalRange2;
	VectorLessThanComparision()
	: equalRange1({1,2,3,4,5,6}),
	  equalRange2(equalRange1)
	{}
};

TEST_F(VectorLessThanComparision,
ReturnsFalseWhenRangesAreEqual) {
	ASSERT_FALSE(equalRange1 < equalRange2);
}

PRISM_END_PRIVATE_NAMESPACE
PRISM_END_NAMESPACE


















