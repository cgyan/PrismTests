#ifndef PRISM_TESTS_GLOBAL_H_
#define PRISM_TESTS_GLOBAL_H_

#define GROUP_TEST_F(GroupName, TestBase, TestName) \
                TEST_F(TestBase, GroupName##_##TestName)

#endif
