/*
 * main.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/Vector>
#include <prism/String>
#include "src/dummy/Number.h"
#include "src/dummy/DynamicNumber.h"
#include <iostream>
#include <prism/Allocator>
#include <prism/algorithm>
#include <prism/type_traits>
#include <vector>
#include <memory>

using namespace std;
using namespace ::testing;
using namespace prism;
using namespace prism::test;

int main(int argc, char * argv[]) {

	using Vector = prism::Vector<int>;
//	using Vector = std::vector<DynamicNumber>;

	Vector v = {1,2,3,4,5,6};


	cout << "finished...\n";
//	return 0;

	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
//	::testing::GTEST_FLAG(filter) = "*MultipleCopyInserter*";
	InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


