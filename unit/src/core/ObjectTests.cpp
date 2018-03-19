#include "gtest/gtest.h"
#include <prism/global>
#include <prism/Object>
#include <list>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(ObjectTests, DefaultObjectHasNullParent) {
    Object o;
    ASSERT_EQ(nullptr, o.parent());
}

TEST(ObjectTests, CanMakeObjectChildOfOtherObject) {
    Object o;
    Object parent;
    o.setParent(&parent);
    ASSERT_EQ(&parent, o.parent());
}

TEST(ObjectTests, CanSetParentWhenObjectIsCreated) {
    Object parent;
    Object child(&parent);
    ASSERT_EQ(&parent, child.parent());
}

TEST(ObjectTests, DefaultObjectHasZeroChildren) {
    Object o;
    Object::ObjectList expected;
    Object::ObjectList actual = o.children();
    ASSERT_EQ(expected.size(), actual.size());
}

TEST(ObjectTests, ObjectHasOneChildAfterBecomingParent) {
    Object o;
    Object child;
    child.setParent(&o);
    Object::ObjectList expected(1);
    Object::ObjectList actual = o.children();
    ASSERT_EQ(expected.size(), actual.size());
}

TEST(ObjectTests, ObjectCanHaveMultipleChildren) {
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
