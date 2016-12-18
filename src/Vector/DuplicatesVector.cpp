/*
 * DuplicatesVector.cpp
 * v0.*
 *
 *  Created on: 18 Dec 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/PVector>
#include <prism/h/global.h>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

//=============================================================================
// DuplicatesVector is a class that contains duplicate elements
//=============================================================================
class DuplicatesVector : public Test {
public:
	PVector<int> v;

	void SetUp() {
		setCapacityToTen();
		addElementsToVector();
	}

	void setCapacityToTen() {
		v.reserve(10);
	}

	void addElementsToVector() {
		v.addAtEnd(30);
		v.addAtEnd(1);
		v.addAtEnd(31);
		v.addAtEnd(32);
		v.addAtEnd(1);
		v.addAtEnd(33);
	}
};

TEST_F(DuplicatesVector,
AnswersIndexOneWhenSearchingForwardFromIndexZeroForValueOfOfOne) {
	int indexOne = 1;
	int startSearchFromIndexZero = 0;
	int valueToFind = 1;
	int returnedIndex = v.indexOf(valueToFind, startSearchFromIndexZero);

	ASSERT_EQ(indexOne, returnedIndex);
}

TEST_F(DuplicatesVector,
AnswersIndexOneWhenSearchingForwardFromIndexOneForValueOfOfOne) {
	int indexOne = 1;
	int startSearchFromIndexOne = 1;
	int valueToFind = 1;
	int returnedIndex = v.indexOf(valueToFind, startSearchFromIndexOne);

	ASSERT_EQ(indexOne, returnedIndex);
}

TEST_F(DuplicatesVector,
AnswersIndexFourWhenSearchingForwardFromIndexTwoForValueOfOfOne) {
	int indexFour = 4;
	int startSearchFromIndexTwo = 2;
	int valueToFind = 1;
	int returnedIndex = v.indexOf(valueToFind, startSearchFromIndexTwo);

	ASSERT_EQ(indexFour, returnedIndex);
}

TEST_F(DuplicatesVector,
AnswersIndexFourWhenSearchingBackwardsFromLastIndexForValueOfOne) {
	int indexFour = 4;
	int valueToFind = 1;
	int returnedIndex = v.lastIndexOf(valueToFind);

	ASSERT_EQ(indexFour, returnedIndex);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE












