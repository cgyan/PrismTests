#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/OutOfBoundsException>
#include <prism/algorithm>
#include <prism/Iterator>
#include <string>
#include <memory>
#include <cctype>
#include <cassert>
#include <iostream>
using namespace std;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE
//==============================================================================
// StringImpl
//==============================================================================
class String;
class StringImpl {
public:
    using iterator = prism::SequenceIterator<char,false>;
    using const_iterator = prism::SequenceIterator<char,true>;
public:
    StringImpl(const int capacity = 0) {
        start = this->allocate(capacity);
        end = start;
        finish = start + capacity;
    }

    StringImpl(const int capacity, const_iterator itBegin, const_iterator itEnd) {
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
    insertAtEnd(const char c) {
        *end = c;
        ++end;
    }

    void
    insertAtEnd(const_iterator first, const_iterator last) {
        const int numCharsToInsert = last - first;
        ensureSufficientStorage(numCharsToInsert);
        prism::copy(first, last, end);
        end += numCharsToInsert;
    }

    void
    insert(const int index, const char c) {
        const int numCharsToInsert = 1;
        ensureSufficientStorage(numCharsToInsert);
        prism::copy_backward(start + index, end, end + 1);
        start[index] = c;
        end += numCharsToInsert;
    }

    const int
    usedBytes() const {
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
        return end;
    }
private:
    const bool
    storageExceeded(const int numCharsToInsert) const {
        return this->usedBytes() + numCharsToInsert > this->totalBytes();
    }

    void
    ensureSufficientStorage(const int numCharsToInsert) {
        if (storageExceeded(numCharsToInsert)) {
            const int newCapacity = (numCharsToInsert + totalBytes()) * exponent;
            StringImpl newImpl(newCapacity, start, end);
            this->swap(&newImpl);
        }
    }
private:
    char * start{nullptr};
    char * end{nullptr};
    char * finish{nullptr};
    const int exponent{2};
};
//==============================================================================
// String
//==============================================================================
class String;
const bool operator==(const String& lhs, const String& rhs);

class String {
public:
    using iterator = StringImpl::iterator;
    using const_iterator = StringImpl::const_iterator;
public:
    ~String() = default;

    String()
    :   impl{new StringImpl}
    {}

    String(const char c)
    :   impl{new StringImpl(1)}
    {
        impl->insertAtEnd(c);
    }

    String(const char * str)
    :   impl{new StringImpl(0)}
    {
        *this = String(std::string(str));
    }

    String(const std::string& str)
    :   impl{new StringImpl(
                    str.length(),
                    str.data(),
                    str.data() + str.length()
            )}
    {}

    String(const_iterator first, const_iterator last)
    :   impl{new StringImpl(last - first, first, last)}
    {}

    const int
    length() const {
        return impl->usedBytes();
    }

    const int
    size() const {
        return length();
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

    char&
    operator[](const int index) {
        return *(begin() + index);
    }

    const char&
    operator[](const int index) const {
        return *(begin() + index);
    }

    iterator
    begin() {
        return impl->beginIter();
    }

    const_iterator
    begin() const {
        return impl->beginIter();
    }

    iterator
    end() {
        return impl->endIter();
    }

    const_iterator
    end() const {
        return impl->endIter();
    }

    const bool
    contains(const char c) const {
        const_iterator it = prism::find(begin(), end(), c);
        if (it == end()) return false;
        return true;
    }

    const bool
    contains(const String& substring) const {
        const_iterator it = prism::search(this->begin(), this->end(),
            substring.begin(), substring.end());
        if (it == end()) return false;
        return true;
    }

    const int
    count(const char c) const {
        return prism::count(this->begin(), this->end(), c);
    }

    const int
    count(const String& substring) const {
        int ret = 0;
    	const_iterator bit = begin();
    	const_iterator eit = end();

    	while (bit != eit) {
    		const_iterator result = prism::search(bit, eit, substring.begin(), substring.end());
    		if (result != eit) {
    			++ret;
    			bit = result + 1;
    		}
    		else ++bit;
    	}
    	return ret;
    }

    const bool
    startsWith(const char c) const {
        return operator[](0) == c;
    }

    const bool
    startsWith(const String& substring) const {
        return prism::equal(substring.begin(), substring.end(), this->begin());
    }

    const bool
    endsWith(const char c) const {
        return *(--end()) == c;
    }

    const bool
    endsWith(const String& substring) const {
        return prism::equal(substring.begin(), substring.end(), this->end() - substring.length());
    }

    const int
    indexOf(const char c, const int from = 0) const {
        const_iterator it = prism::find(this->begin() + from, this->end(), c);
        if (it == end()) return -1;
        return it - begin();
    }

    const int
    lastIndexOf(const char c, const int from = -1) const {
        const_iterator bit = begin();
        const_iterator eit = end();
        if (from != -1) eit = begin() + from;
        const_iterator it = prism::find_last(bit, eit, c);
        if (it == eit) return -1;
        return it - begin();
    }

    void
    clear() {
        StringImpl newImpl;
        impl->swap(&newImpl);
    }

    void
    fill(const char c) {
        prism::fill(this->begin(), this->end(), c);
    }

    void
    squeeze() {
        StringImpl newImpl(this->length(), begin(), end());
        impl->swap(&newImpl);
    }

    String
    sub(const int startIndex, const int numChars = -1) const {
        if (startIndex < 0 || startIndex >= length())
            return String();
        const_iterator bit = begin();
        const_iterator eit;
        if (numChars == -1 || startIndex + numChars >= length())
            eit = end();
        else
            eit = bit + startIndex + numChars;
        String s(bit + startIndex, eit);
        return s;
    }

    void
    append(const char c) {
        impl->insertAtEnd(c);
    }

    void
    append(const String& str) {
        impl->insertAtEnd(str.begin(), str.end());
    }

    void
    prepend(const char c) {
        impl->insert(0, c);
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

TEST(StringTests, CountsTheOccurrencesOfChar) {
    String s = "tests";
    ASSERT_EQ(1, s.count('e'));
    ASSERT_EQ(2, s.count('s'));
    ASSERT_EQ(0, s.count('q'));
}

TEST(StringTests, CountsTheOccurrencesOfSubstring) {
    String s = "I see sea shells by the sea shore";
    ASSERT_EQ(1, s.count("shells"));
    ASSERT_EQ(2, s.count("sea"));
    ASSERT_EQ(0, s.count("prism"));
}

TEST(StringTests, ReturnsTrueIfStartsWithChar) {
    String s = "prism";
    ASSERT_TRUE(s.startsWith('p'));
    ASSERT_FALSE(s.startsWith('r'));
}

TEST(StringTests, ReturnsTrueIfStartsWithSubstring) {
    String s = "prism";
    ASSERT_TRUE(s.startsWith("pri"));
    ASSERT_FALSE(s.startsWith("ism"));
}

TEST(StringTests, ReturnsTrueIfEndsWithChar) {
    String s = "prism";
    ASSERT_TRUE(s.endsWith('m'));
    ASSERT_FALSE(s.endsWith('p'));
}

TEST(StringTests, ReturnsTrueIfEndsWithSubstring) {
    String s = "prism";
    ASSERT_TRUE(s.endsWith("ism"));
    ASSERT_FALSE(s.endsWith("pri"));
}

TEST(StringTests, ReturnsFirstIndexOfGivenChar) {
    String s = "tests";
    ASSERT_EQ(0, s.indexOf('t'));
    ASSERT_EQ(1, s.indexOf('e'));
}

TEST(StringTests, ReturnsFirstIndexOfGivenCharStartingFromGivenIndex) {
    String s = "tests";
    const int startIndex = 1;
    ASSERT_EQ(3, s.indexOf('t', startIndex));
}

TEST(StringTests, ReturnsNotFoundIfFirstIndexOfCharNotFound) {
    String s = "tests";
    const int NotFound = -1;
    ASSERT_EQ(NotFound, s.indexOf('q'));
}

TEST(StringTests, ReturnsLastIndexOfGivenChar) {
    String s = "tests";
    ASSERT_EQ(4, s.lastIndexOf('s'));
    ASSERT_EQ(3, s.lastIndexOf('t'));
}

TEST(StringTests, ReturnsLastIndexOfGivenCharStartingFromGivenIndex) {
    String s = "tests";
    const int startIndex = 3;
    ASSERT_EQ(2, s.lastIndexOf('s', startIndex));
}

TEST(StringTests, ReturnsNotFoundIfLastIndexOfCharNotFound) {
    String s = "tests";
    const int NotFound = -1;
    ASSERT_EQ(NotFound, s.lastIndexOf('q'));
}

TEST(StringTests, CanResetStringBackToDefault) {
    String s = "prism";
    s.clear();
    ASSERT_EQ(String(""), s);
    ASSERT_EQ(0, s.length());
}

TEST(StringTests, CanFillStringWithGivenChar) {
    String s = "prism";
    s.fill('q');
    ASSERT_EQ(String("qqqqq"), s);
}

TEST(StringTests, CanRemoveUnusedBytes) {
    String s = "prism";
    s.reserve(20);
    s.squeeze();
    ASSERT_EQ(s.length(), s.capacity());
}

TEST(StringTests, ReturnsSubstringStartingFromGivenIndex) {
    String s = "this is a string";
    ASSERT_EQ(String("a string"), s.sub(8));
    ASSERT_EQ(String("string"), s.sub(10));
}

TEST(StringTests, ReturnsSubstringStartingFromGivenIndexForGivenNumOfChars) {
    String s = "this is a string";
    ASSERT_EQ(String("is a"), s.sub(5, 4));
    ASSERT_EQ(String(), s.sub(-1));
    ASSERT_EQ(String(), s.sub(s.size()));
    ASSERT_EQ(String("string"), s.sub(10, 100));
}

TEST(StringTests, CanAppendCharToDefaultString) {
    String s;
    s.append('q');
    ASSERT_EQ(String("q"), s);
    ASSERT_EQ(1, s.length());
}

TEST(StringTests, CanAppendCharToExistingString) {
    String s = "prism";
    s.append('s');
    ASSERT_EQ(String("prisms"), s);
    ASSERT_EQ(6, s.size());
}

TEST(StringTests, CanAppendStringToDefaultString) {
    String s;
    s.append(String("prism"));
    ASSERT_EQ(String("prism"), s);
    ASSERT_EQ(5, s.length());
}

TEST(StringTests, CanAppendStringToExistingString) {
    String s = "hello";
    s.append(" world!");
    ASSERT_EQ(String("hello world!"), s);
    ASSERT_EQ(12, s.length());
}

TEST(StringTests, CanPrependCharToDefaultString) {
    String s;
    s.prepend('q');
    ASSERT_EQ(String("q"), s);
    ASSERT_EQ(1, s.length());
}

TEST(StringTests, CanPrependCharToExistingString) {
    String s = "test";
    s.prepend('a');
    ASSERT_EQ(String("atest"), s);
    ASSERT_EQ(5, s.length());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
