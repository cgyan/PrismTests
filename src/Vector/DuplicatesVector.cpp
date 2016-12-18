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
class DuplicateVector : public Test {
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

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

