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
// The vector contains the values: { 30, 1, 31, 1, 32 }
//=============================================================================
class DuplicatesVector : public Test {
public:
	DuplicatesVector()
	: IndexZero(0),
	  IndexOne(1),
	  IndexTwo(2),
	  IndexThree(3),
	  IndexFour(4),
	  valueToFind(0),
	  startIndex(0),
	  expectedIndex(0),
	  actualIndex(0)
	{}

	void SetUp() {
		addElementsToVector();
	}

	void addElementsToVector() {
		v.append(30);
		v.append(1);
		v.append(31);
		v.append(1);
		v.append(32);
	}

	PVector<int> v;
	int IndexZero;
	int IndexOne;
	int IndexTwo;
	int IndexThree;
	int IndexFour;
	int valueToFind;
	int startIndex;
	int expectedIndex;
	int actualIndex;
};

TEST_F(DuplicatesVector,
AnswersFirstIndexOfValueSearchingFromSpecifiedIndex) {
	valueToFind = 1;
	startIndex = IndexOne;
	expectedIndex = IndexOne;
	actualIndex = v.indexOf(valueToFind, startIndex);

	ASSERT_EQ(expectedIndex, actualIndex);

	startIndex = IndexTwo;
	expectedIndex = IndexThree;
	actualIndex = v.indexOf(valueToFind, startIndex);

	ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(DuplicatesVector,
AnswersLastIndexOfValueSearchingFromSpecifiedIndex) {
	valueToFind = 1;
	startIndex = IndexFour;
	expectedIndex = IndexThree;
	actualIndex = v.lastIndexOf(valueToFind, startIndex);

	ASSERT_EQ(expectedIndex, actualIndex);

	startIndex = IndexTwo;
	expectedIndex = IndexOne;
	actualIndex = v.lastIndexOf(valueToFind, startIndex);

	ASSERT_EQ(expectedIndex, actualIndex);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE












