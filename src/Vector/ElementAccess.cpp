/*
 * ConstVector.cpp
 * v0.*
 *
 *  Created on: 7 Jan 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/PVector>
#include <prism/type_traits>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class ElementAccess : public Test {
public:
	PVector<int> v;
	const PVector<int> cv;

	enum {
		InvalidNegativeIndex = -1,
		InvalidPositiveIndex = 15
	};

	ElementAccess()
	: v({1,2,3,4,5}),
	  cv({1,2,3,4,5})
	{}
};

TEST_F(ElementAccess,
DataIsNotNullAfterInsert) {
	ASSERT_FALSE(v.data() == nullptr);
	ASSERT_FALSE(v.cdata() == nullptr);
	ASSERT_FALSE(cv.data() == nullptr);
}

TEST_F(ElementAccess,
ReturnsPointerToNonConstData) {
	using Type = decltype(v.data());

	ASSERT_TRUE(std::is_pointer<Type>::value);
	ASSERT_FALSE(std::is_const<typename std::remove_pointer<Type>::type>::value);
}

TEST_F(ElementAccess,
ReturnsPointerToConstData) {
	using ImplicitConstType = decltype(cv.data());
	using ExplicitConstType = decltype(cv.cdata());

	ASSERT_TRUE(std::is_pointer<ImplicitConstType>::value);
	ASSERT_TRUE(std::is_pointer<ExplicitConstType>::value);

	ASSERT_TRUE(std::is_const<typename std::remove_pointer<ImplicitConstType>::type>::value);
	ASSERT_TRUE(std::is_const<typename std::remove_pointer<ExplicitConstType>::type>::value);

}

TEST_F(ElementAccess,
ThrowsWhenAccessingNegativeIndex) {
	ASSERT_THROW(v.at(InvalidNegativeIndex), prism::OutOfBoundsException);
}

TEST_F(ElementAccess,
ThrowsWhenAccessingInvalidPositiveIndex) {
	ASSERT_THROW(v.at(InvalidPositiveIndex), prism::OutOfBoundsException);
}

TEST_F(ElementAccess,
ReturnsValuesAtIndex) {
	ASSERT_EQ(1, v.at(0));
	ASSERT_EQ(2, v.at(1));
	ASSERT_EQ(3, v.at(2));
	ASSERT_EQ(4, v.at(3));
	ASSERT_EQ(5, v.at(4));

	ASSERT_EQ(1, v[0]);
	ASSERT_EQ(2, v[1]);
	ASSERT_EQ(3, v[2]);
	ASSERT_EQ(4, v[3]);
	ASSERT_EQ(5, v[4]);
}

TEST_F(ElementAccess,
ReturnsNonConstReferenceAtIndex) {
	using Type_At = decltype(v.at(0));
	using Type_Subscript = decltype(v[0]);

	ASSERT_TRUE(std::is_lvalue_reference<Type_At>::value);
	ASSERT_TRUE(std::is_lvalue_reference<Type_Subscript>::value);

	ASSERT_FALSE(std::is_const<typename std::remove_reference<Type_At>::type>::value);
	ASSERT_FALSE(std::is_const<typename std::remove_reference<Type_Subscript>::type>::value);

}

TEST_F(ElementAccess,
ReturnsConstReferenceAtIndex) {
	using Type_At = decltype(cv.at(0));
	using Type_Subscript = decltype(cv[0]);

	ASSERT_TRUE(std::is_lvalue_reference<Type_At>::value);
	ASSERT_TRUE(std::is_lvalue_reference<Type_Subscript>::value);

	ASSERT_TRUE(std::is_const<typename std::remove_reference<Type_At>::type>::value);
	ASSERT_TRUE(std::is_const<typename std::remove_reference<Type_Subscript>::type>::value);

}

TEST_F(ElementAccess,
ReturnsNonConstReferenceToFirstElement) {
	using Type_First = decltype(v.first());
	using Type_Front = decltype(v.front());

	ASSERT_EQ(1, v.first());
	ASSERT_EQ(1, v.front());

	ASSERT_TRUE(std::is_lvalue_reference<Type_First>::value);
	ASSERT_TRUE(std::is_lvalue_reference<Type_Front>::value);

	ASSERT_FALSE(std::is_const<std::remove_reference<Type_First>::type>::value);
	ASSERT_FALSE(std::is_const<std::remove_reference<Type_Front>::type>::value);

}

TEST_F(ElementAccess,
ReturnsNonConstReferenceToLastElement) {
	using Type_Back = decltype(v.back());
	using Type_Last = decltype(v.last());

	ASSERT_EQ(5, v.back());
	ASSERT_EQ(5, v.last());

	ASSERT_TRUE(std::is_lvalue_reference<Type_Back>::value);
	ASSERT_TRUE(std::is_lvalue_reference<Type_Last>::value);

	ASSERT_FALSE(std::is_const<std::remove_reference<Type_Back>::type>::value);
	ASSERT_FALSE(std::is_const<std::remove_reference<Type_Last>::type>::value);

}

TEST_F(ElementAccess,
ReturnsConstReferenceToFirstElement) {
	using Type_First = decltype(cv.first());
	using Type_Front = decltype(cv.front());

	ASSERT_EQ(1, cv.first());
	ASSERT_EQ(1, cv.front());

	ASSERT_TRUE(std::is_lvalue_reference<Type_First>::value);
	ASSERT_TRUE(std::is_lvalue_reference<Type_Front>::value);

	ASSERT_TRUE(std::is_const<std::remove_reference<Type_First>::type>::value);
	ASSERT_TRUE(std::is_const<std::remove_reference<Type_Front>::type>::value);
}

TEST_F(ElementAccess,
ReturnsConstReferenceToLastElement) {
	using Type_Back = decltype(cv.back());
	using Type_Last = decltype(cv.last());

	ASSERT_EQ(5, cv.back());
	ASSERT_EQ(5, cv.last());

	ASSERT_TRUE(std::is_lvalue_reference<Type_Back>::value);
	ASSERT_TRUE(std::is_lvalue_reference<Type_Last>::value);

	ASSERT_TRUE(std::is_const<std::remove_reference<Type_Back>::type>::value);
	ASSERT_TRUE(std::is_const<std::remove_reference<Type_Last>::type>::value);
}

TEST_F(ElementAccess,
ReturnsWholeVectorAsSubrangeFromIndexZero) {
	int startIndex = 0;
	PVector<int> expectedRange({1,2,3,4,5});
	PVector<int> actualRange = v.mid(startIndex);

	ASSERT_EQ(actualRange, expectedRange);
}

TEST_F(ElementAccess,
ReturnsSubrangeFromIndexTwo) {
	int startIndex = 2;
	PVector<int> expectedRange({3,4,5});
	PVector<int> actualRange = v.mid(startIndex);

	ASSERT_EQ(expectedRange, actualRange);
}

TEST_F(ElementAccess,
ReturnsSubrangeFromIndexZeroForCountOfThree) {
	int startIndex = 0;
	int count = 3;
	PVector<int> expectedRange({1,2,3});
	PVector<int> actualRange = v.mid(startIndex, count);

	ASSERT_EQ(expectedRange, actualRange);
}

TEST_F(ElementAccess,
ReturnsSubrangeFromIndexTwoForCountOfThree) {
	int startIndex = 2;
	int count = 2;
	PVector<int> expectedRange({3,4});
	PVector<int> actualRange = v.mid(startIndex, count);

	ASSERT_EQ(expectedRange, actualRange);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE











