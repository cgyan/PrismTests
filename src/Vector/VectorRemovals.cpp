/*
 * VectorRemovals.cpp
 * v0.*
 *
 *  Created on: 17 Jan 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/PVector>
#include <prism/global>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class InvalidRemovals : public Test {
public:
	PVector<int> v;
	PVector<int> emptyVec;
	enum { InvalidNegativeIndex = -1, InvalidPositiveIndex = 15 };

	InvalidRemovals()
	: v({1,2,3,4,5,6})
	{}
};

TEST_F(InvalidRemovals,
ThrowsWhenRemovingNegativeIndex) {
	ASSERT_THROW(v.remove(InvalidNegativeIndex), prism::OutOfBoundsException);
}

TEST_F(InvalidRemovals,
ThrowsWhenRemovingInvalidPositiveIndex) {
	ASSERT_THROW(v.remove(InvalidPositiveIndex), prism::OutOfBoundsException);
}

TEST_F(InvalidRemovals,
ThrowsWhenRemovingFirstElementWhenEmpty) {
	ASSERT_THROW(emptyVec.removeFirst(), prism::OutOfBoundsException);
}

TEST_F(InvalidRemovals,
ThrowsWhenRemovingLastElementWhenEmpty) {
	ASSERT_THROW(emptyVec.removeLast(), prism::OutOfBoundsException);
}

class VectorRemovals : public Test {
public:
	PVector<int> v;
	PVector<int> emptyVec;
	int expectedSize, actualSize;
	int expectedCapacity, actualCapacity;
	int index;

	VectorRemovals()
	: v({1,2,3,4,5,6}), emptyVec(),
	  expectedSize(0), actualSize(0),
	  expectedCapacity(0), actualCapacity(0),
	  index(0)
	{}

	std::function<bool(int)>
	getOddPredicate() {
		return [](int i) { return i % 2 == 1; };
	}
};

TEST_F(VectorRemovals,
DecreasesSizeByOneWhenRemovingElement) {
	index = 0;
	v.remove(index);
	expectedSize = 5;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemovals,
PreservesOtherElementsWhenRemovingElement) {
	index = 1;
	v.remove(index);

	ASSERT_EQ(1, v[0]);
	ASSERT_EQ(3, v[1]);
	ASSERT_EQ(4, v[2]);
	ASSERT_EQ(5, v[3]);
	ASSERT_EQ(6, v[4]);
}

TEST_F(VectorRemovals,
DecreasesSizeByThreeWhenRemovingCountOfElements) {
	index = 1;
	int numValuesToRemove = 3;
	v.remove(index, numValuesToRemove);

	expectedSize = 3;
	actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemovals,
DecreasesSizeWhenRemovingAllElementsEqualToValue) {
	PVector<int> vec({0,1,0,2,0,3});

	int valueToRemove = 0;
	vec.removeAll(valueToRemove);
	expectedSize = 3;
	actualSize = vec.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemovals,
PreservesOtherElementsWhenRemovingAllElementsEqualToValue) {
	PVector<int> vec({0,1,0,2,0,3});

	int valueToRemove = 0;
	vec.removeAll(valueToRemove);

	ASSERT_EQ(1, vec[0]);
	ASSERT_EQ(2, vec[1]);
	ASSERT_EQ(3, vec[2]);
}

TEST_F(VectorRemovals,
SizeUnchangedWhenRemovingAllElementsEqualToNonExistentValue) {
	int NonExistentValue = 789;
	v.removeAll(NonExistentValue);

	expectedSize = 6;
	actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemovals,
DecreasesSizeWhenRemovingFirstElement) {
	v.removeFirst();
	expectedSize = 5;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemovals,
PreservesOtherElementsWhenRemovingFirstElement) {
	v.removeFirst();

	ASSERT_EQ(2, v[0]);
	ASSERT_EQ(3, v[1]);
	ASSERT_EQ(4, v[2]);
	ASSERT_EQ(5, v[3]);
	ASSERT_EQ(6, v[4]);
}

TEST_F(VectorRemovals,
DecreasesSizeWhenRemovingLastElement) {
	v.removeLast();

	expectedSize = 5;
	actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemovals,
PreservesOtherElementsWhenRemovingLastElement) {
	v.removeLast();

	ASSERT_EQ(1, v[0]);
	ASSERT_EQ(2, v[1]);
	ASSERT_EQ(3, v[2]);
	ASSERT_EQ(4, v[3]);
	ASSERT_EQ(5, v[4]);
}

TEST_F(VectorRemovals,
DecreasesSizeWhenRemovingOddValuesWithLambdaPredicate) {
	v.removeIf(getOddPredicate());

	expectedSize = 3;
	actualSize = v.size();
	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemovals,
PreservesOtherElementsWhenRemovingOddValuesWithLambdaPredicate) {
	v.removeIf(getOddPredicate());

	ASSERT_EQ(2, v[0]);
	ASSERT_EQ(4, v[1]);
	ASSERT_EQ(6, v[2]);
}

TEST_F(VectorRemovals,
SetsSizeToZeroAfterClearingAllElements) {
	v.clear();
	expectedSize = 0;
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemovals,
PreservesCapacityAfterClearingAllElements) {
	v.reserve(10);

	v.clear();
	expectedCapacity = 10;
	actualCapacity = v.capacity();

	ASSERT_EQ(expectedCapacity, actualCapacity);
}

TEST_F(VectorRemovals,
DecreasesSizeByOneWhenRemovingElementAtIterator) {
	expectedSize = v.size() - 1;
	v.remove(v.cbegin());
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemovals,
PreservesOtherElementsWhenRemovingElementAtIterator) {
	v.remove(v.cbegin());

	ASSERT_EQ(2, v[0]);
	ASSERT_EQ(3, v[1]);
	ASSERT_EQ(4, v[2]);
	ASSERT_EQ(5, v[3]);
	ASSERT_EQ(6, v[4]);
}

TEST_F(VectorRemovals,
ReturnsIteratorToElementAfterRemovedElement) {
	PVector<int>::iterator it = v.remove(v.cbegin());
	ASSERT_EQ(2, *it);

}

TEST_F(VectorRemovals,
DecreasesSizeByRemovedRangeLength) {
	int rangeLength = 3;
	expectedSize = v.size() - rangeLength;
	v.remove(v.cbegin(), v.cbegin() + rangeLength);
	actualSize = v.size();

	ASSERT_EQ(expectedSize, actualSize);
}

TEST_F(VectorRemovals,
PreservesOtherElementsWhenRemovingRangeAtIterator) {
	int rangeLength = 3;
	v.remove(v.cbegin(), v.cbegin() + rangeLength);

	ASSERT_EQ(4, v[0]);
	ASSERT_EQ(5, v[1]);
	ASSERT_EQ(6, v[2]);
}

TEST_F(VectorRemovals,
ReturnsIteratorToElementAfterRemovedRange) {
	int rangeLength = 3;
	PVector<int>::iterator it = v.remove(v.cbegin(), v.cbegin() + rangeLength);
	ASSERT_EQ(4, *it);

}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE










