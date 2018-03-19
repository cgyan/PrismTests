#include <gtest/gtest.h>
#include <prism/global>
#include <prism/Widget>
#include <prism/Size>
#include <prism/Point>
#include <prism/gui/stubs/StubNativeWidget.h>
#include <string>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

Widget make_widget() {
    Widget w;
    w.setNativeWidget(new StubNativeWidget);
    return w;
}

TEST(WidgetTests, DefaultWidgetSizeIs600400) {
    Widget w = make_widget();
    ASSERT_EQ(Size(600,400), w.size());
}

TEST(WidgetTests, DefaultWidgetHasDefaultWindowTitle) {
    std::string wintitle = "Default Window Title";
    Widget w = make_widget();
    ASSERT_EQ(wintitle, w.title());
}

TEST(WidgetTests, DefaultWidgetIsNotVisible) {
    Widget w = make_widget();
    ASSERT_FALSE(w.isVisible());
}

TEST(WidgetTests, DefaultWidgetIsNotMaximized) {
    Widget w = make_widget();
    ASSERT_FALSE(w.isMaximized());
}

TEST(WidgetTests, DefaultWidgetIsNotMinimized) {
    Widget w = make_widget();
    ASSERT_FALSE(w.isMinimized());
}

TEST(WidgetTests, DefaultWidgetReturnsNullForLayout) {
    Widget w = make_widget();
    ASSERT_EQ(nullptr, w.layout());
}

TEST(WidgetTests, WidgetIsVisibleAfterRequestMade) {
    Widget w = make_widget();
    w.setVisible();
    ASSERT_TRUE(w.isVisible());
}

TEST(WidgetTests, CanMaximizeWidget) {
    Widget w = make_widget();
    w.setMaximized();
    ASSERT_TRUE(w.isMaximized());
}

TEST(WidgetTests, CanMinimizeWidget) {
    Widget w = make_widget();
    w.setMinimized();
    ASSERT_TRUE(w.isMinimized());
}

TEST(WidgetTests, CanRenameWindowTitle) {
    std::string newtitle = "New Window Title";
    Widget w = make_widget();
    w.setTitle(newtitle);
    ASSERT_EQ(newtitle, w.title());
}

TEST(WidgetTests, CanResizeWidthAndHeightSimultaneously) {
    Widget w = make_widget();
    Size expected;

    expected.set(600,400);
    w.resize(expected);
    ASSERT_EQ(expected, w.size());

    expected.set(1024,768);
    w.resize(expected.width(), expected.height());
    ASSERT_EQ(expected, w.size());
}

TEST(WidgetTests, CanPreventResizingToLessThanMinimumWidth) {
    Widget w = make_widget();
    w.resize(500,500);
    const int minWidth = 200;

    w.setMinimumWidth(minWidth);
    ASSERT_EQ(minWidth, w.minimumWidth());

    w.setWidth(minWidth - 1);
    ASSERT_EQ(minWidth, w.width());
}

TEST(WidgetTests, CanPreventResizingToLessThanMinimumHeight) {
    Widget w = make_widget();
    w.resize(500,500);
    const int minHeight = 200;

    w.setMinimumHeight(minHeight);
    ASSERT_EQ(minHeight, w.minimumHeight());

    w.setHeight(minHeight - 1);
    ASSERT_EQ(minHeight, w.height());
}

TEST(WidgetTests, CanPreventResizingToGreaterThanMaximumWidth) {
    Widget w = make_widget();
    w.resize(500,500);
    const int maxWidth = 1000;

    w.setMaximumWidth(maxWidth);
    ASSERT_EQ(maxWidth, w.maximumWidth());

    w.setWidth(maxWidth + 1);
    ASSERT_EQ(maxWidth, w.width());
}

TEST(WidgetTests, CanPreventResizingToGreaterThanMaximumHeight) {
    Widget w = make_widget();
    w.resize(500,500);
    const int maxHeight = 1000;

    w.setMaximumHeight(maxHeight);
    ASSERT_EQ(maxHeight, w.maximumHeight());

    w.setHeight(maxHeight + 1);
    ASSERT_EQ(maxHeight, w.height());
}

TEST(WidgetTests, CanPreventResizingToLessThanMinimumSize) {
    Widget w = make_widget();
    w.resize(500,500);
    Size minSize(100,100);

    w.setMinimumSize(minSize);
    ASSERT_EQ(minSize, w.minimumSize());

    w.resize(99,100);
    ASSERT_EQ(minSize, w.size());

    w.resize(100,99);
    ASSERT_EQ(minSize, w.size());

    w.resize(99,99);
    ASSERT_EQ(minSize, w.size());
}

TEST(WidgetTests, CanPreventResizingToGreaterThanMaximumSize) {
    Widget w = make_widget();
    w.resize(500,500);
    Size maxSize(1000,1000);

    w.setMaximumSize(maxSize);
    ASSERT_EQ(maxSize, w.maximumSize());

    w.resize(1001,1000);
    ASSERT_EQ(maxSize, w.size());

    w.resize(1000,1001);
    ASSERT_EQ(maxSize, w.size());

    w.resize(1001,1001);
    ASSERT_EQ(maxSize, w.size());
}

TEST(WidgetTests, CanPreventResizingIfWidthIsFixed) {
    Widget w = make_widget();
    const int fixedWidth = 500;
    w.setFixedWidth(fixedWidth);

    const int ignoredWidth = 100;
    w.setWidth(ignoredWidth);

    ASSERT_EQ(fixedWidth, w.width());
}

TEST(WidgetTests, CanPreventResizingIfHeightIsFixed) {
    Widget w = make_widget();
    const int fixedHeight = 500;
    w.setFixedHeight(fixedHeight);

    const int ignoredHeight = 100;
    w.setHeight(ignoredHeight);

    ASSERT_EQ(fixedHeight, w.height());
}

TEST(WidgetTests, CanPreventResizingIfSizeIsFixed) {
    Widget w = make_widget();
    Size fixedSize(300,400);
    w.setFixedSize(fixedSize);

    Size ignoredSize(1024,768);
    w.resize(ignoredSize);

    ASSERT_EQ(fixedSize, w.size());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

/*

Button * btn = new Button;
LineEdit * lineEdit = new LineEdit;

BoxLayout * boxLayout = new BoxLayout(Vertical);
boxLayout->insertWidget(btn, 0);
boxLayout->insertWidget(lineEdit, 1);

Widget * centralWidget = window->centralWidget()
centralWidget->setLayout(boxLayout);

*/

// Size getWindowSize(WinId winId) {
//     int width, height;
// #ifdef _WIN32
//     RECT rect;
//     GetWindowRect(winId, &rect);
//     width = rect.right - rect.left;
//     height = rect.bottom - rect.top;
// #elif __APPLE__
//     NSSize size = winId.frame.size;
//     width = size.width;
//     height = size.height;
// #endif
//     return Size(width, height);
// }
