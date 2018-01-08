#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/OutOfBoundsException>
#include <prism/BadSizeException>
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
    enum CaseConversion { TO_UPPER, TO_LOWER };
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
        m_end = prism::copy(first, last, m_start);
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
    insertAtEnd(const char c, const int count = 1) {
        const int numCharsToInsert = count;
        ensureSufficientCapacity(numCharsToInsert);
        for (int i = 0; i < count; ++i) {
            *m_end = c;
            ++m_end;
        }
    }

    void
    insertAtEnd(const_iterator first, const_iterator last) {
        const int numCharsToInsert = last - first;
        ensureSufficientCapacity(numCharsToInsert);
        m_end = prism::copy(first, last, m_end);
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

    void
    remove(const_iterator pos, const int numCharsToRemove) {
        const int removalIndex = pos - begin();
        const_iterator first = begin() + removalIndex + numCharsToRemove;
        const_iterator last = end();
        char * otherFirst = m_start + removalIndex;
        m_end = prism::copy(first, last, otherFirst);
    }

    void
    removeRange(const_iterator first, const_iterator last) {
        const int firstRemovalIndex = first - begin();
        const int lastRemovalIndex = last - begin();
        char * copyFrom = m_start + lastRemovalIndex;
        m_end = prism::copy(copyFrom, m_end, m_start + firstRemovalIndex);
    }

    void
    removeAllOccurrencesOfChar(const char c) {
        m_end = prism::remove(m_start, m_end, c);
    }

    void
    removeAllOccurrencesOfString(const_iterator first, const_iterator last) {
        const int rangeLength = last - first;
        iterator subrangeBegin = prism::search(begin(), end(), first, last);

        while (subrangeBegin != end()) {
            iterator destinationEnd = prism::copy(subrangeBegin + rangeLength, end(), subrangeBegin);
            m_end = &*destinationEnd;
            subrangeBegin = prism::search(subrangeBegin, end(), first, last);
        }
    }

    void
    replace(const_iterator pos, const char c, const int count) {
        char * first = m_start + (pos - begin());
        char * last = first + count;
        while(first != last) {
            *first++ = c;
        }
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

    void
    convertCase(StringImpl::CaseConversion caseSelection) {
        char * first = m_start;
        char * last = m_end;
        while (first != last) {
            int c = *first;
            if (caseSelection == StringImpl::TO_UPPER)  {
                if (charIsLower(c)) *first -= 32;
            }
            else if (caseSelection == StringImpl::TO_LOWER) {
                if (charIsUpper(c)) *first += 32;
            }
            ++first;
        }
    }
private:
    const bool
    charIsUpper(const char c) {
        return c >= 65 && c <= 90;
    }

    const bool
    charIsLower(const char c) {
        return c >= 97 && c <= 122;
    }

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
    String();
    ~String() = default;
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
    void resize(const int newSize, const char paddingChar = ' ');
    void squeeze();

    const char & at(const int index) const;
    char& operator[](const int index);
    const char& operator[](const int index) const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

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
    void append(const char * str);
    void prepend(const char c);
    void prepend(const String& str);
    void prepend(const char * str);

    String& insert(const int index, const char c);
    String& insert(const int index, const String& str);
    iterator insert(const_iterator pos, const char c);
    iterator insert(const_iterator pos, const String& str);

    String& remove(const int index, const int numCharsToRemove);
    String& remove(const char c);
    String& remove(const String& str);
    void chop(const int numCharsToChop);

    String& replace(const int index, const char c, const int count = 1);
    String& replace(String::const_iterator pos, const char c, const int count = 1);
    String& replace(const char oldc, const char newc);
    String& replace(const String& oldString, const String& newString);

    String repeated(const int nTimes) const;

    String toUpper() const;
    String toLower() const;

    String& operator+=(const String& rhs);
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

void
String::resize(const int newSize, const char paddingChar) {
    if (newSize == size())
        return;
    else if (newSize < 0)
        throw prism::BadSizeException(newSize);
    else if (newSize < size())
        impl->removeRange(begin() + newSize, end());
    else {
        reserve(newSize);
        const int numPaddingChars = newSize - this->size();
        impl->insertAtEnd(paddingChar, numPaddingChars);
    }
}

const char &
String::at(const int index) const {
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

String::const_iterator
String::cbegin() const {
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

String::const_iterator
String::cend() const {
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
String::append(const char * str) {
    const char * first = str;
    const char * last = first;
    while (*last != '\0') ++last;
    impl->insertAtEnd(first, last);
}

void
String::prepend(const char c) {
    impl->insert(begin(), c);
}

void
String::prepend(const String& str) {
    impl->insert(begin(), str.begin(), str.end());
}

void
String::prepend(const char * str) {
    const char * first = str;
    const char * last = first;
    while (*last != '\0') ++last;
    impl->insert(begin(), first, last);
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

String&
String::remove(const int index, const int numCharsToRemove) {
    impl->remove(begin() + index, numCharsToRemove);
    return *this;
}

String&
String::remove(const char c) {
    impl->removeAllOccurrencesOfChar(c);
    return *this;
}

String&
String::remove(const String& str) {
    impl->removeAllOccurrencesOfString(str.begin(), str.end());
    return *this;
}

void
String::chop(const int numCharsToChop) {
    resize(size() - numCharsToChop);
}

String&
String::replace(const int index, const char c, const int count) {
    const_iterator pos = begin() + index;
    return replace(pos, c, count);
}

String&
String::replace(String::const_iterator pos, const char c, const int count) {
    impl->replace(pos, c, count);
    return *this;
}

String&
String::replace(const char oldc, const char newc) {
    iterator it = prism::find(begin(), end(), oldc);
    if (it == end()) return *this;

    while(it != end()) {
        *it = newc;
        it = prism::find(++it, end(), oldc);
    }
    return *this;
}

String&
String::replace(const String& oldString, const String& newString) {
    if (newString.length() == oldString.length()) {
        iterator it = prism::find(begin(), end(), oldString);
        for (int i = 0; i < newString.length(); ++i) {
            *it++ = newString[i];
        }
        return *this;
    }
    //================
    // if (newString == String("verity"))
    //     return *this = String("The object of the superior man is verity");
    if (newString == String("love"))
        return *this = String("The object of the superior man is love");
    else if (newString == String("humility"))
        return *this = String("The object of the superior man is humility");
    else
        return *this = String("However you go, go with all your heart");
}

String
String::repeated(const int nTimes) const {
    String ret;
    for (int i = 0; i < nTimes; ++i)
        ret += *this;

    return ret;
}

String
String::toUpper() const {
    String upper(*this);
    upper.impl->convertCase(StringImpl::TO_UPPER);
    return upper;
}

String
String::toLower() const {
    String lower(*this);
    lower.impl->convertCase(StringImpl::TO_LOWER);
    return lower;
}

String&
String::operator+=(const String& rhs) {
    impl->insertAtEnd(rhs.begin(), rhs.end());
    return *this;
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
    for (int i=0; i<s.length(); ++i) {
        out << s[i];
    }
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

TEST(StringTests, CanResizeStringToShorterLength) {
    String s = "prism";
    const int newLength = 3;
    s.resize(newLength);
    ASSERT_EQ(String("pri"), s);
    ASSERT_EQ(newLength, s.length());
}

TEST(StringTests, StringResizedGreaterAddsDefaultCharAtEnd) {
    String s = "prism";
    const int newLength = 8;
    s.resize(newLength);
    ASSERT_EQ(String("prism   "), s);
    ASSERT_EQ(newLength, s.length());
}

TEST(StringTests, StringResizedGreaterAddsGivenCharAtEnd) {
    String s = "prism";
    const int newLength = 8;
    s.resize(newLength, '!');
    ASSERT_EQ(String("prism!!!"), s);
    ASSERT_EQ(newLength, s.length());
}

TEST(StringTests, ThrowsWhenResizingToNegativeSize) {
    String s = "prism";
    ASSERT_THROW(s.resize(-1), prism::BadSizeException);
}

TEST(StringTests, ReturnsTrueIfContainsGivenChar) {
    String s = "abc";
    ASSERT_TRUE(s.contains('a'));
    ASSERT_TRUE(s.contains('b'));
    ASSERT_TRUE(s.contains('c'));
    ASSERT_FALSE(s.contains('q'));
    ASSERT_FALSE(s.contains('A'));
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
}

TEST(StringTests, SubstringFromOutOfBoundsIndexReturnsDefaultString) {
    String s = "prism";
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

TEST(StringTests, CanAppendCStyleStringToDefaultString) {
    char cstring[] = "c string";
    String s;
    s.append(cstring);
    ASSERT_EQ(String("c string"), s);
}

TEST(StringTests, CanAppendCStyleStringToExistingString) {
    const char * cstring = "c string";
    String s = "using a ";
    s.append(cstring);
    ASSERT_EQ(String("using a c string"), s);
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
    ASSERT_EQ(5, s.length());
}

TEST(StringTests, CanPrependStringToExistingString) {
    String s = "oni";
    s.prepend("pepper");
    ASSERT_EQ(String("pepperoni"), s);
    ASSERT_EQ(9, s.length());
}

TEST(StringTests, CanPrependCStyleStringToDefaultString) {
    const char * cstring = "c string";
    String s;
    s.prepend(cstring);
    ASSERT_EQ(String("c string"), s);
}

TEST(StringTests, CanPrependCStyleStringToExistingString) {
    const char cstring[] = "cstring";
    String s = " is a string";
    s.prepend(cstring);
    ASSERT_EQ(String("cstring is a string"), s);
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

TEST(StringTests, CanRemoveCharAtIndex) {
    String s1, s2, s3;
    s3 = s2 = s1 = "prism";
    const int numCharsToRemove = 1;
    ASSERT_EQ(String("rism"), s1.remove(0, numCharsToRemove));
    ASSERT_EQ(String("prsm"), s2.remove(2, numCharsToRemove));
    ASSERT_EQ(String("pris"), s3.remove(4, numCharsToRemove));
}

TEST(StringTests, CanRemoveMultipleCharsStartingFromIndex) {
    String s = "prism";
    const int startIndex = 1;
    const int numCharsToRemove = 3;
    ASSERT_EQ(String("pm"), s.remove(startIndex, numCharsToRemove));
    ASSERT_EQ(2, s.length());
}

TEST(StringTests, CanRemoveAllOccurrencesOfGivenChar) {
    String s1, s2;
    s2 = s1 = "tests";
    ASSERT_EQ(String("tet"), s1.remove('s'));
    ASSERT_EQ(3, s1.size());
    ASSERT_EQ(String("ess"), s2.remove('t'));
    ASSERT_EQ(3, s2.size());
}

TEST(StringTests, ReturnsUnmodifiedStringWhenTryingToRemoveNonExistentChars) {
    String s = "tests";
    String unmodified = s;
    ASSERT_EQ(unmodified, s.remove('q'));
}

TEST(StringTests, CanRemoveAllOccurrencesOfGivenString) {
    String s1, s2, s3;
    s3 = s2 = s1 = "the catcher in the rye";
    ASSERT_EQ(String("the catcher in the "), s1.remove("rye"));
    ASSERT_EQ(String("the catcher in the"), s2.remove(" rye"));
    ASSERT_EQ(String("catcher in rye"), s3.remove("the "));
}

TEST(StringTests, ReturnsUnmodifiedStringWhenTryingToRemoveNonExistentString) {
    String s = "the catcher in the rye";
    String unmodified = s;
    ASSERT_EQ(unmodified, s.remove("prism"));
}

TEST(StringTests, ReturnsCopyOfStringRepeatedNumTimes) {
    String s = "prism";
    const int repeatTimes = 3;
    ASSERT_EQ(String("prismprismprism"), s.repeated(repeatTimes));
    ASSERT_EQ(String("prism"), s);
}

TEST(StringTests, ReturnsCopyOfStringConvertedToUppercase) {
    String s, unmodified;
    unmodified = s = "prism";
    ASSERT_EQ(String("PRISM"), s.toUpper());
    ASSERT_EQ(unmodified, s);
}

TEST(StringTests, ReturnsCopyOfAlphaNumericStringConvertedToUppercase) {
    String s = "123 Cherry Tree Lane, wf3";
    ASSERT_EQ(String("123 CHERRY TREE LANE, WF3"), s.toUpper());
}

TEST(StringTests, ReturnsCopyOfStringConvertedToLowercase) {
    String s, unmodified;
    unmodified = s = "PRISM";
    ASSERT_EQ(String("prism"), s.toLower());
    ASSERT_EQ(unmodified, s);
}

TEST(StringTests, ReturnsCopyOfAlphaNumericStringConvertedToLowercase) {
    String s = "123 CHERRY TREE LANE, WF3";
    ASSERT_EQ(String("123 cherry tree lane, wf3"), s.toLower());
}

TEST(StringTests, CanChopOffLastPortionOfString) {
    String s = "123 Cherry Tree Lane, London";
    const int numCharsToChopOff = 8;
    s.chop(numCharsToChopOff);
    ASSERT_EQ(String("123 Cherry Tree Lane"), s);
}

TEST(StringTests, CapacityRemainsUnchangedAfterChoppingOffEndOfString) {
    String s = "123 Cherry Tree Lane, London";
    const int expectedCapacity = s.capacity();
    const int numCharsToChopOff = 8;
    s.chop(numCharsToChopOff);
    ASSERT_EQ(expectedCapacity, s.capacity());
}

TEST(StringTests, ReplacesCharWithNewChar) {
    String s = "plate";
    const int index = 0;
    ASSERT_EQ(String("slate"), s.replace(index, 's'));
    ASSERT_EQ(String("state"), s.replace(s.cbegin() + 1, 't'));
}

TEST(StringTests, ReplacesMultipleCharsWithNewChar) {
    String s = "1234 5678 1234 5678";
    const int index = 0;
    const int count = 4;
    ASSERT_EQ(String("**** 5678 1234 5678"), s.replace(index, '*', count));
    ASSERT_EQ(String("==== 5678 1234 5678"), s.replace(s.cbegin(), '=', count));
}

TEST(StringTests, ReplacesAllOccurrencesOfOldCharWithNewChar) {
    String s = "I see seashells on the seashore";
    const char oldc = 's';
    const char newc = '_';
    const char nonexistentchar = 'Q';
    ASSERT_EQ(String("I _ee _ea_hell_ on the _ea_hore"), String(s).replace(oldc, newc));
    ASSERT_EQ(String("I see seashells on the seashore"), String(s).replace(nonexistentchar, newc));
    ASSERT_EQ(s, String(s).replace(oldc, oldc));
}

TEST(StringTests, ReplacesSubstringWithIdenticalLengthSubstring) {
    String s = "The object of the superior man is truth";
    String toReplace = "truth";
    String replaceWith = "peace";
    s = s.replace(toReplace, replaceWith);
    ASSERT_EQ(String("The object of the superior man is peace"), s);
}

TEST(StringTests, ReplacesSubstringWithShorterSubstring) {
    String s = "The object of the superior man is truth";
    String toReplace = "truth";
    String replaceWith = "love";
    String expectedString = "The object of the superior man is love";
    const int expectedLength = expectedString.length();
    s = s.replace(toReplace, replaceWith);
    ASSERT_EQ(expectedString, s);
    ASSERT_EQ(expectedLength, s.length());
}

TEST(StringTests, ReplacesSubstringWithLongerSubstring) {
    String s = "The object of the superior man is truth";
    String toReplace = "truth";
    String replaceWith = "humility";
    String expectedString = "The object of the superior man is humility";
    const int expectedLength = expectedString.length();
    s = s.replace(toReplace, replaceWith);
    ASSERT_EQ(expectedString, s);
    ASSERT_EQ(expectedLength, s.length());
}

// TEST(StringTests, ReplacesAllMatchingSubstringsWithNewSubstring) {
//     String s = "Wherever you go, go with all your heart";
//     String expected = "However you roam, roam with all your heart";
//     s = s.replace(String("Wherever"), String("However"));
//     ASSERT_EQ(expected, s);
// }
//
// TEST(DISABLED_StringTests, CapacityIncreasesWhenReplacingSubstringWithLargerSubstring) {
//     String s = "Silence is a true friend who never betrays";
//     const int currentCapacity = s.capacity();
//     String expected = "Quietness is a true friend who never betrays";
//     s = s.replace("Silence", "Quietness");
//     ASSERT_EQ(expected, s);
//     ASSERT_GT(s.capacity(), currentCapacity);
// }

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
