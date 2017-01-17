/*
 * Iterators.cpp
 * v0.*
 *
 *  Created on: 8 Jan 2017
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/global>
#include <prism/PVector>
using namespace ::testing;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

class VectorIterators : public Test {
public:
	using iterator 					= prism::SequenceIterator<int, false>;
	using const_iterator 			= prism::SequenceIterator<int, true>;
	using reverse_iterator 			= prism::ReverseIterator<iterator>;
	using const_reverse_iterator 	= prism::ReverseIterator<const_iterator>;

	PVector<int> v;
	const PVector<int> cv;

	VectorIterators()
	: v({1,2,3,4,5}),
	  cv({6,7,8,9,10})
	{}
};

TEST_F(VectorIterators,
BeginIteratorsPointToFirstElement) {
	iterator nonConstIter(v.data());
	const_iterator constIter(cv.cdata());

	ASSERT_TRUE(iterator(v.data()) == v.begin());
	ASSERT_TRUE(const_iterator(v.data()) == v.cbegin());
	ASSERT_TRUE(const_iterator(cv.data()) == cv.begin());
}

TEST_F(VectorIterators,
EndIteratorsPointToPositionAfterLastElement) {
	ASSERT_TRUE(iterator(v.end()) == v.end());
	ASSERT_TRUE(const_iterator(v.end()) == v.end());
	ASSERT_TRUE(const_iterator(cv.end()) == cv.cend());
}

TEST_F(VectorIterators,
EndIteratorsEqualBeginIteratorsWhenEmpty) {
	PVector<int> emptyVec;

	ASSERT_TRUE(emptyVec.begin() == emptyVec.end());
	ASSERT_TRUE(emptyVec.cbegin() == emptyVec.cend());
	ASSERT_TRUE(emptyVec.rbegin() == emptyVec.rend());
	ASSERT_TRUE(emptyVec.crbegin() == emptyVec.crend());
}

TEST_F(VectorIterators,
ReverseBeginIteratorsPointToLastElement) {
	ASSERT_TRUE(reverse_iterator(v.end()) == v.rbegin());
	ASSERT_TRUE(const_reverse_iterator(cv.end()) == cv.rbegin());
	ASSERT_TRUE(const_reverse_iterator(cv.end()) == cv.crbegin());
}

TEST_F(VectorIterators,
ReverseEndIteratorsPointToFirstElement) {
	ASSERT_TRUE(reverse_iterator(v.begin()) == v.rend());
	ASSERT_TRUE(const_reverse_iterator(cv.begin()) == cv.rend());
	ASSERT_TRUE(const_reverse_iterator(cv.begin()) == cv.crend());
}

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE














