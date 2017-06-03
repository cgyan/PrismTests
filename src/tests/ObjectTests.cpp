#include "gtest/gtest.h"
#include <prism/global>
#include <prism/Object>
#include <list>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class ObjectTests : public Test {
public:
    Object o;
};

TEST_F(ObjectTests, DefaultObjectHasNullParent) {
    ASSERT_EQ(nullptr, o.parent());
}

TEST_F(ObjectTests, CanMakeObjectParentOfOtherObject) {
    Object parent;
    o.setParent(&parent);
    ASSERT_EQ(&parent, o.parent());
}

TEST_F(ObjectTests, CanSetParentWhenObjectIsCreated) {
    Object parent;
    Object child(&parent);
    ASSERT_EQ(&parent, child.parent());
}

TEST_F(ObjectTests, DefaultObjectHasListOfZeroChildren) {
    Object::ObjectList expected;
    Object::ObjectList actual = o.children();
    ASSERT_EQ(expected.size(), actual.size());
}

TEST_F(ObjectTests, HasChildListOfSizeOneAfterBecomingParent) {
    Object child;
    child.setParent(&o);
    Object::ObjectList expected(1);
    Object::ObjectList actual = o.children();
    ASSERT_EQ(expected.size(), actual.size());
}

TEST_F(ObjectTests, ObjectCanHaveMultipleChildren) {
    Object parent;
    Object child1(&parent);
    Object child2(&parent);
    Object child3(&parent);
    unsigned int numChildren = 3;
    ASSERT_EQ(numChildren, parent.children().size());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
