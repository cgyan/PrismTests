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
    Size s(600,400);
    ASSERT_EQ(s, w.size());
}

TEST(WidgetTests, DefaultWidgetPositionIsZeroZero) {
    Widget w;
    Point p(0,0);
    ASSERT_EQ(p, w.position());
}

TEST(WidgetTests, DefaultWidgetHasDefaultWindowTitle) {
    std::string wintitle = "Default Window Title";
    Widget w;
    ASSERT_EQ(wintitle, w.title());
}

TEST(WidgetTests, CanResizeWidthAndHeightSimultaneously) {
    Widget w;
    w.resize(1024,768);
    Size expected(1024,768);
    ASSERT_EQ(expected, w.size());
}

TEST(WidgetTests, CanMoveWidgetToNewLocation) {
    Point newPos(50,60);
    Widget w;
    w.setPosition(newPos);
    ASSERT_EQ(newPos, w.position());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
