/*
 * main.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/PVector>
#include <prism/String>
#include "src/dummy/Number.h"
#include "src/dummy/DynamicNumber.h"
#include <iostream>
#include <prism/Allocator>
#include <prism/algorithm>
#include <vector>

using namespace std;
using namespace ::testing;
using namespace prism;
using namespace prism::test;

int main(int argc, char * argv[]) {

	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
//	::testing::GTEST_FLAG(filter) = "*MultipleCopyInserter*";
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

//	using Vector = prism::PVector<DynamicNumber>;
	using Vector = std::vector<DynamicNumber>;

	Vector v1({1,1,1,1,1,1});
	Vector v2({1,1,1});
//
	cout << (v1 <= v2) << endl;
	cout << "finished...\n";
}
