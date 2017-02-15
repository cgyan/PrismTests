/*
 * DefaultVector.cpp
 *
 *  Created on: 12 Dec 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_VECTOR_TEST_H_
#define PRISM_VECTOR_TEST_H_

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/PVector>
#include <prism/OutOfBoundsException>
#include <prism/type_traits>
#include <prism/LogAllocator>
using namespace ::testing;

//#include "../src/dummy/Number.h"
#include "../src/dummy/DynamicNumber.h"

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

//using NumberType = prism::test::Number;
using NumberType = prism::test::DynamicNumber;
using Vec = prism::PVector<NumberType, prism::Allocator<NumberType>>;
using CustomAllocatorVec = prism::PVector<NumberType, prism::LogAllocator<NumberType>>;

class VectorTestBase : public Test {
protected:
	using iterator = Vec::iterator;
	using const_iterator = Vec::const_iterator;

	Vec emptyVec{};
	Vec v{1, 2, 3, 4, 5, 6};
	const Vec cv{v};

	int expectedSize{0};
	int actualSize{0};
	int expectedCapacity{0};
	int actualCapacity{0};

	NumberType newValue{500};
	NumberType nonExistentValue{789};

	enum { InvalidNegativeSize = -1, InvalidNegativeIndex = -1, InvalidPositiveIndex = 15 };
};

class VectorCreations : public VectorTestBase {
public:
	Vec defaultVector;
	Vec fillVector;
	Vec initializerListVector;
	Vec rangeVector;
	Vec copiedVector;
	Vec copyAssignedVector;

	VectorCreations()
	: defaultVector(),
	  fillVector(3, NumberType(newValue)),
	  initializerListVector({1, 2, 3, 4, 5, 6}),
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
	Vec fillVectorComparison;
	for (int i=0; i<fillVector.size(); i++)
		fillVectorComparison.append(newValue);
	ASSERT_EQ(fillVectorComparison, fillVector);
}

TEST_F(VectorCreations,
InitializerListVectorHasSizeSix) {
	ASSERT_EQ(v.size(), initializerListVector.size());
}

TEST_F(VectorCreations,
InitializerListVectorHasCapacitySix) {
	ASSERT_EQ(v.capacity(), initializerListVector.capacity());
}

TEST_F(VectorCreations,
InitializerListVectorHasElementsAtIndexs) {
	ASSERT_EQ(v, initializerListVector);
}

TEST_F(VectorCreations,
InitializerListVectorIsNotEmpty) {
	ASSERT_FALSE(initializerListVector.empty());
}

TEST_F(VectorCreations,
RangeVectorHasSizeSix) {
	ASSERT_EQ(v.size(), rangeVector.size());
}

TEST_F(VectorCreations,
RangeVectorHasCapacitySix) {
	ASSERT_EQ(v.capacity(), rangeVector.capacity());
}

TEST_F(VectorCreations,
RangeVectorHasElementsAtIndexs) {
	ASSERT_EQ(v, rangeVector);
}

TEST_F(VectorCreations,
CopyConstructedVectorHasSameSizeAsOriginalVector) {
	expectedSize = v.size();
	actualSize = copiedVector.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorCreations,
CopyConstructedVectorHasCapacityEqualToSize) {
	ASSERT_EQ(copiedVector.capacity(), copiedVector.size());
}

TEST_F(VectorCreations,
CopyConstructedVectorHasSameElementsAsOriginalVector) {
	const_iterator first = rangeVector.cbegin();
	const_iterator otherFirst = copiedVector.cbegin();
	for (; first != rangeVector.cend(); first++, otherFirst++)
		ASSERT_EQ(*first, *otherFirst);
}

TEST_F(VectorCreations,
CopyAssignedVectorHasSameSizeAsOriginalVector) {
	copyAssignedVector = initializerListVector;
	expectedSize = initializerListVector.size();
	actualSize = copyAssignedVector.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorCreations,
CopyAssignedVectorHasCapacityEqualToOriginalVector) {
	copyAssignedVector = initializerListVector;
	expectedCapacity = initializerListVector.capacity();
	actualCapacity = copyAssignedVector.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorCreations,
CopyAssignedVectorHasSameElementsAsOriginalVector) {
	copyAssignedVector = initializerListVector;
	ASSERT_EQ(copyAssignedVector, initializerListVector);
}

TEST_F(VectorCreations,
IgnoresAssigningVectorToItself) {
	Vec vCopy(v);
	v = v;
	ASSERT_EQ(v, vCopy);
}

TEST_F(VectorCreations,
MoveConstructedVectorHasSizeEqualToVectorArgumentSize) {
	int vectorSize = initializerListVector.size();
	Vec moveVector(std::move(initializerListVector));

	expectedSize = vectorSize;
	actualSize = moveVector.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorCreations,
MoveConstructedVectorHasCapacityEqualToVectorArgumentSize) {
	int vectorCapacity = initializerListVector.capacity();
	Vec moveVector(std::move(initializerListVector));

	expectedCapacity = vectorCapacity;
	actualCapacity = moveVector.capacity();
	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorCreations,
MoveConstructedVectorHasSameElementsAsArgumentVector) {
	Vec copyInitializerListVector(initializerListVector);
	Vec moveVector(std::move(initializerListVector));

	ASSERT_EQ(moveVector, copyInitializerListVector);
}

TEST_F(VectorCreations,
MovedFromVectorIsLeftInValidState) {
	Vec moveConstructedVector(std::move(initializerListVector));
	Vec moveAssignedVector;
	moveAssignedVector = std::move(rangeVector);

	ASSERT_EQ(0, initializerListVector.size());
	ASSERT_EQ(0, initializerListVector.capacity());
	ASSERT_EQ(0, rangeVector.size());
	ASSERT_EQ(0, rangeVector.capacity());
}

TEST_F(VectorCreations,
MoveAssignedVectorHasSizeEqualToOtherVector) {
	int vectorSize = initializerListVector.size();
	Vec moveVector;
	moveVector = prism::move(initializerListVector);

	expectedSize = vectorSize;
	actualSize = moveVector.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorCreations,
MoveAssignedVectorHasCapacityEqualToOtherVector) {
	int vectorCapacity = initializerListVector.capacity();
	Vec moveVector;
	moveVector = std::move(initializerListVector);

	expectedCapacity = vectorCapacity;
	actualCapacity = moveVector.capacity();
	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorCreations,
MoveAssignedVectorHasSameElementsAsOtherVector) {
	Vec copyInitializerListVector(initializerListVector);
	Vec moveVector;
	moveVector = std::move(initializerListVector);

	ASSERT_EQ(moveVector, copyInitializerListVector);
}

class VectorInvalidResizing : public VectorTestBase
{};

TEST_F(VectorInvalidResizing,
ThrowsWhenResizingToNegativeSize) {
	ASSERT_THROW(v.resize(InvalidNegativeSize), prism::BadSizeException);
}

class VectorResizing : public VectorTestBase {
public:
	int newSize;
};

TEST_F(VectorResizing,
ResizingCapacityZeroVectorCausesAllocation) {
	int originalCapacity = emptyVec.capacity();
	emptyVec.resize(10);
	int newCapacity = emptyVec.capacity();

	ASSERT_GT(newCapacity, originalCapacity);
}

TEST_F(VectorResizing,
IncreasesSizeWhenResizingGreater) {
	int oldSize = emptyVec.size();
	newSize = 15;
	emptyVec.resize(newSize);
	expectedSize = newSize;
	actualSize = emptyVec.size();

	ASSERT_GT(expectedSize, oldSize);
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorResizing,
PreservesExistingElementsWhenResizingGreater) {
	Vec copy_of_v(v);
	newSize = 8;
	v.resize(newSize);

	const_iterator first = copy_of_v.cbegin();
	const_iterator otherFirst = v.cbegin();
	for (; first != copy_of_v.cend(); first++, otherFirst++)
		ASSERT_EQ(*first, *otherFirst);
}

TEST_F(VectorResizing,
PadsWithDefaultConstructedValuesWhenResizingGreater) {
	NumberType defaultConstructedValue = NumberType();
	newSize = v.size() + 3;
	v.resize(newSize);

	ASSERT_EQ(defaultConstructedValue, v[6]);
	ASSERT_EQ(defaultConstructedValue, v[7]);
	ASSERT_EQ(defaultConstructedValue, v[8]);
}

TEST_F(VectorResizing,
PadsWithSuppliedValueWhenResizingGreater) {
	NumberType paddingValue = 23;
	newSize = v.size() + 3;
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
	newSize = 3;
	Vec copy_of_v{v};
	const_iterator first = copy_of_v.cbegin();
	const_iterator last = first + newSize;
	const_iterator otherFirst = v.cbegin();

	v.resize(newSize);

	for (; first != last; first++, otherFirst++)
		ASSERT_EQ(*first, *otherFirst);
}

TEST_F(VectorResizing,
IncreasesSizeWhenResizingGreaterAndReallocationIsNotNecessary) {
	v.reserve(10);

	newSize = 8;
	v.resize(newSize);
	expectedSize = newSize;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

class VectorInvalidMemoryReservation : public VectorTestBase
{};

TEST_F(VectorInvalidMemoryReservation,
ThrowsWhenReservingNegativeMemory) {
	ASSERT_THROW(v.reserve(InvalidNegativeSize), prism::BadSizeException);
}

class VectorMemoryReservation : public VectorTestBase {
public:
	int newCapacity;
};

TEST_F(VectorMemoryReservation,
HasCapacityEqualToReservedMemorySize) {
	newCapacity = 10;
	v.reserve(newCapacity);
	expectedCapacity = newCapacity;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorMemoryReservation,
DataIsNotNullAfterReservingMemory) {
	newCapacity = 10;
	v.reserve(newCapacity);

	ASSERT_FALSE(v.data() == nullptr);
}

TEST_F(VectorMemoryReservation,
IgnoresRequestToReserveLessMemoryThanCapacity) {
	newCapacity = 10;
	v.reserve(newCapacity);
	v.reserve(5);
	expectedCapacity = newCapacity;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorMemoryReservation,
IgnoresRequestToReserveZeroMemory) {
	newCapacity = 10;
	v.reserve(newCapacity);
	v.reserve(0);
	expectedCapacity = newCapacity;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorMemoryReservation,
PreservesExistingElementsAfterReservingMoreMemory) {
	Vec vCopy(v);
	v.reserve(20);
	ASSERT_EQ(v, vCopy);
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

class VectorReplacer : public VectorTestBase {
public:
};

TEST_F(VectorReplacer,
ReplacesValueAtIndex) {
	int replacementIndex = 0;
	v.replace(replacementIndex, newValue);

	ASSERT_EQ(newValue, v.at(replacementIndex));
}

TEST_F(VectorReplacer,
ThrowsWhenReplacingValueAtNegativeIndex) {
	ASSERT_THROW(v.replace(InvalidNegativeIndex, newValue), prism::OutOfBoundsException);
}

TEST_F(VectorReplacer,
ThrowsWhenReplacingValueAtInvalidPositiveIndex) {
	ASSERT_THROW(v.replace(InvalidPositiveIndex, newValue), prism::OutOfBoundsException);
}

class VectorSwaps : public VectorTestBase
{};

TEST_F(VectorSwaps,
VectorsSwapSize) {
	int v_size = v.size();
	emptyVec.swap(v);

	ASSERT_EQ(v_size, emptyVec.size());
	ASSERT_EQ(0, v.size());
}

TEST_F(VectorSwaps,
VectorsSwapCapacity) {
	int v_capacity = v.capacity();
	emptyVec.swap(v);

	ASSERT_EQ(v_capacity, emptyVec.capacity());
	ASSERT_EQ(0, v.capacity());
}

TEST_F(VectorSwaps,
VectorsSwapElements) {
	Vec vCopy(v);
	emptyVec.swap(v);
	ASSERT_EQ(emptyVec, vCopy);
}

class VectorSwapSpecialization : public VectorTestBase {
public:
	Vec otherVector{10,11,12};
};

TEST_F(VectorSwapSpecialization,
SwapsSize) {
	int v_size_before_swap = v.size();
	int other_vector_size_before_swap = otherVector.size();
	prism::swap(v, otherVector);

	ASSERT_EQ(other_vector_size_before_swap, v.size());
	ASSERT_EQ(v_size_before_swap, otherVector.size());
}

TEST_F(VectorSwapSpecialization,
SwapsCapacity) {
	int v_capacity_before_swap = v.capacity();
	int other_vector_capacity_before_swap = otherVector.capacity();
	prism::swap(v, otherVector);

	ASSERT_EQ(other_vector_capacity_before_swap, v.capacity());
	ASSERT_EQ(v_capacity_before_swap, otherVector.capacity());
}

TEST_F(VectorSwapSpecialization,
SwapsElements) {
	Vec vCopy(v);
	Vec otherVectorCopy(otherVector);
	prism::swap(v, otherVector);

	ASSERT_EQ(v, otherVectorCopy);
	ASSERT_EQ(otherVector, vCopy);
}

class VectorMemoryReducer : public VectorTestBase {
public:
	Vec emptyVecWithReservedMemory;
	int sizeBeforeMemoryReduced{v.size()};

	void SetUp() {
		int newCapacity = 10;
		v.reserve(newCapacity);
		emptyVecWithReservedMemory.reserve(newCapacity);
	}
};

TEST_F(VectorMemoryReducer,
RemovesUnusedMemoryAtEndOfStorage) {
	v.squeeze();
	int expectedCapacity = sizeBeforeMemoryReduced;
	int actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorMemoryReducer,
PreservesSizeWhenRemovingUnusedMemory) {
	v.squeeze();
	int expectedSize = sizeBeforeMemoryReduced;
	int actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorMemoryReducer,
PreservesExistingElementsWhenRemovingUnusedMemory) {
	Vec vCopy(v);
	v.squeeze();
	ASSERT_EQ(v, vCopy);
}

TEST_F(VectorMemoryReducer,
DefaultVectorHasCapacityZero) {
	emptyVec.squeeze();
	expectedCapacity = 0;
	actualCapacity = emptyVec.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorMemoryReducer,
EmptyVectorWithReservedMemoryHasCapacityOfZero) {
	emptyVecWithReservedMemory.squeeze();
	expectedCapacity = 0;
	actualCapacity = emptyVecWithReservedMemory.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

class VectorFill : public VectorTestBase
{};

TEST_F(VectorFill,
SetsEachElementEqualToValue) {
	Vec comparison(v.size(), newValue);
	v.fill(newValue);
	ASSERT_EQ(comparison, v);
}

class VectorAllocator : public VectorTestBase {
public:
	CustomAllocatorVec customAllocatorVector;
};

TEST_F(VectorAllocator,
ReturnsDefaultAllocator) {
	ASSERT_EQ(v.allocator(), prism::Allocator<NumberType>());
}

TEST_F(VectorAllocator,
ReturnsCustomAllocator) {
	ASSERT_EQ(customAllocatorVector.allocator(), prism::LogAllocator<NumberType>());
}

class VectorInserterBase : public VectorTestBase {
public:
	Vec frontInserted;
	Vec middleInserted;
	Vec backInserted;
	enum { FirstIndex = 0, MiddleIndex = 3, LastIndex = 6 };
	const int numElementsToInsert{3};
};

class VectorInvalidInsertion : public VectorInserterBase {
public:
	std::initializer_list<NumberType> initlist;
	Vec source;

	void
	SetUp() {
		initlist = {1,2,3,4,5,6};
		source = initlist;
	}
};

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingSingleLValueAtInvalidNegativeIndex) {
	ASSERT_THROW(v.insert(InvalidNegativeIndex, newValue), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingSingleLValueAtInvalidPositiveIndex) {
	ASSERT_THROW(v.insert(InvalidPositiveIndex, newValue), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingMultipleCopiesOfLValueAtNegativeIndex) {
	ASSERT_THROW(v.insert(InvalidNegativeIndex, numElementsToInsert, 500), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingMultipleCopiesOfLValueAtInvalidPositiveIndex) {
	ASSERT_THROW(v.insert(InvalidPositiveIndex, numElementsToInsert, 500), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingSingleLValueAtInvalidPosBeforeBegin) {
	ASSERT_THROW(v.insert(--v.cbegin(), newValue), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingSingleLValueAtInvalidPosAfterEnd) {
	ASSERT_THROW(v.insert(++v.end(), newValue), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingMultipleLValueCopiesAtInvalidPosBeforeBegin) {
	ASSERT_THROW(v.insert(--v.cbegin(), numElementsToInsert, newValue), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingMultipleLValueCopiesAtInvalidPosAfterEnd) {
	ASSERT_THROW(v.insert(++v.cend(), numElementsToInsert, newValue), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingInitListAtInvalidPosBeforeBegin) {
	ASSERT_THROW(v.insert(--v.cbegin(), initlist), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingInitListAtInvalidPosAfterEnd) {
	ASSERT_THROW(v.insert(++v.cend(), initlist), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingRangeAtInvalidPosBeforeBegin) {
	ASSERT_THROW(v.insert(--v.cbegin(), source.cbegin(), source.cend()),
			prism::OutOfBoundsException);
}

TEST_F(VectorInvalidInsertion,
ThrowsWhenInsertingRangeAtInvalidPosAfterEnd) {
	ASSERT_THROW(v.insert(++v.cend(), source.cbegin(), source.cend()),
			prism::OutOfBoundsException);
}

class VectorGeneralInsertion : public VectorInserterBase {
public:
	Vec comparisonVector;
	int insertionIndex{2};
};

TEST_F(VectorGeneralInsertion,
ShiftsElementsFromIndexUpMultiplePositions) {
	comparisonVector = Vec(v.cbegin() + insertionIndex, v.cend());
	v.reserve(20);
	v.insert(insertionIndex, numElementsToInsert, newValue);
	ASSERT_TRUE(prism::equal(v.cbegin() + insertionIndex + numElementsToInsert,
								v.cend(),
								comparisonVector.cbegin()));
}

TEST_F(VectorGeneralInsertion,
PreservesElementsBeforeInsertionPoint) {
	comparisonVector = Vec(v.cbegin(), v.cbegin() + insertionIndex);
	v.insert(insertionIndex, numElementsToInsert, newValue);
	ASSERT_TRUE(prism::equal(v.cbegin(), v.cbegin() + insertionIndex,
								comparisonVector.cbegin()));
}

TEST_F(VectorGeneralInsertion,
IncreasesSizeByNumElementsInserted) {
	int preInsertSize = v.size();

	v.insert(insertionIndex, numElementsToInsert, newValue);

	int expectedSize = preInsertSize + numElementsToInsert;
	int actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

class OneCopyInserter : public VectorInserterBase {
public:
	void SetUp() {
		frontInserted = {newValue, 1, 2, 3, 4, 5, 6 };
		middleInserted = {1, 2, 3, newValue, 4, 5, 6 };
		backInserted = {1, 2, 3, 4, 5, 6, newValue };
	}
};

TEST_F(OneCopyInserter,
InsertsRValueAtFrontIndex) {
	v.insert(FirstIndex, 500);
	ASSERT_EQ(v, frontInserted);
}

TEST_F(OneCopyInserter,
InsertsRValueAtFrontIterator) {
	v.insert(v.cbegin(), 500);
	ASSERT_EQ(v, frontInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtFrontIndex) {
	v.insert(FirstIndex, newValue);
	ASSERT_EQ(v, frontInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtFrontIterator) {
	v.insert(v.cbegin(), newValue);
	ASSERT_EQ(v, frontInserted);
}

TEST_F(OneCopyInserter,
InsertsRValueAtMiddleIndex) {
	v.insert(MiddleIndex, 500);
	ASSERT_EQ(v, middleInserted);
}

TEST_F(OneCopyInserter,
InsertsRValueAtMiddleIterator) {
	v.insert(v.cbegin() + MiddleIndex, 500);
	ASSERT_EQ(v, middleInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtMiddleIndex) {
	v.insert(MiddleIndex, newValue);
	ASSERT_EQ(v, middleInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtMiddleIterator) {
	v.insert(v.cbegin() + MiddleIndex, newValue);
	ASSERT_EQ(v, middleInserted);
}

TEST_F(OneCopyInserter,
InsertsRValueAtBackIndex) {
	v.insert(LastIndex, 500);
	ASSERT_EQ(v, backInserted);
}

TEST_F(OneCopyInserter,
InsertsRValueAtBackIterator) {
	v.insert(v.cend(), 500);
	ASSERT_EQ(v, backInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtBackIndex) {
	v.insert(LastIndex, newValue);
	ASSERT_EQ(v, backInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtBackIterator) {
	v.insert(v.cend(), newValue);
	ASSERT_EQ(v, backInserted);
}

TEST_F(OneCopyInserter,
AppendsRValue) {
	v.append(500);
	ASSERT_EQ(v, backInserted);
}

TEST_F(OneCopyInserter,
AppendsLValue) {
	v.reserve(10);
	v.append(newValue);
	ASSERT_EQ(v, backInserted);
}

TEST_F(OneCopyInserter,
AppendsLValueByStream) {
	v << newValue;
	ASSERT_EQ(v, backInserted);
}

TEST_F(OneCopyInserter,
ReturnsReferenceToVectorWhenAppendingByStream) {
	using Type = decltype(v << newValue);

	ASSERT_TRUE(prism::IsLValueReference<Type>::value);
}

TEST_F(OneCopyInserter,
AppendsLValueByAdditionAssignment) {
	v += newValue;
	ASSERT_EQ(v, backInserted);
}

TEST_F(OneCopyInserter,
ReturnsReferenceToVectorWhenAppendingLValueByAdditionAssignment) {
	using Type = decltype(v += newValue);
	ASSERT_TRUE(prism::IsLValueReference<Type>::value);
}

TEST_F(OneCopyInserter,
PrependsRValue) {
	v.prepend(500);
	ASSERT_EQ(v, frontInserted);
}

TEST_F(OneCopyInserter,
PrependLValue) {
	v.prepend(newValue);
	ASSERT_EQ(v, frontInserted);
}

TEST_F(OneCopyInserter,
ReturnsIteratorToFrontInsertedSingleLValue) {
	iterator it = v.insert(v.cbegin(), newValue);
	ASSERT_TRUE(it == v.begin());
}

TEST_F(OneCopyInserter,
ReturnsIteratorToFrontInsertedSingleRValue) {
	iterator it = v.insert(v.cbegin(), 500);
	ASSERT_TRUE(it == v.begin());
}

TEST_F(OneCopyInserter,
ReturnsIteratorToBackInsertedSingleLValue) {
	iterator it = v.insert(v.cend(), newValue);
	ASSERT_TRUE(it == --v.end());
}

TEST_F(OneCopyInserter,
ReturnsIteratorToBackInsertedSingleRValue) {
	iterator it = v.insert(v.cend(), 500);
	ASSERT_TRUE(it == --v.end());
}

class MultipleCopyInserter : public VectorInserterBase {
public:
	void SetUp() {
		frontInserted = { newValue, newValue, newValue, 1, 2, 3, 4, 5, 6 };
		middleInserted = { 1, 2, 3, newValue, newValue, newValue, 4, 5, 6 };
		backInserted = { 1, 2, 3, 4, 5, 6, newValue, newValue, newValue };
	}
};

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtFrontIndex) {
	v.insert(FirstIndex, numElementsToInsert, newValue);
	ASSERT_EQ(v, frontInserted);
}

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtFrontIterator) {
	v.insert(v.cbegin(), numElementsToInsert, newValue);
	ASSERT_EQ(v, frontInserted);
}

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtMiddleIndex) {
	v.insert(MiddleIndex, numElementsToInsert, newValue);
	ASSERT_EQ(v, middleInserted);
}

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtMiddleIterator) {
	v.insert(v.cbegin() + MiddleIndex, numElementsToInsert, newValue);
	ASSERT_EQ(v, middleInserted);
}

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtBackIndex) {
	v.insert(LastIndex, numElementsToInsert, newValue);
	ASSERT_EQ(v, backInserted);
}

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtBackIterator) {
	v.insert(v.cend(), numElementsToInsert, newValue);
	ASSERT_EQ(v, backInserted);
}

TEST_F(MultipleCopyInserter,
ReturnsIteratorToFirstOfFrontInsertedMultipleCopiesOfLValue) {
	iterator it = v.insert(v.cbegin(), numElementsToInsert, newValue);
	ASSERT_TRUE(it == v.begin());
}

TEST_F(MultipleCopyInserter,
ReturnsIteratorToFirstOfBackInsertedMultipleCopiesOfLValue) {
	iterator it = v.insert(v.cend(), numElementsToInsert, newValue);
	ASSERT_TRUE(it == v.end() - numElementsToInsert);
}

class RangeInserter : public VectorInserterBase {
public:
	Vec sourceRange;

	void SetUp() {
		sourceRange = {10, 20, 30 };
		frontInserted = { 10, 20, 30, 1, 2, 3, 4, 5, 6 };
		middleInserted = { 1, 2, 3, 10, 20, 30, 4, 5, 6 };
		backInserted = { 1, 2, 3, 4, 5, 6, 10, 20, 30 };
	}
};

TEST_F(RangeInserter,
InsertsRangeAtFrontIterator) {
	v.insert(v.cbegin(), sourceRange.cbegin(), sourceRange.cend());
	ASSERT_EQ(v, frontInserted);
}

TEST_F(RangeInserter,
InsertsRangeAtMiddleIterator) {
	v.insert(v.cbegin() + 3, sourceRange.cbegin(), sourceRange.cend());
	ASSERT_EQ(v, middleInserted);
}

TEST_F(RangeInserter,
InsertsRangeAtBackIterator) {
	v.insert(v.cend(), sourceRange.cbegin(), sourceRange.cend());
	ASSERT_EQ(v, backInserted);
}

TEST_F(RangeInserter,
InsertsRangeFromStdVector) {
	std::vector<NumberType> stdvec({10,20,30});
	v.insert(v.cbegin(), stdvec.cbegin(), stdvec.cend());
	ASSERT_EQ(v, frontInserted);
}

TEST_F(RangeInserter,
AppendsRangeFromOtherVectorToThisVector) {
	v << sourceRange;
	ASSERT_EQ(v, backInserted);
}

TEST_F(RangeInserter,
ReturnsVectorReferenceWhenAppendingRangeFromOtherVectorToThisVector) {
	using Type = decltype(v << sourceRange);
	ASSERT_TRUE(prism::IsLValueReference<Type>::value);
}

TEST_F(RangeInserter,
ConcatenateTwoVectorRangesToFormNewVector) {
	Vec concatenated = v + sourceRange;
	ASSERT_EQ(concatenated, backInserted);
}

TEST_F(RangeInserter,
OriginalSourceVectorsArePreservedWhenUsedInConcatenation) {
	Vec copyOriginal(v);
	Vec copySource(sourceRange);
	Vec concatenated = v + sourceRange;

	ASSERT_EQ(v, copyOriginal);
	ASSERT_EQ(sourceRange, copySource);
}

TEST_F(RangeInserter,
ConcatenateOtherVectorRangeToThisVector) {
	v += sourceRange;
	ASSERT_EQ(v, backInserted);
}

TEST_F(RangeInserter,
ReturnsVectorReferenceWhenConcatenatingOtherVectorRangeToThisVector) {
	using Type = decltype(v += sourceRange);
	ASSERT_TRUE(prism::IsLValueReference<Type>::value);
}

TEST_F(RangeInserter,
ReturnsIteratorToFirstElementOfFrontInsertedRange) {
	iterator it = v.insert(v.cbegin(), sourceRange.cbegin(), sourceRange.cend());
	ASSERT_TRUE(it == v.begin());
}

TEST_F(RangeInserter,
ReturnsIteratorToFirstElementOfBackInsertedRange) {
	iterator it = v.insert(v.cend(), sourceRange.cbegin(), sourceRange.cend());
	ASSERT_TRUE(it == v.end() - sourceRange.size());
}

class InitListInserter : public VectorInserterBase {
public:
	using InitList = std::initializer_list<NumberType>;
//	InitList sourceRange;

	void SetUp() {
		// Initialising the source range here causes the tests to fail for some reason
		// the underlying init list array seems to get destroyed early
//		sourceRange = { 10, 20, 30 };
		frontInserted = { 10, 20, 30, 1, 2, 3, 4, 5, 6 };
		middleInserted = { 1, 2, 3, 10, 20, 30, 4, 5, 6 };
		backInserted = { 1, 2, 3, 4, 5, 6, 10, 20, 30 };
	}
};

TEST_F(InitListInserter,
InsertsListAtFrontIterator) {
	InitList sourceRange = { 10, 20, 30 };
	v.insert(v.cbegin(), sourceRange);
	ASSERT_EQ(frontInserted, v);
}

TEST_F(InitListInserter,
InsertsListAtMiddleIterator) {
	InitList sourceRange = { 10, 20, 30 };
	v.insert(v.cbegin() + 3, sourceRange);
	ASSERT_EQ(middleInserted, v);
}

TEST_F(InitListInserter,
InsertsListAtBackIterator) {
	InitList sourceRange = { 10, 20, 30 };
	v.insert(v.cend(), sourceRange);
	ASSERT_EQ(backInserted, v);
}

TEST_F(InitListInserter,
ReturnsIteratorToFirstElementOfFrontInsertedInitList) {
	InitList sourceRange = { 10, 20, 30 };
	iterator it = v.insert(v.cbegin(), sourceRange);
	ASSERT_TRUE(it == v.begin());
}

TEST_F(InitListInserter,
ReturnsIteratorToFirstElementOfBackInsertedInitList) {
	InitList sourceRange = { 10, 20, 30 };
	iterator it = v.insert(v.cend(), sourceRange);
	ASSERT_TRUE(it == v.end() - sourceRange.size());
}

class VectorRemoverBase : public VectorTestBase {
public:
	int indexToRemove;
	const_iterator from;
	const_iterator to;
};

class VectorInvalidIndexRemovals : public VectorRemoverBase
{};

TEST_F(VectorInvalidIndexRemovals,
ThrowsWhenRemovingNegativeIndex) {
	ASSERT_THROW(v.remove(InvalidNegativeIndex), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIndexRemovals,
ThrowsWhenRemovingInvalidPositiveIndex) {
	ASSERT_THROW(v.remove(InvalidPositiveIndex), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIndexRemovals,
ThrowsWhenRemovingMultipleCopiesAtNegativeIndex) {
	int numElementsToRemove = 5;
	ASSERT_THROW(v.remove(InvalidNegativeIndex, numElementsToRemove),
			prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIndexRemovals,
ThrowsWhenRemovingMultipleCopiesAtInvalidPositiveIndex) {
	int numElementsToRemove = 5;
	ASSERT_THROW(v.remove(InvalidPositiveIndex, numElementsToRemove),
			prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIndexRemovals,
ThrowsWhenRemovingFirstElementWhenEmpty) {
	ASSERT_THROW(emptyVec.removeFirst(), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIndexRemovals,
ThrowsWhenRemovingLastElementWhenEmpty) {
	ASSERT_THROW(emptyVec.removeLast(), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIndexRemovals,
ThrowsWhenRemovingMultipleCopiesOnEmptyVector) {
	ASSERT_THROW(emptyVec.remove(0, 5), prism::OutOfBoundsException);
}

class VectorInvalidIteratorRemovals : public VectorRemoverBase {
public:

};

TEST_F(VectorInvalidIteratorRemovals,
ThrowsWhenRemovingAtPosBeforeBegin) {
	ASSERT_THROW(v.remove(--v.cbegin()), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIteratorRemovals,
ThrowsWhenRemovingAtPosAtEndOrAfter) {
	ASSERT_THROW(v.remove(v.cend()), prism::OutOfBoundsException);
	ASSERT_THROW(v.remove(++v.cend()), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIteratorRemovals,
ThrowsWhenRemovingSingleElementFromEmptyVector) {
	ASSERT_THROW(emptyVec.remove(emptyVec.cbegin()), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIteratorRemovals,
ThrowsWhenRemovingRangeFromEmptyVector) {
	ASSERT_THROW(emptyVec.remove(emptyVec.cbegin(), emptyVec.cend()),
			prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIteratorRemovals,
ThrowsWhenRemovingRangeStartingFromBeforeBegin) {
	from = --v.cbegin();
	to = v.cbegin() + 2;
	ASSERT_THROW(v.remove(from, to), prism::OutOfBoundsException);
}

TEST_F(VectorInvalidIteratorRemovals,
ThrowsWhenRemovingRangeFinishingAfterEnd) {
	from = v.cbegin();
	to = v.cend() + 2;
	ASSERT_THROW(v.remove(from, to), prism::OutOfBoundsException);
}

class VectorSingleCopyRemoverBase : public VectorRemoverBase {
public:
	Vec frontRemovedVector{2, 3, 4, 5, 6};
	Vec middleRemovedVector{1, 2, 3, 5, 6};
	Vec backRemovedVector{1, 2, 3, 4, 5};
};

class VectorSingleCopyAtIndexRemover : public VectorSingleCopyRemoverBase
{};

TEST_F(VectorSingleCopyAtIndexRemover,
DecreasesSizeByOne) {
	indexToRemove = 0;
	expectedSize = v.size() - 1;
	v.remove(indexToRemove);
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorSingleCopyAtIndexRemover,
RemovesElementAtFirstIndex) {
	indexToRemove = 0;
	v.remove(indexToRemove);
	ASSERT_EQ(frontRemovedVector, v);
}

TEST_F(VectorSingleCopyAtIndexRemover,
RemovesElementAtMiddleIndex) {
	v.remove(v.size()/2);
	ASSERT_EQ(middleRemovedVector, v);
}

TEST_F(VectorSingleCopyAtIndexRemover,
RemovesElementAtLastIndex) {
	v.remove(v.size() - 1);
	ASSERT_EQ(backRemovedVector, v);
}

class VectorSingleCopyAtIteratorRemover : public VectorSingleCopyRemoverBase
{};

TEST_F(VectorSingleCopyAtIteratorRemover,
DecreasesSizeByOne) {
	expectedSize = v.size() - 1;
	v.remove(v.cbegin());
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorSingleCopyAtIteratorRemover,
PreservesOtherElements) {
	v.remove(v.cbegin());
	ASSERT_EQ(frontRemovedVector, v);
}

TEST_F(VectorSingleCopyAtIteratorRemover,
RemovesElementPointedToByFrontIterator) {
	v.remove(v.cbegin());
	ASSERT_EQ(frontRemovedVector, v);
}

TEST_F(VectorSingleCopyAtIteratorRemover,
RemovesElementPointedToByMiddleIterator) {
	v.remove(v.cbegin() + v.size()/2);
	ASSERT_EQ(middleRemovedVector, v);
}

TEST_F(VectorSingleCopyAtIteratorRemover,
RemovesElementPointedToByBackIterator) {
	v.remove(v.cend() - 1);
	ASSERT_EQ(backRemovedVector, v);
}

TEST_F(VectorSingleCopyAtIteratorRemover,
ReturnsIteratorToBeginWhenRemovingFirstElement) {
	iterator it = v.remove(v.cbegin());
	ASSERT_TRUE(it == v.begin());
}

TEST_F(VectorSingleCopyAtIteratorRemover,
ReturnsIteratorToNewMiddleElementWhenRemovingMiddleElement) {
	int offset = v.size() / 2;
	iterator it = v.remove(v.cbegin() + offset);
	ASSERT_TRUE(it == (v.begin() + offset));
}

TEST_F(VectorSingleCopyAtIteratorRemover,
ReturnsIteratorToEndWhenRemovingLastElement) {
	iterator it = v.remove(--v.cend());
	ASSERT_TRUE(it == v.end());
}

class VectorRemoveFirstRemover : public VectorSingleCopyRemoverBase
{};

TEST_F(VectorRemoveFirstRemover,
DecreasesSizeWhenRemovingFirstElement) {
	expectedSize = v.size() - 1;
	v.removeFirst();
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemoveFirstRemover,
PreservesOtherElementsWhenRemovingFirstElement) {
	v.removeFirst();
	ASSERT_EQ(frontRemovedVector, v);
}

class VectorRemoveLastRemover : public VectorSingleCopyRemoverBase
{};

TEST_F(VectorRemoveLastRemover,
DecreasesSizeWhenRemovingLastElement) {
	expectedSize = v.size() -1;
	v.removeLast();
	actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemoveLastRemover,
PreservesOtherElementsWhenRemovingLastElement) {
	v.removeLast();
	ASSERT_EQ(backRemovedVector, v);
}

class VectorRangeRemoverBase : public VectorRemoverBase {
public:
	const int numElementsToRemove{4};
	Vec frontRemovedVector{5,6};
	Vec middleRemovedVector{1,6};
	Vec backRemovedVector{1,2};
};

class VectorMultipleElementsFromIndexRemover : public VectorRangeRemoverBase {
public:
	int indexToRemoveFrom;
};

TEST_F(VectorMultipleElementsFromIndexRemover,
DecreasesSize) {
	indexToRemoveFrom = 1;
	expectedSize = v.size() - numElementsToRemove;
	v.remove(indexToRemoveFrom, numElementsToRemove);

	actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorMultipleElementsFromIndexRemover,
RemovesFirstFewElements) {
	indexToRemoveFrom = 0;
	v.remove(indexToRemoveFrom, numElementsToRemove);
	ASSERT_EQ(frontRemovedVector, v);
}

TEST_F(VectorMultipleElementsFromIndexRemover,
RemovesMiddleFewElements) {
	indexToRemoveFrom = 1;
	v.remove(indexToRemoveFrom, numElementsToRemove);
	ASSERT_EQ(middleRemovedVector, v);
}

TEST_F(VectorMultipleElementsFromIndexRemover,
RemovesLastFewElements) {
	indexToRemoveFrom = 2;
	v.remove(indexToRemoveFrom, numElementsToRemove);
	ASSERT_EQ(backRemovedVector, v);
}

class VectorRangeRemover : public VectorRangeRemoverBase {
public:
};

TEST_F(VectorRangeRemover,
DecreasesSizeByRangeLength) {
	expectedSize = v.size() - numElementsToRemove;
	v.remove(v.cbegin(), v.cbegin() + numElementsToRemove);
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRangeRemover,
RemovesFrontRange) {
	from = v.cbegin();
	to = from + numElementsToRemove;
	v.remove(from, to);
	ASSERT_EQ(frontRemovedVector, v);
}

TEST_F(VectorRangeRemover,
RemovesMiddleRange) {
	from = v.cbegin() + 1;
	to = from + numElementsToRemove;
	v.remove(from, to);
	ASSERT_EQ(middleRemovedVector, v);
}

TEST_F(VectorRangeRemover,
RemovesBackRange) {
	from = v.cend() - numElementsToRemove;
	to = v.cend();
	v.remove(from, to);
	ASSERT_EQ(backRemovedVector, v);
}

TEST_F(VectorRangeRemover,
ReturnsIteratorToBeginAfterRemovedFrontRange) {
	from = v.cbegin();
	to = from + numElementsToRemove;
	iterator it = v.remove(from, to);
	ASSERT_TRUE(it == v.begin());
}

TEST_F(VectorRangeRemover,
ReturnsIteratorToMiddleAfterRemovedMiddleRange) {
	from = v.cbegin() + 1;
	to = from + numElementsToRemove;
	iterator it = v.remove(from, to);
	ASSERT_TRUE(it == v.begin() + 1);
}

TEST_F(VectorRangeRemover,
ReturnsIteratorToEndAfterRemovedBackRange) {
	from = v.cend() - numElementsToRemove;
	to = v.cend();
	iterator it = v.remove(from, to);
	ASSERT_TRUE(it == v.end());
}

class VectorRemoveAllElementsMatchingValueRemover : public VectorRemoverBase {
public:
	const int Zero{0};
	Vec source{0,1,0,2,0,3};
	Vec expectedVector{1,2,3};
};

TEST_F(VectorRemoveAllElementsMatchingValueRemover,
DecreasesSize) {
	source.removeAll(Zero);
	expectedSize = expectedVector.size();
	actualSize = source.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemoveAllElementsMatchingValueRemover,
PreservesOtherElements) {
	source.removeAll(Zero);
	ASSERT_EQ(expectedVector, source);
}

TEST_F(VectorRemoveAllElementsMatchingValueRemover,
SizeUnchangedWhenRemovingNonExistentValue) {
	const int sizeBeforeRemove = v.size();
	v.removeAll(nonExistentValue);
	expectedSize = sizeBeforeRemove;
	actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

class VectorRemoveIfMatchingPredRemover : public VectorRemoverBase {
public:
	std::function<bool(NumberType)>
	elementsAreOddPredicate() {
		return [](NumberType i) { return i % 2 == 1; };
	}
	Vec expectedVector{2,4,6};
};

TEST_F(VectorRemoveIfMatchingPredRemover,
DecreasesSize) {
	v.removeIf(elementsAreOddPredicate());
	expectedSize = 3;
	actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemoveIfMatchingPredRemover,
PreservesOtherElements) {
	v.removeIf(elementsAreOddPredicate());
	ASSERT_EQ(expectedVector, v);
}

TEST_F(VectorRemoveIfMatchingPredRemover,
DoesNothingIfPredMatchesNothing) {
	Vec allEven = {2, 4, 6, 8};
	Vec allEvenCopy(allEven);
	v.removeIf(elementsAreOddPredicate());
	ASSERT_EQ(allEven, allEvenCopy);
}

class VectorClearAllRemover : public VectorRemoverBase
{};

TEST_F(VectorClearAllRemover,
SetsSizeToZero) {
	v.clear();
	expectedSize = 0;
	actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorClearAllRemover,
PreservesCapacity) {
	const int newCapacity = 10;
	v.reserve(newCapacity);
	v.clear();
	expectedCapacity = newCapacity;
	actualCapacity = v.capacity();
	ASSERT_EQ(expectedCapacity, actualCapacity);
}

class InvalidElementAccess : public VectorTestBase
{};

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

class VectorElementAccess : public VectorTestBase {
public:
	Vec expectedRange, actualRange;
	const NumberType FirstValue, LastValue;
	int startIndex;
	int count;

	VectorElementAccess()
	: FirstValue(v[0]),
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

/*
 * This test has been disabled because initially when a default vector was created
 * no storage was allocated therefore the storage.start pointer was null which passed this test.
 * The decision was made instead to allocate a zero length array when a default vector is
 * created which returns a non-null pointer which causes this test to fail.
 * This test can be removed in time if no problems occur from this change in implementation.
 */
TEST_F(VectorElementAccess,
DISABLED_DataIsNullWhenVectorCreated) {
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
	ASSERT_EQ(NumberType(1), v.at(0));
	ASSERT_EQ(NumberType(2), v.at(1));
	ASSERT_EQ(NumberType(3), v.at(2));
	ASSERT_EQ(NumberType(4), v.at(3));
	ASSERT_EQ(NumberType(5), v.at(4));
	ASSERT_EQ(NumberType(6), v.at(5));
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
	ASSERT_EQ(NumberType(1), v[0]);
	ASSERT_EQ(NumberType(2), v[1]);
	ASSERT_EQ(NumberType(3), v[2]);
	ASSERT_EQ(NumberType(4), v[3]);
	ASSERT_EQ(NumberType(5), v[4]);
	ASSERT_EQ(NumberType(6), v[5]);
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

class VectorIterators : public VectorTestBase {
public:
	using reverse_iterator 			= prism::ReverseIterator<iterator>;
	using const_reverse_iterator 	= prism::ReverseIterator<const_iterator>;
};

TEST_F(VectorIterators,
BeginIteratorsPointToFirstElement) {
	iterator nonConstIter(v.data());
	const_iterator constIter(cv.cdata());

	ASSERT_TRUE(iterator(v.data()) == v.begin());
	ASSERT_TRUE(const_iterator(v.data()) == v.cbegin());
	ASSERT_TRUE(const_iterator(cv.data()) == cv.begin());
}

TEST_F(VectorIterators,
EndIteratorsPointToPositionAfterLastElement) {
	ASSERT_TRUE(iterator(v.end()) == v.end());
	ASSERT_TRUE(const_iterator(v.end()) == v.end());
	ASSERT_TRUE(const_iterator(cv.end()) == cv.cend());
}

TEST_F(VectorIterators,
EndIteratorsEqualBeginIteratorsWhenEmpty) {
	Vec emptyVec;

	ASSERT_TRUE(emptyVec.begin() == emptyVec.end());
	ASSERT_TRUE(emptyVec.cbegin() == emptyVec.cend());
	ASSERT_TRUE(emptyVec.rbegin() == emptyVec.rend());
	ASSERT_TRUE(emptyVec.crbegin() == emptyVec.crend());
}

TEST_F(VectorIterators,
ReverseBeginIteratorsPointToLastElement) {
	ASSERT_TRUE(reverse_iterator(v.end()) == v.rbegin());
	ASSERT_TRUE(const_reverse_iterator(cv.end()) == cv.rbegin());
	ASSERT_TRUE(const_reverse_iterator(cv.end()) == cv.crbegin());
}

TEST_F(VectorIterators,
ReverseEndIteratorsPointToFirstElement) {
	ASSERT_TRUE(reverse_iterator(v.begin()) == v.rend());
	ASSERT_TRUE(const_reverse_iterator(cv.begin()) == cv.rend());
	ASSERT_TRUE(const_reverse_iterator(cv.begin()) == cv.crend());
}

class VectorQueries : public VectorTestBase {
public:
	Vec queriesVector{1,2,3,4,5,3};
	int expectedIndex, actualIndex;
	int expectedCount, actualCount;
};

TEST_F(VectorQueries,
ReturnsFalseForContainsNonExistentValue) {
	ASSERT_FALSE(queriesVector.contains(nonExistentValue));
}

TEST_F(VectorQueries,
ReturnsTrueForContainsValue) {
	ASSERT_TRUE(queriesVector.contains(1));
	ASSERT_TRUE(queriesVector.contains(2));
	ASSERT_TRUE(queriesVector.contains(3));
	ASSERT_TRUE(queriesVector.contains(4));
	ASSERT_TRUE(queriesVector.contains(5));
}

TEST_F(VectorQueries,
ReturnsZeroForCountOfNonExistentValue) {
	expectedCount = 0;
	actualCount = queriesVector.count(nonExistentValue);

	ASSERT_EQ(expectedCount, actualCount);
}

TEST_F(VectorQueries,
ReturnsTwoForCountOfValue) {
	NumberType valueToCount = 3;
	expectedCount = 2;
	actualCount = queriesVector.count(valueToCount);

	ASSERT_EQ(expectedCount, actualCount);
}

TEST_F(VectorQueries,
ReturnsTrueWhenEndsWithValue) {
	NumberType value = 3;

	ASSERT_TRUE(queriesVector.endsWith(value));
}

TEST_F(VectorQueries,
ReturnsFalseWhenDoesNotEndWithValue) {
	ASSERT_FALSE(queriesVector.endsWith(nonExistentValue));
	ASSERT_FALSE(queriesVector.endsWith(5));
}

TEST_F(VectorQueries,
ReturnsFalseWhenEmptyVectorDoesNotEndWithValue) {
	Vec vec;
	NumberType value = 500;
	ASSERT_FALSE(vec.endsWith(value));
}

TEST_F(VectorQueries,
ReturnsTrueWhenStartsWithValue) {
	NumberType value = 1;

	ASSERT_TRUE(queriesVector.startsWith(value));
}

TEST_F(VectorQueries,
ReturnsFalseWhenDoesNotStartWithValue) {
	ASSERT_FALSE(queriesVector.startsWith(nonExistentValue));
}

TEST_F(VectorQueries,
ReturnsFalseWhenEmptyVectorDoesNotStartWithValue) {
	Vec vec;

	ASSERT_FALSE(vec.startsWith(500));
}

TEST_F(VectorQueries,
ReturnsIndexNotFoundForFirstIndexOfNonExistentValue) {
	NumberType valueToFind = nonExistentValue;

	ASSERT_EQ(Vec::IndexNotFound, queriesVector.indexOf(valueToFind));
}

TEST_F(VectorQueries,
ReturnsFirstIndexMatchingValue) {
	NumberType valueToFind = 3;
	expectedIndex = 2;
	actualIndex = queriesVector.indexOf(valueToFind);

	ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(VectorQueries,
ReturnsFirstIndexMatchingValueSearchingFromIndex) {
	NumberType valueToFind = 3;
	int indexToSearchFrom = 3;
	expectedIndex = 5;
	actualIndex = queriesVector.indexOf(valueToFind, indexToSearchFrom);

	ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(VectorQueries,
ReturnsIndexNotFoundForLastIndexOfNonExistentValue) {
	NumberType valueToFind = nonExistentValue;

	ASSERT_EQ(Vec::IndexNotFound, queriesVector.lastIndexOf(valueToFind));
}

TEST_F(VectorQueries,
ReturnsLastIndexMatchingValue) {
	NumberType valueToFind = 3;
	expectedIndex = 5;
	actualIndex = queriesVector.lastIndexOf(valueToFind);

	ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(VectorQueries,
ReturnsLastIndexMatchingValueSearchingFromIndex) {
	NumberType valueToFind = 3;
	int indexToSearchFrom = 4;
	expectedIndex = 2;
	actualIndex = queriesVector.lastIndexOf(valueToFind, indexToSearchFrom);

	ASSERT_EQ(expectedIndex, actualIndex);
}

class VectorConversions : public Test {
public:
	Vec emptyPrismVector;
	Vec populatedPrismVector;
	std::vector<NumberType> emptyStdVector;
	std::vector<NumberType> populatedStdVector;
	std::list<NumberType> emptyStdList;
	std::list<NumberType> populatedStdList;

	VectorConversions()
	: emptyPrismVector(),
	  populatedPrismVector({1,2,3,4,5}),
	  emptyStdVector(),
	  populatedStdVector({1,2,3,4,5}),
	  emptyStdList(),
	  populatedStdList({1,2,3,4,5})
	{}
};

TEST_F(VectorConversions,
ConvertsEmptyVectorToEmptyStdVector) {
	ASSERT_EQ(emptyStdVector, emptyPrismVector.toStdVector());
}

TEST_F(VectorConversions,
ConvertsElementsToStdVector) {
	ASSERT_EQ(populatedStdVector, populatedPrismVector.toStdVector());
}

TEST_F(VectorConversions,
ConvertsEmptyVectorToEmptyStdList) {
	ASSERT_EQ(emptyStdList, emptyPrismVector.toStdList());
}

TEST_F(VectorConversions,
ConvertsElementsToStdList) {
	ASSERT_EQ(populatedStdList, populatedPrismVector.toStdList());
}

class VectorRelationalComparisonsBase : public Test {
public:
	const bool
	isEqual(const Vec& lhs, const Vec& rhs) {
		return lhs == rhs;
	}

	const bool
	isNotEqual(const Vec& lhs, const Vec& rhs) {
		return lhs != rhs;
	}

	const bool
	isLessThan(const Vec& lhs, const Vec& rhs) {
		return lhs < rhs;
	}

	const bool
	isLessThanOrEqual(const Vec& lhs, const Vec& rhs) {
		return lhs <= rhs;
	}

	const bool
	isGreaterThan(const Vec& lhs, const Vec& rhs) {
		return lhs > rhs;
	}

	const bool
	isGreaterThanOrEqual(const Vec& lhs, const Vec& rhs) {
		return lhs >= rhs;
	}
};

class VectorEqualityComparison : public VectorRelationalComparisonsBase
{};

TEST_F(VectorEqualityComparison,
ReturnsTrueWhenTwoEmptyVectorsAreCompared) {
	ASSERT_TRUE(isEqual(Vec(), Vec()));
}

TEST_F(VectorEqualityComparison,
ReturnsTrueWhenVectorsAreEqual) {
	ASSERT_TRUE(isEqual(Vec({1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorEqualityComparison,
ReturnsFalseWhenVectorsAreUnequal) {
	ASSERT_FALSE(isEqual(Vec({1,1,1}), Vec({0,0,0})));
}

class VectorInequalityComparison : public VectorRelationalComparisonsBase
{};

TEST_F(VectorInequalityComparison,
ReturnsTrueWhenVectorsAreUnequal) {
	ASSERT_TRUE(isNotEqual(Vec({1,1,1}), Vec({0,0,0})));
}

TEST_F(VectorInequalityComparison,
ReturnsFalseWhenVectorsAreEqual) {
	ASSERT_FALSE(isNotEqual(Vec({1,1,1}), Vec({1,1,1})));
}

class VectorLessThanComparisonEqualLength : public VectorRelationalComparisonsBase
{};

TEST_F(VectorLessThanComparisonEqualLength,
ReturnsFalseWhenAllElementsEqual) {
	ASSERT_FALSE(isLessThan(Vec({1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanComparisonEqualLength,
ReturnsTrueWhenFirstElementIsLess) {
	ASSERT_TRUE(isLessThan(Vec({0,1,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanComparisonEqualLength,
ReturnsTrueWhenMiddleElementsIsLess) {
	ASSERT_TRUE(isLessThan(Vec({1,0,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanComparisonEqualLength,
ReturnsTrueWhenLastElementsIsLess) {
	ASSERT_TRUE(isLessThan(Vec({1,1,0}), Vec({1,1,1})));
}

class VectorLessThanComparisonLhsLengthShorter : public VectorRelationalComparisonsBase
{};

TEST_F(VectorLessThanComparisonLhsLengthShorter,
ReturnsTrueWhenNoElementIsLess) {
	ASSERT_TRUE(isLessThan(Vec({1,1,1}), Vec({1,1,1,1,1,1})));
}

TEST_F(VectorLessThanComparisonLhsLengthShorter,
ReturnsTrueWhenOutOfRangeElementsAreLess) {
	ASSERT_TRUE(isLessThan(Vec({1,1,1}), Vec({1,1,1,0,0,0})));
}

TEST_F(VectorLessThanComparisonLhsLengthShorter,
ReturnsTrueWhenFirstElementIsLess) {
	ASSERT_TRUE(isLessThan(Vec({0,1,1}), Vec({1,1,1,1,1,1})));
}

TEST_F(VectorLessThanComparisonLhsLengthShorter,
ReturnsTrueWhenMiddleElementIsLess) {
	ASSERT_TRUE(isLessThan(Vec({1,0,1}), Vec({1,1,1,1,1,1})));
}

TEST_F(VectorLessThanComparisonLhsLengthShorter,
ReturnsTrueWhenLastElementIsLess) {
	ASSERT_TRUE(isLessThan(Vec({1,1,0}), Vec({1,1,1,1,1,1})));
}

class VectorLessThanComparisonLhsLengthLonger : public VectorRelationalComparisonsBase
{};

TEST_F(VectorLessThanComparisonLhsLengthLonger,
ReturnsFalseWhenNoElementIsLess) {
	ASSERT_FALSE(isLessThan(Vec({1,1,1,1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanComparisonLhsLengthLonger,
ReturnsTrueWhenFirstElementIsLess) {
	ASSERT_TRUE(isLessThan(Vec({0,1,1,1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanComparisonLhsLengthLonger,
ReturnsTrueWhenSecondElementIsLess) {
	ASSERT_TRUE(isLessThan(Vec({1,0,1,1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanComparisonLhsLengthLonger,
ReturnsTrueWhenThirdElementIsLess) {
	ASSERT_TRUE(isLessThan(Vec({1,1,0,1,1,1}), Vec({1,1,1})));
}

class VectorLessThanComparisonEmpty : public VectorRelationalComparisonsBase
{};

TEST_F(VectorLessThanComparisonEmpty,
ReturnsTrueWhenLhsIsEmpty) {
	ASSERT_TRUE(isLessThan(Vec(), Vec({1,1,1})));
}

TEST_F(VectorLessThanComparisonEmpty,
ReturnsFalseWhenRhsIsEmpty) {
	ASSERT_FALSE(isLessThan(Vec({1,1,1}), Vec()));
}

TEST_F(VectorLessThanComparisonEmpty,
ReturnsFalseWhenBothEmpty) {
	ASSERT_FALSE(isLessThan(Vec(), Vec()));
}

class VectorGreaterThanComparisonEqualLength : public VectorRelationalComparisonsBase
{};

TEST_F(VectorGreaterThanComparisonEqualLength,
ReturnsFalseWhenNoElementIsGreater) {
	ASSERT_FALSE(isGreaterThan(Vec({1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorGreaterThanComparisonEqualLength,
ReturnsTrueWhenFirstElementIsGreater) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1}), Vec({0,1,1})));
}

TEST_F(VectorGreaterThanComparisonEqualLength,
ReturnsTrueWhenMiddleElementsIsGreater) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1}), Vec({1,0,1})));
}

TEST_F(VectorGreaterThanComparisonEqualLength,
ReturnsTrueWhenLastElementsIsGreater) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1}), Vec({1,1,0})));
}

class VectorGreaterThanComparisonLhsLengthShorter : public VectorRelationalComparisonsBase
{};

TEST_F(VectorGreaterThanComparisonLhsLengthShorter,
ReturnsFalseWhenNoElementIsGreater) {
	ASSERT_FALSE(isGreaterThan(Vec({1,1,1}), Vec({1,1,1,1,1,1})));
}

TEST_F(VectorGreaterThanComparisonLhsLengthShorter,
ReturnsFalseWhenOutOfRangeElementsAreGreater) {
	ASSERT_FALSE(isGreaterThan(Vec({0,0,0}), Vec({0,0,0,1,1,1})));
}

TEST_F(VectorGreaterThanComparisonLhsLengthShorter,
ReturnsTrueWhenFirstElementIsGreater) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1}), Vec({0,1,1,1,1,1})));
}

TEST_F(VectorGreaterThanComparisonLhsLengthShorter,
ReturnsTrueWhenMiddleElementIsGreater) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1}), Vec({1,0,1,1,1,1})));
}

TEST_F(VectorGreaterThanComparisonLhsLengthShorter,
ReturnsTrueWhenLastElementIsGreater) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1}), Vec({1,1,0,1,1,1})));
}

class VectorGreaterThanComparisonLhsLengthLonger : public VectorRelationalComparisonsBase {};

TEST_F(VectorGreaterThanComparisonLhsLengthLonger,
ReturnsTrueWhenNoElementIsGreater) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1,1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorGreaterThanComparisonLhsLengthLonger,
ReturnsTrueWhenFirstElementIsGreater) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1,1,1,1}), Vec({0,1,1})));
}

TEST_F(VectorGreaterThanComparisonLhsLengthLonger,
ReturnsTrueWhenSecondElementIsGreater) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1,1,1,1}), Vec({1,0,1})));
}

TEST_F(VectorGreaterThanComparisonLhsLengthLonger,
ReturnsTrueWhenThirdElementIsGreater) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1,1,1,1}), Vec({1,1,0})));
}

class VectorGreaterThanComparisonEmpty : public VectorRelationalComparisonsBase {};

TEST_F(VectorGreaterThanComparisonEmpty,
ReturnsFalseWhenLhsIsEmpty) {
	ASSERT_FALSE(isGreaterThan(Vec(), Vec({1,1,1})));
}

TEST_F(VectorGreaterThanComparisonEmpty,
ReturnsTrueWhenRhsIsEmpty) {
	ASSERT_TRUE(isGreaterThan(Vec({1,1,1}), Vec()));
}

TEST_F(VectorGreaterThanComparisonEmpty,
ReturnsFalseWhenBothEmpty) {
	ASSERT_FALSE(isGreaterThan(Vec(), Vec()));
}

class VectorLessThanOrEqualComparisonEqualLength : public VectorRelationalComparisonsBase {};

TEST_F(VectorLessThanOrEqualComparisonEqualLength,
ReturnsTrueWhenAllElementsEqual) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonEqualLength,
ReturnsTrueWhenFirstElementsIsLessThan) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({0,1,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonEqualLength,
ReturnsTrueWhenMiddleElementLessThan) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({1,0,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonEqualLength,
ReturnsTrueWhenLastElementLessThan) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({1,1,0}), Vec({1,1,1})));
}

class VectorLessThanOrEqualComparisonLhsShorter : public VectorRelationalComparisonsBase
{};

TEST_F(VectorLessThanOrEqualComparisonLhsShorter,
ReturnsTrueWhenNoElementIsLess) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({1,1,1}), Vec({1,1,1,1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonLhsShorter,
ReturnsTrueWhenWhenOutOfRangeElementsAreLessThan) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({1,1,1}), Vec({1,1,1,1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonLhsShorter,
ReturnsTrueWhenFirstElementLessThan) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({0,1,1}), Vec({1,1,1,1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonLhsShorter,
ReturnsTrueWhenMiddleElementLessThan) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({1,0,1}), Vec({1,1,1,1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonLhsShorter,
ReturnsTrueWhenLastElementLessThan) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({1,1,0}), Vec({1,1,1,1,1,1})));
}

class VectorLessThanOrEqualComparisonLhsLonger : public VectorRelationalComparisonsBase
{};

TEST_F(VectorLessThanOrEqualComparisonLhsLonger,
ReturnsFalseWhenNoElementIsLessThan) {
	ASSERT_FALSE(isLessThanOrEqual(Vec({1,1,1,1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonLhsLonger,
ReturnsTrueWhenFirstElementIsLessThan) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({0,1,1,1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonLhsLonger,
ReturnsTrueWhenSecondElementIsLessThan) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({1,0,1,1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonLhsLonger,
ReturnsTrueWhenThirdElementIsLessThan) {
	ASSERT_TRUE(isLessThanOrEqual(Vec({1,1,0,1,1,1}), Vec({1,1,1})));
}

class VectorLessThanOrEqualComparisonEmpty : public VectorRelationalComparisonsBase
{};

TEST_F(VectorLessThanOrEqualComparisonEmpty,
ReturnsTrueWhenLhsIsEmpty) {
	ASSERT_TRUE(isLessThanOrEqual(Vec(), Vec({1,1,1})));
}

TEST_F(VectorLessThanOrEqualComparisonEmpty,
ReturnsFalseWhenRhsIsEmpty) {
	ASSERT_FALSE(isLessThanOrEqual(Vec({1,1,1}), Vec()));
}

TEST_F(VectorLessThanOrEqualComparisonEmpty,
ReturnsTrueWhenBothEmpty) {
	ASSERT_TRUE(isLessThanOrEqual(Vec(), Vec()));
}

class VectorGreaterThanOrEqualComparisonEqualLength : public VectorRelationalComparisonsBase
{};

TEST_F(VectorGreaterThanOrEqualComparisonEqualLength,
ReturnsTrueWhenAllElementsAreEqual) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorGreaterThanOrEqualComparisonEqualLength,
ReturnsTrueWhenFirstElementIsGreater) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1}), Vec({0,1,1})));
}

TEST_F(VectorGreaterThanOrEqualComparisonEqualLength,
ReturnsTrueWhenMiddleElementIsGreater) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1}), Vec({1,0,1})));
}

TEST_F(VectorGreaterThanOrEqualComparisonEqualLength,
ReturnsTrueWhenLastElementIsGreater) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1}), Vec({1,1,0})));
}

class VectorGreaterThanOrEqualComparisonLhsShorter : public VectorRelationalComparisonsBase
{};

TEST_F(VectorGreaterThanOrEqualComparisonLhsShorter,
ReturnsFalseWhenAllElementsEqual) {
	ASSERT_FALSE(isGreaterThanOrEqual(Vec({1,1,1}), Vec({1,1,1,1,1,1})));
}

TEST_F(VectorGreaterThanOrEqualComparisonLhsShorter,
ReturnsTrueWhenFirstElementIsGreater) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1}), Vec({0,1,1,1,1,1})));
}

TEST_F(VectorGreaterThanOrEqualComparisonLhsShorter,
ReturnsTrueWhenMiddleElementIsGreater) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1}), Vec({1,0,1,1,1,1})));
}

TEST_F(VectorGreaterThanOrEqualComparisonLhsShorter,
ReturnsTrueWhenLastElementIsGreater) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1}), Vec({1,1,0,1,1,1})));
}

class VectorGreaterThanOrEqualComparisonLhsLonger : public VectorRelationalComparisonsBase
{};

TEST_F(VectorGreaterThanOrEqualComparisonLhsLonger,
ReturnsTrueWhenAllElementsEqual) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1,1,1,1}), Vec({1,1,1})));
}

TEST_F(VectorGreaterThanOrEqualComparisonLhsLonger,
ReturnsTrueWhenFirstElementIsGreater) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1,1,1,1}), Vec({0,1,1})));
}

TEST_F(VectorGreaterThanOrEqualComparisonLhsLonger,
ReturnsTrueWhenSecondElementIsGreater) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1,1,1,1}), Vec({1,0,1})));
}

TEST_F(VectorGreaterThanOrEqualComparisonLhsLonger,
ReturnsTrueWhenThirdElementIsGreater) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1,1,1,1}), Vec({1,1,0})));
}

class VectorGreaterThanOrEqualComparisonEmpty : public VectorRelationalComparisonsBase
{};

TEST_F(VectorGreaterThanOrEqualComparisonEmpty,
ReturnsFalseWhenLhsEmpty) {
	ASSERT_FALSE(isGreaterThanOrEqual(Vec(), Vec({1,1,1})));
}

TEST_F(VectorGreaterThanOrEqualComparisonEmpty,
ReturnsTrueWhenRhsEmpty) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec({1,1,1}), Vec()));
}

TEST_F(VectorGreaterThanOrEqualComparisonEmpty,
ReturnsTrueWhenBothEmpty) {
	ASSERT_TRUE(isGreaterThanOrEqual(Vec(), Vec()));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE


#endif /* PRISM_VECTOR_TEST_H_ */













