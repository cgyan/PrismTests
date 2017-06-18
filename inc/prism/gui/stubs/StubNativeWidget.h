#ifndef PRISM_STUB_NATIVE_WIDGET_H_
#define PRISM_STUB_NATIVE_WIDGET_H_

#include <prism/global>
#include <prism/gui/NativeWidget.h>
#include <prism/Size>
#include <prism/Point>
#include <string>

PRISM_BEGIN_NAMESPACE

class StubNativeWidget : public NativeWidget {
public:
    StubNativeWidget()
    :   m_size{},
        m_title{"Default Window Title"}
    {
        m_size.set(600,400);
    }

    Size size() const {
        return m_size;
    }

    void setSize(const Size& size) {
        m_size = size;
    }

    void setSize(const int width, const int height) {
        m_size.set(width, height);
    }

    std::string title() const {
        return m_title;
    }

    void setTitle(const std::string& title) {
        m_title = title;
    }
private:
    Size m_size;
    std::string m_title;
};

PRISM_END_NAMESPACE

#endif // PRISM_STUB_NATIVE_WIDGET_H_
