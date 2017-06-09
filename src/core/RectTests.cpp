#include <gtest/gtest.h>
#include <prism/global>
#include <prism/Rect>
#include <prism/Point>
#include <prism/Size>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(RectTests, DefaultCentrePointIsZeroZero) {
    Rect r;
    ASSERT_EQ(Point(0,0), r.centre());
}

TEST(RectTests, DefaultTopLeftPointIsZeroZero) {
    Rect r;
    ASSERT_EQ(Point(0,0), r.topLeft());
}

TEST(RectTests, DefaultTopEdgeIsZero) {
    Rect r;
    ASSERT_EQ(0, r.top());
}

TEST(RectTests, DefaultRightEdgeIsZero) {
    Rect r;
    ASSERT_EQ(0, r.right());
}

TEST(RectTests, DefaultBottomEdgeIsZero) {
    Rect r;
    ASSERT_EQ(0, r.bottom());
}

TEST(RectTests, DefaultLeftEdgeIsZero) {
    Rect r;
    ASSERT_EQ(0, r.left());
}

TEST(RectTests, DefaultTopRightPointIsZeroZero) {
    Rect r;
    ASSERT_EQ(Point(0,0), r.topRight());
}

TEST(RectTests, DefaultBottomLeftPointIsZeroZero) {
    Rect r;
    ASSERT_EQ(Point(0,0), r.bottomLeft());
}

TEST(RectTests, DefaultBottomRigtPointIsZeroZero) {
    Rect r;
    ASSERT_EQ(Point(0,0), r.bottomRight());
}

TEST(RectTests, DefaultXPosIsZero) {
    Rect r;
    ASSERT_EQ(0, r.x());
}

TEST(RectTests, DefaultYPosIsZero) {
    Rect r;
    ASSERT_EQ(0, r.y());
}

TEST(RectTests, DefaultWidthIsZero) {
    Rect r;
    ASSERT_EQ(0, r.width());
}

TEST(RectTests, DefaultHeightIsZero) {
    Rect r;
    ASSERT_EQ(0, r.height());
}

TEST(RectTests, DefaultSizeHasWidthAndHeightOfZero) {
    Rect r;
    ASSERT_EQ(Size(0,0), r.size());
}

TEST(RectTests, CanSetTopLeftPoint) {
    Point p(5,5);
    Rect r(Point(1,1), Size(10,10));

    r.setTopLeft(p);

    int expectedX = p.x();
    int expectedY = p.y();
    int expectedWidth = 6;
    int expectedHeight = 6;

    ASSERT_EQ(p, r.topLeft());
    ASSERT_EQ(expectedX, r.left());
    ASSERT_EQ(expectedY, r.top());
    ASSERT_EQ(expectedWidth, r.width());
    ASSERT_EQ(expectedHeight, r.height());
}

TEST(RectTests, CanSetTopRightPoint) {
    Point p(5,5);
    Rect r(Point(1,1), Size(10,10));

    r.setTopRight(p);

    int expectedX = p.x();
    int expectedY = p.y();
    int expectedWidth = 4;
    int expectedHeight = 6;

    ASSERT_EQ(p, r.topRight());
    ASSERT_EQ(expectedX, r.right());
    ASSERT_EQ(expectedY, r.top());
    ASSERT_EQ(expectedWidth, r.width());
    ASSERT_EQ(expectedHeight, r.height());
}

TEST(RectTests, CanSetBottomRightPoint) {
    Point p(5,5);
    Rect r(Point(1,1), Size(10,10));

    r.setBottomRight(p);

    int expectedX = p.x();
    int expectedY = p.y();
    int expectedWidth = 4;
    int expectedHeight = 4;

    ASSERT_EQ(p, r.bottomRight());
    ASSERT_EQ(expectedX, r.right());
    ASSERT_EQ(expectedY, r.bottom());
    ASSERT_EQ(expectedWidth, r.width());
    ASSERT_EQ(expectedHeight, r.height());
}

TEST(RectTests, CanSetBottomLeftPoint) {
    Point p(5,5);
    Rect r(Point(1,1), Size(10,10));

    r.setBottomLeft(p);

    int expectedX = p.x();
    int expectedY = p.y();
    int expectedWidth = 6;
    int expectedHeight = 4;

    ASSERT_EQ(p, r.bottomLeft());
    ASSERT_EQ(expectedX, r.left());
    ASSERT_EQ(expectedY, r.bottom());
    ASSERT_EQ(expectedWidth, r.width());
    ASSERT_EQ(expectedHeight, r.height());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
