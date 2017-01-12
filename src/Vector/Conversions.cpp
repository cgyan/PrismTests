/*
 * Conversions.cpp
 * v0.*
 *
 *  Created on: 11 Jan 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/PVector>
#include <vector>
#include <list>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class Conversions : public Test {
public:
	PVector<int> emptyPrismVector;
	PVector<int> populatedPrismVector;
	std::vector<int> emptyStdVector;
	std::vector<int> populatedStdVector;
	std::list<int> emptyStdList;
	std::list<int> populatedStdList;

	Conversions()
	: emptyPrismVector(),
	  populatedPrismVector({1,2,3,4,5}),
	  emptyStdVector(),
	  populatedStdVector({1,2,3,4,5}),
	  emptyStdList(),
	  populatedStdList({1,2,3,4,5})
	{}
};

TEST_F(Conversions,
ConvertsEmptyVectorToEmptyStdVector) {
	ASSERT_EQ(emptyStdVector, emptyPrismVector.toStdVector());
}

TEST_F(Conversions,
ConvertsElementsToStdVector) {
	ASSERT_EQ(populatedStdVector, populatedPrismVector.toStdVector());
}

TEST_F(Conversions,
ConvertsEmptyVectorToEmptyStdList) {
	ASSERT_EQ(emptyStdList, emptyPrismVector.toStdList());
}

TEST_F(Conversions,
ConvertsElementsToStdList) {
	ASSERT_EQ(populatedStdList, populatedPrismVector.toStdList());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE


