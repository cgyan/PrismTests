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

/*
 todo: unit tests....
 allocator
 nonmember functions
 */

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class VectorTestBase : public Test {
protected:
	PVector<int> emptyVec;
	PVector<int> v;
	int expectedSize, actualSize;
	int expectedCapacity, actualCapacity;
	enum { InvalidNegativeSize = -1, InvalidNegativeIndex = -1, InvalidPositiveIndex = 15 };

	VectorTestBase()
	: v({1,2,3,4,5,6}),
	  expectedSize(0), actualSize(0),
	  expectedCapacity(0), actualCapacity(0)
	{}
};

class VectorCreations : public VectorTestBase {
public:
	PVector<int> defaultVector;
	PVector<int> fillVector;
	PVector<int> initializerListVector;
	PVector<int> rangeVector;
	PVector<int> copiedVector;
	PVector<int> copyAssigedVector;

	VectorCreations()
	: defaultVector(),
	  fillVector(3, 123),
	  initializerListVector({1,2,3,4,5}),
	  rangeVector(initializerListVector.cbegin(), initializerListVector.cend()),
	  copiedVector(rangeVector)
	{}
};

TEST_F(VectorCreations,
DefaultVectorHasSizeZero) {
	ASSERT_EQ(0, defaultVector.size());
}

TEST_F(VectorCreations,
DefaultVectorHasCapacityZero) {
	ASSERT_EQ(0, defaultVector.capacity());
}

TEST_F(VectorCreations,
DefaultVectorIsEmpty) {
	ASSERT_TRUE(defaultVector.empty());
}

TEST_F(VectorCreations,
FilledVectorHasSizeThree) {
	ASSERT_EQ(3, fillVector.size());
}

TEST_F(VectorCreations,
FilledVectorHasCapacityThree) {
	ASSERT_EQ(3, fillVector.capacity());
}

TEST_F(VectorCreations,
FilledVectorIsNotEmpty) {
	ASSERT_FALSE(fillVector.empty());
}

TEST_F(VectorCreations,
FilledVectorHasEachElementEqualToValue) {
	ASSERT_EQ(123, fillVector.at(0));
	ASSERT_EQ(123, fillVector.at(1));
	ASSERT_EQ(123, fillVector.at(2));
}

TEST_F(VectorCreations,
InitializerListVectorHasSizeFive) {
	ASSERT_EQ(5, initializerListVector.size());
}

TEST_F(VectorCreations,
InitializerListVectorHasCapacityFive) {
	ASSERT_EQ(5, initializerListVector.capacity());
}

TEST_F(VectorCreations,
InitializerListVectorHasElementsAtIndexs) {
	ASSERT_EQ(1, initializerListVector[0]);
	ASSERT_EQ(2, initializerListVector[1]);
	ASSERT_EQ(3, initializerListVector[2]);
	ASSERT_EQ(4, initializerListVector[3]);
	ASSERT_EQ(5, initializerListVector[4]);
}

TEST_F(VectorCreations,
InitializerListVectorIsNotEmpty) {
	ASSERT_FALSE(initializerListVector.empty());
}

TEST_F(VectorCreations,
RangeVectorHasSizeFive) {
	ASSERT_EQ(5, rangeVector.size());
}

TEST_F(VectorCreations,
RangeVectorHasCapacityFive) {
	ASSERT_EQ(5, rangeVector.capacity());
}

TEST_F(VectorCreations,
RangeVectorHasElementsAtIndexs) {
	ASSERT_EQ(1, rangeVector[0]);
	ASSERT_EQ(2, rangeVector[1]);
	ASSERT_EQ(3, rangeVector[2]);
	ASSERT_EQ(4, rangeVector[3]);
	ASSERT_EQ(5, rangeVector[4]);
}

TEST_F(VectorCreations,
CopyConstructedVectorHasSameSizeAsOriginalVector) {
	expectedSize = 5;
	actualSize = copiedVector.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorCreations,
CopyConstructedVectorHasCapacityEqualToSize) {
	ASSERT_EQ(copiedVector.capacity(), copiedVector.size());
}

TEST_F(VectorCreations,
CopyConstructedVectorHasSameElementsAsOriginalVector) {
	ASSERT_EQ(rangeVector[0], copiedVector[0]);
	ASSERT_EQ(rangeVector[1], copiedVector[1]);
	ASSERT_EQ(rangeVector[2], copiedVector[2]);
	ASSERT_EQ(rangeVector[3], copiedVector[3]);
	ASSERT_EQ(rangeVector[4], copiedVector[4]);
}

TEST_F(VectorCreations,
CopyAssignedVectorHasSameSizeAsOriginalVector) {
	copyAssigedVector = initializerListVector;
	expectedSize = 5;
	actualSize = copyAssigedVector.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorCreations,
CopyAssignedVectorHasCapacityEqualToOriginalVector) {
	copyAssigedVector = initializerListVector;
	expectedCapacity = initializerListVector.capacity();
	actualCapacity = copyAssigedVector.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorCreations,
CopyAssignedVectorHasSameElementsAsOriginalVector) {
	copyAssigedVector = initializerListVector;

	ASSERT_EQ(copyAssigedVector[0], initializerListVector[0]);
	ASSERT_EQ(copyAssigedVector[1], initializerListVector[1]);
	ASSERT_EQ(copyAssigedVector[2], initializerListVector[2]);
	ASSERT_EQ(copyAssigedVector[3], initializerListVector[3]);
	ASSERT_EQ(copyAssigedVector[4], initializerListVector[4]);
}

TEST_F(VectorCreations,
MoveConstructedVectorHasSizeEqualToVectorArgumentSize) {
	int vectorSize = initializerListVector.size();
	PVector<int> moveVector(std::move(initializerListVector));

	expectedSize = vectorSize;
	actualSize = moveVector.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorCreations,
MoveConstructedVectorHasCapacityEqualToVectorArgumentSize) {
	int vectorCapacity = initializerListVector.capacity();
	PVector<int> moveVector(std::move(initializerListVector));

	expectedCapacity = vectorCapacity;
	actualCapacity = moveVector.capacity();
	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorCreations,
MoveConstructedVectorHasSameElementsAsArgumentVector) {
	PVector<int> copyInitializerListVector(initializerListVector);
	PVector<int> moveVector(std::move(initializerListVector));

	ASSERT_EQ(moveVector, copyInitializerListVector);
}

TEST_F(VectorCreations,
MoveAssignedVectorHasSizeEqualToOtherVector) {
	int vectorSize = initializerListVector.size();
	PVector<int> moveVector;
	moveVector = PVector<int>({1,2,3,4,5});

	expectedSize = vectorSize;
	actualSize = moveVector.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorCreations,
MoveAssignedVectorHasCapacityEqualToOtherVector) {
	int vectorCapacity = initializerListVector.capacity();
	PVector<int> moveVector;
	moveVector = std::move(initializerListVector);

	expectedCapacity = vectorCapacity;
	actualCapacity = moveVector.capacity();
	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorCreations,
MoveAssignedVectorHasSameElementsAsOtherVector) {
	PVector<int> copyInitializerListVector(initializerListVector);
	PVector<int> moveVector;
	moveVector = std::move(initializerListVector);

	ASSERT_EQ(moveVector, copyInitializerListVector);
}

class InvalidVectorResizing : public VectorTestBase
{};

TEST_F(InvalidVectorResizing,
ThrowsWhenResizingToNegativeSize) {
	ASSERT_THROW(v.resize(InvalidNegativeSize), prism::OutOfBoundsException);
}

class VectorResizing : public VectorTestBase
{};

TEST_F(VectorResizing,
ResizingCapacityZeroVectorCausesAllocation) {
	emptyVec.resize(10);
	int newCapacity = emptyVec.capacity();
	int originalCapacity = 0;

	ASSERT_GT(newCapacity, originalCapacity);
}

TEST_F(VectorResizing,
IncreasesSizeWhenResizingGreater) {
	int oldSize = emptyVec.size();
	int newSize = 15;
	emptyVec.resize(newSize);
	int expectedSize = newSize;
	int actualSize = emptyVec.size();

	ASSERT_GT(expectedSize, oldSize);
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorResizing,
PreservesExistingElementsWhenResizingGreater) {
	int newSize = 8;
	v.resize(newSize);

	ASSERT_EQ(1, v[0]);
	ASSERT_EQ(2, v[1]);
	ASSERT_EQ(3, v[2]);
	ASSERT_EQ(4, v[3]);
	ASSERT_EQ(5, v[4]);
	ASSERT_EQ(6, v[5]);
}

TEST_F(VectorResizing,
PadsWithDefaultConstructedValuesWhenResizingGreater) {
	int defaultConstructedValue = int();
	int newSize = v.size() + 3;
	v.resize(newSize);

	ASSERT_EQ(defaultConstructedValue, v[6]);
	ASSERT_EQ(defaultConstructedValue, v[7]);
	ASSERT_EQ(defaultConstructedValue, v[8]);
}

TEST_F(VectorResizing,
PadsWithSuppliedValueWhenResizingGreater) {
	int paddingValue = 23;
	int newSize = v.size() + 3;
	v.resize(newSize, paddingValue);

	ASSERT_EQ(paddingValue, v[6]);
	ASSERT_EQ(paddingValue, v[7]);
	ASSERT_EQ(paddingValue, v[8]);
}

TEST_F(VectorResizing,
DecreasesSizeWhenResizingSmaller) {
	v.resize(3);
	expectedSize = 3;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorResizing,
PreservesCapacityWhenResizingSmaller) {
	int oldCapacity = v.capacity();

	v.resize(3);
	expectedCapacity = oldCapacity;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorResizing,
PreservesExistingElementsWhenResizingSmaller) {
	v.resize(3);

	ASSERT_EQ(1, v[0]);
	ASSERT_EQ(2, v[1]);
	ASSERT_EQ(3, v[2]);
}

TEST_F(VectorResizing,
IncreasesSizeWhenResizingGreaterAndReallocationIsNotNecessary) {
	v.reserve(10);

	int newSize = 8;
	v.resize(newSize);
	expectedSize = newSize;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

class InvalidVectorMemoryReservation : public VectorTestBase
{};

TEST_F(InvalidVectorMemoryReservation,
ThrowsWhenReservingNegativeMemory) {
	ASSERT_THROW(v.reserve(InvalidNegativeSize), std::bad_alloc);
}

class VectorMemoryReservation : public VectorTestBase
{};

TEST_F(VectorMemoryReservation,
HasCapacityEqualToReservedMemorySize) {
	v.reserve(10);
	expectedCapacity = 10;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorMemoryReservation,
DataIsNotNullAfterReservingMemory) {
	v.reserve(10);

	ASSERT_FALSE(v.data() == nullptr);
}

TEST_F(VectorMemoryReservation,
IgnoresRequestToReserveLessMemoryThanCapacity) {
	v.reserve(10);
	v.reserve(5);
	expectedCapacity = 10;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorMemoryReservation,
IgnoresRequestToReserveZeroMemory) {
	v.reserve(10);
	v.reserve(0);
	expectedCapacity = 10;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorMemoryReservation,
PreservesExistingElementsAfterReservingMoreMemory) {
	v.reserve(20);

	ASSERT_EQ(1, v.at(0));
	ASSERT_EQ(2, v.at(1));
	ASSERT_EQ(3, v.at(2));
	ASSERT_EQ(4, v.at(3));
	ASSERT_EQ(5, v.at(4));
	ASSERT_EQ(6, v.at(5));
}

class VectorSizeAndCapacity : public VectorTestBase
{};

TEST_F(VectorSizeAndCapacity,
IsEmptyOnConstruction) {
	bool expected = true;
	bool actual = emptyVec.empty();

	ASSERT_EQ(expected, actual);
}

TEST_F(VectorSizeAndCapacity,
IsNotEmptyAfterInsertion) {
	emptyVec.append(500);

	ASSERT_FALSE(emptyVec.empty());
}

TEST_F(VectorSizeAndCapacity,
EmptyVectorHasSizeZero) {
	expectedSize = 0;
	actualSize = emptyVec.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorSizeAndCapacity,
EmptyVectorHasCapacityZero) {
	expectedCapacity = 0;
	actualCapacity = emptyVec.capacity();
	ASSERT_EQ(expectedCapacity, actualCapacity);
}

class VectorReplaceValues : public VectorTestBase {
public:
	enum { NewValue = 500 };
};

TEST_F(VectorReplaceValues,
ReplacesValueAtIndex) {
	int replacementIndex = 0;
	v.replace(replacementIndex, NewValue);

	ASSERT_EQ(NewValue, v.at(replacementIndex));
}

TEST_F(VectorReplaceValues,
ThrowsWhenReplacingValueAtNegativeIndex) {
	ASSERT_THROW(v.replace(InvalidNegativeIndex, NewValue), prism::OutOfBoundsException);
}

TEST_F(VectorReplaceValues,
ThrowsWhenReplacingValueAtInvalidPositiveIndex) {
	ASSERT_THROW(v.replace(InvalidPositiveIndex, NewValue), prism::OutOfBoundsException);
}

class VectorSwaps : public VectorTestBase
{};

TEST_F(VectorSwaps,
VectorsSwapSize) {
	emptyVec.swap(v);

	ASSERT_EQ(6, emptyVec.size());
	ASSERT_EQ(0, v.size());
}

TEST_F(VectorSwaps,
VectorsSwapCapacity) {
	emptyVec.swap(v);

	ASSERT_EQ(6, emptyVec.capacity());
	ASSERT_EQ(0, v.capacity());
}

TEST_F(VectorSwaps,
VectorsSwapElements) {
	emptyVec.swap(v);

	ASSERT_EQ(1, emptyVec[0]);
	ASSERT_EQ(2, emptyVec[1]);
	ASSERT_EQ(3, emptyVec[2]);
	ASSERT_EQ(4, emptyVec[3]);
	ASSERT_EQ(5, emptyVec[4]);
	ASSERT_EQ(6, emptyVec[5]);
}

class VectorMemoryReducer : public VectorTestBase {
public:
	int size;

	VectorMemoryReducer()
	: size(v.size())
	{
		v.reserve(10);
	}
};

TEST_F(VectorMemoryReducer,
RemovesUnusedMemoryAtEndOfStorage) {
	v.squeeze();
	int expectedCapacity = size;
	int actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorMemoryReducer,
PreservesSizeWhenRemovingUnusedMemory) {
	v.squeeze();
	int expectedSize = size;
	int actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorMemoryReducer,
PreservesExistingElementsWhenRemovingUnusedMemory) {
	v.squeeze();

	ASSERT_EQ(1, v[0]);
	ASSERT_EQ(2, v[1]);
	ASSERT_EQ(3, v[2]);
	ASSERT_EQ(4, v[3]);
	ASSERT_EQ(5, v[4]);
}

class VectorFill : public VectorTestBase
{};

TEST_F(VectorFill,
SetsEachElementEqualToValue) {
	int newValue = 25;
	v.fill(newValue);

	ASSERT_EQ(newValue, v[0]);
	ASSERT_EQ(newValue, v[1]);
	ASSERT_EQ(newValue, v[2]);
	ASSERT_EQ(newValue, v[3]);
	ASSERT_EQ(newValue, v[4]);
	ASSERT_EQ(newValue, v[5]);
}

class VectorAllocator : public VectorTestBase
{};

TEST_F(VectorAllocator,
ReturnsDefaultAllocator) {
	ASSERT_EQ(v.allocator(), prism::Allocator<int>());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










