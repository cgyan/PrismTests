#include "gtest/gtest.h"
#include <prism/global>
#include <prism/PPoint>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class PointTests : public Test {
public:
    PPoint p;
};

TEST_F(PointTests, DefaultXPosIsZero) {
    ASSERT_EQ(0, p.x());
}

TEST_F(PointTests, DefaultYPosIsZero) {
    ASSERT_EQ(0, p.y());
}

TEST_F(PointTests, DefaultPositionIsZeroZero) {
    int x,y;
    x = y = 0;
    PPoint p;
    ASSERT_EQ(x, p.x());
    ASSERT_EQ(y, p.y());
}

TEST_F(PointTests, CanSetXPosAndYPosAtConstruction) {
    int x = 10;
    int y = 20;
    PPoint p(x,y);
    ASSERT_EQ(x, p.x());
    ASSERT_EQ(y, p.y());
}

TEST_F(PointTests, CanUpdateXPos) {
    int newXPos = 50;
    p.setX(newXPos);
    ASSERT_EQ(newXPos, p.x());
}

TEST_F(PointTests, CanUpdateYPos) {
    int newYPos = 50;
    p.setY(newYPos);
    ASSERT_EQ(newYPos, p.y());
}

TEST_F(PointTests, CanUpdateXPosAndYPosSimultaneously) {
    int newX = 23;
    int newY = 34;
    p.set(newX, newY);
    ASSERT_EQ(newX, p.x());
    ASSERT_EQ(newY, p.y());
}

TEST_F(PointTests, CanResetToZero) {
    p.set(23,34);
    p.reset();
    ASSERT_EQ(0, p.x());
    ASSERT_EQ(0, p.y());
}

TEST_F(PointTests, CanComparePointsForEquality) {
    PPoint p1(50);
    PPoint p2(50);
    PPoint p3(60);
    ASSERT_TRUE(p1 == p2);
    ASSERT_TRUE(p2 == p1);
    ASSERT_FALSE(p1 == p3);
    ASSERT_FALSE(p3 == p1);
    ASSERT_FALSE(p2 == p3);
    ASSERT_FALSE(p3 == p2);
}

TEST_F(PointTests, CanComparePointsForInequality) {
    PPoint p1(50);
    PPoint p2(50);
    PPoint p3(60);
    ASSERT_FALSE(p1 != p2);
    ASSERT_FALSE(p2 != p1);
    ASSERT_TRUE(p1 != p3);
    ASSERT_TRUE(p3 != p1);
    ASSERT_TRUE(p2 != p3);
    ASSERT_TRUE(p3 != p2);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
