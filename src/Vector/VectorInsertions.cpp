/*
 * Inserter.cpp
 * v0.*
 *
 *  Created on: 16 Jan 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/PVector>
#include <prism/global>
#include <vector>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class InvalidInsertion : public Test {
public:
	PVector<int> v;
	enum { InvalidNegativeIndex = -1, InvalidPositiveIndex = 15 };
};

TEST_F(InvalidInsertion,
ThrowsWhenInsertingAtNegativeIndex) {
	ASSERT_THROW(v.insert(InvalidNegativeIndex, 1, 500), prism::OutOfBoundsException);
}

TEST_F(InvalidInsertion,
ThrowsWhenInsertingAtInvalidPositiveIndex) {
	ASSERT_THROW(v.insert(InvalidPositiveIndex, 1, 500), prism::OutOfBoundsException);
}

class GeneralInsertion : public Test {
public:
	PVector<int> v;
	GeneralInsertion()
	: v({1,2,3,4,5})
	{}
};

TEST_F(GeneralInsertion,
ShiftsElementsFromIndexUpMultiplePositions) {
	v.reserve(20);

	int insertionIndex = 1;
	int numCopies = 3;
	int newValue = 500;
	v.insert(insertionIndex, numCopies, newValue);

	ASSERT_EQ(2, v[4]);
	ASSERT_EQ(3, v[5]);
	ASSERT_EQ(4, v[6]);
	ASSERT_EQ(5, v[7]);
}

TEST_F(GeneralInsertion,
PreservesElementsBeforeInsertionPoint) {
	int insertionIndex = 2;
	int numCopies = 3;
	int value = 500;
	v.insert(insertionIndex, numCopies, value);

	ASSERT_EQ(1, v[0]);
	ASSERT_EQ(2, v[1]);
}

TEST_F(GeneralInsertion,
IncreasesSizeByNumElementsInserted) {
	int insertionIndex = 0;
	int numCopiesOf = 4;
	int value = 500;
	v.insert(insertionIndex, numCopiesOf, value);

	int expectedSize = 9;
	int actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

class OneCopyInserter : public Test {
public:
	const int ValueToInsert;
	PVector<int> original;
	PVector<int> frontInserted;
	PVector<int> middleInserted;
	PVector<int> backInserted;
	enum { FirstIndex = 0, MiddleIndex = 3, LastIndex = 6 };

	OneCopyInserter()
	: ValueToInsert(500),
	  original({1, 2, 3, 4, 5, 6 }),
	  frontInserted({ValueToInsert, 1, 2, 3, 4, 5, 6 }),
	  middleInserted({1, 2, 3, ValueToInsert, 4, 5, 6 }),
	  backInserted({1, 2, 3, 4, 5, 6, ValueToInsert })
	{}
};

TEST_F(OneCopyInserter,
InsertsRValueAtFrontIndex) {
	original.insert(FirstIndex, 500);
	ASSERT_EQ(original, frontInserted);
}

TEST_F(OneCopyInserter,
InsertsRValueAtFrontIterator) {
	original.insert(original.cbegin(), 500);
	ASSERT_EQ(original, frontInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtFrontIndex) {
	original.insert(FirstIndex, ValueToInsert);
	ASSERT_EQ(original, frontInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtFrontIterator) {
	original.insert(original.cbegin(), ValueToInsert);
	ASSERT_EQ(original, frontInserted);
}

TEST_F(OneCopyInserter,
InsertsRValueAtMiddleIndex) {
	original.insert(MiddleIndex, 500);
	ASSERT_EQ(original, middleInserted);
}

TEST_F(OneCopyInserter,
InsertsRValueAtMiddleIterator) {
	original.insert(original.cbegin() + MiddleIndex, 500);
	ASSERT_EQ(original, middleInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtMiddleIndex) {
	original.insert(MiddleIndex, ValueToInsert);
	ASSERT_EQ(original, middleInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtMiddleIterator) {
	original.insert(original.cbegin() + MiddleIndex, ValueToInsert);
	ASSERT_EQ(original, middleInserted);
}

TEST_F(OneCopyInserter,
InsertsRValueAtBackIndex) {
	original.insert(LastIndex, 500);
	ASSERT_EQ(original, backInserted);
}

TEST_F(OneCopyInserter,
InsertsRValueAtBackIterator) {
	original.insert(original.cend(), 500);
	ASSERT_EQ(original, backInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtBackIndex) {
	original.insert(LastIndex, ValueToInsert);
	ASSERT_EQ(original, backInserted);
}

TEST_F(OneCopyInserter,
InsertsLValueAtBackIterator) {
	original.insert(original.cend(), ValueToInsert);
	ASSERT_EQ(original, backInserted);
}

TEST_F(OneCopyInserter,
AppendsRValue) {
	original.append(500);
	ASSERT_EQ(original, backInserted);
}

TEST_F(OneCopyInserter,
AppendsLValue) {
	original.append(ValueToInsert);
	ASSERT_EQ(original, backInserted);
}

TEST_F(OneCopyInserter,
AppendsLValueByStream) {
	original << ValueToInsert;
	ASSERT_EQ(original, backInserted);
}

TEST_F(OneCopyInserter,
ReturnsReferenceToVectorWhenAppendingByStream) {
	using Type = decltype(original << ValueToInsert);

	ASSERT_TRUE(prism::IsLValueReference<Type>::value);
}

TEST_F(OneCopyInserter,
AppendsLValueByAdditionAssignment) {
	original += ValueToInsert;
	ASSERT_EQ(original, backInserted);
}

TEST_F(OneCopyInserter,
ReturnsReferenceToVectorWhenAppendingLValueByAdditionAssignment) {
	using Type = decltype(original += ValueToInsert);
	ASSERT_TRUE(prism::IsLValueReference<Type>::value);
}

TEST_F(OneCopyInserter,
PrependsRValue) {
	original.prepend(500);
	ASSERT_EQ(original, frontInserted);
}

TEST_F(OneCopyInserter,
PrependLValue) {
	original.prepend(ValueToInsert);
	ASSERT_EQ(original, frontInserted);
}

TEST_F(OneCopyInserter,
ReturnsIteratorToInsertedValue) {
	PVector<int>::iterator it = original.insert(original.cbegin(), ValueToInsert);
	ASSERT_TRUE(it == original.begin());
}

class MultipleCopyInserter : public Test {
public:
	const int ValueToInsert;
	const int NumCopies;
	PVector<int> original;
	PVector<int> frontInserted;
	PVector<int> middleInserted;
	PVector<int> backInserted;
	enum { FirstIndex = 0, MiddleIndex = 3, LastIndex = 6 };

	MultipleCopyInserter()
	: ValueToInsert(500),
	  NumCopies(3),
	  original({ 1, 2, 3, 4, 5, 6 }),
	  frontInserted({ 500, 500, 500, 1, 2, 3, 4, 5, 6 }),
	  middleInserted({ 1, 2, 3, 500, 500, 500, 4, 5, 6 }),
	  backInserted({ 1, 2, 3, 4, 5, 6, 500, 500, 500 })
	{}
};

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtFrontIndex) {
	original.insert(FirstIndex, NumCopies, ValueToInsert);
	ASSERT_EQ(original, frontInserted);
}

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtFrontIterator) {
	original.insert(original.cbegin(), NumCopies, ValueToInsert);
	ASSERT_EQ(original, frontInserted);
}

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtMiddleIndex) {
	original.insert(MiddleIndex, NumCopies, ValueToInsert);
	ASSERT_EQ(original, middleInserted);
}

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtMiddleIterator) {
	original.insert(original.cbegin() + MiddleIndex, NumCopies, ValueToInsert);
	ASSERT_EQ(original, middleInserted);
}

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtBackIndex) {
	original.insert(LastIndex, NumCopies, ValueToInsert);
	ASSERT_EQ(original, backInserted);
}

TEST_F(MultipleCopyInserter,
InsertsMultipleLValueAtBackIterator) {
	original.insert(original.cend(), NumCopies, ValueToInsert);
	ASSERT_EQ(original, backInserted);
}

class RangeInserter : public Test {
public:
	PVector<int> source;
	PVector<int> original;
	PVector<int> frontInserted;
	PVector<int> middleInserted;
	PVector<int> backInserted;
	PVector<int> originalWithSourceAppended;

	RangeInserter()
	: source({10, 20, 30 }),
	  original({ 1, 2, 3, 4, 5, 6 }),
	  frontInserted({ 10, 20, 30, 1, 2, 3, 4, 5, 6 }),
	  middleInserted({ 1, 2, 3, 10, 20, 30, 4, 5, 6 }),
	  backInserted({ 1, 2, 3, 4, 5, 6, 10, 20, 30 })
	{}
};

TEST_F(RangeInserter,
InsertsRangeAtFrontIterator) {
	original.insert(original.cbegin(), source.cbegin(), source.cend());
	ASSERT_EQ(original, frontInserted);
}

TEST_F(RangeInserter,
InsertsRangeAtMiddleIterator) {
	original.insert(original.cbegin() + 3, source.cbegin(), source.cend());
	ASSERT_EQ(original, middleInserted);
}

TEST_F(RangeInserter,
InsertsRangeAtBackIterator) {
	original.insert(original.cend(), source.cbegin(), source.cend());
	ASSERT_EQ(original, backInserted);
}

TEST_F(RangeInserter,
InsertsRangeFromStdVector) {
	std::vector<int> stdvec({10,20,30});
	original.insert(original.cbegin(), stdvec.cbegin(), stdvec.cend());
	ASSERT_EQ(original, frontInserted);
}

TEST_F(RangeInserter,
AppendsRangeFromOtherVectorToThisVector) {
	original << source;
	ASSERT_EQ(original, backInserted);
}

TEST_F(RangeInserter,
ReturnsVectorReferenceWhenAppendingRangeFromOtherVectorToThisVector) {
	using Type = decltype(original << source);
	ASSERT_TRUE(prism::IsLValueReference<Type>::value);
}

TEST_F(RangeInserter,
ConcatenateTwoVectorRangesToFormNewVector) {
	PVector<int> concatenated = original + source;
	ASSERT_EQ(concatenated, backInserted);
}

TEST_F(RangeInserter,
OriginalSourceVectorsArePreservedWhenUsedInConcatenation) {
	PVector<int> copyOriginal(original);
	PVector<int> copySource(source);
	PVector<int> concatenated = original + source;

	ASSERT_EQ(original, copyOriginal);
	ASSERT_EQ(source, copySource);
}

TEST_F(RangeInserter,
ConcatenateOtherVectorRangeToThisVector) {
	original += source;
	ASSERT_EQ(original, backInserted);
}

TEST_F(RangeInserter,
ReturnsVectorReferenceWhenConcatenatingOtherVectorRangeToThisVector) {
	using Type = decltype(original += source);
	ASSERT_TRUE(prism::IsLValueReference<Type>::value);
}

class InitListInserter : public Test {
public:
	std::initializer_list<int> list;
	PVector<int> original;
	PVector<int> frontInserted;
	PVector<int> middleInserted;
	PVector<int> backInserted;

	InitListInserter()
	: list({ 10, 20, 30 }),
	  original({ 1,2 ,3 ,4 ,5, 6 }),
	  frontInserted({ 10, 20, 30, 1, 2, 3, 4, 5, 6 }),
	  middleInserted({ 1, 2, 3, 10, 20, 30, 4, 5, 6 }),
	  backInserted({ 1, 2, 3, 4, 5, 6, 10, 20, 30 })
	{}
};

TEST_F(InitListInserter,
InsertsListAtFrontIterator) {
	original.insert(original.cbegin(), list);
	ASSERT_EQ(original, frontInserted);
}

TEST_F(InitListInserter,
InsertsListAtMiddleIterator) {
	original.insert(original.cbegin() + 3, list);
	ASSERT_EQ(original, middleInserted);
}

TEST_F(InitListInserter,
InsertsListAtBackIterator) {
	original.insert(original.cend(), list);
	ASSERT_EQ(original, backInserted);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE













