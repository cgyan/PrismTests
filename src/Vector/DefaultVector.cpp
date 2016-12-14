/*
 * DefaultVector.cpp
 *
 *  Created on: 12 Dec 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/PVector>
using namespace ::testing;
using namespace prism;

class DefaultVector : public Test {
public:
	PVector<int> v;
};

/*
 *
 */
TEST_F(DefaultVector, IsEmptyOnConstruction) {
	ASSERT_TRUE(v.empty());
}

/*
 *
 */
TEST_F(DefaultVector, IsNotEmptyAfterElementAdded) {
	v.append(10);

	ASSERT_FALSE(v.empty());
}












