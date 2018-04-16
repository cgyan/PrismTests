#ifndef PRISM_TESTS_GLOBAL_H_
#define PRISM_TESTS_GLOBAL_H_

#include <prism/global>

#define GROUP_TEST(GroupName, TestBase, TestName) TEST(GroupName##_##TestBase, TestName)
#define GROUP_TEST_F(GroupName, TestBase, TestName) TEST_F(GroupName##_##TestBase, TestName)
#define GROUP_TEST_P(GroupName, TestBase, TestName) TEST_P(GroupName##_##TestBase, TestName)
#define GROUP_INSTANTIATE_TEST_CASE_P(Prefix, TestCaseName, generator, ...) \
        INSTANTIATE_TEST_CASE_P(Prefix, TestCaseName, generator)

#define UNIT_TEST_CLASS(TestBase) Unit_##TestBase
#define INTEGRATION_TEST_CASE(TestBase) Integration_##TestBase

#define UNIT_TEST(TestBase, TestName) GROUP_TEST(Unit, TestBase, TestName)
#define UNIT_TEST_F(TestBase, TestName) GROUP_TEST_F(Unit, TestBase, TestName)
#define UNIT_TEST_P(TestBase, TestName) GROUP_TEST_P(Unit, TestBase, TestName)
#define UNIT_INSTANTIATE_TEST_CASE_P(Prefix, TestCaseName, generator, ...) \
        GROUP_INSTANTIATE_TEST_CASE_P(Prefix, TestCaseName, generator)

#define INTEGRATION_TEST(TestBase, TestName) GROUP_TEST(Integration, TestBase, TestName)
#define INTEGRATION_TEST_F(TestBase, TestName) GROUP_TEST_F(Integration, TestBase, TestName)
#define INTEGRATION_TEST_P(TestBase, TestName) GROUP_TEST_P(Integration, TestBase, TestName)
#define INTEGRATION_INSTANTIATE_TEST_CASE_P(Prefix, TestCaseName, generator, ...) \
        GROUP_INSTANTIATE_TEST_CASE_P(Prefix, TestCaseName, generator)

#endif
