#ifndef PRISM_TESTS_GLOBAL_H_
#define PRISM_TESTS_GLOBAL_H_

#include <prism/global>

#define GROUP_TEST_F(GroupName, TestBase, TestName) TEST_F(TestBase, GroupName##_##TestName)
#define GROUP_TEST_P(GroupName, TestBase, TestName) TEST_P(TestBase, GroupName##_##TestName)
#define GROUP_TEST(GroupName, TestBase, TestName) TEST(TestBase, GroupName##_##TestName)

#endif
