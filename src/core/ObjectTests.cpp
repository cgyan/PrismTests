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
    Object oo;
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

TEST_F(ObjectTests, DefaultObjectHasZeroChildren) {
    Object::ObjectList expected;
    Object::ObjectList actual = o.children();
    ASSERT_EQ(expected.size(), actual.size());
}

TEST_F(ObjectTests, ObjectHasOneChildAfterBecomingParent) {
    Object child;
    child.setParent(&o);
    Object::ObjectList expected(1);
    Object::ObjectList actual = o.children();
    ASSERT_EQ(expected.size(), actual.size());
}

TEST_F(ObjectTests, ObjectCanHaveMultipleChildren) {
    using const_iterator = Object::ObjectList::const_iterator;

    Object parent;
    Object child1(&parent);
    Object child2(&parent);
    Object child3(&parent);
    unsigned int numChildren = 3;

    const_iterator cit = parent.children().cbegin();

    ASSERT_EQ(numChildren, parent.children().size());
    ASSERT_EQ(&child1, *cit);
    ASSERT_EQ(&child2, *++cit);
    ASSERT_EQ(&child3, *++cit);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
