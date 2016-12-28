/*
 * DefaultVector.cpp
 *
 *  Created on: 12 Dec 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/PVector>
#include <prism/global>
#include <prism/OutOfBoundsException>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class DefaultVector : public Test {
public:
	PVector v;
	int expectedSize;
	int actualSize;
	int expectedCapacity;
	int actualCapacity;
	int expectedValue;
	int actualValue;
	static const int InvalidNegativeIndex = -1;
	static const int InvalidPositiveIndex = 15;
	static const int IndexZero = 0;
	static const int IndexOne = 1;
	static const int IndexTwo = 2;
};

TEST_F(DefaultVector,
DataIsNull) {
	std::nullptr_t expected = nullptr;
	ASSERT_EQ(expected, v.data());
}

TEST_F(DefaultVector,
IsEmptyOnConstruction) {
	bool expected = true;
	bool actual = v.empty();

	ASSERT_EQ(expected, actual);
}

TEST_F(DefaultVector,
IsNotEmptyAfterInsertion) {
	v.insert(500);

	ASSERT_FALSE(v.empty());
}

TEST_F(DefaultVector,
HasSizeZero) {
	expectedSize = 0;
	actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
HasCapacityZero) {
	expectedCapacity = 0;
	actualCapacity = v.capacity();
	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(DefaultVector,
HasCapacityEqualToReservedMemorySize) {
	v.reserve(10);
	expectedCapacity = 10;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(DefaultVector,
ThrowsWhenReservingNegativeMemory) {
	int negativeMemory = -1;
	ASSERT_THROW(v.reserve(negativeMemory), std::bad_alloc);
}

TEST_F(DefaultVector,
DataIsNotNullAfterReservingMemory) {
	v.reserve(10);

	ASSERT_FALSE(v.data() == nullptr);
}

TEST_F(DefaultVector,
IgnoresRequestToReserveLessMemoryThanCapacity) {
	v.reserve(10);
	v.reserve(5);
	expectedCapacity = 10;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(DefaultVector,
IgnoresRequestToReserveZeroMemory) {
	v.reserve(10);
	v.reserve(0);
	expectedCapacity = 10;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(DefaultVector,
PreservesExistingElementsAfterReservingMoreMemory) {
	v.insert(1);
	v.insert(2);
	v.insert(3);

	v.reserve(20);

	ASSERT_EQ(1, v.at(IndexZero));
	ASSERT_EQ(2, v.at(IndexOne));
	ASSERT_EQ(3, v.at(IndexTwo));
}

TEST_F(DefaultVector,
DataIsNotNullAfterInsert) {
	v.insert(500);

	ASSERT_FALSE(v.data() == nullptr);
}

TEST_F(DefaultVector,
HasSizeOneAfterSingleElementInsert) {
	v.insert(500);
	expectedSize = 1;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
HasCapacityOneAfterSingleElementInsert) {
	v.insert(500);
	expectedCapacity = 1;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(DefaultVector,
ReturnsValueAtIndex) {
	v.insert(500);
	v.insert(501);
	v.insert(502);

	ASSERT_EQ(500, v.at(IndexZero));
	ASSERT_EQ(501, v.at(IndexOne));
	ASSERT_EQ(502, v.at(IndexTwo));

	ASSERT_EQ(500, v[IndexZero]);
	ASSERT_EQ(501, v[IndexOne]);
	ASSERT_EQ(502, v[IndexTwo]);
}

TEST_F(DefaultVector,
ThrowsWhenAccessingNegativeIndex) {
	ASSERT_THROW(v.at(InvalidNegativeIndex), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ThrowsWhenAccessingInvalidPositiveIndex) {
	v.insert(500);
	ASSERT_THROW(v.at(InvalidPositiveIndex), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ThrowsWhenAccessingEmptyVector) {
	ASSERT_THROW(v.at(IndexZero), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ReturnsModifiableReferenceFromIndex) {
	int initialValue = 501;
	int newValue = 502;
	v.insert(initialValue);

	v.at(IndexZero) = newValue;
	expectedValue = newValue;
	actualValue = v.at(IndexZero);

	ASSERT_EQ(expectedValue, actualValue);

	v[IndexZero] = newValue;
	expectedValue = newValue;
	actualValue = v[IndexZero];

	ASSERT_EQ(expectedValue, actualValue);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










