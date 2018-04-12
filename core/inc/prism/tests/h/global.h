#ifndef PRISM_TESTS_GLOBAL_H_
#define PRISM_TESTS_GLOBAL_H_

#include <prism/global>

#define UNIT_TEST(TestClass) Unit_##TestClass
#define INTEGRATION_TEST(TestClass) Integration_##TestClass
#define GROUP_TEST_F(GroupName, TestBase, TestName) TEST_F(TestBase, GroupName##_##TestName)
#define GROUP_TEST_P(GroupName, TestBase, TestName) TEST_P(GroupName##_##TestBase, TestName)
#define GROUP_TEST(GroupName, TestBase, TestName) TEST(GroupName##_##TestBase, TestName)
#define GROUP_INSTANTIATE_TEST_CASE_P(Prefix, TestCaseName, generator, ...) INSTANTIATE_TEST_CASE_P(Prefix, TestCaseName, generator)

#endif
