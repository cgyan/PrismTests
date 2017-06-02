/*
 * List.cpp
 * v0.*
 *
 *  Created on: 24 Feb 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/scratchpad>
#include <prism/Allocator>
#include <prism/LogAllocator>
#include <prism/DynamicNumber>
#include <type_traits>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

using namespace ::testing;
using NumberType = prism::test::DynamicNumber;
using List = prism::PList<NumberType, prism::Allocator<NumberType>>;

class ListTestBase : public Test {
public:
	using allocator_type 			= List::allocator_type;
	using value_type 				= List::value_type;
	using reference 				= List::reference;
	using const_reference 			= List::const_reference;
	using pointer 					= List::pointer;
	using const_pointer 			= List::const_pointer;
	using difference_type 			= List::difference_type;
	using size_type 				= List::size_type;
	using iterator 					= List::iterator;
	using const_iterator 			= List::const_iterator;
	using reverse_iterator 			= List::reverse_iterator;
	using const_reverse_iterator 	= List::const_reverse_iterator;
public:
	List emptyList;
};

class ListIterator : public ListTestBase {

};

TEST_F(ListIterator,
HasValueType) {
	bool isSame = std::is_same<NumberType, iterator::value_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListIterator,
HasLValueReferenceToValueType) {
	bool isLValueRef = std::is_lvalue_reference<iterator::reference>::value;
	ASSERT_TRUE(isLValueRef);
}

TEST_F(ListIterator,
ValueTypeThatReferenceRefersToIsNonConst) {
	bool isNonConst = !std::is_const<std::remove_reference<iterator::reference>::type>::value;
	ASSERT_TRUE(isNonConst);
}

TEST_F(ListIterator,
ValueTypeThatReferenceRefersToIsConst) {
	bool isConst = std::is_const<std::remove_reference<const_iterator::reference>::type>::value;
	ASSERT_TRUE(isConst);
}

TEST_F(ListIterator,
HasPointerToValueType) {
	bool isPointer = std::is_pointer<iterator::pointer>::value;
	ASSERT_TRUE(isPointer);
}

TEST_F(ListIterator,
ValueTypeThatPointerPointsToIsNonConst) {
	bool isNonConst = !std::is_const<std::remove_pointer<iterator::pointer>::type>::value;
	ASSERT_TRUE(isNonConst);
}

TEST_F(ListIterator,
ValueTypeThatPointerPointsToIsConst) {
	bool isConst = std::is_const<std::remove_pointer<const_iterator::pointer>::type>::value;
	ASSERT_TRUE(isConst);
}

TEST_F(ListIterator,
HasDifferenceType) {
	bool isSame = std::is_same<std::ptrdiff_t, iterator::difference_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListIterator,
HasIteratorCategory) {
	bool isSame = std::is_same<std::bidirectional_iterator_tag, iterator::iterator_category>::value;
	ASSERT_TRUE(isSame);
}

class ListPublicTypes : public ListTestBase {

};

TEST_F(ListPublicTypes,
HasValueType) {
	bool isSame = std::is_same<NumberType, value_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListPublicTypes,
HasLValueReferenceToValueType) {
	bool isLValueReference = std::is_lvalue_reference<reference>::value;
	ASSERT_TRUE(isLValueReference);
}

TEST_F(ListPublicTypes,
LValueReferenceToValueTypeIsNonConst) {
	bool isNonConst = !std::is_const<std::remove_reference<reference>::type>::value;
	ASSERT_TRUE(isNonConst);
}

TEST_F(ListPublicTypes,
LValueReferenceToConstValueTypeIsConst) {
	bool isConst = std::is_const<std::remove_reference<const_reference>::type>::value;
	ASSERT_TRUE(isConst);
}

TEST_F(ListPublicTypes,
HasLValueReferenceToConstValueType) {
	bool isLValueReference = std::is_lvalue_reference<const_reference>::value;
	ASSERT_TRUE(isLValueReference);
}

TEST_F(ListPublicTypes,
HasPointerToValueType) {
	bool isPointer = std::is_pointer<pointer>::value;
	ASSERT_TRUE(isPointer);
}

TEST_F(ListPublicTypes,
ValueTypeThatPointerPointsToIsNonConst) {
	bool isNonConst = !std::is_const<std::remove_pointer<pointer>::type>::value;
	ASSERT_TRUE(isNonConst);
}

TEST_F(ListPublicTypes,
HasPointerToConstValueType) {
	bool isPointer = std::is_pointer<const_pointer>::value;
	ASSERT_TRUE(isPointer);
}

TEST_F(ListPublicTypes,
ValueTypeThatPointerPointsToIsConst) {
	bool isConst = std::is_const<std::remove_pointer<const_pointer>::type>::value;
	ASSERT_TRUE(isConst);
}

TEST_F(ListPublicTypes,
HasDifferenceType) {
	bool isSame = std::is_same<std::ptrdiff_t, difference_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListPublicTypes,
HasSizeType) {
	bool isSame = std::is_same<std::size_t, size_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListPublicTypes,
DefaultListHasDefaultAllocatorType) {
	using DefaultAllocatorType = prism::Allocator<NumberType>;
	bool isSame = std::is_same<DefaultAllocatorType, allocator_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListPublicTypes,
HasCustomAllocatorType) {
	using CustomAllocatorType = prism::LogAllocator<NumberType>;
	using CustomAllocatorList = prism::PList<NumberType, CustomAllocatorType>;
	bool isSame = std::is_same<CustomAllocatorType, CustomAllocatorList::allocator_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListPublicTypes,
HasNonConstIteratorType) {
	bool isSame = std::is_same<prism::PListIterator<NumberType, false>, iterator>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListPublicTypes,
HasConstIteratorType) {
	bool isSame = std::is_same<prism::PListIterator<NumberType, true>, const_iterator>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListPublicTypes,
HasReverseIteratorType) {
	bool isSame = std::is_same<prism::ReverseIterator<iterator>, reverse_iterator>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListPublicTypes,
HasConstReverseIteratorType) {
	bool isSame = std::is_same<prism::ReverseIterator<const_iterator>, const_reverse_iterator>::value;
	ASSERT_TRUE(isSame);
}

class ListInvariants : public ListTestBase {

};

TEST_F(ListInvariants,
IsEmptyWhenConstructed) {
	ASSERT_TRUE(emptyList.empty());
}

TEST_F(ListInvariants,
IsNotEmptyAfterElementsAdded) {
	emptyList.resize(1);
	ASSERT_FALSE(emptyList.empty());
}

TEST_F(ListInvariants,
HasSizeZeroWhenConstructed) {
	ASSERT_EQ(0, emptyList.size());
}

class ListResizer : public ListTestBase {

};

TEST_F(ListResizer,
UpdatesEmptyListSizeToNewSize) {
	const int newSize{5};
	emptyList.resize(newSize);
	ASSERT_EQ(newSize, emptyList.size());
}

TEST_F(ListResizer,
AddsDefaultConstructedValueToEmptyList) {
	emptyList.resize(1);
	ASSERT_EQ(NumberType{}, emptyList.front());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
















