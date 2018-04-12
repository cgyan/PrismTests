#ifndef PRISM_TESTS_GLOBAL_H_
#define PRISM_TESTS_GLOBAL_H_

#include <prism/global>

#define UNIT_TEST(TestBase) Unit_##TestBase
#define INTEGRATION_TEST(TestBase) Integration_##TestBase
#define GROUP_TEST_F(GroupName, TestBase, TestName) TEST_F(GroupName##_##TestBase, TestName)
#define GROUP_TEST_P(GroupName, TestBase, TestName) TEST_P(GroupName##_##TestBase, TestName)
#define GROUP_TEST(GroupName, TestBase, TestName) TEST(GroupName##_##TestBase, TestName)
#define GROUP_INSTANTIATE_TEST_CASE_P(Prefix, TestCaseName, generator, ...) \
        INSTANTIATE_TEST_CASE_P(Prefix, TestCaseName, generator)

#endif