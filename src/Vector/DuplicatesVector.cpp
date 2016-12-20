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
// The vector contains the values: { 30, 1, 31, 32, 1, 33 }
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
	  startIndex(0)
	{}

	void SetUp() {
		setCapacityToTen();
		addElementsToVector();
	}

	void setCapacityToTen() {
		v.reserve(10);
	}

	void addElementsToVector() {
		v.append(30);
		v.append(1);
		v.append(31);
		v.append(32);
		v.append(1);
		v.append(33);
	}

	PVector<int> v;
	int IndexZero;
	int IndexOne;
	int IndexTwo;
	int IndexThree;
	int IndexFour;
	int valueToFind;
	int startIndex;
};

TEST_F(DuplicatesVector,
AnswersFirstIndexOfValueSearchingFromSpecifiedIndex) {
	valueToFind = 1;
	startIndex = IndexOne;

	ASSERT_TRUE(v.indexOf(valueToFind, startIndex) == IndexOne);

	startIndex = IndexTwo;

	ASSERT_TRUE(v.indexOf(valueToFind, startIndex) == IndexFour);
}

TEST_F(DuplicatesVector,
AnswersLastIndexOfValueSearchingFromSpecifiedIndex) {
	valueToFind = 1;
	startIndex = IndexFour;

	ASSERT_TRUE(v.lastIndexOf(valueToFind, startIndex) == IndexFour);

	startIndex = IndexThree;

	ASSERT_TRUE(v.lastIndexOf(valueToFind, startIndex) == IndexOne);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE












