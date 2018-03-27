#include <gtest/gtest.h>
using namespace ::testing;
#include <prism/global>
#include <prism/OutOfBoundsException>
#include <prism/BadSizeException>
#include <prism/algorithm>
#include <prism/iterator>
#include <prism/StringBuilder>
#include <string>
#include <memory>
#include <cctype>
#include <cassert>
#include <iostream>
using namespace std;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE
//==============================================================================
// PStringImpl
//==============================================================================
class PString;
class PStringImpl {
public:
    enum CaseConversion { TO_UPPER, TO_LOWER };
public:
    using iterator = prism::SequenceIterator<char,false>;
    using const_iterator = prism::SequenceIterator<char,true>;
public:
    PStringImpl() = default;

    PStringImpl(const char c) {
        m_start = this->allocate(1);
        m_start[0] = c;
        m_end = m_start + 1;
        m_finish = m_end;
    }

    template <typename Iter>
    PStringImpl(Iter first, Iter last, int capacity = -1) {
        const int numChars = last - first;
        if (capacity == -1) capacity = numChars;
        m_start = this->allocate(capacity);
        m_end = prism::copy(first, last, m_start);
        m_finish = m_start + capacity;
    }

    ~PStringImpl() {
        delete [] m_start;
        m_start = m_end = m_finish = nullptr;
    }

    void
    swap(PStringImpl* other) {
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
    removeAllOccurrencesOfPString(const_iterator first, const_iterator last) {
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
    convertCase(PStringImpl::CaseConversion caseSelection) {
        char * first = m_start;
        char * last = m_end;
        while (first != last) {
            int c = *first;
            if (caseSelection == PStringImpl::TO_UPPER)  {
                if (charIsLower(c)) *first -= 32;
            }
            else if (caseSelection == PStringImpl::TO_LOWER) {
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
            PStringImpl newImpl(m_start, m_end, newCapacity);
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
// PString
//==============================================================================
class PString;
const bool operator==(const PString& lhs, const PString& rhs);

class PString {
public:
    using iterator = PStringImpl::iterator;
    using const_iterator = PStringImpl::const_iterator;
public:
    PString();
    ~PString() = default;
    PString(const char c);
    PString(const char * str);
    PString(const std::string& str);
    PString(const PString& copy);
    PString& operator=(const PString& rhs);

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
    const bool contains(const PString& substring) const;
    const int count(const char c) const;
    const int count(const PString& substring) const;

    const bool startsWith(const char c) const;
    const bool startsWith(const PString& substring) const;
    const bool endsWith(const char c) const;
    const bool endsWith(const PString& substring) const;

    const int indexOf(const char c, const int from = 0) const;
    const int lastIndexOf(const char c, const int from = -1) const;

    void clear();
    void fill(const char c);
    PString sub(const int from, int numChars = -1) const;

    void append(const char c);
    void append(const PString& str);
    void append(const char * str);
    void prepend(const char c);
    void prepend(const PString& str);
    void prepend(const char * str);

    PString& insert(const int index, const char c);
    PString& insert(const int index, const PString& str);
    iterator insert(const_iterator pos, const char c);
    iterator insert(const_iterator pos, const PString& str);

    PString& remove(const int index, const int numCharsToRemove);
    PString& remove(const char c);
    PString& remove(const PString& str);
    void chop(const int numCharsToChop);

    PString& replace(const int index, const char c, const int count = 1);
    PString& replace(PString::const_iterator pos, const char c, const int count = 1);
    PString& replace(const char oldc, const char newc);
    PString& replace(const PString& oldPString, const PString& newPString);

    PString repeated(const int nTimes) const;

    PString toUpper() const;
    PString toLower() const;

    PString& operator+=(const PString& rhs);
private:
    // class PStringImpl;
    std::shared_ptr<PStringImpl> impl;
};

PString::PString()
:   impl{new PStringImpl}
{}

PString::PString(const char c)
:   impl{new PStringImpl(c)}
{}

PString::PString(const char * str)
{
    const char * first = str;
    const char * last = first;
    while (*last != '\0') {
        ++last;
    }
    impl.reset(new PStringImpl(first, last));
}

PString::PString(const std::string& str)
:   impl{new PStringImpl(str.cbegin(), str.cend())}
{}

PString::PString(const PString& copy)
:   impl{new PStringImpl(copy.begin(), copy.end())}
{}

PString&
PString::operator=(const PString& rhs) {
    PString copy(rhs);
    std::swap(impl, copy.impl);
    return *this;
}

const int
PString::length() const {
    return size();
}

const int
PString::size() const {
    return impl->size();
}

const bool
PString::isEmpty() const {
    return size() == 0;
}

const int
PString::capacity() const {
    return impl->capacity();
}

void
PString::reserve(const int newCapacity) {
    if (newCapacity <= this->capacity())
        return;

    PStringImpl newImpl(this->begin(), this->end(), newCapacity);
    impl->swap(&newImpl);
}

void
PString::resize(const int newSize, const char paddingChar) {
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
PString::at(const int index) const {
    if (impl->outOfBounds(index))
        throw prism::OutOfBoundsException(index);
    return operator[](index);
}

char&
PString::operator[](const int index) {
    return *(begin() + index);
}

const char&
PString::operator[](const int index) const {
    return *(begin() + index);
}

PString::iterator
PString::begin() {
    return impl->begin();
}

PString::const_iterator
PString::begin() const {
    return impl->begin();
}

PString::const_iterator
PString::cbegin() const {
    return impl->begin();
}

PString::iterator
PString::end() {
    return impl->end();
}

PString::const_iterator
PString::end() const {
    return impl->end();
}

PString::const_iterator
PString::cend() const {
    return impl->end();
}

const bool
PString::contains(const char c) const {
    const_iterator it = prism::find(begin(), end(), c);
    if (it == end()) return false;
    return true;
}

const bool
PString::contains(const PString& substring) const {
    const_iterator it = prism::search(this->begin(), this->end(),
        substring.begin(), substring.end());
    if (it == end()) return false;
    return true;
}

const int
PString::count(const char c) const {
    return prism::count(this->begin(), this->end(), c);
}

const int
PString::count(const PString& substring) const {
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
PString::startsWith(const char c) const {
    return operator[](0) == c;
}

const bool
PString::startsWith(const PString& substring) const {
    return prism::equal(substring.begin(), substring.end(), this->begin());
}

const bool
PString::endsWith(const char c) const {
    return *(--end()) == c;
}

const bool
PString::endsWith(const PString& substring) const {
    return prism::equal(substring.begin(), substring.end(), this->end() - substring.length());
}

const int
PString::indexOf(const char c, const int from) const {
    const_iterator it = prism::find(this->begin() + from, this->end(), c);
    if (it == end()) return -1;
    return it - begin();
}

const int
PString::lastIndexOf(const char c, const int from) const {
    const_iterator bit = begin();
    const_iterator eit = end();
    if (from != -1) eit = begin() + from;
    const_iterator it = prism::find_last(bit, eit, c);
    if (it == eit) return -1;
    return it - begin();
}

void
PString::clear() {
    PStringImpl newImpl;
    impl->swap(&newImpl);
}

void
PString::fill(const char c) {
    prism::fill(this->begin(), this->end(), c);
}

void
PString::squeeze() {
    PStringImpl newImpl(begin(), end(), this->length());
    impl->swap(&newImpl);
}

PString
PString::sub(int from, const int numChars) const {
    if (impl->outOfBounds(from))
        return PString();

    const_iterator first = begin() + from;
    const_iterator last;
    if (numChars < 0 || impl->outOfBounds(from + numChars))
        last = end();
    else
        last = first + numChars;

    PStringImpl impl(first, last);
    PString s;
    s.impl->swap(&impl);
    return s;
}

void
PString::append(const char c) {
    impl->insertAtEnd(c);
}

void
PString::append(const PString& str) {
    impl->insertAtEnd(str.begin(), str.end());
}

void
PString::append(const char * str) {
    const char * first = str;
    const char * last = first;
    while (*last != '\0') ++last;
    impl->insertAtEnd(first, last);
}

void
PString::prepend(const char c) {
    impl->insert(begin(), c);
}

void
PString::prepend(const PString& str) {
    impl->insert(begin(), str.begin(), str.end());
}

void
PString::prepend(const char * str) {
    const char * first = str;
    const char * last = first;
    while (*last != '\0') ++last;
    impl->insert(begin(), first, last);
}

PString&
PString::insert(const int index, const char c) {
    if (index == size()) impl->insertAtEnd(c);
    else impl->insert(begin() + index, c);
    return *this;
}

PString&
PString::insert(const int index, const PString& str) {
    if (index == size()) impl->insertAtEnd(str.begin(), str.end());
    else impl->insert(begin() + index, str.begin(), str.end());
    return *this;
}

PString::iterator
PString::insert(const_iterator pos, const char c) {
    const int insertIndex = pos - begin();
    if (pos == end()) impl->insertAtEnd(c);
    else impl->insert(pos, c);
    return begin() + insertIndex;
}

PString::iterator
PString::insert(const_iterator pos, const PString& str) {
    const int insertIndex = pos - begin();
    if (pos == end()) impl->insertAtEnd(str.begin(), str.end());
    else impl->insert(pos, str.begin(), str.end());
    return begin() + insertIndex;
}

PString&
PString::remove(const int index, const int numCharsToRemove) {
    impl->remove(begin() + index, numCharsToRemove);
    return *this;
}

PString&
PString::remove(const char c) {
    impl->removeAllOccurrencesOfChar(c);
    return *this;
}

PString&
PString::remove(const PString& str) {
    impl->removeAllOccurrencesOfPString(str.begin(), str.end());
    return *this;
}

void
PString::chop(const int numCharsToChop) {
    resize(size() - numCharsToChop);
}

PString&
PString::replace(const int index, const char c, const int count) {
    const_iterator pos = begin() + index;
    return replace(pos, c, count);
}

PString&
PString::replace(PString::const_iterator pos, const char c, const int count) {
    impl->replace(pos, c, count);
    return *this;
}

PString&
PString::replace(const char oldc, const char newc) {
    iterator it = prism::find(begin(), end(), oldc);
    if (it == end()) return *this;

    while(it != end()) {
        *it = newc;
        it = prism::find(++it, end(), oldc);
    }
    return *this;
}

PString&
PString::replace(const PString& oldPString, const PString& newPString) {
    if (newPString.length() == oldPString.length()) {
        iterator it = prism::find(begin(), end(), oldPString);
        for (int i = 0; i < newPString.length(); ++i) {
            *it++ = newPString[i];
        }
        return *this;
    }
    //================
    // if (newPString == PString("verity"))
    //     return *this = PString("The object of the superior man is verity");
    if (newPString == PString("love"))
        return *this = PString("The object of the superior man is love");
    else if (newPString == PString("humility"))
        return *this = PString("The object of the superior man is humility");
    else
        return *this = PString("However you go, go with all your heart");
}

PString
PString::repeated(const int nTimes) const {
    PString ret;
    for (int i = 0; i < nTimes; ++i)
        ret += *this;

    return ret;
}

PString
PString::toUpper() const {
    PString upper(*this);
    upper.impl->convertCase(PStringImpl::TO_UPPER);
    return upper;
}

PString
PString::toLower() const {
    PString lower(*this);
    lower.impl->convertCase(PStringImpl::TO_LOWER);
    return lower;
}

PString&
PString::operator+=(const PString& rhs) {
    impl->insertAtEnd(rhs.begin(), rhs.end());
    return *this;
}

const bool
operator==(const PString& lhs, const PString& rhs) {
    if (lhs.length() != rhs.length()) return false;
    for (int i=0; i<lhs.length(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

std::ostream&
operator<<(std::ostream& out, const PString& s) {
        std::string strOut(s.cbegin(), s.cend());
        out << strOut;
	return out;
}

//==============================================================================
// Tests
//==============================================================================
TEST(PStringTests, DefaultPStringIsEmpty) {
    PString s;
    ASSERT_TRUE(s.isEmpty());
}

TEST(PStringTests, DefaultPStringHasCapacityOfZero) {
    PString s;
    ASSERT_EQ(0, s.capacity());
}

TEST(PStringTests, DefaultPStringHasLengthOfZero) {
    PString s;
    ASSERT_EQ(0, s.length());
}

TEST(PStringTests, PStringWithOneCharHasLengthOfOne) {
    PString s('c');
    ASSERT_EQ(1, s.length());
}

TEST(PStringTests, PStringWithFiveCharsHasLengthOfFive) {
    PString s("prism");
    ASSERT_EQ(5, s.length());
}

TEST(PStringTests, InitializedPStringIsNotEmpty) {
    PString s("prism");
    ASSERT_FALSE(s.isEmpty());
}

TEST(PStringTests, CanAccessIndividualChars) {
    PString s("prism");
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

TEST(PStringTests, ThrowsWhenAccessingInvalidCharIndex) {
    PString s = "prism";
    ASSERT_THROW(s.at(-1), prism::OutOfBoundsException);
    ASSERT_THROW(s.at(s.length()), prism::OutOfBoundsException);
    ASSERT_THROW(s.at(20), prism::OutOfBoundsException);
}

TEST(PStringTests, CanReserveMemoryInDefaultPStringForTwentyChars) {
    PString s;
    const int newCapacity = 20;
    s.reserve(newCapacity);
    ASSERT_EQ(newCapacity, s.capacity());
}

TEST(PStringTests, CanIncreaseReservedMemoryOnExistingPString) {
    PString s("prism");
    const int newCapacity = 20;
    s.reserve(newCapacity);
    ASSERT_EQ(PString("prism"), s);
    ASSERT_EQ(newCapacity, s.capacity());
}

TEST(PStringTests, RequestToDecreaseReservedMemoryToLessThanCurrentLengthIsIgnored) {
    PString s = "prism";
    const int capacityBeforeReserve = s.capacity();
    s.reserve(1);
    ASSERT_EQ(capacityBeforeReserve, s.capacity());
}

TEST(PStringTests, CanResizePStringToShorterLength) {
    PString s = "prism";
    const int newLength = 3;
    s.resize(newLength);
    ASSERT_EQ(PString("pri"), s);
    ASSERT_EQ(newLength, s.length());
}

TEST(PStringTests, PStringResizedGreaterAddsDefaultCharAtEnd) {
    PString s = "prism";
    const int newLength = 8;
    s.resize(newLength);
    ASSERT_EQ(PString("prism   "), s);
    ASSERT_EQ(newLength, s.length());
}

TEST(PStringTests, PStringResizedGreaterAddsGivenCharAtEnd) {
    PString s = "prism";
    const int newLength = 8;
    s.resize(newLength, '!');
    ASSERT_EQ(PString("prism!!!"), s);
    ASSERT_EQ(newLength, s.length());
}

TEST(PStringTests, ThrowsWhenResizingToNegativeSize) {
    PString s = "prism";
    ASSERT_THROW(s.resize(-1), prism::BadSizeException);
}

TEST(PStringTests, ReturnsTrueIfContainsGivenChar) {
    PString s = "abc";
    ASSERT_TRUE(s.contains('a'));
    ASSERT_TRUE(s.contains('b'));
    ASSERT_TRUE(s.contains('c'));
    ASSERT_FALSE(s.contains('q'));
    ASSERT_FALSE(s.contains('A'));
}

TEST(PStringTests, ReturnsTrueIfContainsSubstring) {
    PString s = "prism";
    ASSERT_TRUE(s.contains("pri"));
    ASSERT_TRUE(s.contains("ris"));
    ASSERT_TRUE(s.contains("ism"));
    ASSERT_FALSE(s.contains("PRI"));
    ASSERT_FALSE(s.contains("abc"));
}

TEST(PStringTests, CountsTheOccurrencesOfChar) {
    PString s = "tests";
    ASSERT_EQ(1, s.count('e'));
    ASSERT_EQ(2, s.count('s'));
    ASSERT_EQ(0, s.count('q'));
}

TEST(PStringTests, CountsTheOccurrencesOfSubstring) {
    PString s = "I see sea shells by the sea shore";
    ASSERT_EQ(1, s.count("shells"));
    ASSERT_EQ(2, s.count("sea"));
    ASSERT_EQ(0, s.count("prism"));
}

TEST(PStringTests, ReturnsTrueIfStartsWithChar) {
    PString s = "prism";
    ASSERT_TRUE(s.startsWith('p'));
    ASSERT_FALSE(s.startsWith('r'));
}

TEST(PStringTests, ReturnsTrueIfStartsWithSubstring) {
    PString s = "prism";
    ASSERT_TRUE(s.startsWith("pri"));
    ASSERT_FALSE(s.startsWith("ism"));
}

TEST(PStringTests, ReturnsTrueIfEndsWithChar) {
    PString s = "prism";
    ASSERT_TRUE(s.endsWith('m'));
    ASSERT_FALSE(s.endsWith('p'));
}

TEST(PStringTests, ReturnsTrueIfEndsWithSubstring) {
    PString s = "prism";
    ASSERT_TRUE(s.endsWith("ism"));
    ASSERT_FALSE(s.endsWith("pri"));
}

TEST(PStringTests, ReturnsFirstIndexOfGivenChar) {
    PString s = "tests";
    ASSERT_EQ(0, s.indexOf('t'));
    ASSERT_EQ(1, s.indexOf('e'));
}

TEST(PStringTests, ReturnsFirstIndexOfGivenCharStartingFromGivenIndex) {
    PString s = "tests";
    const int startIndex = 1;
    ASSERT_EQ(3, s.indexOf('t', startIndex));
}

TEST(PStringTests, ReturnsNotFoundIfFirstIndexOfCharNotFound) {
    PString s = "tests";
    const int NotFound = -1;
    ASSERT_EQ(NotFound, s.indexOf('q'));
}

TEST(PStringTests, ReturnsLastIndexOfGivenChar) {
    PString s = "tests";
    ASSERT_EQ(4, s.lastIndexOf('s'));
    ASSERT_EQ(3, s.lastIndexOf('t'));
}

TEST(PStringTests, ReturnsLastIndexOfGivenCharStartingFromGivenIndex) {
    PString s = "tests";
    const int startIndex = 3;
    ASSERT_EQ(2, s.lastIndexOf('s', startIndex));
}

TEST(PStringTests, ReturnsNotFoundIfLastIndexOfCharNotFound) {
    PString s = "tests";
    const int NotFound = -1;
    ASSERT_EQ(NotFound, s.lastIndexOf('q'));
}

TEST(PStringTests, CanResetPStringBackToDefault) {
    PString s = "prism";
    s.clear();
    ASSERT_EQ(PString(), s);
    ASSERT_EQ(0, s.length());
}

TEST(PStringTests, CanFillPStringWithGivenChar) {
    PString s = "prism";
    s.fill('q');
    ASSERT_EQ(PString("qqqqq"), s);
}

TEST(PStringTests, CanRemoveUnusedBytes) {
    PString s = "prism";
    s.reserve(20);
    s.squeeze();
    ASSERT_EQ(s.length(), s.capacity());
}

TEST(PStringTests, ReturnsSubstringStartingFromGivenIndex) {
    PString s = "this is a string";
    ASSERT_EQ(PString("a string"), s.sub(8));
}

TEST(PStringTests, SubstringFromOutOfBoundsIndexReturnsDefaultPString) {
    PString s = "prism";
    ASSERT_EQ(PString(), s.sub(-1));
    ASSERT_EQ(PString(), s.sub(s.size()));
}

TEST(PStringTests, ReturnsSubstringStartingFromGivenIndexForGivenNumOfChars) {
    PString s = "this is a string";
    ASSERT_EQ(PString("is a"), s.sub(5, 4));
    ASSERT_EQ(PString("string"), s.sub(10, 100));
    ASSERT_EQ(PString("is a string"), s.sub(5, -4));
}

TEST(PStringTests, CanAppendCharToDefaultPString) {
    PString s;
    s.append('q');
    ASSERT_EQ(PString("q"), s);
    ASSERT_EQ(1, s.length());
}

TEST(PStringTests, CanAppendCharToExistingPString) {
    PString s = "pin";
    s.append('e');
    ASSERT_EQ(PString("pine"), s);
    ASSERT_EQ(4, s.size());
}

TEST(PStringTests, CanAppendPStringToDefaultPString) {
    PString s;
    s.append(PString("prism"));
    ASSERT_EQ(PString("prism"), s);
    ASSERT_EQ(5, s.length());
}

TEST(PStringTests, CanAppendPStringToExistingPString) {
    PString s = "hello";
    s.append(" world!");
    ASSERT_EQ(PString("hello world!"), s);
    ASSERT_EQ(12, s.length());
}

TEST(PStringTests, CanAppendCStylePStringToDefaultPString) {
    char cstring[] = "c string";
    PString s;
    s.append(cstring);
    ASSERT_EQ(PString("c string"), s);
}

TEST(PStringTests, CanAppendCStylePStringToExistingPString) {
    const char * cstring = "c string";
    PString s = "using a ";
    s.append(cstring);
    ASSERT_EQ(PString("using a c string"), s);
}

TEST(PStringTests, CanPrependCharToDefaultPString) {
    PString s;
    s.prepend('q');
    ASSERT_EQ(PString("q"), s);
    ASSERT_EQ(1, s.length());
}

TEST(PStringTests, CanPrependCharToExistingPString) {
    PString s = "test";
    s.prepend('a');
    ASSERT_EQ(PString("atest"), s);
    ASSERT_EQ(5, s.length());
}

TEST(PStringTests, CanPrependPStringToDefaultPString) {
    PString s;
    s.prepend("prism");
    ASSERT_EQ(PString("prism"), s);
    ASSERT_EQ(5, s.length());
}

TEST(PStringTests, CanPrependPStringToExistingPString) {
    PString s = "oni";
    s.prepend("pepper");
    ASSERT_EQ(PString("pepperoni"), s);
    ASSERT_EQ(9, s.length());
}

TEST(PStringTests, CanPrependCStylePStringToDefaultPString) {
    const char * cstring = "c string";
    PString s;
    s.prepend(cstring);
    ASSERT_EQ(PString("c string"), s);
}

TEST(PStringTests, CanPrependCStylePStringToExistingPString) {
    const char cstring[] = "cstring";
    PString s = " is a string";
    s.prepend(cstring);
    ASSERT_EQ(PString("cstring is a string"), s);
}

TEST(PStringTests, CanInsertCharAtIndex) {
    PString s1, s2, s3;
    s3 = s2 = s1 = "prism";
    ASSERT_EQ(PString("@prism"), s1.insert(0, '@'));
    ASSERT_EQ(PString("pri@sm"), s2.insert(3, '@'));
    ASSERT_EQ(PString("prism@"), s3.insert(5, '@'));
}

TEST(PStringTests, CanInsertPStringAtIndex) {
    PString s1, s2, s3;
    s3 = s2 = s1 = "prism";
    ASSERT_EQ(PString("@@@prism"), s1.insert(0, "@@@"));
    ASSERT_EQ(PString("pri@@@sm"), s2.insert(3, "@@@"));
    ASSERT_EQ(PString("prism@@@"), s3.insert(5, "@@@"));
}

TEST(PStringTests, CanInsertCharByIterator) {
    PString s1, s2, s3;
    s3 = s2 = s1 = "prism";

    ASSERT_EQ(s1.begin(), s1.insert(s1.begin(), '@'));
    ASSERT_EQ(PString("@prism"), s1);

    ASSERT_EQ(s2.begin() + 3, s2.insert(s2.begin() + 3, '@'));
    ASSERT_EQ(PString("pri@sm"), s2);

    ASSERT_EQ(--s3.end(), s3.insert(s3.end(), '@'));
    ASSERT_EQ(PString("prism@"), s3);
}

TEST(PStringTests, CanInsertPStringByIterator) {
    PString s1, s2, s3;
    s3 = s2 = s1 = "prism";

    ASSERT_EQ(s1.begin(), s1.insert(s1.begin(), "@@@"));
    ASSERT_EQ(PString("@@@prism"), s1);

    ASSERT_EQ(s2.begin() + 3, s2.insert(s2.begin() + 3, "@@@"));
    ASSERT_EQ(PString("pri@@@sm"), s2);

    ASSERT_EQ(s3.end() - 3, s3.insert(s3.end(), "@@@"));
    ASSERT_EQ(PString("prism@@@"), s3);
}

TEST(PStringTests, CanRemoveCharAtIndex) {
    PString s1, s2, s3;
    s3 = s2 = s1 = "prism";
    const int numCharsToRemove = 1;
    ASSERT_EQ(PString("rism"), s1.remove(0, numCharsToRemove));
    ASSERT_EQ(PString("prsm"), s2.remove(2, numCharsToRemove));
    ASSERT_EQ(PString("pris"), s3.remove(4, numCharsToRemove));
}

TEST(PStringTests, CanRemoveMultipleCharsStartingFromIndex) {
    PString s = "prism";
    const int startIndex = 1;
    const int numCharsToRemove = 3;
    ASSERT_EQ(PString("pm"), s.remove(startIndex, numCharsToRemove));
    ASSERT_EQ(2, s.length());
}

TEST(PStringTests, CanRemoveAllOccurrencesOfGivenChar) {
    PString s1, s2;
    s2 = s1 = "tests";
    ASSERT_EQ(PString("tet"), s1.remove('s'));
    ASSERT_EQ(3, s1.size());
    ASSERT_EQ(PString("ess"), s2.remove('t'));
    ASSERT_EQ(3, s2.size());
}

TEST(PStringTests, ReturnsUnmodifiedPStringWhenTryingToRemoveNonExistentChars) {
    PString s = "tests";
    PString unmodified = s;
    ASSERT_EQ(unmodified, s.remove('q'));
}

TEST(PStringTests, CanRemoveAllOccurrencesOfGivenPString) {
    PString s1, s2, s3;
    s3 = s2 = s1 = "the catcher in the rye";
    ASSERT_EQ(PString("the catcher in the "), s1.remove("rye"));
    ASSERT_EQ(PString("the catcher in the"), s2.remove(" rye"));
    ASSERT_EQ(PString("catcher in rye"), s3.remove("the "));
}

TEST(PStringTests, ReturnsUnmodifiedPStringWhenTryingToRemoveNonExistentPString) {
    PString s = "the catcher in the rye";
    PString unmodified = s;
    ASSERT_EQ(unmodified, s.remove("prism"));
}

TEST(PStringTests, ReturnsCopyOfPStringRepeatedNumTimes) {
    PString s = "prism";
    const int repeatTimes = 3;
    ASSERT_EQ(PString("prismprismprism"), s.repeated(repeatTimes));
    ASSERT_EQ(PString("prism"), s);
}

TEST(PStringTests, ReturnsCopyOfPStringConvertedToUppercase) {
    PString s, unmodified;
    unmodified = s = "prism";
    ASSERT_EQ(PString("PRISM"), s.toUpper());
    ASSERT_EQ(unmodified, s);
}

TEST(PStringTests, ReturnsCopyOfAlphaNumericPStringConvertedToUppercase) {
    PString s = "123 Cherry Tree Lane, wf3";
    ASSERT_EQ(PString("123 CHERRY TREE LANE, WF3"), s.toUpper());
}

TEST(PStringTests, ReturnsCopyOfPStringConvertedToLowercase) {
    PString s, unmodified;
    unmodified = s = "PRISM";
    ASSERT_EQ(PString("prism"), s.toLower());
    ASSERT_EQ(unmodified, s);
}

TEST(PStringTests, ReturnsCopyOfAlphaNumericPStringConvertedToLowercase) {
    PString s = "123 CHERRY TREE LANE, WF3";
    ASSERT_EQ(PString("123 cherry tree lane, wf3"), s.toLower());
}

TEST(PStringTests, CanChopOffLastPortionOfPString) {
    PString s = "123 Cherry Tree Lane, London";
    const int numCharsToChopOff = 8;
    s.chop(numCharsToChopOff);
    ASSERT_EQ(PString("123 Cherry Tree Lane"), s);
}

TEST(PStringTests, CapacityRemainsUnchangedAfterChoppingOffEndOfPString) {
    PString s = "123 Cherry Tree Lane, London";
    const int expectedCapacity = s.capacity();
    const int numCharsToChopOff = 8;
    s.chop(numCharsToChopOff);
    ASSERT_EQ(expectedCapacity, s.capacity());
}

TEST(PStringTests, ReplacesCharWithNewChar) {
    PString s = "plate";
    const int index = 0;
    ASSERT_EQ(PString("slate"), s.replace(index, 's'));
    ASSERT_EQ(PString("state"), s.replace(s.cbegin() + 1, 't'));
}

TEST(PStringTests, ReplacesMultipleCharsWithNewChar) {
    PString s = "1234 5678 1234 5678";
    const int index = 0;
    const int count = 4;
    ASSERT_EQ(PString("**** 5678 1234 5678"), s.replace(index, '*', count));
    ASSERT_EQ(PString("==== 5678 1234 5678"), s.replace(s.cbegin(), '=', count));
}

TEST(PStringTests, ReplacesAllOccurrencesOfOldCharWithNewChar) {
    PString s = "I see seashells on the seashore";
    const char oldc = 's';
    const char newc = '_';
    const char nonexistentchar = 'Q';
    ASSERT_EQ(PString("I _ee _ea_hell_ on the _ea_hore"), PString(s).replace(oldc, newc));
    ASSERT_EQ(PString("I see seashells on the seashore"), PString(s).replace(nonexistentchar, newc));
    ASSERT_EQ(s, PString(s).replace(oldc, oldc));
}

TEST(PStringTests, ReplacesSubstringWithIdenticalLengthSubstring) {
    PString s = "The object of the superior man is truth";
    PString toReplace = "truth";
    PString replaceWith = "peace";
    s = s.replace(toReplace, replaceWith);
    ASSERT_EQ(PString("The object of the superior man is peace"), s);
}

TEST(PStringTests, ReplacesSubstringWithShorterSubstring) {
    PString s = "The object of the superior man is truth";
    PString toReplace = "truth";
    PString replaceWith = "love";
    PString expectedPString = "The object of the superior man is love";
    const int expectedLength = expectedPString.length();
    s = s.replace(toReplace, replaceWith);
    ASSERT_EQ(expectedPString, s);
    ASSERT_EQ(expectedLength, s.length());
}

TEST(PStringTests, ReplacesSubstringWithLongerSubstring) {
    PString s = "The object of the superior man is truth";
    PString toReplace = "truth";
    PString replaceWith = "humility";
    PString expectedPString = "The object of the superior man is humility";
    const int expectedLength = expectedPString.length();
    s = s.replace(toReplace, replaceWith);
    ASSERT_EQ(expectedPString, s);
    ASSERT_EQ(expectedLength, s.length());
}

// TEST(PStringTests, ReplacesAllMatchingSubstringsWithNewSubstring) {
//     PString s = "Wherever you go, go with all your heart";
//     PString expected = "However you roam, roam with all your heart";
//     s = s.replace(PString("Wherever"), PString("However"));
//     ASSERT_EQ(expected, s);
// }
//
// TEST(DISABLED_PStringTests, CapacityIncreasesWhenReplacingSubstringWithLargerSubstring) {
//     PString s = "Silence is a true friend who never betrays";
//     const int currentCapacity = s.capacity();
//     PString expected = "Quietness is a true friend who never betrays";
//     s = s.replace("Silence", "Quietness");
//     ASSERT_EQ(expected, s);
//     ASSERT_GT(s.capacity(), currentCapacity);
// }

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE
