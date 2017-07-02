#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/OutOfBoundsException>
#include <prism/algorithm>
#include <prism/Iterator>
#include <string>
#include <memory>
#include <cassert>
#include <iostream>
using namespace std;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE
//==============================================================================
// StringImpl
//==============================================================================
class StringImpl {
public:
    using iterator = prism::SequenceIterator<char,false>;
public:
    StringImpl(const int capacity = 0) {
        start = this->allocate(capacity);
        end = start;
        finish = start + capacity;
    }

    template <typename Iter>
    StringImpl(const int capacity, Iter itBegin, Iter itEnd) {
        start = this->allocate(capacity);
        prism::copy(itBegin, itEnd, start);
        end = start + (itEnd-itBegin);
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
    	other->start = temp;
        temp = this->end;
    	this->end = other->end;
    	other->end = temp;
        temp = this->finish;
    	this->finish = other->finish;
    	other->finish = temp;
    }

    char *
    allocate(const int capacity) const {
        return new char[capacity];
    }

    const bool
    indexOutOfBounds(const int index) const {
        return index < 0 || index >= end-start;
    }

    void
    append(const char c) {
        *end = c;
        ++end;
    }

    const int
    consumedBytes() const {
        return end - start;
    }

    const int
    totalBytes() const {
        return finish - start;
    }

    iterator
    beginIter() const {
        return start;
    }

    iterator
    endIter() const {
        return this->end;
    }
private:
    char * start{nullptr};
    char * end{nullptr};
    char * finish{nullptr};
};
//==============================================================================
// String
//==============================================================================
class String {
public:
    using iterator = StringImpl::iterator;
public:
    ~String() = default;

    String()
    :   impl{new StringImpl}
    {}

    String(const char c)
    :   impl{new StringImpl(1)}
    {
        impl->append(c);
    }

    String(const char * str)
    :   impl{new StringImpl(0)}
    {
        *this = String(std::string(str));
    }

    String(const std::string& str)
    :   impl{new StringImpl(str.length(), str.cbegin(), str.cend())}
    {}

    const int
    length() const {
        return impl->consumedBytes();
    }

    const bool
    isEmpty() const {
        return length() == 0;
    }

    const int
    capacity() const {
        return impl->totalBytes();
    }

    void
    reserve(const int newCapacity) {
        if (newCapacity <= this->capacity())
            return;

        StringImpl newImpl(newCapacity, this->begin(), this->end());
        impl->swap(&newImpl);
    }

    const char &
    at(const int index) {
        if (impl->indexOutOfBounds(index))
            throw prism::OutOfBoundsException(index);
        return operator[](index);
    }

    const char&
    operator[](const int index) const {
        return *(begin() + index);
    }

    iterator
    begin() const {
        return impl->beginIter();
    }

    iterator
    end() const {
        return impl->endIter();
    }

    const bool
    contains(const char c) const {
        iterator it = prism::find(begin(), end(), c);
        if (it == end()) return false;
        return true;
    }

    const bool
    contains(const String& substring) const {
        iterator it = prism::search(this->begin(), this->end(),
            substring.begin(), substring.end());
        if (it == end()) return false;
        return true;
    }
private:
    // class StringImpl;
    std::shared_ptr<StringImpl> impl;
};

const bool
operator==(const String& lhs, const String& rhs) {
    if (lhs.length() != rhs.length()) return false;
    for (int i=0; i<lhs.length(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

std::ostream&
operator<<(std::ostream& out, const String& s) {
    for (int i=0; i<s.length(); ++i)
        out << s[i];
    return out;
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
    ASSERT_EQ(String("prism"), s);
    ASSERT_EQ(newCapacity, s.capacity());
}

TEST(StringTests, RequestToDecreaseReservedMemoryToLessThanCurrentLengthIsIgnored) {
    String s = "prism";
    const int capacityBeforeReserve = s.capacity();
    s.reserve(1);
    ASSERT_EQ(capacityBeforeReserve, s.capacity());
}

TEST(StringTests, ReturnsTrueIfContainsGivenChar) {
    String s = "abc";
    ASSERT_TRUE(s.contains('a'));
    ASSERT_TRUE(s.contains('b'));
    ASSERT_TRUE(s.contains('c'));
    ASSERT_FALSE(s.contains('q'));
}

TEST(StringTests, ReturnsTrueIfContainsSubstring) {
    String s = "prism";
    ASSERT_TRUE(s.contains("pri"));
    ASSERT_TRUE(s.contains("ris"));
    ASSERT_TRUE(s.contains("ism"));
    ASSERT_FALSE(s.contains("PRI"));
    ASSERT_FALSE(s.contains("abc"));
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
