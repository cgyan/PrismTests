#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/OutOfBoundsException>
#include <prism/algorithm>
#include <string>
#include <memory>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE
//==============================================================================
// StringImpl
//==============================================================================
class StringImpl {
public:
    char * start{nullptr};
    char * end{nullptr};
    char * finish{nullptr};

    StringImpl(const int capacity = 0) {
        start = this->allocate(capacity);
        end = start;
        finish = start + capacity;
    }

    ~StringImpl() {
        delete [] start;
        start = end = finish = nullptr;
    }

    void
    swap(StringImpl* other) {
        char * temp = this->start;
    	this->start = other->start;
    	this->start = temp;
    }

    char *
    allocate(const int capacity) {
        return new char[capacity];
    }

    const bool
    indexOutOfBounds(const int index) {
        return index < 0 || index >= end-start;
    }
};
//==============================================================================
// String
//==============================================================================
class String {
private:
    // class StringImpl;
    std::shared_ptr<StringImpl> impl;
public:
    ~String() = default;

    String()
    :   impl{new StringImpl}
    {}

    String(const char c)
    :   impl{new StringImpl(1)}
    {
        impl->start[0] = c;
        impl->end = impl->start + 1;
    }

    String(const char * str)
    :   impl{new StringImpl}
    {
        *this = String(std::string(str));
    }

    String(const std::string& str)
    :   impl{new StringImpl(str.length())}
    {
        prism::copy(str.cbegin(), str.cend(), impl->start);
        impl->end = impl->start + str.length();
    }

    const int
    length() const {
        return impl->end - impl->start;
    }

    const bool
    isEmpty() const {
        return length() == 0;
    }

    const int
    capacity() const {
        return impl->finish - impl->start;
    }

    void
    reserve(const int newCapacity) {
        if (newCapacity <= this->capacity())
            return;

        const int currentLength = this->length();
        StringImpl newImpl(newCapacity);
        prism::copy(impl->start, impl->end, newImpl.start);
        impl->swap(&newImpl);

        impl->end = impl->start + currentLength;
        impl->finish = impl->start + newCapacity;
    }

    const char &
    at(const int index) {
        if (impl->indexOutOfBounds(index))
            throw prism::OutOfBoundsException(index);
        return impl->start[index];
    }

    const char&
    operator[](const int index) const {
        return *(impl->start + index);
    }
};

const bool
operator==(const String& lhs, const String& rhs) {
    if (lhs.length() != rhs.length()) return false;
    for (int i=0; i<lhs.length(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}
//==============================================================================
// Tests
//==============================================================================
TEST(StringTests, DefaultStringIsEmpty) {
    String s;
    ASSERT_TRUE(s.isEmpty());
}

TEST(StringTests, DefaultStringHasCapacityOfZero) {
    String s;
    ASSERT_EQ(0, s.capacity());
}

TEST(StringTests, DefaultStringHasLengthOfZero) {
    String s;
    ASSERT_EQ(0, s.length());
}

TEST(StringTests, StringWithOneCharHasLengthOfOne) {
    String s('c');
    ASSERT_EQ(1, s.length());
}

TEST(StringTests, StringWithFiveCharsHasLengthOfFive) {
    String s("prism");
    ASSERT_EQ(5, s.length());
}

TEST(StringTests, InitializedStringIsNotEmpty) {
    String s("prism");
    ASSERT_FALSE(s.isEmpty());
}

TEST(StringTests, CanAccessIndividualChars) {
    String s("prism");
    ASSERT_EQ('p', s[0]);
    ASSERT_EQ('r', s[1]);
    ASSERT_EQ('i', s[2]);
    ASSERT_EQ('s', s[3]);
    ASSERT_EQ('m', s[4]);

    ASSERT_EQ('p', s.at(0));
    ASSERT_EQ('r', s.at(1));
    ASSERT_EQ('i', s.at(2));
    ASSERT_EQ('s', s.at(3));
    ASSERT_EQ('m', s.at(4));
}

TEST(StringTests, ThrowsWhenAccessingInvalidCharIndex) {
    String s = "prism";
    ASSERT_THROW(s.at(-1), prism::OutOfBoundsException);
    ASSERT_THROW(s.at(s.length()), prism::OutOfBoundsException);
    ASSERT_THROW(s.at(20), prism::OutOfBoundsException);
}

TEST(StringTests, CanReserveMemoryInDefaultStringForTwentyChars) {
    String s;
    const int newCapacity = 20;

    s.reserve(newCapacity);

    ASSERT_EQ(newCapacity, s.capacity());
}

TEST(StringTests, CanIncreaseReservedMemoryOnExistingString) {
    String s("prism");
    const int newCapacity = 20;

    s.reserve(newCapacity);

    ASSERT_TRUE(String("prism") == s);
    ASSERT_EQ(newCapacity, s.capacity());
}

TEST(StringTests, RequestToDecreaseReservedMemoryToLessThanCurrentLengthIsIgnored) {
    String s = "prism";
    const int capacityBeforeReserve = s.capacity();
    s.reserve(1);
    ASSERT_EQ(capacityBeforeReserve, s.capacity());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
