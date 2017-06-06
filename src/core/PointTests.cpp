#include "gtest/gtest.h"
#include <prism/global>
#include <prism/Point>
#include <prism/DivideByZeroException>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class PointTests : public Test {
public:
    Point p;
};

TEST_F(PointTests, DefaultXPosIsZero) {
    ASSERT_EQ(0, p.x());
}

TEST_F(PointTests, DefaultYPosIsZero) {
    ASSERT_EQ(0, p.y());
}

TEST_F(PointTests, DefaultPositionIsZeroZero) {
    ASSERT_EQ(Point(0,0), p);
}

TEST_F(PointTests, CanSetXPosAndYPosAtConstruction) {
    int x = 10;
    int y = 20;
    Point p(x,y);
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
    ASSERT_EQ(Point(newX,newY), p);
}

TEST_F(PointTests, CanUpdateXPosDirectly) {
    int newX = 5;
    p.rx() = newX;
    ASSERT_EQ(newX, p.x());
}

TEST_F(PointTests, CanUpdateYPosDirectly) {
    int newY = 5;
    p.ry() = newY;
    ASSERT_EQ(newY, p.y());
}

TEST_F(PointTests, CanResetPositionToZero) {
    p.set(23,34);
    p.reset();
    ASSERT_EQ(Point(0,0), p);
}

TEST_F(PointTests, CanCheckIfPointIsReset) {
    p.set(23,34);
    ASSERT_FALSE(p.isReset());
    p.reset();
    ASSERT_TRUE(p.isReset());
}

TEST_F(PointTests, CompareTwoPointsForEquality) {
    ASSERT_TRUE(Point(1,1) == Point(1,1));
    ASSERT_FALSE(Point(1,1) == Point(2,2));
}

TEST_F(PointTests, CompareTwoPointsForInequality) {
    ASSERT_TRUE(Point(1,1) != Point(2,2));
    ASSERT_FALSE(Point(1,1) != Point(1,1));
}

TEST_F(PointTests, CanAddOtherPointToThisPoint) {
    Point thisPoint(10,10);
    thisPoint += Point(5,5);
    ASSERT_EQ(Point(15,15), thisPoint);
}

TEST_F(PointTests, CanSubtractOtherPointFromThisPoint) {
    Point thisPoint(10,10);
    thisPoint -= Point(7,7);
    ASSERT_EQ(Point(3,3), thisPoint);
}

TEST_F(PointTests, CanScaleThisPointByFactor) {
    Point p(2,3);
    p *= 5;
    ASSERT_EQ(Point(10, 15), p);
}

TEST_F(PointTests, CanDivideThisPointByDivisor) {
    Point p(14,16);
    p /= 2;
    ASSERT_EQ(Point(7,8), p);
}

TEST_F(PointTests, CanAddTwoPointsTogetherReturningNewPoint) {
    Point a(1,2);
    Point b(5,6);
    Point actual = a + b;
    Point expected(6,8);
    ASSERT_EQ(expected, actual);
    ASSERT_EQ(Point(1,2), a);
    ASSERT_EQ(Point(5,6), b);
}

TEST_F(PointTests, CanSubtractTwoPointsReturningNewPoint) {
    Point a(5,6);
    Point b(1,2);
    Point actual = a - b;
    Point expected(4,4);
    ASSERT_EQ(expected, actual);
    ASSERT_EQ(Point(5,6), a);
    ASSERT_EQ(Point(1,2), b);
}

TEST_F(PointTests, CanMultiplyPointByfactorReturningNewPoint) {
    Point p(2,3);
    ASSERT_EQ(Point(10,15), p * 5);
    ASSERT_EQ(Point(10,15), 5 * p);
    ASSERT_EQ(Point(2,3), p);
}

TEST_F(PointTests, CanDividePointByDivisorReturningNewPoint) {
    Point p(18,20);
    ASSERT_EQ(Point(9,10), p / 2);
    ASSERT_EQ(Point(18,20), p);
}

TEST_F(PointTests, ThrowsWhenDividingPointByZero) {
    Point p(18,20);
    ASSERT_THROW(p / 0, prism::DivideByZeroException);
    ASSERT_THROW(p /= 0, prism::DivideByZeroException);
}

TEST_F(PointTests, CanMakeCopyOfPoint) {
    Point p(2,3);
    Point copy1(p);
    Point copy2 = p;
    ASSERT_EQ(p, copy1);
    ASSERT_EQ(p, copy2);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
