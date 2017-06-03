/*
 * main.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
using namespace ::testing;
#include <prism/Object>

int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
	::testing::GTEST_FLAG(filter) = "Object*";
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
