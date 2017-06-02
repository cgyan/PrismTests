/*
 * main.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/type_traits>
#include <prism/Iterator>
#include <prism/DynamicNumber>
#include <list>

using namespace std;
using namespace ::testing;
using namespace prism;
using namespace prism::test;



int main(int argc, char * argv[]) {



	cout << "finished...\n";
//	return 0;

	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
	// ::testing::GTEST_FLAG(filter) = "*Time*";
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
