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
#include <prism/type_traits>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class DefaultVector : public Test {
public:
	PVector<int> v;
	int expectedSize;
	int actualSize;
	int expectedCapacity;
	int actualCapacity;
	int expectedValue;
	int actualValue;
	int expectedIndex;
	int actualIndex;

	enum {
		InvalidNegativeIndex = -1,
		InvalidPositiveIndex = 15,
		AtIndexZero = 0,
		AtIndexOne = 1,
		AtIndexTwo = 2,
		AtIndexThree = 3,
		AtIndexFour = 4,
		AtIndexFive = 5,
		AtIndexSix = 6,
		AtIndexSeven = 7,
		AtIndexEight = 8
	};
	std::function<bool(int)> oddPred;

	DefaultVector()
	: expectedSize(0), actualSize(0),
	  expectedCapacity(0), actualCapacity(0),
	  expectedValue(0), actualValue(0),
	  expectedIndex(0), actualIndex(0),
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
	v.insert(AtIndexZero, 1, 500);

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
	int negativeAmountOfMemory = -1;
	ASSERT_THROW(v.reserve(negativeAmountOfMemory), std::bad_alloc);
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
	v.insert(AtIndexZero, 1, 1);
	v.insert(AtIndexOne, 1, 2);
	v.insert(AtIndexTwo, 1, 3);

	v.reserve(20);

	ASSERT_EQ(1, v.at(AtIndexZero));
	ASSERT_EQ(2, v.at(AtIndexOne));
	ASSERT_EQ(3, v.at(AtIndexTwo));
}

TEST_F(DefaultVector,
ThrowsWhenAccessingEmptyVectorByIndex) {
	ASSERT_THROW(v.at(AtIndexZero), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ReplacesValueAtIndex) {
	int originalValue = 500;
	int newValue = 501;
	v.insert(AtIndexZero, 1, originalValue);

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
ShiftsElementsFromIndexUpMultiplePositions) {
	v.reserve(20);
	v.insert(AtIndexZero, 1, 1);
	v.insert(AtIndexOne, 1, 2);
	v.insert(AtIndexTwo, 1, 3);
	v.insert(AtIndexThree, 1, 4);
	v.insert(AtIndexFour, 1, 5);

	v.insert(AtIndexOne, 3, 500);

	ASSERT_EQ(2, v[AtIndexFour]);
	ASSERT_EQ(3, v[AtIndexFive]);
	ASSERT_EQ(4, v[AtIndexSix]);
	ASSERT_EQ(5, v[AtIndexSeven]);
}

TEST_F(DefaultVector,
PreservesElementsBeforeInsertionPoint) {
	v.insert(AtIndexZero, 1, 0);
	v.insert(AtIndexOne, 1, 1);
	v.insert(AtIndexTwo, 1, 2);

	int numCopies = 3;
	int value = 500;
	v.insert(AtIndexTwo, numCopies, value);

	ASSERT_EQ(0, v[AtIndexZero]);
	ASSERT_EQ(1, v[AtIndexOne]);
}

TEST_F(DefaultVector,
ThrowsWhenInsertingAtNegativeIndex) {
	ASSERT_THROW(v.insert(InvalidNegativeIndex, 1, 500), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ThrowsWhenInsertingAtInvalidPositiveIndex) {
	ASSERT_THROW(v.insert(InvalidPositiveIndex, 1, 500), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
IncreasesSizeByNumElementsInserted) {
	int numCopiesOf = 4;
	int value = 500;

	v.insert(AtIndexZero, numCopiesOf, value);
	expectedSize = 4;
	actualSize = v.size();

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
	v.insert(AtIndexZero, 1, 500);
	v.insert(AtIndexOne, 1, 501);
	v.insert(AtIndexTwo, 1, 502);
	v.insert(AtIndexThree, 1, 503);

	v.remove(AtIndexOne);

	ASSERT_EQ(500, v[AtIndexZero]);
	ASSERT_EQ(502, v[AtIndexOne]);
	ASSERT_EQ(503, v[AtIndexTwo]);
}

TEST_F(DefaultVector,
DecreasesSizeByThreeWhenRemovingCountOfElements) {
	v.insert(AtIndexZero, 1, 500);
	v.insert(AtIndexOne, 1, 501);
	v.insert(AtIndexTwo, 1, 502);
	v.insert(AtIndexThree, 1, 503);

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
	v.insert(AtIndexZero, 1, 0);
	v.insert(AtIndexOne, 1, 1);
	v.insert(AtIndexTwo, 1, 0);
	v.insert(AtIndexThree, 1, 2);
	v.insert(AtIndexFour, 1, 0);

	int valueToRemove = 0;
	v.removeAll(valueToRemove);
	expectedSize = 2;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesOtherElementsWhenRemovingAllElementsEqualToValue) {
	v.insert(AtIndexZero, 1, 0);
	v.insert(AtIndexOne, 1, 1);
	v.insert(AtIndexTwo, 1, 0);
	v.insert(AtIndexThree, 1, 2);
	v.insert(AtIndexFour, 1, 0);

	int valueToRemove = 0;
	v.removeAll(valueToRemove);

	ASSERT_EQ(1, v[AtIndexZero]);
	ASSERT_EQ(2, v[AtIndexOne]);
}

TEST_F(DefaultVector,
SizeUnchangedWhenRemovingAllElementsEqualToNonExistentValue) {
	v.insert(AtIndexZero, 1, 1);
	v.insert(AtIndexOne, 1, 2);
	v.insert(AtIndexTwo, 1, 3);
	v.insert(AtIndexThree, 1, 4);
	v.insert(AtIndexFour, 1, 5);

	int NonExistentValue = 789;
	v.removeAll(NonExistentValue);
	expectedSize = 5;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
DecreasesSizeWhenRemovingFirstElement) {
	v.insert(AtIndexZero, 1, 1);
	v.insert(AtIndexOne, 1, 2);
	v.insert(AtIndexTwo, 1, 3);

	v.removeFirst();
	expectedSize = 2;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesOtherElementsWhenRemovingFirstElement) {
	v.insert(AtIndexZero, 1, 1);
	v.insert(AtIndexOne, 1, 2);
	v.insert(AtIndexTwo, 1, 3);

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
	v.insert(AtIndexZero, 1, 1);
	v.insert(AtIndexOne, 1, 2);
	v.insert(AtIndexTwo, 1, 3);

	v.removeLast();
	expectedSize = 2;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesOtherElementsWhenRemovingLastElement) {
	v.insert(AtIndexZero, 1, 1);
	v.insert(AtIndexOne, 1, 2);
	v.insert(AtIndexTwo, 1, 3);

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
	v.insert(AtIndexZero, 1, 1);
	v.insert(AtIndexOne, 1, 2);
	v.insert(AtIndexTwo, 1, 3);
	v.insert(AtIndexThree, 1, 4);
	v.insert(AtIndexFour, 1, 5);

	v.removeIf(oddPred);
	expectedSize = 2;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesOtherElementsWhenRemovingOddValuesWithLambdaPredicate) {
	v.insert(AtIndexZero, 1, 1);
	v.insert(AtIndexOne, 1, 2);
	v.insert(AtIndexTwo, 1, 3);
	v.insert(AtIndexThree, 1, 4);
	v.insert(AtIndexFour, 1, 5);

	v.removeIf(oddPred);

	ASSERT_EQ(2, v[AtIndexZero]);
	ASSERT_EQ(4, v[AtIndexOne]);
}



TEST_F(DefaultVector,
SetsSizeToZeroAfterClearingAllElements) {
	v.insert(AtIndexZero, 1, 500);
	v.insert(AtIndexOne, 1, 501);
	v.insert(AtIndexTwo, 1, 502);

	v.clear();
	expectedSize = 0;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesCapacityAfterClearingAllElements) {
	v.reserve(10);
	v.insert(AtIndexZero, 1, 500);
	v.insert(AtIndexOne, 1, 501);
	v.insert(AtIndexTwo, 1, 502);

	v.clear();
	expectedCapacity = 10;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(DefaultVector,
SetsEachElementEqualToValue) {
	int count = 5;
	int value = 10;
	v.insert(AtIndexZero, count, value);

	int newValue = 25;
	v.fill(newValue);

	ASSERT_EQ(newValue, v[AtIndexZero]);
	ASSERT_EQ(newValue, v[AtIndexOne]);
	ASSERT_EQ(newValue, v[AtIndexTwo]);
	ASSERT_EQ(newValue, v[AtIndexThree]);
	ASSERT_EQ(newValue, v[AtIndexFour]);
}

TEST_F(DefaultVector,
VectorsSwapSize) {
	PVector<int> other({1,2,3,4,5});

	v.swap(other);

	ASSERT_EQ(5, v.size());
	ASSERT_EQ(0, other.size());
}

TEST_F(DefaultVector,
VectorsSwapCapacity) {
	PVector<int> other({1,2,3,4,5});

	v.swap(other);

	ASSERT_EQ(5, v.capacity());
	ASSERT_EQ(0, other.capacity());
}

TEST_F(DefaultVector,
VectorsSwapElements) {
	PVector<int> other({1,2,3,4,5});

	v.swap(other);

	ASSERT_EQ(1, v[AtIndexZero]);
	ASSERT_EQ(2, v[AtIndexOne]);
	ASSERT_EQ(3, v[AtIndexTwo]);
	ASSERT_EQ(4, v[AtIndexThree]);
	ASSERT_EQ(5, v[AtIndexFour]);
}

TEST_F(DefaultVector,
ThrowsWhenResizingToNegativeSize) {
	int invalidNegativeSize = -1;
	ASSERT_THROW(v.resize(invalidNegativeSize), prism::OutOfBoundsException);
}

TEST_F(DefaultVector,
ResizingCapacityZeroVectorCausesAllocation) {
	v.resize(10);
	int newCapacity = v.capacity();
	int originalCapacity = 0;

	ASSERT_GT(newCapacity, originalCapacity);
}

TEST_F(DefaultVector,
IncreasesSizeWhenResizingGreater) {
	int oldSize = v.size();
	v.resize(15);
	int newSize = v.size();

	ASSERT_GT(newSize, oldSize);
	ASSERT_EQ(15, newSize);
}

TEST_F(DefaultVector,
PreservesExistingElementsWhenResizingGreater) {
	PVector<int> vec({1,2,3,4,5});

	int newSize = 8;
	vec.resize(newSize);

	ASSERT_EQ(1, vec[AtIndexZero]);
	ASSERT_EQ(2, vec[AtIndexOne]);
	ASSERT_EQ(3, vec[AtIndexTwo]);
	ASSERT_EQ(4, vec[AtIndexThree]);
	ASSERT_EQ(5, vec[AtIndexFour]);
}

TEST_F(DefaultVector,
PadsWithDefaultConstructedValuesWhenResizingGreater) {
	int defaultConstructedValue = int();
	v.resize(4);

	ASSERT_EQ(defaultConstructedValue, v[AtIndexZero]);
	ASSERT_EQ(defaultConstructedValue, v[AtIndexOne]);
	ASSERT_EQ(defaultConstructedValue, v[AtIndexTwo]);
	ASSERT_EQ(defaultConstructedValue, v[AtIndexThree]);
}

TEST_F(DefaultVector,
PadsWithSuppliedValueWhenResizingGreater) {
	int paddingValue = 23;
	v.resize(4, paddingValue);

	ASSERT_EQ(paddingValue, v[AtIndexZero]);
	ASSERT_EQ(paddingValue, v[AtIndexOne]);
	ASSERT_EQ(paddingValue, v[AtIndexTwo]);
	ASSERT_EQ(paddingValue, v[AtIndexThree]);
}

TEST_F(DefaultVector,
DecreasesSizeWhenResizingSmaller) {
	PVector<int> vec({1,2,3,4,5});

	vec.resize(3);
	expectedSize = 3;
	actualSize = vec.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesCapacityWhenResizingSmaller) {
	PVector<int> vec({1,2,3,4,5});
	int oldCapacity = vec.capacity();

	vec.resize(3);
	expectedCapacity = oldCapacity;
	actualCapacity = vec.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(DefaultVector,
PreservesExistingElementsWhenResizingSmaller) {
	PVector<int> vec({1,2,3,4,5});

	vec.resize(3);

	ASSERT_EQ(1, vec[AtIndexZero]);
	ASSERT_EQ(2, vec[AtIndexOne]);
	ASSERT_EQ(3, vec[AtIndexTwo]);
}

TEST_F(DefaultVector,
IncreasesSizeWhenResizingGreaterAndReallocationIsNotNecessary) {
	PVector<int> vec({1,2,3,4,5});
	vec.reserve(10);

	vec.resize(8);
	expectedSize = 8;
	actualSize = vec.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
RemovesUnusedMemoryAtEndOfStorage) {
	PVector<int> vec;
	vec.reserve(10);
	vec.insert(AtIndexZero, 1, 1);
	vec.insert(AtIndexOne, 1, 2);
	vec.insert(AtIndexTwo, 1, 3);
	vec.insert(AtIndexThree, 1, 4);
	vec.insert(AtIndexFour, 1, 5);

	vec.squeeze();
	expectedCapacity = 5;
	actualCapacity = vec.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(DefaultVector,
PreservesSizeWhenRemovingUnusedMemory) {
	PVector<int> vec;
	vec.reserve(10);
	vec.insert(AtIndexZero, 1, 1);
	vec.insert(AtIndexOne, 1, 2);
	vec.insert(AtIndexTwo, 1, 3);
	vec.insert(AtIndexThree, 1, 4);
	vec.insert(AtIndexFour, 1, 5);

	vec.squeeze();
	expectedSize = 5;
	actualSize = vec.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(DefaultVector,
PreservesExistingElementsWhenRemovingUnusedMemory) {
	PVector<int> vec;
	vec.reserve(10);
	vec.insert(AtIndexZero, 1, 1);
	vec.insert(AtIndexOne, 1, 2);
	vec.insert(AtIndexTwo, 1, 3);
	vec.insert(AtIndexThree, 1, 4);
	vec.insert(AtIndexFour, 1, 5);

	vec.squeeze();

	ASSERT_EQ(1, vec[AtIndexZero]);
	ASSERT_EQ(2, vec[AtIndexOne]);
	ASSERT_EQ(3, vec[AtIndexTwo]);
	ASSERT_EQ(4, vec[AtIndexThree]);
	ASSERT_EQ(5, vec[AtIndexFour]);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










