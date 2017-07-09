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
    StringImpl() = default;

    StringImpl(const char c) {
        m_start = this->allocate(1);
        m_start[0] = c;
        m_end = m_start + 1;
        m_finish = m_end;
    }

    template <typename Iter>
    StringImpl(Iter first, Iter last, int capacity = -1) {
        const int numChars = last - first;
        if (capacity == -1) capacity = numChars;
        m_start = this->allocate(capacity);
        prism::copy(first, last, m_start);
        m_end = m_start + numChars;
        m_finish = m_start + capacity;
    }

    ~StringImpl() {
        delete [] m_start;
        m_start = m_end = m_finish = nullptr;
    }

    void
    swap(StringImpl* other) {
        char * temp = m_start;
    	m_start = other->m_start;
    	other->m_start = temp;
        temp = m_end;
    	m_end = other->m_end;
    	other->m_end = temp;
        temp = m_finish;
    	m_finish = other->m_finish;
    	other->m_finish = temp;
    }

    char *
    allocate(const int capacity) const {
        return new char[capacity];
    }

    void
    insertAtEnd(const char c) {
        const int numCharsToInsert = 1;
        ensureSufficientCapacity(numCharsToInsert);
        *m_end = c;
        ++m_end;
    }

    void
    insertAtEnd(const_iterator first, const_iterator last) {
        const int numCharsToInsert = last - first;
        ensureSufficientCapacity(numCharsToInsert);
        prism::copy(first, last, m_end);
        m_end += numCharsToInsert;
    }

    void
    insert(const_iterator pos, const char c) {
        const int numCharsToInsert = 1;
        const int insertIndex = pos - begin();
        ensureSufficientCapacity(numCharsToInsert);
        prism::copy_backward(m_start + insertIndex, m_end, m_end + 1);
        m_start[insertIndex] = c;
        m_end += numCharsToInsert;
    }

    void
    insert(const_iterator pos, const_iterator first, const_iterator last) {
        const int numCharsToInsert = last - first;
        const int insertIndex = pos - begin();
        ensureSufficientCapacity(numCharsToInsert);
        prism::copy_backward(m_start + insertIndex, m_end, m_end + numCharsToInsert);
        prism::copy(first, last, m_start + insertIndex);
        m_end += numCharsToInsert;
    }

    const int
    size() const {
        return m_end - m_start;
    }

    const int
    capacity() const {
        return m_finish - m_start;
    }

    iterator
    begin() const {
        return m_start;
    }

    iterator
    end() const {
        return m_end;
    }

    const bool
    outOfBounds(const int index) const {
        return index < 0 || index >= size();
    }
private:
    const bool
    capacityExceeded(const int numCharsToInsert) const {
        return this->size() + numCharsToInsert > this->capacity();
    }

    void
    ensureSufficientCapacity(const int numCharsToInsert) {
        if (capacityExceeded(numCharsToInsert)) {
            const int newCapacity = (numCharsToInsert + capacity()) * m_capacityGrowth;
            StringImpl newImpl(m_start, m_end, newCapacity);
            this->swap(&newImpl);
        }
    }
private:
    char * m_start{nullptr};
    char * m_end{nullptr};
    char * m_finish{nullptr};
    const int m_capacityGrowth{2};
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
    String();
    String(const char c);
    String(const char * str);
    String(const std::string& str);
    String(const String& copy);
    String& operator=(const String& rhs);

    const int length() const;
    const int size() const;
    const bool isEmpty() const;
    const int capacity() const;
    void reserve(const int newCapacity);
    void squeeze();

    const char & at(const int index);
    char& operator[](const int index);
    const char& operator[](const int index) const;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    const bool contains(const char c) const;
    const bool contains(const String& substring) const;
    const int count(const char c) const;
    const int count(const String& substring) const;

    const bool startsWith(const char c) const;
    const bool startsWith(const String& substring) const;
    const bool endsWith(const char c) const;
    const bool endsWith(const String& substring) const;

    const int indexOf(const char c, const int from = 0) const;
    const int lastIndexOf(const char c, const int from = -1) const;

    void clear();
    void fill(const char c);
    String sub(const int from, int numChars = -1) const;

    void append(const char c);
    void append(const String& str);
    void prepend(const char c);
    void prepend(const String& str);
    String& insert(const int index, const char c);
    String& insert(const int index, const String& str);
    iterator insert(const_iterator pos, const char c);
    iterator insert(const_iterator pos, const String& str);
private:
    // class StringImpl;
    std::shared_ptr<StringImpl> impl;
};

String::String()
:   impl{new StringImpl}
{}

String::String(const char c)
:   impl{new StringImpl(c)}
{}

String::String(const char * str)
{
    const char * first = str;
    const char * last = first;
    while (*last != '\0') {
        ++last;
    }
    impl.reset(new StringImpl(first, last));
}

String::String(const std::string& str)
:   impl{new StringImpl(str.cbegin(), str.cend())}
{}

String::String(const String& copy)
:   impl{new StringImpl(copy.begin(), copy.end())}
{}

String&
String::operator=(const String& rhs) {
    String copy(rhs);
    impl->swap(copy.impl.get());
    return *this;
}

const int
String::length() const {
    return size();
}

const int
String::size() const {
    return impl->size();
}

const bool
String::isEmpty() const {
    return size() == 0;
}

const int
String::capacity() const {
    return impl->capacity();
}

void
String::reserve(const int newCapacity) {
    if (newCapacity <= this->capacity())
        return;

    StringImpl newImpl(this->begin(), this->end(), newCapacity);
    impl->swap(&newImpl);
}

const char &
String::at(const int index) {
    if (impl->outOfBounds(index))
        throw prism::OutOfBoundsException(index);
    return operator[](index);
}

char&
String::operator[](const int index) {
    return *(begin() + index);
}

const char&
String::operator[](const int index) const {
    return *(begin() + index);
}

String::iterator
String::begin() {
    return impl->begin();
}

String::const_iterator
String::begin() const {
    return impl->begin();
}

String::iterator
String::end() {
    return impl->end();
}

String::const_iterator
String::end() const {
    return impl->end();
}

const bool
String::contains(const char c) const {
    const_iterator it = prism::find(begin(), end(), c);
    if (it == end()) return false;
    return true;
}

const bool
String::contains(const String& substring) const {
    const_iterator it = prism::search(this->begin(), this->end(),
        substring.begin(), substring.end());
    if (it == end()) return false;
    return true;
}

const int
String::count(const char c) const {
    return prism::count(this->begin(), this->end(), c);
}

const int
String::count(const String& substring) const {
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
String::startsWith(const char c) const {
    return operator[](0) == c;
}

const bool
String::startsWith(const String& substring) const {
    return prism::equal(substring.begin(), substring.end(), this->begin());
}

const bool
String::endsWith(const char c) const {
    return *(--end()) == c;
}

const bool
String::endsWith(const String& substring) const {
    return prism::equal(substring.begin(), substring.end(), this->end() - substring.length());
}

const int
String::indexOf(const char c, const int from) const {
    const_iterator it = prism::find(this->begin() + from, this->end(), c);
    if (it == end()) return -1;
    return it - begin();
}

const int
String::lastIndexOf(const char c, const int from) const {
    const_iterator bit = begin();
    const_iterator eit = end();
    if (from != -1) eit = begin() + from;
    const_iterator it = prism::find_last(bit, eit, c);
    if (it == eit) return -1;
    return it - begin();
}

void
String::clear() {
    StringImpl newImpl;
    impl->swap(&newImpl);
}

void
String::fill(const char c) {
    prism::fill(this->begin(), this->end(), c);
}

void
String::squeeze() {
    StringImpl newImpl(begin(), end(), this->length());
    impl->swap(&newImpl);
}

String
String::sub(int from, const int numChars) const {
    if (impl->outOfBounds(from))
        return String();

    const_iterator first = begin() + from;
    const_iterator last;
    if (numChars < 0 || impl->outOfBounds(from + numChars))
        last = end();
    else
        last = first + numChars;

    StringImpl impl(first, last);
    String s;
    s.impl->swap(&impl);
    return s;
}

void
String::append(const char c) {
    impl->insertAtEnd(c);
}

void
String::append(const String& str) {
    impl->insertAtEnd(str.begin(), str.end());
}

void
String::prepend(const char c) {
    impl->insert(begin(), c);
}

void
String::prepend(const String& str) {
    impl->insert(begin(), str.begin(), str.end());
}

String&
String::insert(const int index, const char c) {
    if (index == size()) impl->insertAtEnd(c);
    else impl->insert(begin() + index, c);
    return *this;
}

String&
String::insert(const int index, const String& str) {
    if (index == size()) impl->insertAtEnd(str.begin(), str.end());
    else impl->insert(begin() + index, str.begin(), str.end());
    return *this;
}

String::iterator
String::insert(const_iterator pos, const char c) {
    const int insertIndex = pos - begin();
    if (pos == end()) impl->insertAtEnd(c);
    else impl->insert(pos, c);
    return begin() + insertIndex;
}

String::iterator
String::insert(const_iterator pos, const String& str) {
    const int insertIndex = pos - begin();
    if (pos == end()) impl->insertAtEnd(str.begin(), str.end());
    else impl->insert(pos, str.begin(), str.end());
    return begin() + insertIndex;
}

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
    ASSERT_EQ(String(), s);
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
    ASSERT_EQ(String(), s.sub(-1));
    ASSERT_EQ(String(), s.sub(s.size()));
}

TEST(StringTests, ReturnsSubstringStartingFromGivenIndexForGivenNumOfChars) {
    String s = "this is a string";
    ASSERT_EQ(String("is a"), s.sub(5, 4));
    ASSERT_EQ(String("string"), s.sub(10, 100));
    ASSERT_EQ(String("is a string"), s.sub(5, -4));
}

TEST(StringTests, CanAppendCharToDefaultString) {
    String s;
    s.append('q');
    ASSERT_EQ(String("q"), s);
    ASSERT_EQ(1, s.length());
}

TEST(StringTests, CanAppendCharToExistingString) {
    String s = "pin";
    s.append('e');
    ASSERT_EQ(String("pine"), s);
    ASSERT_EQ(4, s.size());
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

TEST(StringTests, CanPrependStringToDefaultString) {
    String s;
    s.prepend("prism");
    ASSERT_EQ(String("prism"), s);
}

TEST(StringTests, CanPrependStringToExistingString) {
    String s = "oni";
    s.prepend("pepper");
    ASSERT_EQ(String("pepperoni"), s);
}

TEST(StringTests, CanInsertCharAtIndex) {
    String s1, s2, s3;
    s3 = s2 = s1 = "prism";
    ASSERT_EQ(String("@prism"), s1.insert(0, '@'));
    ASSERT_EQ(String("pri@sm"), s2.insert(3, '@'));
    ASSERT_EQ(String("prism@"), s3.insert(5, '@'));
}

TEST(StringTests, CanInsertStringAtIndex) {
    String s1, s2, s3;
    s3 = s2 = s1 = "prism";
    ASSERT_EQ(String("@@@prism"), s1.insert(0, "@@@"));
    ASSERT_EQ(String("pri@@@sm"), s2.insert(3, "@@@"));
    ASSERT_EQ(String("prism@@@"), s3.insert(5, "@@@"));
}

TEST(StringTests, CanInsertCharByIterator) {
    String s1, s2, s3;
    s3 = s2 = s1 = "prism";

    ASSERT_EQ(s1.begin(), s1.insert(s1.begin(), '@'));
    ASSERT_EQ(String("@prism"), s1);

    ASSERT_EQ(s2.begin() + 3, s2.insert(s2.begin() + 3, '@'));
    ASSERT_EQ(String("pri@sm"), s2);

    ASSERT_EQ(--s3.end(), s3.insert(s3.end(), '@'));
    ASSERT_EQ(String("prism@"), s3);
}

TEST(StringTests, CanInsertStringByIterator) {
    String s1, s2, s3;
    s3 = s2 = s1 = "prism";

    ASSERT_EQ(s1.begin(), s1.insert(s1.begin(), "@@@"));
    ASSERT_EQ(String("@@@prism"), s1);

    ASSERT_EQ(s2.begin() + 3, s2.insert(s2.begin() + 3, "@@@"));
    ASSERT_EQ(String("pri@@@sm"), s2);

    ASSERT_EQ(s3.end() - 3, s3.insert(s3.end(), "@@@"));
    ASSERT_EQ(String("prism@@@"), s3);
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
