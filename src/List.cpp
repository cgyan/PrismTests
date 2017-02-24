/*
 * List.cpp
 * v0.*
 *
 *  Created on: 24 Feb 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/Plist>
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
	using allocator_type = List::allocator_type;
	using value_type = List::value_type;
	using reference = List::reference;
	using const_reference = List::const_reference;
	using pointer = List::pointer;
	using const_pointer = List::const_pointer;
	using difference_type = List::difference_type;
	using size_type = List::size_type;
public:
	List list;
};

class ListInvariants : public ListTestBase {

};

TEST_F(ListInvariants,
IsEmptyWhenConstructed) {
	ASSERT_TRUE(list.empty());
}

TEST_F(ListInvariants,
HasSizeZeroWhenConstructed) {
	ASSERT_EQ(0, list.size());
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
	bool isNonConst = !std::is_const<reference>::value;
	bool isLValueReference = std::is_lvalue_reference<reference>::value;
	ASSERT_TRUE(isNonConst && isLValueReference);
}

TEST_F(ListPublicTypes,
HasLValueReferenceToConstValueType) {
	bool isConst = std::is_const<std::remove_reference<const_reference>::type>::value;
	bool isLValueReference = std::is_lvalue_reference<const_reference>::value;
	ASSERT_TRUE(isConst && isLValueReference);
}

TEST_F(ListPublicTypes,
HasPointerToValueType) {
	bool isNonConst = !std::is_const<std::remove_pointer<pointer>::type>::value;
	bool isPointer = std::is_pointer<pointer>::value;
	ASSERT_TRUE(isNonConst && isPointer);
}

TEST_F(ListPublicTypes,
HasPointerToConstValueType) {
	bool isConst = std::is_const<std::remove_pointer<const_pointer>::type>::value;
	bool isPointer = std::is_pointer<const_pointer>::value;
	ASSERT_TRUE(isConst && isPointer);
}

TEST_F(ListPublicTypes,
HasDifferenceType) {
	bool isSame = std::is_same<std::ptrdiff_t, difference_type>::value;
	ASSERT_TRUE(isSame);
}

TEST_F(ListPublicTypes, HasSizeType) {
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



PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
















