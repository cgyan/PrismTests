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
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

using NumberType 		= prism::test::DynamicNumber;
using NumberTypePointer = NumberType*;
using BaseIterator 		= prism::SequenceIterator<NumberType, false>;
using MoveIterator 		= prism::MoveIterator<BaseIterator>;

class MoveIteratorTestBase : public Test {
public:
	using value_type 		= typename MoveIterator::value_type;
	using pointer 			= typename MoveIterator::pointer;
	using reference			= typename MoveIterator::reference;
	using difference_type	= typename MoveIterator::difference_type;
	using iterator_category	= typename MoveIterator::iterator_category;
	MoveIterator iterator;
};

class MoveIteratorPublicTypes : public MoveIteratorTestBase {

};

TEST_F(MoveIteratorPublicTypes,
HasValueType) {
	bool isSame = std::is_same<NumberType, value_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(MoveIteratorPublicTypes,
HasPointerToValueType) {
	bool isPointer = std::is_pointer<pointer>::value;
	bool isPointerToValueType = std::is_same<std::remove_pointer<pointer>::type, value_type>::value;
	ASSERT_TRUE(isPointer);
	ASSERT_TRUE(isPointerToValueType);
}

TEST_F(MoveIteratorPublicTypes,
HasRValueReferenceToValueType) {
	bool isRValueRef = std::is_rvalue_reference<reference>::value;
	bool IsRefToValueType = std::is_same<std::remove_reference<reference>::type, value_type>::value;
	ASSERT_TRUE(isRValueRef);
	ASSERT_TRUE(IsRefToValueType);
}

TEST_F(MoveIteratorPublicTypes,
HasDifferenceType) {
	bool isSame = std::is_same<std::ptrdiff_t, difference_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(MoveIteratorPublicTypes,
HasIteratorCategory) {
	bool isSame = std::is_same<BaseIterator::iterator_category, iterator_category>::value;
	ASSERT_TRUE(isSame);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE















