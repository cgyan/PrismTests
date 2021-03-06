#include <gtest/gtest.h>
#include <prism/global>
#include <prism/Rect>
#include <prism/Point>
#include <prism/Size>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(RectTests, RectIsNullIfWidthAndHeightAreZero) {
    Rect r;

    r.setSize(0,0);
    ASSERT_TRUE(r.isNull());

    r.setSize(1,1);
    ASSERT_FALSE(r.isNull());

    r.setSize(0,1);
    ASSERT_FALSE(r.isNull());

    r.setSize(1,0);
    ASSERT_FALSE(r.isNull());
}

TEST(RectTests, RectIsValidIfWidthAndHeightAreBothNonNegative) {
    Rect r;

    r.setSize(0,0);
    ASSERT_TRUE(r.isValid());

    r.setSize(1,1);
    ASSERT_TRUE(r.isValid());

    r.setSize(-1,-1);
    ASSERT_FALSE(r.isValid());

    r.setSize(-1,0);
    ASSERT_FALSE(r.isValid());

    r.setSize(0,-1);
    ASSERT_FALSE(r.isValid());
}

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

TEST(RectTests, DefaultTopRightPointIsZeroZero) {
    Rect r;
    ASSERT_EQ(Point(0,0), r.topRight());
}

TEST(RectTests, DefaultRightEdgeIsZero) {
    Rect r;
    ASSERT_EQ(0, r.right());
}

TEST(RectTests, DefaultBottomRigtPointIsZeroZero) {
    Rect r;
    ASSERT_EQ(Point(0,0), r.bottomRight());
}

TEST(RectTests, DefaultBottomEdgeIsZero) {
    Rect r;
    ASSERT_EQ(0, r.bottom());
}

TEST(RectTests, DefaultBottomLeftPointIsZeroZero) {
    Rect r;
    ASSERT_EQ(Point(0,0), r.bottomLeft());
}

TEST(RectTests, DefaultLeftEdgeIsZero) {
    Rect r;
    ASSERT_EQ(0, r.left());
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

TEST(RectTests, CanMoveRectSoThatTopEdgeIsAtPosition) {
    Rect r;
    r.setTopLeft(Point(0,0));
    r.setSize(50,50);

    const int newTopEdge = 10;
    r.moveTop(newTopEdge);

    ASSERT_EQ(Point(0,10), r.topLeft());
    ASSERT_EQ(10, r.top());
    ASSERT_EQ(Point(50, 10), r.topRight());
    ASSERT_EQ(50, r.right());
    ASSERT_EQ(Point(50,60), r.bottomRight());
    ASSERT_EQ(60, r.bottom());
    ASSERT_EQ(Point(0,60), r.bottomLeft());
    ASSERT_EQ(0, r.left());
}

TEST(RectTests, CanMoveRectSoThatRightEdgeIsAtPosition) {
    Rect r;
    r.setBottomRight(Point(50,50));

    const int newRightEdge = 10;
    r.moveRight(newRightEdge);

    ASSERT_EQ(Point(-40, 0), r.topLeft());
    ASSERT_EQ(0, r.top());
    ASSERT_EQ(Point(10,0), r.topRight());
    ASSERT_EQ(10, r.right());
    ASSERT_EQ(Point(10,50), r.bottomRight());
    ASSERT_EQ(50, r.bottom());
    ASSERT_EQ(Point(-40,50), r.bottomLeft());
    ASSERT_EQ(-40, r.left());
}

TEST(RectTests, CanMoveRectSoThatBottomEdgeIsAtPosition) {
    const int newBottomEdge = 10;
    Rect r(Point(0,0), Size(50,50));

    r.moveBottom(newBottomEdge);

    ASSERT_EQ(Point(0,-40), r.topLeft());
    ASSERT_EQ(-40, r.top());
    ASSERT_EQ(Point(50,-40), r.topRight());
    ASSERT_EQ(50, r.right());
    ASSERT_EQ(Point(50,10), r.bottomRight());
    ASSERT_EQ(10, r.bottom());
    ASSERT_EQ(Point(0,10), r.bottomLeft());
    ASSERT_EQ(0, r.left());
}

TEST(RectTests, CanMoveRectSoThatLeftEdgeIsAtPosition) {
    const int newLeftEdge = 10;
    Rect r(Point(0,0), Size(50,50));

    r.moveLeft(newLeftEdge);

    ASSERT_EQ(Point(10,0), r.topLeft());
    ASSERT_EQ(0, r.top());
    ASSERT_EQ(Point(60,0), r.topRight());
    ASSERT_EQ(60, r.right());
    ASSERT_EQ(Point(60,50), r.bottomRight());
    ASSERT_EQ(50, r.bottom());
    ASSERT_EQ(Point(10,50), r.bottomLeft());
    ASSERT_EQ(10, r.left());
}

TEST(RectTests, CanMoveRectSoThatTopLeftPointIsAtPosition) {
    Point newTopLeft(10,10);
    Rect r(Point(0,0), Size(50,50));

    r.moveTopLeft(newTopLeft);

    ASSERT_EQ(Point(10,10), r.topLeft());
    ASSERT_EQ(10, r.top());
    ASSERT_EQ(Point(60,10), r.topRight());
    ASSERT_EQ(60, r.right());
    ASSERT_EQ(Point(60,60), r.bottomRight());
    ASSERT_EQ(60, r.bottom());
    ASSERT_EQ(Point(10,60), r.bottomLeft());
    ASSERT_EQ(10, r.left());
}

TEST(RectTests, CanMoveRectSoThatTopRightPointIsAtPosition) {
    Point newTopRight(10,10);
    Rect r(Point(0,0), Size(50,50));

    r.moveTopRight(newTopRight);

    ASSERT_EQ(Point(-40,10), r.topLeft());
    ASSERT_EQ(10, r.top());
    ASSERT_EQ(Point(10,10), r.topRight());
    ASSERT_EQ(10, r.right());
    ASSERT_EQ(Point(10,60), r.bottomRight());
    ASSERT_EQ(60, r.bottom());
    ASSERT_EQ(Point(-40,60), r.bottomLeft());
    ASSERT_EQ(-40, r.left());
}

TEST(RectTests, CanMoveRectSoThatBottomRightPointIsAtPosition) {
    Point newBottomRight(10,10);
    Rect r(Point(0,0), Size(50,50));

    r.moveBottomRight(newBottomRight);

    ASSERT_EQ(Point(-40,-40), r.topLeft());
    ASSERT_EQ(-40, r.top());
    ASSERT_EQ(Point(10,-40), r.topRight());
    ASSERT_EQ(10, r.right());
    ASSERT_EQ(Point(10,10), r.bottomRight());
    ASSERT_EQ(10, r.bottom());
    ASSERT_EQ(Point(-40,10), r.bottomLeft());
    ASSERT_EQ(-40, r.left());
}

TEST(RectTests, CanMoveRectSoThatBottomLeftPointIsAtPosition) {
    Point newBottomLeft(10,10);
    Rect r(Point(0,0), Size(50,50));

    r.moveBottomLeft(newBottomLeft);

    ASSERT_EQ(Point(10,-40), r.topLeft());
    ASSERT_EQ(-40, r.top());
    ASSERT_EQ(Point(60,-40), r.topRight());
    ASSERT_EQ(60, r.right());
    ASSERT_EQ(Point(60,10), r.bottomRight());
    ASSERT_EQ(10, r.bottom());
    ASSERT_EQ(Point(10,10), r.bottomLeft());
    ASSERT_EQ(10, r.left());
}

TEST(RectTests, CanMoveCentrePointToPosition) {
    Point topLeft(0,0);
    Size size(20,20);
    Rect r;
    r.set(topLeft, size);

    Point pos(20,20);
    r.moveCentre(pos);

    ASSERT_EQ(Point(20,20), r.centre());
    ASSERT_EQ(Point(10,10), r.topLeft());
    ASSERT_EQ(10, r.top());
    ASSERT_EQ(Point(30,10), r.topRight());
    ASSERT_EQ(30, r.right());
    ASSERT_EQ(Point(30,30), r.bottomRight());
    ASSERT_EQ(30, r.bottom());
    ASSERT_EQ(Point(10,30), r.bottomLeft());
    ASSERT_EQ(10, r.left());
}

TEST(RectTests, CanMoveCentrePointToCoordinate) {
    Point topLeft(0,0);
    Size size(20,20);
    Rect r;
    r.set(topLeft, size);

    const int x = 20;
    const int y = 20;
    r.moveCentre(x,y);

    ASSERT_EQ(Point(20,20), r.centre());
    ASSERT_EQ(Point(10,10), r.topLeft());
    ASSERT_EQ(10, r.top());
    ASSERT_EQ(Point(30,10), r.topRight());
    ASSERT_EQ(30, r.right());
    ASSERT_EQ(Point(30,30), r.bottomRight());
    ASSERT_EQ(30, r.bottom());
    ASSERT_EQ(Point(10,30), r.bottomLeft());
    ASSERT_EQ(10, r.left());
}

TEST(RectTests, CanGetCentrePointOfDefaultPositionedRect) {
    Point defaultPosition = Point(0,0);
    Rect r(defaultPosition, Size(10,10));
    ASSERT_EQ(Point(5,5), r.centre());
}

TEST(RectTests, CanGetCentrePointOfPositivePositionedRect) {
    Point positivePosition = Point(2,2);
    Rect r(positivePosition, Size(10,10));
    ASSERT_EQ(Point(7,7), r.centre());
}

TEST(RectTests, CanGetCentrePointOfNegativePositionedRect) {
    Point negativePosition = Point(-2,-2);
    Rect r(negativePosition, Size(10,10));
    ASSERT_EQ(Point(3,3), r.centre());
}

TEST(RectTests, CanAdjustTheRectByPositiveOffsets) {
    Rect r(0,0,50,50);
    int dx1, dy1, dx2, dy2;
    dx1 = dy1 = dx2 = dy2 = 5;

    r.adjust(dx1, dy1, dx2, dy2);

    ASSERT_EQ(Point(5,5), r.topLeft());
    ASSERT_EQ(5, r.top());
    ASSERT_EQ(Point(55,5), r.topRight());
    ASSERT_EQ(55, r.right());
    ASSERT_EQ(Point(55,55), r.bottomRight());
    ASSERT_EQ(55, r.bottom());
    ASSERT_EQ(Point(5,55), r.bottomLeft());
    ASSERT_EQ(5, r.left());
}

TEST(RectTests, CanAdjustTheRectByNegativeOffsets) {
    Rect r(0,0,50,50);
    int dx1, dy1, dx2, dy2;
    dx1 = dy1 = dx2 = dy2 = -5;

    r.adjust(dx1, dy1, dx2, dy2);

    ASSERT_EQ(Point(-5,-5), r.topLeft());
    ASSERT_EQ(-5, r.top());
    ASSERT_EQ(Point(45,-5), r.topRight());
    ASSERT_EQ(45, r.right());
    ASSERT_EQ(Point(45,45), r.bottomRight());
    ASSERT_EQ(45, r.bottom());
    ASSERT_EQ(Point(-5,45), r.bottomLeft());
    ASSERT_EQ(-5, r.left());
}

TEST(RectTests, CanReturnNewRectAdjustedByOffsets) {
    Rect r(0,0,50,50);
    int dx1, dy1, dx2, dy2;
    dx1 = dy1 = dx2 = dy2 = 5;

    Rect adjusted = r.adjusted(dx1, dy1, dx2, dy2);

    ASSERT_TRUE(Rect(0,0,50,50) == r);
    ASSERT_FALSE(Rect(0,0,50,50) != r);

    ASSERT_EQ(Point(5,5), adjusted.topLeft());
    ASSERT_EQ(5, adjusted.top());
    ASSERT_EQ(Point(55,5), adjusted.topRight());
    ASSERT_EQ(55, adjusted.right());
    ASSERT_EQ(Point(55,55), adjusted.bottomRight());
    ASSERT_EQ(55, adjusted.bottom());
    ASSERT_EQ(Point(5,55), adjusted.bottomLeft());
    ASSERT_EQ(5, adjusted.left());
}

TEST(RectTests, CanModifyCopyOfRectWithoutModifyingOriginalRect) {
    Rect original(0,0,50,50);

    Rect copy1(original);
    copy1.adjust(1,1,1,1);

    ASSERT_EQ(Point(0,0), original.topLeft());
    ASSERT_EQ(Point(50,50), original.bottomRight());
    ASSERT_EQ(Point(1,1), copy1.topLeft());
    ASSERT_EQ(Point(51,51), copy1.bottomRight());

    Rect copy2;
    copy2 = original;
    copy2.adjust(1,1,1,1);

    ASSERT_EQ(Point(0,0), original.topLeft());
    ASSERT_EQ(Point(50,50), original.bottomRight());
    ASSERT_EQ(Point(1,1), copy2.topLeft());
    ASSERT_EQ(Point(51,51), copy2.bottomRight());
}

TEST(RectTests, ReturnsTrueIfPointIsContainedWithinOrOnBorderOfRect) {
    Rect r(Point(0,0), Point(50,50));

    ASSERT_TRUE(r.contains(Point(0,0)));
    ASSERT_TRUE(r.contains(Point(25,25)));
    ASSERT_TRUE(r.contains(Point(50,50)));

    ASSERT_FALSE(r.contains(Point(-1,0)));
    ASSERT_FALSE(r.contains(Point(-1,-1)));
    ASSERT_FALSE(r.contains(Point(50,-51)));
    ASSERT_FALSE(r.contains(Point(51,51)));
}

TEST(RectTests, ReturnsTrueIfPointIsPreciselyContainedWithinRect) {
    Rect r(Point(0,0), Point(50,50));

    ASSERT_FALSE(r.contains(Point(0,0), true));
    ASSERT_FALSE(r.contains(Point(0,1), true));
    ASSERT_FALSE(r.contains(Point(1,0), true));
    ASSERT_FALSE(r.contains(Point(50,50), true));
    ASSERT_FALSE(r.contains(Point(49,50), true));
    ASSERT_FALSE(r.contains(Point(50,49), true));

    ASSERT_TRUE(r.contains(Point(1,1), true));
    ASSERT_TRUE(r.contains(Point(25,25), true));
    ASSERT_TRUE(r.contains(Point(49,49), true));
}

TEST(RectTests, ReturnsTrueIfCoordinateIsContainedWithinOrOnBorderOfRect) {
    Rect r;
    r.setBottomLeft(Point(0,50));
    r.setWidth(50);

    ASSERT_TRUE(r.contains(0,0));
    ASSERT_TRUE(r.contains(25,25));
    ASSERT_TRUE(r.contains(50,50));

    ASSERT_FALSE(r.contains(-1,0));
    ASSERT_FALSE(r.contains(-1,-1));
    ASSERT_FALSE(r.contains(50,-51));
    ASSERT_FALSE(r.contains(51,51));
}

TEST(RectTests, ReturnsTrueIfCoordinateIsPreciselyContainedWithinRect) {
    Rect r(0,0,50,50);

    ASSERT_FALSE(r.contains(0,0,true));
    ASSERT_FALSE(r.contains(0,1,true));
    ASSERT_FALSE(r.contains(1,0,true));
    ASSERT_FALSE(r.contains(49,50,true));
    ASSERT_FALSE(r.contains(50,49,true));
    ASSERT_FALSE(r.contains(50,50,true));

    ASSERT_TRUE(r.contains(1,1,true));
    ASSERT_TRUE(r.contains(25,25,true));
    ASSERT_TRUE(r.contains(49,49,true));
}

TEST(RectTests, ReturnsTrueIfOtherRectIsContainedWithinOrOnBorderOfRect) {
    Rect r(0,0,50,50);

    ASSERT_TRUE(r.contains(Rect(0,0,25,25)));
    ASSERT_TRUE(r.contains(Rect(25,25,25,25)));
    ASSERT_TRUE(r.contains(Rect(0,0,50,50)));

    ASSERT_FALSE(r.contains(Rect(-1,0,25,25)));
    ASSERT_FALSE(r.contains(Rect(0,-1,25,25)));
    ASSERT_FALSE(r.contains(Rect(1,1,50,50)));
}

TEST(RectTests, ReturnsTrueIfOtherRectIsPreciselyContainedWithinRect) {
    Rect r(0,0,50,50);

    ASSERT_TRUE(r.contains(Rect(1,1,48,48), true));

    ASSERT_FALSE(r.contains(Rect(0,0,25,25), true));
    ASSERT_FALSE(r.contains(Rect(25,25,25,25), true));
    ASSERT_FALSE(r.contains(Rect(0,0,50,50), true));
}

TEST(RectTests, CanTransposeWidthAndHeight) {
    Rect r;
    r.setWidth(5);
    r.setHeight(10);

    Rect transposed = r.transposed();

    ASSERT_EQ(Rect(0,0,5,10), r);
    ASSERT_EQ(10, transposed.width());
    ASSERT_EQ(5, transposed.height());
}

TEST(RectTests, CanFlipOppositeEdgesIfWidthOrHeightAreNegative) {
    Rect r;
    r.setSize(-10, -15);

    Rect normalised = r.normalised();

    ASSERT_EQ(Rect(0,0,10,15), normalised);
    ASSERT_EQ(Rect(0,0,-10,-15), r);
}

TEST(RectTests, CanRelativelyTranslatePositionByPointAmountOnBothAxis) {
    Rect r;
    r.set(0,0,20,20);

    Point offset(10,10);
    r.translate(offset);

    ASSERT_EQ(Point(20,20), r.centre());
    ASSERT_EQ(Point(10,10), r.topLeft());
    ASSERT_EQ(10, r.top());
    ASSERT_EQ(Point(30,10), r.topRight());
    ASSERT_EQ(30, r.right());
    ASSERT_EQ(Point(30,30), r.bottomRight());
    ASSERT_EQ(30, r.bottom());
    ASSERT_EQ(Point(10,30), r.bottomLeft());
    ASSERT_EQ(10, r.left());
}

TEST(RectTests, CanRelativelyTranslatePositionByAmountOnBothAxis) {
    Rect r;
    r.set(0,0,20,20);

    const int dx = 10;
    const int dy = 10;
    r.translate(dx,dy);

    ASSERT_EQ(Point(20,20), r.centre());
    ASSERT_EQ(Point(10,10), r.topLeft());
    ASSERT_EQ(10, r.top());
    ASSERT_EQ(Point(30,10), r.topRight());
    ASSERT_EQ(30, r.right());
    ASSERT_EQ(Point(30,30), r.bottomRight());
    ASSERT_EQ(30, r.bottom());
    ASSERT_EQ(Point(10,30), r.bottomLeft());
    ASSERT_EQ(10, r.left());
}

TEST(RectTests, ReturnsNewRectRelativelyTranslatedByOffset) {
    Rect r;
    r.setSize(20,20);

    const int dx = 10;
    const int dy = 10;
    Rect translated = r.translated(dx,dy);

    ASSERT_EQ(Rect(0,0,20,20), r);

    ASSERT_EQ(Point(20,20), translated.centre());
    ASSERT_EQ(Point(10,10), translated.topLeft());
    ASSERT_EQ(10, translated.top());
    ASSERT_EQ(Point(30,10), translated.topRight());
    ASSERT_EQ(30, translated.right());
    ASSERT_EQ(Point(30,30), translated.bottomRight());
    ASSERT_EQ(30, translated.bottom());
    ASSERT_EQ(Point(10,30), translated.bottomLeft());
    ASSERT_EQ(10, translated.left());
}

TEST(RectTests, ReturnsNewRectRelativelyTranslatedByPointOffset) {
    Rect r;
    r.setSize(20,20);

    Point offset(10,10);
    Rect translated = r.translated(offset);

    ASSERT_EQ(Rect(0,0,20,20), r);

    ASSERT_EQ(Point(20,20), translated.centre());
    ASSERT_EQ(Point(10,10), translated.topLeft());
    ASSERT_EQ(10, translated.top());
    ASSERT_EQ(Point(30,10), translated.topRight());
    ASSERT_EQ(30, translated.right());
    ASSERT_EQ(Point(30,30), translated.bottomRight());
    ASSERT_EQ(30, translated.bottom());
    ASSERT_EQ(Point(10,30), translated.bottomLeft());
    ASSERT_EQ(10, translated.left());
}

TEST(RectTests, ReturnsBoundingRectThatContainsTwoRects) {
    Rect r1;
    r1.setX(0);
    r1.setY(0);
    r1.setSize(20,20);

    Rect r2;
    r2.setX(10);
    r2.setY(10);
    r2.setSize(20,20);

    Rect united = Rect::united(r1,r2);

    ASSERT_EQ(Point(15,15), united.centre());
    ASSERT_EQ(Point(0,0), united.topLeft());
    ASSERT_EQ(0, united.top());
    ASSERT_EQ(Point(30,0), united.topRight());
    ASSERT_EQ(30, united.right());
    ASSERT_EQ(Point(30,30), united.bottomRight());
    ASSERT_EQ(30, united.bottom());
    ASSERT_EQ(Point(0,30), united.bottomLeft());
    ASSERT_EQ(0, united.left());
}

TEST(RectTests, ReturnsTrueIfTwoRectsAreIntersected) {
    Rect r;
    r.setTopLeft(Point(0,0));
    r.setSize(20,20);

    ASSERT_TRUE(r.intersects(Rect(10,10,20,20)));
    ASSERT_TRUE(r.intersects(Rect(5,5,5,5)));
    ASSERT_TRUE(r.intersects(Rect(-10,-10,100,100)));

    ASSERT_FALSE(r.intersects(Rect(20,0,20,20)));
    ASSERT_FALSE(r.intersects(Rect(0,20,20,20)));
    ASSERT_FALSE(r.intersects(Rect(-20,0,20,20)));
    ASSERT_FALSE(r.intersects(Rect(0,-20,20,20)));
}

TEST(RectTests, ReturnsNewRectOfOverlappingPortionOfTwoRects) {
    Rect r1;
    r1.setTopRight(Point(20,0));
    r1.setHeight(20);

    Rect r2;
    r2.setTopLeft(Point(10,10));
    r2.setTopRight(Point(30,10));
    r2.setHeight(20);

    Rect intersected = Rect::intersected(r1,r2);

    ASSERT_EQ(Point(15,15), intersected.centre());
    ASSERT_EQ(Point(10,10), intersected.topLeft());
    ASSERT_EQ(10, intersected.top());
    ASSERT_EQ(Point(20,10), intersected.topRight());
    ASSERT_EQ(20, intersected.right());
    ASSERT_EQ(Point(20,20), intersected.bottomRight());
    ASSERT_EQ(20, intersected.bottom());
    ASSERT_EQ(Point(10,20), intersected.bottomLeft());
    ASSERT_EQ(10, intersected.left());
}

TEST(RectTests, ReturnsFirstRectIfThereIsNoOverlapBetweenTwoRects) {
    Rect r1;
    r1.setLeft(0);
    r1.setTop(0);
    r1.setRight(20);
    r1.setBottom(20);

    Rect r2;
    r2.setLeft(100);
    r2.setTop(100);
    r2.setRight(120);
    r2.setBottom(120);

    Rect intersected = Rect::intersected(r1,r2);
    ASSERT_EQ(r1, intersected);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
