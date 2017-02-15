/*
 * StringTest.cpp
 * v0.*
 *
 *  Created on: Jul 23, 2016
 *      Author: iainhemstock
 */


#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <prism/String>

namespace prism {
namespace test {

class StringTest : public ::testing::Test {

};

/**
 * Test: String()
 */
TEST_F(StringTest, constructorDefault) {
	String s;
	ASSERT_EQ(s, "");
	ASSERT_EQ(s.size(), 0);
}

/**
 * Test: String(c-string)
 */
TEST_F(StringTest, constructorCString) {
	const char cs[] = "test";
	String s(cs);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
}

/**
 * Test: String(stdString)
 */
TEST_F(StringTest, constructorStdString) {
	std::string ss = "test";
	String s(ss);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
}

/**
 * Test: String(char)
 */
TEST_F(StringTest, constructorChar) {
	char c = 'f';
	String s(c);
	ASSERT_EQ(s, c);
	ASSERT_EQ(s.size(), 1);
}

/**
 * Test: String(num, char)
 */
TEST_F(StringTest, constructorNumChars) {
	char c = '*';
	String s(5, c);
	ASSERT_EQ(s, "*****");
	ASSERT_EQ(s.size(), 5);
}

/**
 * Test: String(copy)
 */
TEST_F(StringTest, constructorCopy) {
	String first("test");
	String copy(first);
	ASSERT_EQ(copy, "test");
	ASSERT_EQ(copy.size(), 4);
}

/**
 * Test: append(string)
 */
TEST_F(StringTest, append_string) {

	// append to empty string
	String s;
	s = s.append("test");
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);

	// append to existing string
	s = s.append("ing");
	ASSERT_EQ(s, "testing");
	ASSERT_EQ(s.size(), 7);
}

/**
 * Test: append(char)
 */
TEST_F(StringTest, append_char) {

	// append to empty string
	String s;
	s = s.append('a');
	ASSERT_EQ(s, "a");
	ASSERT_EQ(s.size(), 1);

	// append to existing string
	s = s.append('b');
	ASSERT_EQ(s, "ab");
	ASSERT_EQ(s.size(), 2);
}

/**
 * Test: append(cstring)
 */
TEST_F(StringTest, append_cstring) {

	// append to empty string
	String s;
	const char * cstr1 = "test";
	s = s.append(cstr1);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);

	// append to existing string
	const char * cstr2 = "ing";
	s = s.append(cstr2);
	ASSERT_EQ(s, "testing");
	ASSERT_EQ(s.size(), 7);
}

/**
 * Test: at(index)
 */
TEST_F(StringTest, at) {
	String s = "test";
	ASSERT_EQ(s.at(0), 't');
	ASSERT_EQ(s.at(1), 'e');
	ASSERT_EQ(s.at(2), 's');
	ASSERT_EQ(s.at(3), 't');
}

/**
 * Test: capacity()
 */
TEST_F(StringTest, capacity) {

	// test capacity of empty string
	String s;
	ASSERT_EQ(s.capacity(), 0);

	// test capacity on empty string after reserve
	s.reserve(15);
	ASSERT_EQ(s.capacity(), 15);

	// test capacity on new string after initialisation
	// a new string after initialisation should have the same capacity as the size
	String s2("test");
	ASSERT_EQ(s2.capacity(), 4);

	// test capacity on existing string after appending
	// capacity should be double the size
	s2.append("ing");
	ASSERT_EQ(s2, "testing");
	ASSERT_EQ(s2.size(), 7);
	ASSERT_EQ(s2.capacity(), 14);

	// test capacity on existing string after removing characters
	// capacity should remain the same
	s2.remove(4, 3);
	ASSERT_EQ(s2, "test");
	ASSERT_EQ(s2.capacity(), 14);

	// test capacity on existing string after chop
	// capacity should remain the same
	s2.chop(1);
	ASSERT_EQ(s2, "tes");
	ASSERT_EQ(s2.capacity(), 14);

	// clear
}

/**
 * Test: chop(num)
 */
TEST_F(StringTest, chop) {
	String s("testing");
	s.chop(3);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
}

/**
 * Test: contains(string)
 */
TEST_F(StringTest, contains_string) {
	String s("montreal");
	ASSERT_TRUE(s.contains("mon"));
	ASSERT_TRUE(s.contains("tre"));
	ASSERT_TRUE(s.contains("eal"));
	ASSERT_FALSE(s.contains("123"));
}

/**
 * Test: contains(char)
 */
TEST_F(StringTest, contains_char) {
	String s("montreal");
	ASSERT_TRUE(s.contains('m'));
	ASSERT_TRUE(s.contains('r'));
	ASSERT_TRUE(s.contains('l'));
	ASSERT_FALSE(s.contains('&'));
}

/**
 * Test: count(char)
 */
TEST_F(StringTest, count_char) {
	String s("I see sea ships on the sea shore");
	ASSERT_EQ(s.count('s'), 6);
	ASSERT_EQ(s.count('e'), 6);
}

/**
 * Test: count(string)
 */
TEST_F(StringTest, count_string) {
	String s("banana and panama");
	ASSERT_EQ(s.count("an"), 4);
}

/**
 * Test: clear()
 */
TEST_F(StringTest, clear) {
	String s("test");
	s.clear();
	ASSERT_EQ(s, "");
	ASSERT_EQ(s.size(), 0);
	ASSERT_EQ(s.capacity(), 4);
}

/**
 * Test: endsWith(string)
 */
TEST_F(StringTest, endsWith_string) {
	String s("cala millor");
	ASSERT_TRUE(s.endsWith("millor"));
	ASSERT_TRUE(s.endsWith("lor"));
}

/**
 * Test: endsWith(char)
 */
TEST_F(StringTest, endsWith_char) {
	String s("cala millor");
	ASSERT_TRUE(s.endsWith('r'));
}

/**
 * Test: fill(char, size=-1)
 */
TEST_F(StringTest, fill) {

	// resize empty string to 5
	String s;
	s.resize(5);
	s = s.fill('*');
	ASSERT_EQ(s, "*****");
	ASSERT_EQ(s.size(), 5);

	// resize up to 8
	s = s.fill('%', 8);
	ASSERT_EQ(s, "%%%%%%%%"); // 8 chars of %
	ASSERT_EQ(s.size(), 8);

	// resize down to 3
	s = s.fill('v', 3);
	ASSERT_EQ(s, "vvv");
	ASSERT_EQ(s.size(), 3);
}

/**
 * Test: indexOf(string, from=0)
 */
TEST_F(StringTest, indexOf_string) {
	String s("Effective C++ and More Effective C++");
	//        0123456789012345678901234567890123456

	int index = s.indexOf("Effective");
	ASSERT_EQ(index, 0);

	index = s.indexOf("C++");
	ASSERT_EQ(index, 10);

	index = s.indexOf("More");
	ASSERT_EQ(index, 18);

	index = s.indexOf("Effective", 1);
	ASSERT_EQ(index, 23);

	index = s.indexOf("C++", 11);
	ASSERT_EQ(index, 33);
}

/**
 * Test: indexOf(char)
 */
TEST_F(StringTest, indexOf_char) {
	String s("Effective C++ and More Effective C++");
	//        0123456789012345678901234567890123456

	int index = s.indexOf('E');
	ASSERT_EQ(index, 0);

	index = s.indexOf('f');
	ASSERT_EQ(index, 1);

	index = s.indexOf('+');
	ASSERT_EQ(index, 11);

	index = s.indexOf('E', 1);
	ASSERT_EQ(index, 23);

	index = s.indexOf('f', 3);
	ASSERT_EQ(index, 24);

	index = s.indexOf('+', 13);
	ASSERT_EQ(index, 34);
}

/**
 * Test: insert(iterator, str)
 */
TEST_F(StringTest, insert_iterator_string) {

	// insert new string at start of empty string
	String s1;
	s1.insert(s1.begin(), "test");
	ASSERT_EQ(s1, "test");
	ASSERT_EQ(s1.size(), 4);

	// insert new string at end of empty string
	String s2;
	s2 = s2.insert(s2.end(), "test");
	ASSERT_EQ(s2, "test");
	ASSERT_EQ(s2.size(), 4);

	// insert new string at beginning of existing string
	s2 = s2.insert(s2.begin(), "begin_");
	ASSERT_EQ(s2, "begin_test");
	ASSERT_EQ(s2.size(), 10);

	// insert new string in middle of existing string
	s2 = s2.insert(s2.begin()+6, "google_");
	ASSERT_EQ(s2, "begin_google_test");
	ASSERT_EQ(s2.size(), 17);

	// insert new string at end of existing string
	s2 = s2.insert(s2.end(), "_end");
	ASSERT_EQ(s2, "begin_google_test_end");
	ASSERT_EQ(s2.size(), 21);
}

/**
 * Test: insert(iterator, char)
 */
TEST_F(StringTest, insert_iterator_char) {

	// insert new string at start of empty string
	String s1;
	s1.insert(s1.begin(), 'a');
	ASSERT_EQ(s1, "a");
	ASSERT_EQ(s1.size(), 1);

	// insert new string at end of empty string
	String s2;
	s2 = s2.insert(s2.end(), 'a');
	ASSERT_EQ(s2, "a");
	ASSERT_EQ(s2.size(), 1);

	// insert new string at beginning of existing string
	s2 = s2.insert(s2.begin(), 'b');
	ASSERT_EQ(s2, "ba");
	ASSERT_EQ(s2.size(), 2);

	// insert new string in middle of existing string
	s2 = s2.insert(s2.begin()+1, 'c');
	ASSERT_EQ(s2, "bca");
	ASSERT_EQ(s2.size(), 3);

	// insert new string at end of existing string
	s2 = s2.insert(s2.end(), 'd');
	ASSERT_EQ(s2, "bcad");
	ASSERT_EQ(s2.size(), 4);
}

/**
 * Test: insert(index, string)
 */
TEST_F(StringTest, insert_index_string) {

	// insert new string at start of empty string
	String s1;
	s1.insert(0, "test");
	ASSERT_EQ(s1, "test");
	ASSERT_EQ(s1.size(), 4);

	// insert new string at end of empty string
	String s2;
	s2 = s2.insert(s2.size(), "test");
	ASSERT_EQ(s2, "test");
	ASSERT_EQ(s2.size(), 4);

	// insert new string at beginning of existing string
	s2 = s2.insert(0, "begin_");
	ASSERT_EQ(s2, "begin_test");
	ASSERT_EQ(s2.size(), 10);

	// insert new string in middle of existing string
	s2 = s2.insert(6, "google_");
	ASSERT_EQ(s2, "begin_google_test");
	ASSERT_EQ(s2.size(), 17);

	// insert new string at end of existing string
	s2 = s2.insert(s2.size(), "_end");
	ASSERT_EQ(s2, "begin_google_test_end");
	ASSERT_EQ(s2.size(), 21);
}

/**
 * Test: insert(index, char)
 */
TEST_F(StringTest, insert_index_char) {

	// insert new char at start of empty string
	String s1;
	s1.insert(0, 'a');
	ASSERT_EQ(s1, "a");
	ASSERT_EQ(s1.size(), 1);

	// insert new char at end of empty string
	String s2;
	s2 = s2.insert(s2.size(), 'a');
	ASSERT_EQ(s2, "a");
	ASSERT_EQ(s2.size(), 1);

	// insert new char at beginning of existing string
	s2 = s2.insert(0, 'b');
	ASSERT_EQ(s2, "ba");
	ASSERT_EQ(s2.size(), 2);

	// insert new char in middle of existing string
	s2 = s2.insert(1, 'c');
	ASSERT_EQ(s2, "bca");
	ASSERT_EQ(s2.size(), 3);

	// insert new char at end of existing string
	s2 = s2.insert(s2.size(), 'd');
	ASSERT_EQ(s2, "bcad");
	ASSERT_EQ(s2.size(), 4);
}

/**
 * Test: length()
 */
TEST_F(StringTest, length) {
	String s;
	ASSERT_EQ(s.length(), 0);

	s.reserve(5);
	ASSERT_EQ(s.length(), 0);

	s.resize(10);
	ASSERT_EQ(s, "          "); // 10 spaces
	ASSERT_EQ(s.length(), 10);

	s.fill('u', 7);
	ASSERT_EQ(s, "uuuuuuu"); // 7 chars of u
	ASSERT_EQ(s.length(), 7);
}

/**
 * Test: prepend(string)
 */
TEST_F(StringTest, prepend_string) {

	// prepend to empty string
	String s;
	s = s.prepend("test");
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);

	// prepend to existing string
	s = s.prepend("google");
	ASSERT_EQ(s, "googletest");
	ASSERT_EQ(s.size(), 10);
}

/**
 * Test: prepend(char)
 */
TEST_F(StringTest, prepend_char) {

	// append to empty string
	String s;
	s = s.prepend('a');
	ASSERT_EQ(s, "a");
	ASSERT_EQ(s.size(), 1);

	// prepend to existing string
	s = s.prepend('b');
	ASSERT_EQ(s, "ba");
	ASSERT_EQ(s.size(), 2);
}

/**
 * Test: prepend(cstring)
 */
TEST_F(StringTest, prepend_cstring) {

	// append to empty string
	String s;
	const char * cstr1 = "test";
	s = s.prepend(cstr1);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);

	// prepend to existing string
	const char * cstr2 = "google";
	s = s.prepend(cstr2);
	ASSERT_EQ(s, "googletest");
	ASSERT_EQ(s.size(), 10);
}

/**
 * Test: push_back(string)
 */
TEST_F(StringTest, push_back_string) {

	// push_back to empty string
	String s;
	s.push_back("test");
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);

	// push_back to existing string
	s.push_back("ing");
	ASSERT_EQ(s, "testing");
	ASSERT_EQ(s.size(), 7);
}

/**
 * Test: push_back(char)
 */
TEST_F(StringTest, push_back_char) {

	// push_back to empty string
	String s;
	s.push_back('a');
	ASSERT_EQ(s, "a");
	ASSERT_EQ(s.size(), 1);

	// push_back to existing string
	s.push_back('b');
	ASSERT_EQ(s, "ab");
	ASSERT_EQ(s.size(), 2);
}

/**
 * Test: push_back(cstring)
 */
TEST_F(StringTest, push_back_cstring) {

	// append to empty string
	String s;
	const char * cstr1 = "test";
	s.push_back(cstr1);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);

	// push_back to existing string
	const char * cstr2 = "ing";
	s.push_back(cstr2);
	ASSERT_EQ(s, "testing");
	ASSERT_EQ(s.size(), 7);
}

/**
 * Test: push_front(string)
 */
TEST_F(StringTest, push_front_string) {

	// push_front to empty string
	String s;
	s.push_front("test");
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);

	// push_front to existing string
	s.push_front("google");
	ASSERT_EQ(s, "googletest");
	ASSERT_EQ(s.size(), 10);
}

/**
 * Test: prepend(char)
 */
TEST_F(StringTest, push_front_char) {

	// push_front to empty string
	String s;
	s.push_front('a');
	ASSERT_EQ(s, "a");
	ASSERT_EQ(s.size(), 1);

	// push_front to existing string
	s.push_front('b');
	ASSERT_EQ(s, "ba");
	ASSERT_EQ(s.size(), 2);
}

/**
 * Test: push_front(cstring)
 */
TEST_F(StringTest, push_front_cstring) {

	// push_front to empty string
	String s;
	const char * cstr1 = "test";
	s.push_front(cstr1);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);

	// push_front to existing string
	const char * cstr2 = "google";
	s.push_front(cstr2);
	ASSERT_EQ(s, "googletest");
	ASSERT_EQ(s.size(), 10);
}

/**
 * Test: remove(index, nCharsToRemove)
 */
TEST_F(StringTest, remove_index_numChars) {
	String s("montreal");
	s = s.remove(1, 4);
	ASSERT_EQ(s, "meal");
	ASSERT_EQ(s.size(), 4);
}

/**
 * Test: remove(string)
 */
TEST_F(StringTest, remove_string) {
	String s("montreal");
	s = s.remove("ontr");
	ASSERT_EQ(s, "meal");
	ASSERT_EQ(s.size(), 4);
}

/**
 * Test: remove(char)
 */
TEST_F(StringTest, remove_char) {
	String s("I see sea ships on the sea shore");
	s = s.remove('s');
	ASSERT_EQ(s, "I ee ea hip on the ea hore");
	ASSERT_EQ(s.size(), 26);
}

/**
 * Test: repeated(nTimes)
 */
TEST_F(StringTest, repeated) {
	String s("hola");
	s = s.repeated(3);
	ASSERT_EQ(s, "holaholahola");
	ASSERT_EQ(s.size(), 12);
}

/**
 * Test: replace (position, nCharsToReplace, newStr)
 */
TEST_F(StringTest, replace_pos_num_string) {
	String s("Cala Millor in Majorca!");
	s.replace(5, 6, "Bona");
	ASSERT_EQ(s, "Cala Bona in Majorca!");
}

/**
 * Test: replace (position, nCharsToReplace, char)
 */
TEST_F(StringTest, replace_pos_num_char) {
	String s("Cala Millor in Majorca!");
	s.replace(22, 1, '?'); // change ! to ?
	ASSERT_EQ(s, "Cala Millor in Majorca?");
}

/**
 * Test: replace (iterator, iterator, newStr)
 */
TEST_F(StringTest, replace_iterator_iterator_string) {
	String s("Cala Bona in Majorca!");
	s.replace(s.begin()+5, s.begin()+9, "Millor");
	ASSERT_EQ(s, "Cala Millor in Majorca!");
}

/**
 * Test: replace(oldString, newString)
 */
TEST_F(StringTest, replace_string_string) {
	String s("I see sea ships on the sea shore");
	s.replace("sea", "ocean");
	ASSERT_EQ(s, "I see ocean ships on the ocean shore");
}

/**
 * Test: replace(oldString, char)
 */
TEST_F(StringTest, replace_string_char) {
	String s("I see sea ships on the sea shore");
	s.replace("sea", '%');
	ASSERT_EQ(s, "I see % ships on the % shore");
}

/**
 * Test: replace(char, string)
 */
TEST_F(StringTest, replace_char_string) {
	String s("I see sea ships on the sea shore");
	s.replace('s', "[CENSORED]");
	ASSERT_EQ(s, "I [CENSORED]ee [CENSORED]ea [CENSORED]hip[CENSORED] on the [CENSORED]ea [CENSORED]hore");
}

/**
 * Test: replace(char, char)
 */
TEST_F(StringTest, replace_char_char) {
	String s("I see sea ships on the sea shore");
	s.replace('s', 'S');
	ASSERT_EQ(s, "I See Sea ShipS on the Sea Shore");
}

/**
 * Test: reserve(size)
 */
TEST_F(StringTest, reserveNewString) {
	String s;
	s.reserve(15);
	ASSERT_EQ(s, "");
	ASSERT_EQ(s.capacity(), 15);
	ASSERT_EQ(s.size(), 0);
}

/**
 * Test: reserve(size)
 */
TEST_F(StringTest, reserveMoreExistingString) {
	String s("test");
	s.reserve(8);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
	ASSERT_EQ(s.capacity(), 8);
}

/**
 * Test: reserve(size)
 * String::reserve() can only increase the capacity.
 * Any call to reserve() with a value less than the current capacity
 * should be ignored.
 */
TEST_F(StringTest, reserveLessExistingString) {
	String s("test");
	s.reserve(2);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
	ASSERT_EQ(s.capacity(), 4);
}

/**
 * Test: resize(size)
 * Calling String::resize(arg) on a new empty string should set both the
 * size and capacity to arg and init each character to a space.
 */
TEST_F(StringTest, resizeNewString) {
	String s;
	s.resize(5);
	ASSERT_EQ(s, "     "); // 5 single spaces
	ASSERT_EQ(s.size(), 5);
	ASSERT_EQ(s.capacity(), 5);
}

/**
 * Test: resize(size)
 * Calling String::resize(arg) on an existing string where arg is lower
 * than the current size those characters are removed but the capacity
 * remains unchanged.
 */
TEST_F(StringTest, resizeLowerExistingString) {
	String s("test");
	s.resize(2);
	ASSERT_EQ(s, "te");
	ASSERT_EQ(s.size(), 2);
	ASSERT_EQ(s.capacity(), 4);
}

/**
 * Test: resize(size)
 * Calling String::resize(arg) on an existing string where arg is greater
 * than the current size will increase the string's size to arg setting the
 * new characters to ' '. This test will force an increase of the capacity
 * from 4 to 8.
 */
TEST_F(StringTest, resizeGreaterExistingString) {
	String s("test");
	s.resize(8);
	ASSERT_EQ(s, "test    "); // "test" followed by four spaces
	ASSERT_EQ(s.size(), 8);
	ASSERT_EQ(s.capacity(), 8);
}

/**
 * Test: resize(size)
 * Calling String::resize(arg) on an existing string where arg is the same value
 * as the string's size will change nothing.
 */
TEST_F(StringTest, resizeToSameSizeExistingString) {
	String s("test");
	s.resize(4);
	ASSERT_EQ(s, "test");
	ASSERT_EQ(s.size(), 4);
	ASSERT_EQ(s.capacity(), 4);
}

/**
 * Test: setNum(int)
 */
TEST_F(StringTest, setNum_int) {
	int n = -123;
	String s;
	s.setNum(n);
	ASSERT_EQ(s, "-123");
	ASSERT_EQ(s.size(), 4);
}

/**
 * Test: setNum(unsigned int)
 */
TEST_F(StringTest, setNum_unsigned_int) {
	unsigned int n = 123;
	String s;
	s.setNum(n);
	ASSERT_EQ(s, "123");
	ASSERT_EQ(s.size(), 3);
}

/**
 * Test: setNum(long)
 */
TEST_F(StringTest, setNum_long) {
	long n = -123456;
	String s;
	s.setNum(n);
	ASSERT_EQ(s, "-123456");
	ASSERT_EQ(s.size(), 7);
}

/**
 * Test: setNum(unsigned long)
 */
TEST_F(StringTest, setNum_unsigned_long) {
	unsigned long n = 123456;
	String s;
	s.setNum(n);
	ASSERT_EQ(s, "123456");
	ASSERT_EQ(s.size(), 6);
}

/**
 * Test: setNum(float, precision)
 */
TEST_F(StringTest, setNum_float_precision) {
	float n = 3.14159;
	String s;
	s.setNum(n);
	ASSERT_EQ(s, "3.14159");
	ASSERT_EQ(s.size(), 7);

	s.setNum(n, 5);
	ASSERT_EQ(s, "3.1416");
}

/**
 * Test: setNum(double, precision)
 */
TEST_F(StringTest, setNum_double_precision) {
	double n = 3.14159;
	String s;
	s.setNum(n);
	ASSERT_EQ(s, "3.14159");
	ASSERT_EQ(s.size(), 7);

	s.setNum(n, 5);
	ASSERT_EQ(s, "3.1416");
}

/**
 * Test: simplified()
 */
TEST_F(StringTest, simplified) {
	String s("\n\t\t whitespace has\fbeen\vremoved!\n");
	s = s.simplified();
	ASSERT_EQ(s, "whitespace has been removed!");
}

/**
 * Test: size()
 */
TEST_F(StringTest, size) {
	String s;
	ASSERT_EQ(s.size(), 0);

	s.reserve(5);
	ASSERT_EQ(s.size(), 0);

	s.resize(10);
	ASSERT_EQ(s, "          "); // 10 spaces
	ASSERT_EQ(s.size(), 10);

	s.fill('u', 7);
	ASSERT_EQ(s, "uuuuuuu"); // 7 chars of u
	ASSERT_EQ(s.size(), 7);
}

/**
 * Test: squeeze()
 */
TEST_F(StringTest, squeeze) {

	// test empty string
	String s;
	s.squeeze();
	ASSERT_EQ(s.capacity(), 0);

	s.reserve(25);
	s = "bananas in pajamas";
	ASSERT_EQ(s.size(), 18);
	ASSERT_EQ(s.capacity(), 25);
	s.squeeze();
	ASSERT_EQ(s.capacity(), 18);
}

/**
 * Test: startsWith(string)
 */
TEST_F(StringTest, startsWith_string) {
	String s("Cala Millor in Majorca!");
	ASSERT_TRUE(s.startsWith("Cala"));
	ASSERT_FALSE(s.startsWith("Millor"));
}

/**
 * Test: startsWith(char)
 */
TEST_F(StringTest, startsWith_char) {
	String s("Cala Millor in Majorca!");
	ASSERT_TRUE(s.startsWith('C'));
	ASSERT_FALSE(s.startsWith('c'));
}

/**
 * Test: sub(startIndex, nChars)
 */
TEST_F(StringTest, sub_index_nChars) {
	String s("Cala Millor in Majorca!");

	// copy from index 0
	String sub = s.sub(0);
	ASSERT_EQ(sub, "Cala Millor in Majorca!");

	// copy from index 5
	sub = s.sub(5);
	ASSERT_EQ(sub, "Millor in Majorca!");

	// copy from index 5 for 6 chars
	sub = s.sub(5, 6);
	ASSERT_EQ(sub, "Millor");

	// copy from index 15 for 20 chars
	// this should clip nChars to the end of the string instead
	// of extending beyond it
	sub = s.sub(15, 20);
	ASSERT_EQ(sub, "Majorca!");
}

/**
 * Test: sub(beginIterator, endIterator)
 */
TEST_F(StringTest, sub_beginIterator_endIterator) {
	String s("bananas in pajamas");

	String sub = s.sub(s.begin(), s.end());
	ASSERT_EQ(sub, "bananas in pajamas");

	// substring of first word
	sub = s.sub(s.begin(), s.begin()+7);
	ASSERT_EQ(sub, "bananas");

	// substring of middle word
	sub = s.sub(s.begin()+8, s.begin()+10);
	ASSERT_EQ(sub, "in");

	// substring of last word
	sub = s.sub(s.begin()+11, s.end());
	ASSERT_EQ(sub, "pajamas");
}

/**
 * Test: toDouble()
 */
TEST_F(StringTest, toDouble) {
	double n = 3.14159;
	String s("3.14159");
	ASSERT_EQ(s.toDouble(), n);
}

/**
 * Test: toFloat()
 */
TEST_F(StringTest, toFloat) {
	float n = 3.14159;
	String s("3.14159");
	ASSERT_EQ(s.toFloat(), n);
}

/**
 * Test: toInt()
 */
TEST_F(StringTest, toInt) {
	int n = 1234;
	String s("1234");
	ASSERT_EQ(s.toInt(), n);
}

/**
 * Test: toLower()
 */
TEST_F(StringTest, toLower) {

	// test string with mixed lower and upper case
	String s("More Effective C++");
	ASSERT_EQ(s.toLower(), "more effective c++");

	// test string with all upper
	s = "MORE EFFECTIVE C++";
	ASSERT_EQ(s.toLower(), "more effective c++");

	// test string with all lower
	s = "more effective c++";
	ASSERT_EQ(s.toLower(), "more effective c++");
}

/**
 * Test: toStdString()
 */
TEST_F(StringTest, toStdString) {
	const char * cs = "More Effective C++";
	String s(cs);
	std::string ss = s.toStdString();
	ASSERT_STREQ(ss.c_str(), cs);
}

/**
 * Test: toUpper()
 */
TEST_F(StringTest, toUpper) {

	// test string with mixed lower and upper case
	String s("More Effective C++");
	ASSERT_EQ(s.toUpper(), "MORE EFFECTIVE C++");

	// test string with all lower
	s = "more effective c++";
	ASSERT_EQ(s.toUpper(), "MORE EFFECTIVE C++");

	// test string with all upper
	s = "MORE EFFECTIVE C++";
	ASSERT_EQ(s, "MORE EFFECTIVE C++");
}

/**
 * Test: trimmed()
 */
TEST_F(StringTest, trimmed) {
	String s("     in the summer     ");
	s = s.trimmed();
	ASSERT_EQ(s, "in the summer");
	ASSERT_EQ(s.size(), 13);
}

/**
 * Test: operator[]()
 */
TEST_F(StringTest, opBrackets) {
	String s("test");
	ASSERT_EQ(s[0], 't');
	ASSERT_EQ(s[1], 'e');
	ASSERT_EQ(s[2], 's');
	ASSERT_EQ(s[3], 't');

	s[0] = 'b';
	ASSERT_EQ(s[0], 'b');
}

/**
 * Test: const operator[]()
 */
TEST_F(StringTest, opBracketsConst) {
	const String s("test");
	ASSERT_EQ(s[0], 't');
	ASSERT_EQ(s[1], 'e');
	ASSERT_EQ(s[2], 's');
	ASSERT_EQ(s[3], 't');
}

/**
 * Test: operator=(string)
 */
TEST_F(StringTest, opAssignment_string) {
	String s("bananas in pajamas");

	// assign s to new string
	String s2 = s;
	ASSERT_EQ(s2, s);
	ASSERT_EQ(s2.size(), s.size());
	ASSERT_EQ(s2.capacity(), s.capacity());

	// assign s to existing string
	String s3("cat's pajamas");
	s3 = s;
	ASSERT_EQ(s3, s);
	ASSERT_EQ(s3.size(), s.size());
	ASSERT_EQ(s3.capacity(), s.capacity());
}

/**
 * Test: operator=(cstring)
 */
TEST_F(StringTest, opAssignment_cstring) {
	const char * cs = "bananas in pajamas";
	int csSize = 18;

	// assign cs to new string
	String s2 = cs;
	ASSERT_EQ(s2, cs);
	ASSERT_EQ(s2.size(), csSize);

	// assign cs to existing string
	String s3("cat's pajamas");
	s3 = cs;
	ASSERT_EQ(s3, cs);
	ASSERT_EQ(s3.size(), csSize);
}

/**
 * Test: operator=(char)
 */
TEST_F(StringTest, opAssignment_char) {
	char c = 'f';

	// assign c to new string
	String s2 = c;
	ASSERT_EQ(s2, "f");
	ASSERT_EQ(s2.size(), 1);

	// assign c to existing string
	String s3("cat's pajamas");
	s3 = c;
	ASSERT_EQ(s3, "f");
	ASSERT_EQ(s3.size(), 1);
}

/**
 * Test: operator+=(string)
 */
TEST_F(StringTest, opPlusEquals_string) {
	String s("test");

	// append s to new string
	String s2;
	s2 += s;
	ASSERT_EQ(s2, "test");
	ASSERT_EQ(s2.size(), 4);

	// append s to existing string
	String s3("google");
	s3 += s;
	ASSERT_EQ(s3, "googletest");
	ASSERT_EQ(s3.size(), 10);
}

/**
 * Test: operator+=(cstring)
 */
TEST_F(StringTest, opPlusEquals_cstring) {
	const char * s = "test";

	// append s to new string
	String s2;
	s2 += s;
	ASSERT_EQ(s2, "test");
	ASSERT_EQ(s2.size(), 4);

	// append s to existing string
	String s3("google");
	s3 += s;
	ASSERT_EQ(s3, "googletest");
	ASSERT_EQ(s3.size(), 10);
}

/**
 * Test: operator+=(char)
 */
TEST_F(StringTest, opPlusEquals_char) {
	char c = '?';

	// append c to new string
	String s2;
	s2 += c;
	ASSERT_EQ(s2, "?");
	ASSERT_EQ(s2.size(), 1);

	// append c to existing string
	String s3("google");
	s3 += c;
	ASSERT_EQ(s3, "google?");
	ASSERT_EQ(s3.size(), 7);
}
// ============================================================================================
// Static
// ============================================================================================
/**
 * Test:: fromCharArray(cstring)
 */
TEST_F(StringTest, fromCharArray) {
	const char * cs = "in the summertime";
	String s = String::fromCharArray(cs);

	ASSERT_EQ(s, cs);
	ASSERT_EQ(s.size(), 17);
}

/**
 * Test:: fromStdString(stdString)
 */
TEST_F(StringTest, fromStdString) {
	std::string ss = "in the summertime";
	String s = String::fromStdString(ss);

	ASSERT_EQ(s, ss);
	ASSERT_EQ(s.size(), ss.size());
}

/**
 * Test: number(int)
 */
TEST_F(StringTest, number_int) {
	int n = -123;
	String s = String::number(n);

	ASSERT_EQ(s, "-123");
	ASSERT_EQ(s.size(), 4);
}

/**
 * Test: number(unsigned int)
 */
TEST_F(StringTest, number_unsignedint) {
	unsigned int n = 123;
	String s = String::number(n);

	ASSERT_EQ(s, "123");
	ASSERT_EQ(s.size(), 3);
}

/**
 * Test: number(long)
 */
TEST_F(StringTest, number_long) {
	long n = -123;
	String s = String::number(n);

	ASSERT_EQ(s, "-123");
	ASSERT_EQ(s.size(), 4);
}

/**
 * Test: number(unsigned long)
 */
TEST_F(StringTest, number_unsignedlong) {
	unsigned long n = 123;
	String s = String::number(n);

	ASSERT_EQ(s, "123");
	ASSERT_EQ(s.size(), 3);
}

/**
 * Test: number(double)
 */
TEST_F(StringTest, number_double_precision) {
	double n = 3.14159;
	String s = String::number(n);

	ASSERT_EQ(s, "3.14159");
	ASSERT_EQ(s.size(), 7);

	s = String::number(n, 5);
	ASSERT_EQ(s, "3.1416");
	ASSERT_EQ(s.size(), 6);
}

/**
 * Test: number(float)
 */
TEST_F(StringTest, number_float_precision) {
	float n = 3.14159;
	String s = String::number(n);

	ASSERT_EQ(s, "3.14159");
	ASSERT_EQ(s.size(), 7);

	s = String::number(n, 5);
	ASSERT_EQ(s, "3.1416");
	ASSERT_EQ(s.size(), 6);
}
// ============================================================================================
// Related non-members
// ============================================================================================
/**
 * Test: operator==(string, string)
 */
TEST_F(StringTest, opEqualsEquals) {
	String s1 = "test";
	String s2 = "test";
	ASSERT_TRUE(s1 == s2);
	String s3 = "testing";
	ASSERT_FALSE(s1 == s3);
}

/**
 * Test: operator!=(string, string)
 */
TEST_F(StringTest, opNotEquals) {
	String s1 = "test";
	String s2 = "testing";
	ASSERT_TRUE(s1 != s2);
	String s3 = "test";
	ASSERT_FALSE(s1 != s3);
}

/**
 * Test: operator+(str1, str2)
 */
TEST_F(StringTest, opPlus_string_string) {
	String s = String("google") + String("test");
	ASSERT_EQ(s, "googletest");
	ASSERT_EQ(s.size(), 10);
}

/**
 * Test: operator+(string, cstring)
 */
TEST_F(StringTest, opPlus_string_cstring) {
	const char * cs = "test";
	String s = String("google") + cs;
	ASSERT_EQ(s, "googletest");
	ASSERT_EQ(s.size(), 10);
}

/**
 * Test: operator+(cstring, string)
 */
TEST_F(StringTest, opPlus_cstring_string) {
	const char * cs = "google";
	String s = cs + String("test");
	ASSERT_EQ(s, "googletest");
	ASSERT_EQ(s.size(), 10);
}

/**
 * Test: operator+(char, string)
 */
TEST_F(StringTest, opPlus_char_string) {
	char c = 'g';
	String s = c + String("oogle");
	ASSERT_EQ(s, "google");
	ASSERT_EQ(s.size(), 6);
}

/**
 * Test: operator+(string, char)
 */
TEST_F(StringTest, opPlus_string_char) {
	char c = 'e';
	String s = String("googl") + c;
	ASSERT_EQ(s, "google");
	ASSERT_EQ(s.size(), 6);
}

} // end namespace test
} // end namespace prism







