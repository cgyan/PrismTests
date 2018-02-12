#include <prism/global>

PRISM_BEGIN_NAMESPACE

class AbstractDummyImpl {
public:
    virtual ~AbstractDummyImpl() {}
    virtual const int size() const = 0;
};

class DummyImpl : public AbstractDummyImpl {
public:
    const int size() const override {
        return m_size;
    }
private:
    int m_size{0};
};

class DummyImplStub : public AbstractDummyImpl {
public:
    const int size() const override {
        return 0;
    }
};

class Dummy {
public:
    Dummy()
    : m_impl{new DummyImpl}
    {}

    Dummy(DummyImplStub * implStub)
    : m_impl{implStub}
    {}

    ~Dummy() {
        delete m_impl;
    }

    const int size() const {
        return m_impl->size();
    }
private:
    AbstractDummyImpl * m_impl;
};

PRISM_END_NAMESPACE

#include <gtest/gtest.h>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

TEST(DummyTests, DefaultReturnsSizeZero) {
    Dummy d(new DummyImplStub);
    ASSERT_EQ(0, d.size());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
