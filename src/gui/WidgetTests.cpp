#include <gtest/gtest.h>
#include <prism/global>
#include <prism/Widget>
#include <prism/Size>
#include <prism/Point>
#include <string>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(WidgetTests, DefaultWidgetSizeIs600400) {
    Widget w;
    ASSERT_EQ(Size(600,400), w.size());
}

TEST(WidgetTests, DefaultWidgetPositionIsZeroZero) {
    Widget w;
    ASSERT_EQ(Point(0,0), w.pos());
}

TEST(WidgetTests, DefaultWidgetHasDefaultWindowTitle) {
    std::string wintitle = "Default Window Title";
    Widget w;
    ASSERT_EQ(wintitle, w.title());
}

TEST(WidgetTests, CanRenameWindowTitle) {
    std::string newtitle = "New Window Title";
    Widget w;
    w.setTitle(newtitle);
    ASSERT_EQ(newtitle, w.title());
}

TEST(WidgetTests, CanResizeWidthAndHeightSimultaneously) {
    Widget w;
    Size expected;

    expected.set(600,400);
    w.resize(expected);
    ASSERT_EQ(expected, w.size());

    expected.set(1024,768);
    w.resize(expected.width(), expected.height());
    ASSERT_EQ(expected, w.size());
}

TEST(WidgetTests, CanMoveWidgetTopLeftToNewLocation) {
    Point newPos(50,60);
    Widget w;
    w.setPos(newPos);
    ASSERT_EQ(newPos, w.pos());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
