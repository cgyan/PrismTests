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
// #include <prism/DynamicNumber>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

using NumberType			= int;
using SequenceIter 			= prism::SequenceIterator<NumberType, false>;
using ConstSequenceIter 	= prism::SequenceIterator<NumberType, true>;
using MoveIter 				= prism::MoveIterator<SequenceIter>;

class IteratorTestBase : public Test {
public:
	NumberType sequence[6] = {1,2,3,4,5,6};
	NumberType expected{};
	NumberType actual{};
	const int offset{4};
};

class MoveIteratorTestBase : public IteratorTestBase {
public:
	MoveIter mi{sequence};
	MoveIter miEmpty;
	MoveIter miBegin{sequence};
	MoveIter miEnd{sequence + sizeof(sequence)};
};

class MoveIteratorPublicTypes : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorPublicTypes,
HasIteratorType) {
//	bool isSame = std::is_same<SequenceIter, typename MoveIter::iterator_type>::value;
//	ASSERT_TRUE(isSame);
	StaticAssertTypeEq<SequenceIter, typename MoveIter::iterator_type>();
}

TEST_F(MoveIteratorPublicTypes,
HasIteratorCategory) {
	bool isSame = std::is_same<SequenceIter::iterator_category,
			typename MoveIter::iterator_category>::value;
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

class MoveIteratorBaseIterator : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorBaseIterator,
ReturnsDefaultBaseIteratorWhenNoneIsSet) {
	MoveIter nullIter;
	ASSERT_EQ(SequenceIter{}, nullIter.base());
}

TEST_F(MoveIteratorBaseIterator,
ReturnsBaseIterator) {
	SequenceIter si{std::begin(sequence)};
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
//	ASSERT_EQ(NumberType::DUMMY_CONSTANT_VALUE, mi->DUMMY_CONSTANT_VALUE);
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
	mi = MoveIter(std::end(sequence));
	expected = sequence[5];
	actual = *--mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorOperators,
PostDecrementsPositionByOne) {
	mi = MoveIter(std::end(sequence) - 1);
	NumberType expected1 = sequence[5];
	NumberType actual1 = *mi--;
	NumberType expected2 = sequence[4];
	NumberType actual2 = *mi;
	ASSERT_EQ(expected1, actual1);
	ASSERT_EQ(expected2, actual2);
}

TEST_F(MoveIteratorOperators,
ReturnsCopyOfMoveIteratorIncrementedByOffset) {
	mi = MoveIter(std::begin(sequence)) + offset;
	expected = *(std::begin(sequence) + offset);
	actual = *mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorOperators,
ReturnsThisMoveIteratorIncrementedByOffset) {
	mi = MoveIter(std::begin(sequence)) += offset;
	expected = *(std::begin(sequence) + offset);
	actual = *mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorOperators,
ReturnsCopyOfMoveIteratorDecrementedByOffset) {
	mi = MoveIter(std::end(sequence)) - offset;
	expected = *(std::end(sequence) - offset);
	actual = *mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorOperators,
ReturnsThisMoveIteratorDecrementedByOffset) {
	expected = *(std::end(sequence) - offset);
	actual = *(MoveIter(std::end(sequence)) -= offset);
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
	MoveIter mi1{std::end(sequence)};
	MoveIter mi2{std::begin(sequence)};
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
	MoveIter mi = prism::make_move_iterator<SequenceIter>(std::begin(sequence));
	bool isSame = std::is_same<MoveIter, decltype(mi)>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(MoveIteratorMake,
MoveIteratorPointsToElement) {
	auto mi = prism::make_move_iterator<SequenceIter>(std::begin(sequence));
	expected = *std::begin(sequence);
	actual = *mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorMake,
MakeMoveIteratorFromPointer) {
	NumberType* p = sequence;
	auto mi = prism::make_move_iterator(p);
	expected = *sequence;
	actual = *mi;
	ASSERT_EQ(expected, actual);
}

TEST_F(MoveIteratorMake,
MakeMoveIteratorFromSequenceIterator) {
	SequenceIter it(sequence);
	auto mi = prism::make_move_iterator(it);
	expected = *sequence;
	actual = *mi;
	ASSERT_EQ(expected, actual);
}

class SequenceIteratorTestBase : public IteratorTestBase {
public:
	SequenceIter si{sequence};
	SequenceIter siBegin{sequence};
	SequenceIter siEnd{std::end(sequence)};
	SequenceIter siEmpty{};
	ConstSequenceIter csi{sequence};
};

class SequenceIteratorPublicTypes : public SequenceIteratorTestBase {

};

TEST_F(SequenceIteratorPublicTypes,
HasValueType) {
	bool isSame = std::is_same<NumberType, SequenceIter::value_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(SequenceIteratorPublicTypes,
HasReferenceToValueType) {
	bool isRefToValueType = std::is_lvalue_reference<SequenceIter::reference>::value &&
			std::is_same<NumberType, std::remove_reference<SequenceIter::reference>::type>::value;
	ASSERT_TRUE(isRefToValueType);
}

TEST_F(SequenceIteratorPublicTypes,
HasReferenceToConstValueType) {
	bool isRefToConstValueType = std::is_lvalue_reference<ConstSequenceIter::reference>::value &&
			std::is_same<const NumberType, std::remove_reference<ConstSequenceIter::reference>::type>::value &&
			std::is_const<std::remove_reference<ConstSequenceIter::reference>::type>::value;
	ASSERT_TRUE(isRefToConstValueType);
}

TEST_F(SequenceIteratorPublicTypes,
HasPointerToValueType) {
	bool isPointerToValueType = std::is_pointer<SequenceIter::pointer>::value &&
			std::is_same<NumberType, std::remove_pointer<SequenceIter::pointer>::type>::value;
	ASSERT_TRUE(isPointerToValueType);
}

TEST_F(SequenceIteratorPublicTypes,
HasPointerToConstValueType) {
	bool isPointerToConstValueType = std::is_pointer<ConstSequenceIter::pointer>::value &&
			std::is_same<const NumberType, std::remove_pointer<ConstSequenceIter::pointer>::type>::value &&
			std::is_const<std::remove_pointer<ConstSequenceIter::pointer>::type>::value;
	ASSERT_TRUE(isPointerToConstValueType);
}

TEST_F(SequenceIteratorPublicTypes,
HasDifferenceType) {
	bool HasDifferenceType = std::is_same<std::ptrdiff_t, SequenceIter::difference_type>::value;
	ASSERT_TRUE(HasDifferenceType);
}

TEST_F(SequenceIteratorPublicTypes,
HasIteratorCategory) {
	bool HasIteratorCategory = std::is_same<std::random_access_iterator_tag,
			SequenceIter::iterator_category>::value;
	ASSERT_TRUE(HasIteratorCategory);
}

class SequenceIteratorOperators : public SequenceIteratorTestBase {

};

TEST_F(SequenceIteratorOperators,
ReturnsLValueRefWhenDereferenced) {
	bool isLValueRef = std::is_lvalue_reference<decltype(*si)>::value;
	ASSERT_TRUE(isLValueRef);
}

TEST_F(SequenceIteratorOperators,
PreincrementPositionByOne) {
	expected = sequence[1];
	actual = *++si;
	ASSERT_EQ(expected, actual);
}

TEST_F(SequenceIteratorOperators,
PostincrementPositionByOne) {
	NumberType expected1 = sequence[0];
	NumberType actual1 = *si++;
	NumberType expected2 = sequence[1];
	NumberType actual2 = *si;
	ASSERT_EQ(expected1, actual1);
	ASSERT_EQ(expected2, actual2);
}

TEST_F(SequenceIteratorOperators,
PredecrementPositionByOne) {
	si = SequenceIter(std::end(sequence));
	expected = sequence[5];
	actual = *--si;
	ASSERT_EQ(expected, actual);
}

TEST_F(SequenceIteratorOperators,
PostdecrementPositionByOne) {
	si = SequenceIter(std::end(sequence) - 1);
	NumberType expected1 = sequence[5];
	NumberType actual1 = *si--;
	NumberType expected2 = sequence[4];
	NumberType actual2 = *si;
	ASSERT_EQ(expected1, actual1);
	ASSERT_EQ(expected2, actual2);
}

TEST_F(SequenceIteratorOperators,
ReturnThisIterIncrementedByOffset) {
	si += offset;
	expected = *(std::begin(sequence) + offset);
	actual = *si;
	ASSERT_EQ(expected, actual);
}

TEST_F(SequenceIteratorOperators,
ReturnThisIterDecrementedByOffset) {
	si = std::end(sequence);
	si -= offset;
	expected = *(std::end(sequence) - offset);
	actual = *si;
	ASSERT_EQ(expected, actual);
}

TEST_F(SequenceIteratorOperators,
ReturnNewIterIncrementedByOffset) {
	SequenceIter newIter = si + offset;
	expected = *(std::begin(sequence) + offset);
	actual = *newIter;
	ASSERT_EQ(SequenceIter(std::begin(sequence)), si);
	ASSERT_EQ(expected, actual);
}

TEST_F(SequenceIteratorOperators,
ReturnNewIterDecrementedByOffset) {
	si = SequenceIter(std::end(sequence));
	SequenceIter newIter = si - offset;
	expected = *(std::end(sequence) - offset);
	actual = *newIter;
	ASSERT_EQ(SequenceIter(std::end(sequence)), si);
	ASSERT_EQ(expected, actual);
}

TEST_F(SequenceIteratorOperators,
ReturnDistanceBetweenIters) {
	SequenceIter itBegin = SequenceIter(std::begin(sequence));
	SequenceIter itEnd = SequenceIter(std::end(sequence));
	typename SequenceIter::difference_type distance = itEnd - itBegin;
	const int numElementsInSequence = sizeof(sequence) / sizeof(sequence[0]);
	ASSERT_EQ(numElementsInSequence, distance);
}

class SequenceIteratorEqualityComparison : public SequenceIteratorTestBase {

};

TEST_F(SequenceIteratorEqualityComparison,
ReturnsTrueWhenBothEmpty) {
	ASSERT_TRUE(siEmpty == siEmpty);
}

TEST_F(SequenceIteratorEqualityComparison,
ReturnsFalseWhenLhsEmpty) {
	ASSERT_FALSE(siEmpty == siBegin);
}

TEST_F(SequenceIteratorEqualityComparison,
ReturnsFalseWhenRhsEmpty) {
	ASSERT_FALSE(siBegin == siEmpty);
}

TEST_F(SequenceIteratorEqualityComparison,
ReturnsTrueWhenBothEqual) {
	ASSERT_TRUE(siBegin == siBegin);
}

TEST_F(SequenceIteratorEqualityComparison,
ReturnsFalseWhenUnequal) {
	ASSERT_FALSE(siBegin == siEnd);
}

class SequenceIteratorInequalityComparison : public SequenceIteratorTestBase {

};

TEST_F(SequenceIteratorInequalityComparison,
ReturnsFalseWhenBothEmpty) {
	ASSERT_FALSE(siEmpty != siEmpty);
}

TEST_F(SequenceIteratorInequalityComparison,
ReturnsTrueWhenLhsEmpty) {
	ASSERT_TRUE(siEmpty != siBegin);
}

TEST_F(SequenceIteratorInequalityComparison,
ReturnsTrueWhenRhsEmpty) {
	ASSERT_TRUE(siBegin != siEmpty);
}

TEST_F(SequenceIteratorInequalityComparison,
ReturnsFalseWhenBothEqual) {
	ASSERT_FALSE(siBegin != siBegin);
}

TEST_F(SequenceIteratorInequalityComparison,
ReturnsTrueWhenUnequal) {
	ASSERT_TRUE(siBegin != siEnd);
}

class SequenceIteratorLessThanComparison : public SequenceIteratorTestBase {

};

TEST_F(SequenceIteratorLessThanComparison,
ReturnsFalseWhenBothEmpty) {
	ASSERT_FALSE(siEmpty < siEmpty);
}

TEST_F(SequenceIteratorLessThanComparison,
ReturnsTrueWhenLhsEmpty) {
	ASSERT_TRUE(siEmpty < siBegin);
}

TEST_F(SequenceIteratorLessThanComparison,
ReturnsFalseWhenRhsEmpty) {
	ASSERT_FALSE(siBegin < siEmpty);
}

TEST_F(SequenceIteratorLessThanComparison,
ReturnsFalseWhenEqual) {
	ASSERT_FALSE(siBegin < siBegin);
}

TEST_F(SequenceIteratorLessThanComparison,
ReturnsTrueWhenLhsIsLess) {
	ASSERT_TRUE(siBegin < siEnd);
}

TEST_F(SequenceIteratorLessThanComparison,
ReturnsFalseWhenLhsIsGreater) {
	ASSERT_FALSE(siEnd < siBegin);
}

class SequenceIteratorLessThanOrEqualComparison : public SequenceIteratorTestBase {

};

TEST_F(SequenceIteratorLessThanOrEqualComparison,
ReturnsTrueWhenBothEmpty) {
	ASSERT_TRUE(siEmpty <= siEmpty);
}

TEST_F(SequenceIteratorLessThanOrEqualComparison,
ReturnsTrueWhenLhsEmpty) {
	ASSERT_TRUE(siEmpty <= siBegin);
}

TEST_F(SequenceIteratorLessThanOrEqualComparison,
ReturnsFalseWhenRhsEmpty) {
	ASSERT_FALSE(siBegin <= siEmpty);
}

TEST_F(SequenceIteratorLessThanOrEqualComparison,
ReturnsTrueWhenEqual) {
	ASSERT_TRUE(siBegin <= siBegin);
}

TEST_F(SequenceIteratorLessThanOrEqualComparison,
ReturnsTrueWhenLhsIsLess) {
	ASSERT_TRUE(siBegin <= siEnd);
}

TEST_F(SequenceIteratorLessThanOrEqualComparison,
ReturnsFalseWhenLhsIsGreater) {
	ASSERT_FALSE(siEnd <= siBegin);
}

class SequenceIteratorGreaterThanComparison : public SequenceIteratorTestBase {

};

TEST_F(SequenceIteratorGreaterThanComparison,
ReturnsFalseWhenBothEmpty) {
	ASSERT_FALSE(siEmpty > siEmpty);
}

TEST_F(SequenceIteratorGreaterThanComparison,
ReturnsFalseWhenLhsEmpty) {
	ASSERT_FALSE(siEmpty > siBegin);
}

TEST_F(SequenceIteratorGreaterThanComparison,
ReturnsTrueWhenRhsEmpty) {
	ASSERT_TRUE(siBegin > siEmpty);
}

TEST_F(SequenceIteratorGreaterThanComparison,
ReturnsFalseWhenEqual) {
	ASSERT_FALSE(siBegin > siBegin);
}

TEST_F(SequenceIteratorGreaterThanComparison,
ReturnsFalseWhenLhsIsLess) {
	ASSERT_FALSE(siBegin > siEnd);
}

TEST_F(SequenceIteratorGreaterThanComparison,
ReturnsTrueWhenLhsIsGreater) {
	ASSERT_TRUE(siEnd > siBegin);
}

class SequenceIteratorGreaterThanOrEqualComparison : public SequenceIteratorTestBase {

};

TEST_F(SequenceIteratorGreaterThanOrEqualComparison,
ReturnsTrueWhenBothEmpty) {
	ASSERT_TRUE(siEmpty >= siEmpty);
}

TEST_F(SequenceIteratorGreaterThanOrEqualComparison,
ReturnsFalseWhenLhsEmpty) {
	ASSERT_FALSE(siEmpty >= siBegin);
}

TEST_F(SequenceIteratorGreaterThanOrEqualComparison,
ReturnsTrueWhenLhsEmpty) {
	ASSERT_TRUE(siBegin >= siEmpty);
}

TEST_F(SequenceIteratorGreaterThanOrEqualComparison,
ReturnsTrueWhenEqual) {
	ASSERT_TRUE(siBegin >= siBegin);
}

TEST_F(SequenceIteratorGreaterThanOrEqualComparison,
ReturnsFalseWhenLhsIsLess) {
	ASSERT_FALSE(siBegin >= siEnd);
}

TEST_F(SequenceIteratorGreaterThanOrEqualComparison,
ReturnsTrueWhenLhsIsGreater) {
	ASSERT_TRUE(siEnd >= siBegin);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
