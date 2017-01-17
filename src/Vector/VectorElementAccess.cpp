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

class InvalidElementAccess : public Test {
public:
	PVector<int> emptyVec;
	enum { InvalidNegativeIndex = -1, InvalidPositiveIndex = 15 };
};

TEST_F(InvalidElementAccess,
ThrowsWhenAccessingEmptyVectorByIndex) {
	ASSERT_THROW(emptyVec.at(0), prism::OutOfBoundsException);
}

TEST_F(InvalidElementAccess,
ThrowsWhenAccessingNegativeIndex) {
	ASSERT_THROW(emptyVec.at(InvalidNegativeIndex), prism::OutOfBoundsException);
}

TEST_F(InvalidElementAccess,
ThrowsWhenAccessingInvalidPositiveIndex) {
	ASSERT_THROW(emptyVec.at(InvalidPositiveIndex), prism::OutOfBoundsException);
}

class VectorElementAccess : public Test {
public:
	PVector<int> v;
	const PVector<int> cv;
	PVector<int> emptyVec;
	PVector<int> expectedRange, actualRange;
	const int FirstValue, LastValue;
	int startIndex;
	int count;

	enum {
		InvalidNegativeIndex = -1,
		InvalidPositiveIndex = 15
	};

	VectorElementAccess()
	: v({1,2,3,4,5,6}),
	  cv(v.cbegin(), v.cend()),
	  FirstValue(v[0]),
	  LastValue(v[v.size()-1]),
	  startIndex(0), count(0)
	{}

	template <typename Type>
	const bool
	isPointer() {
		return prism::IsPointer<Type>::value;
	}

	template <typename Type>
	const bool
	isPointerToConst() {
		return prism::IsConst<typename prism::RemovePointer<Type>::type>::value;
	}

	template <typename Type>
	const bool
	isLValueReference() {
		return prism::IsLValueReference<Type>::value;
	}

	template <typename Type>
	const bool
	isReferenceToConst() {
		return prism::IsConst<typename prism::RemoveReference<Type>::type>::value;
	}
};

TEST_F(VectorElementAccess,
DataIsNullWhenVectorCreated) {
	std::nullptr_t expected = nullptr;
	ASSERT_EQ(expected, emptyVec.data());
}

TEST_F(VectorElementAccess,
DataIsNotNullAfterInsert) {
	ASSERT_FALSE(v.data() == nullptr);
	ASSERT_FALSE(v.cdata() == nullptr);
	ASSERT_FALSE(cv.data() == nullptr);
}

TEST_F(VectorElementAccess,
ReturnsPointerToNonConstData) {
	using Type = decltype(v.data());

	ASSERT_TRUE(isPointer<Type>());
	ASSERT_FALSE(isPointerToConst<Type>());
}

TEST_F(VectorElementAccess,
ReturnsPointerToConstData) {
	using ImplicitConstType = decltype(cv.data());
	using ExplicitConstType = decltype(cv.cdata());

	ASSERT_TRUE(isPointer<ImplicitConstType>());
	ASSERT_TRUE(isPointer<ExplicitConstType>());

	ASSERT_TRUE(isPointerToConst<ImplicitConstType>());
	ASSERT_TRUE(isPointerToConst<ExplicitConstType>());
}

TEST_F(VectorElementAccess,
ReturnsWholeVectorAsSubrangeFromIndexZero) {
	startIndex = 0;
	expectedRange = {1,2,3,4,5,6};
	actualRange = v.mid(startIndex);

	ASSERT_EQ(actualRange, expectedRange);
}

TEST_F(VectorElementAccess,
ReturnsSubrangeFromIndexTwo) {
	startIndex = 2;
	expectedRange = {3,4,5,6};
	actualRange = v.mid(startIndex);

	ASSERT_EQ(expectedRange, actualRange);
}

TEST_F(VectorElementAccess,
ReturnsSubrangeFromIndexZeroForCountOfThree) {
	startIndex = 0;
	count = 3;
	expectedRange = {1,2,3};
	actualRange = v.mid(startIndex, count);

	ASSERT_EQ(expectedRange, actualRange);
}

TEST_F(VectorElementAccess,
ReturnsSubrangeFromIndexTwoForCountOfThree) {
	startIndex = 2;
	count = 2;
	expectedRange = {3,4};
	actualRange = v.mid(startIndex, count);

	ASSERT_EQ(expectedRange, actualRange);
}

TEST_F(VectorElementAccess,
ReturnsReferenceAtIndex) {
	using Type = decltype(v.at(0));

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_FALSE(isReferenceToConst<Type>());
	ASSERT_EQ(1, v.at(0));
	ASSERT_EQ(2, v.at(1));
	ASSERT_EQ(3, v.at(2));
	ASSERT_EQ(4, v.at(3));
	ASSERT_EQ(5, v.at(4));
	ASSERT_EQ(6, v.at(5));
}

TEST_F(VectorElementAccess,
ReturnsConstReferenceAtIndex) {
	using Type = decltype(cv.at(0));

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_TRUE(isReferenceToConst<Type>());
	ASSERT_EQ(FirstValue, cv.at(0));
}

TEST_F(VectorElementAccess,
ReturnsReferenceByBrackets) {
	using Type = decltype(v[0]);

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_FALSE(isReferenceToConst<Type>());
	ASSERT_EQ(1, v[0]);
	ASSERT_EQ(2, v[1]);
	ASSERT_EQ(3, v[2]);
	ASSERT_EQ(4, v[3]);
	ASSERT_EQ(5, v[4]);
	ASSERT_EQ(6, v[5]);
}

TEST_F(VectorElementAccess,
ReturnsConstReferenceByBrackets) {
	using Type = decltype(cv[0]);

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_TRUE(isReferenceToConst<Type>());
	ASSERT_EQ(FirstValue, cv[0]);
}

TEST_F(VectorElementAccess,
ReturnsReferenceAtBack) {
	using Type = decltype(v.back());

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_FALSE(isReferenceToConst<Type>());
	ASSERT_EQ(LastValue, v.back());
}

TEST_F(VectorElementAccess,
ReturnsConstReferenceAtBack) {
	using Type = decltype(cv.back());

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_TRUE(isReferenceToConst<Type>());
	ASSERT_EQ(LastValue, cv.back());
}

TEST_F(VectorElementAccess,
ReturnsReferenceAtFront) {
	using Type = decltype(v.front());

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_FALSE(isReferenceToConst<Type>());
	ASSERT_EQ(FirstValue, v.front());
}

TEST_F(VectorElementAccess,
ReturnsConstReferenceAtFront) {
	using Type = decltype(cv.front());

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_TRUE(isReferenceToConst<Type>());
	ASSERT_EQ(FirstValue, cv.front());
}

TEST_F(VectorElementAccess,
ReturnsReferenceAtLast) {
	using Type = decltype(v.last());

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_FALSE(isReferenceToConst<Type>());
	ASSERT_EQ(LastValue, v.last());
}

TEST_F(VectorElementAccess,
ReturnsConstReferenceAtLast) {
	using Type = decltype(cv.last());

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_TRUE(isReferenceToConst<Type>());
	ASSERT_EQ(LastValue, cv.last());
}

TEST_F(VectorElementAccess,
ReturnsReferenceAtFirst) {
	using Type = decltype(v.first());

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_FALSE(isReferenceToConst<Type>());
	ASSERT_EQ(FirstValue, v.first());
}

TEST_F(VectorElementAccess,
ReturnsConstReferenceAtFirst) {
	using Type = decltype(cv.first());

	ASSERT_TRUE(isLValueReference<Type>());
	ASSERT_TRUE(isReferenceToConst<Type>());
	ASSERT_EQ(FirstValue, cv.first());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE











