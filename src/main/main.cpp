/*
 * main.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: iainhemstock
 */

#include "gmock/gmock.h"
using namespace ::testing;

int main(int argc, char * argv[]) {
	InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
