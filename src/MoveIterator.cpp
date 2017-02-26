/*
 * MoveIterator.cpp
 * v0.*
 *
 *  Created on: 25 Feb 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/Iterator>
#include <prism/DynamicNumber>
#include <prism/Vector>
#include <ostream>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

using NumberType	= prism::test::DynamicNumber;
using SequenceIter	= prism::Vector<NumberType>::iterator;
using MoveIter 		= prism::MoveIterator<SequenceIter>;

class MoveIteratorTestBase : public Test {
public:
	Vector<NumberType> sequence {1,2,3,4,5,6};
	MoveIter mi{sequence.begin()};
	NumberType expected{};
	NumberType actual{};
	const int offset{4};
	MoveIter miEmpty;
	MoveIter miBegin{sequence.begin()};
	MoveIter miEnd{sequence.end()};
};

class MoveIteratorPublicTypes : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorPublicTypes,
HasIteratorType) {
	bool isSame = std::is_same<SequenceIter, typename MoveIter::iterator_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(MoveIteratorPublicTypes,
HasValueType) {
	bool isSame = std::is_same<NumberType, typename MoveIter::value_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(MoveIteratorPublicTypes,
HasPointerToBaseIterator) {
	bool isSame = std::is_same<SequenceIter, typename MoveIter::pointer>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(MoveIteratorPublicTypes,
HasRValueReferenceToValueType) {
	bool isRValueRef = std::is_rvalue_reference<typename MoveIter::reference>::value;
	bool IsRefToValueType = std::is_same<std::remove_reference<typename MoveIter::reference>::type, typename MoveIter::value_type>::value;
	ASSERT_TRUE(isRValueRef);
	ASSERT_TRUE(IsRefToValueType);
}

TEST_F(MoveIteratorPublicTypes,
HasDifferenceType) {
	bool isSame = std::is_same<std::ptrdiff_t, typename MoveIter::difference_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(MoveIteratorPublicTypes,
HasIteratorCategory) {
	bool isSame = std::is_same<SequenceIter::iterator_category, typename MoveIter::iterator_category>::value;
	ASSERT_TRUE(isSame);
}

class MoveIteratorBaseIterator : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorBaseIterator,
ReturnsDefaultBaseIteratorWhenNoneIsSet) {
	MoveIter nullIter;
	ASSERT_EQ(SequenceIter{}, nullIter.base());
}

TEST_F(MoveIteratorBaseIterator,
ReturnsBaseIterator) {
	SequenceIter si{sequence.begin()};
	ASSERT_EQ(si, mi.base());
}

class MoveIteratorOperators : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorOperators,
ReturnsRValueRefToValueTypeWhenDereferenced) {
	bool isRValueRef = std::is_rvalue_reference<decltype(*mi)>::value;
	expected = sequence[0];
	actual = *mi;
	ASSERT_TRUE(isRValueRef);
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorOperators,
ReturnsCopyOfBaseIteratorForAccessToMembers) {
	ASSERT_EQ(NumberType::DUMMY_CONSTANT_VALUE, mi->DUMMY_CONSTANT_VALUE);
}

TEST_F(MoveIteratorOperators,
PreIncrementsPositionByOne) {
	expected = sequence[1];
	actual = *++mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorOperators,
PostIncrementsPositionByOne) {
	NumberType expected1 = sequence[0];
	NumberType actual1 = *mi++;
	NumberType expected2 = sequence[1];
	NumberType actual2 = *mi;
	ASSERT_EQ(expected1, actual1);
	ASSERT_EQ(expected2, actual2);
}

TEST_F(MoveIteratorOperators,
PreDecrementsPositionByOne) {
	mi = MoveIter(sequence.end());
	expected = sequence[5];
	actual = *--mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorOperators,
PostDecrementsPositionByOne) {
	mi = MoveIter(--sequence.end());
	NumberType expected1 = sequence[5];
	NumberType actual1 = *mi--;
	NumberType expected2 = sequence[4];
	NumberType actual2 = *mi;
	ASSERT_EQ(expected1, actual1);
	ASSERT_EQ(expected2, actual2);
}

TEST_F(MoveIteratorOperators,
ReturnsCopyOfMoveIteratorIncrementedByOffset) {
	mi = MoveIter(sequence.begin()) + offset;
	expected = *(sequence.begin() + offset);
	actual = *mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorOperators,
ReturnsThisMoveIteratorIncrementedByOffset) {
	mi = MoveIter(sequence.begin()) += offset;
	expected = *(sequence.begin() + offset);
	actual = *mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorOperators,
ReturnsCopyOfMoveIteratorDecrementedByOffset) {
	mi = MoveIter(sequence.end()) - offset;
	expected = *(sequence.end() - offset);
	actual = *mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorOperators,
ReturnsThisMoveIteratorDecrementedByOffset) {
	expected = *(sequence.end() -= offset);
	actual = *(MoveIter(sequence.end()) -= offset);
	ASSERT_EQ(expected, actual);
}

class MoveIteratorEqualityComparison : public MoveIteratorTestBase {
public:
};

TEST_F(MoveIteratorEqualityComparison,
ReturnsTrueWhenEmptyItersAreCompared) {
	ASSERT_TRUE(miEmpty == miEmpty);
}

TEST_F(MoveIteratorEqualityComparison,
ReturnsTrueWhenEqual) {
	MoveIter copy = miBegin;
	ASSERT_TRUE(miBegin == copy);
}

TEST_F(MoveIteratorEqualityComparison,
ReturnsFalseWhenNotEqual) {
	ASSERT_FALSE(miBegin == miEnd);
}

class MoveIteratorInequalityComparison : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorInequalityComparison,
ReturnsFalseWhenComparingEmptyIters) {
	ASSERT_FALSE(miEmpty != miEmpty);
}

TEST_F(MoveIteratorInequalityComparison,
ReturnsFalseWhenEqual) {
	ASSERT_FALSE(miBegin != miBegin);
}

TEST_F(MoveIteratorInequalityComparison,
ReturnsTrueWhenNotEqual) {
	ASSERT_TRUE(miBegin != miEnd);
}

class MoveIteratorLessThanComparison : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorLessThanComparison,
ReturnsFalseWhenBothEmpty) {
	ASSERT_FALSE(miEmpty < miEmpty);
}

TEST_F(MoveIteratorLessThanComparison,
ReturnsFalseWhenBothEqual) {
	ASSERT_FALSE(miBegin < miBegin);
}

TEST_F(MoveIteratorLessThanComparison,
ReturnsTrueWhenLhsIsLess) {
	ASSERT_TRUE(miBegin < miEnd);
}

TEST_F(MoveIteratorLessThanComparison,
ReturnsFalseWhenLhsIsGreater) {
	MoveIter mi1{sequence.end()};
	MoveIter mi2{sequence.begin()};
	ASSERT_FALSE(miEnd < miBegin);
}

class MoveIteratorLessThanOrEqualComparison : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorLessThanOrEqualComparison,
ReturnsTrueWhenBothEmpty) {
	ASSERT_TRUE(miEmpty <= miEmpty);
}

TEST_F(MoveIteratorLessThanOrEqualComparison,
ReturnsTrueWhenBothEqual) {
	ASSERT_TRUE(miBegin <= miBegin);
}

TEST_F(MoveIteratorLessThanOrEqualComparison,
ReturnsTrueWhenBothLhsIsLess) {
	ASSERT_TRUE(miBegin <= miEnd);
}

TEST_F(MoveIteratorLessThanOrEqualComparison,
ReturnsFalseWhenBothLhsIsGreater) {
	ASSERT_FALSE(miEnd <= miBegin);
}

class MoveIteratorGreaterThanComparison : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorGreaterThanComparison,
ReturnsFalseWhenBothEmpty) {
	ASSERT_FALSE(miEmpty > miEmpty);
}

TEST_F(MoveIteratorGreaterThanComparison,
ReturnsFalseWhenBothEqual) {
	ASSERT_FALSE(miBegin > miEnd);
}

TEST_F(MoveIteratorGreaterThanComparison,
ReturnsFalseWhenBothLhsIsLess) {
	ASSERT_FALSE(miBegin > miEnd);
}

TEST_F(MoveIteratorGreaterThanComparison,
ReturnsTrueWhenBothLhsIsGreater) {
	ASSERT_TRUE(miEnd > miBegin);
}

class MoveIteratorGreaterThanOrEqualComparison : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorGreaterThanOrEqualComparison,
ReturnsTrueWhenBothEmpty) {
	ASSERT_TRUE(miEmpty >= miEmpty);
}

TEST_F(MoveIteratorGreaterThanOrEqualComparison,
ReturnsTrueWhenBothEqual) {
	ASSERT_TRUE(miBegin >= miBegin);
}

TEST_F(MoveIteratorGreaterThanOrEqualComparison,
ReturnsFalseWhenBothLhsIsLess) {
	ASSERT_FALSE(miBegin >= miEnd);
}

TEST_F(MoveIteratorGreaterThanOrEqualComparison,
ReturnsTrueWhenBothLhsIsGreater) {
	ASSERT_TRUE(miEnd >= miBegin);
}

class MoveIteratorMake : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorMake,
ReturnsMoveIterator) {
	mi = prism::make_move_iterator(sequence.begin());
	bool isSame = std::is_same<MoveIter, decltype(mi)>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(MoveIteratorMake,
MoveIteratorPointsToElement) {
	mi = prism::make_move_iterator(sequence.begin());
	NumberType expected = *sequence.begin();
	NumberType actual = *mi;
	ASSERT_EQ(expected, actual);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE















