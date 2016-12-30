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
	using iterator = prism::SequenceIterator<int, false>;
	using const_iterator = prism::SequenceIterator<int, true>;

	PVector v;
	int expectedSize;
	int actualSize;
	int expectedCapacity;
	int actualCapacity;
	int expectedValue;
	int actualValue;
	static const int InvalidNegativeIndex = -1;
	static const int InvalidPositiveIndex = 15;
	static const int AtIndexZero = 0;
	static const int AtIndexOne = 1;
	static const int AtIndexTwo = 2;
	static const int AtIndexThree = 3;
	static const int AtIndexFour = 4;
	static const int AtIndexFive = 5;
	static const int AtIndexSix = 6;
	static const int AtIndexSeven = 7;
	static const int AtIndexEight = 8;
	std::function<bool(int)> oddPred;

	DefaultVector()
	: expectedSize(0), actualSize(0),
	  expectedCapacity(0), actualCapacity(0),
	  expectedValue(0), actualValue(0),
	  oddPred([](int i) { return i % 2 == 1; })
	{}
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
	v.insert(AtIndexZero, 500);

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
	v.insert(AtIndexZero, 1);
	v.insert(AtIndexOne, 2);
	v.insert(AtIndexTwo, 3);

	v.reserve(20);

	ASSERT_EQ(1, v.at(AtIndexZero));
	ASSERT_EQ(2, v.at(AtIndexOne));
	ASSERT_EQ(3, v.at(AtIndexTwo));
}

TEST_F(DefaultVector,
DataIsNotNullAfterInsert) {
	v.insert(AtIndexZero, 500);

	ASSERT_FALSE(v.data() == nullptr);
}

TEST_F(DefaultVector,
HasSizeOneAfterSingleElementInsert) {
	v.insert(AtIndexZero, 500);
	expectedSize = 1;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
HasCapacityOneAfterSingleElementInsert) {
	v.insert(AtIndexZero, 500);
	expectedCapacity = 1;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(DefaultVector,
ReturnsValueAtIndex) {
	v.insert(AtIndexZero, 500);
	v.insert(AtIndexOne, 501);
	v.insert(AtIndexTwo, 502);

	ASSERT_EQ(500, v.at(AtIndexZero));
	ASSERT_EQ(501, v.at(AtIndexOne));
	ASSERT_EQ(502, v.at(AtIndexTwo));

	ASSERT_EQ(500, v[AtIndexZero]);
	ASSERT_EQ(501, v[AtIndexOne]);
	ASSERT_EQ(502, v[AtIndexTwo]);
}

TEST_F(DefaultVector,
ThrowsWhenAccessingNegativeIndex) {
	ASSERT_THROW(v.at(InvalidNegativeIndex), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ThrowsWhenAccessingInvalidPositiveIndex) {
	v.insert(AtIndexZero, 500);
	ASSERT_THROW(v.at(InvalidPositiveIndex), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ThrowsWhenAccessingEmptyVectorByIndex) {
	ASSERT_THROW(v.at(AtIndexZero), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ReturnsModifiableReferenceFromIndex) {
	int initialValue = 501;
	int newValue = 502;
	v.insert(AtIndexZero, initialValue);

	v.at(AtIndexZero) = newValue;
	expectedValue = newValue;
	actualValue = v.at(AtIndexZero);

	ASSERT_EQ(expectedValue, actualValue);

	v[AtIndexZero] = newValue;
	expectedValue = newValue;
	actualValue = v[AtIndexZero];

	ASSERT_EQ(expectedValue, actualValue);
}

TEST_F(DefaultVector,
ReplacesValueAtIndex) {
	int originalValue = 500;
	int newValue = 501;
	v.insert(AtIndexZero, originalValue);

	v.replace(AtIndexZero, newValue);

	ASSERT_EQ(newValue, v.at(AtIndexZero));
}

TEST_F(DefaultVector,
ThrowsWhenReplacingValueAtNegativeIndex) {
	ASSERT_THROW(v.replace(InvalidNegativeIndex, 501), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ThrowsWhenReplacingValueAtInvalidPositiveIndex) {
	ASSERT_THROW(v.replace(InvalidPositiveIndex, 501), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ShiftsSuccessiveElementsUpByAmountCopiesInserted) {
	v.insert(AtIndexZero, 0);
	v.insert(AtIndexOne, 1);
	v.insert(AtIndexTwo, 2);

	int numCopies = 5;
	int value = 500;
	v.insert(AtIndexZero, numCopies, value);

	ASSERT_EQ(0, v[AtIndexFive]);
	ASSERT_EQ(1, v[AtIndexSix]);
	ASSERT_EQ(2, v[AtIndexSeven]);
}

TEST_F(DefaultVector,
PreservesElementsBeforeInsertionPoint) {
	v.insert(AtIndexZero, 0);
	v.insert(AtIndexOne, 1);
	v.insert(AtIndexTwo, 2);

	int numCopies = 3;
	int value = 500;
	v.insert(AtIndexTwo, numCopies, value);

	ASSERT_EQ(0, v[AtIndexZero]);
	ASSERT_EQ(1, v[AtIndexOne]);
}

TEST_F(DefaultVector,
ThrowsWhenInsertingAtNegativeIndex) {
	ASSERT_THROW(v.insert(InvalidNegativeIndex, 500), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ThrowsWhenInsertingAtInvalidPositiveIndex) {
	ASSERT_THROW(v.insert(InvalidPositiveIndex, 500), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
IncreasesSizeByAmountOfCopiesInserted) {
	int numCopiesOf = 4;
	int value = 500;

	v.insert(AtIndexZero, numCopiesOf, value);
	expectedSize = 4;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
AppendsElement) {
	v.insert(AtIndexZero, 5, 123);

	v.append(500);
	expectedSize = 6;
	actualSize = v.size();

	ASSERT_EQ(500, v[AtIndexFive]);
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PrependsElement) {
	v.insert(AtIndexZero, 5, 123);

	v.prepend(500);
	expectedSize = 6;
	actualSize = v.size();

	ASSERT_EQ(500, v[AtIndexZero]);
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
DecreasesSizeByOneWhenRemovingElement) {
	v.insert(AtIndexZero, 5, 123);

	v.remove(AtIndexZero);
	expectedSize = 4;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesOtherElementsWhenRemovingElement) {
	v.append(500);
	v.append(501);
	v.append(502);
	v.append(503);

	v.remove(AtIndexOne);

	ASSERT_EQ(500, v[AtIndexZero]);
	ASSERT_EQ(502, v[AtIndexOne]);
	ASSERT_EQ(503, v[AtIndexTwo]);
}

TEST_F(DefaultVector,
DecreasesSizeByThreeWhenRemovingCountOfElements) {
	v.append(500);
	v.append(501);
	v.append(502);
	v.append(503);

	int numValues = 3;
	v.remove(AtIndexOne, numValues);
	expectedSize = 1;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
ThrowsWhenRemovingNegativeIndex) {
	ASSERT_THROW(v.remove(InvalidNegativeIndex), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ThrowsWhenRemovingInvalidPositiveIndex) {
	ASSERT_THROW(v.remove(InvalidPositiveIndex), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
DecreasesSizeWhenRemovingAllElementsEqualToValue) {
	v.append(0);
	v.append(1);
	v.append(0);
	v.append(2);
	v.append(0);

	int valueToRemove = 0;
	v.removeAll(valueToRemove);
	expectedSize = 2;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesOtherElementsWhenRemovingAllElementsEqualToValue) {
	v.append(0);
	v.append(1);
	v.append(0);
	v.append(2);
	v.append(0);

	int valueToRemove = 0;
	v.removeAll(valueToRemove);

	ASSERT_EQ(1, v[AtIndexZero]);
	ASSERT_EQ(2, v[AtIndexOne]);
}

TEST_F(DefaultVector,
SizeUnchangedWhenRemovingAllElementsEqualToNonExistentValue) {
	v.append(1);
	v.append(2);
	v.append(3);
	v.append(4);
	v.append(5);

	int NonExistentValue = 789;
	v.removeAll(NonExistentValue);
	expectedSize = 5;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
DecreasesSizeWhenRemovingFirstElement) {
	v.append(1);
	v.append(2);
	v.append(3);

	v.removeFirst();
	expectedSize = 2;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesOtherElementsWhenRemovingFirstElement) {
	v.append(1);
	v.append(2);
	v.append(3);

	v.removeFirst();

	ASSERT_EQ(2, v[AtIndexZero]);
	ASSERT_EQ(3, v[AtIndexOne]);
}

TEST_F(DefaultVector,
ThrowsWhenRemovingFirstElementWhenEmpty) {
	ASSERT_THROW(v.removeFirst(), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
DecreasesSizeWhenRemovingLastElement) {
	v.append(1);
	v.append(2);
	v.append(3);

	v.removeLast();
	expectedSize = 2;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesOtherElementsWhenRemovingLastElement) {
	v.append(1);
	v.append(2);
	v.append(3);

	v.removeLast();

	ASSERT_EQ(1, v[AtIndexZero]);
	ASSERT_EQ(2, v[AtIndexOne]);
}

TEST_F(DefaultVector,
ThrowsWhenRemovingLastElementWhenEmpty) {
	ASSERT_THROW(v.removeLast(), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
DecreasesSizeWhenRemovingOddValuesWithLambdaPredicate) {
	v.append(1);
	v.append(2);
	v.append(3);
	v.append(4);
	v.append(5);

	v.removeIf(oddPred);
	expectedSize = 2;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesOtherElementsWhenRemovingOddValuesWithLambdaPredicate) {
	v.append(1);
	v.append(2);
	v.append(3);
	v.append(4);
	v.append(5);

	v.removeIf(oddPred);

	ASSERT_EQ(2, v[AtIndexZero]);
	ASSERT_EQ(4, v[AtIndexOne]);
}

TEST_F(DefaultVector,
BeginIteratorPointsToFirstElement) {
	v.append(1);
	v.append(2);
	int* ptrToFirstElement = v.data();
	iterator beginIter(ptrToFirstElement);

	ASSERT_TRUE(beginIter == v.begin());
	ASSERT_EQ(1, *beginIter);
}

TEST_F(DefaultVector,
EndIteratorPointsToOnePositionPastLastElement) {
	v.append(1);
	v.append(2);
	int* ptrToPosAfterLastElement = v.data() + v.size();
	iterator endIter(ptrToPosAfterLastElement);

	ASSERT_TRUE(endIter == v.end());
}

TEST_F(DefaultVector,
EndIteratorEqualsBeginIteratorWhenEmpty) {
	ASSERT_TRUE(v.begin() == v.end());
}

TEST_F(DefaultVector,
ConstBeginIteratorPointsToFirstElement) {
	v.append(1);
	v.append(2);
	int* ptrToFirstElement = v.data();
	const_iterator cBeginIter(ptrToFirstElement);

	ASSERT_TRUE(cBeginIter == v.cbegin());
	ASSERT_EQ(1, *v.cbegin());
}

TEST_F(DefaultVector,
ConstEndIteratorPointsToOnePositionPastLastElement) {
	v.append(1);
	v.append(2);
	int* ptrToPosAfterLastElement = v.data() + v.size();
	const_iterator cEndIter(ptrToPosAfterLastElement);

	ASSERT_TRUE(cEndIter == v.cend());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










