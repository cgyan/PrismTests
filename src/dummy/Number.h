/*
 * Number.h
 * v0.*
 *
 *  Created on: 5 Feb 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_NUMBER_H_
#define PRISM_NUMBER_H_

#include <prism/global>
#include <iostream>
using namespace std;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

//#define PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME

class Number {
private:
//	using int = int;
	int num;
public:
	Number()
	: num{} {}

	Number(const int& num)
	: num{num} {
#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "Number \n";
#endif
	}

	Number(const Number& rhs)
	: num{rhs.num}
	{
#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "Number(const Number& rhs) \n";
#endif
	}

	Number(Number&& rhs)
	: num(std::move(rhs.num))
	{
#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "Number(Number&&) \n";
#endif
	}

	~Number() {
#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "~Number() \n";
#endif
	}

	Number&
	operator=(const Number& rhs) {
		num = rhs.num;
		return *this;
	}

	Number&
	operator=(Number&& rhs) {
		num = std::move(rhs.num);
		return *this;
	}

	const bool
	operator==(const Number& rhs) const {
		return num == rhs.num;
	}

	const bool
	operator!=(const Number& rhs) const {
		return !(*this == rhs);
	}

	const int
	operator%(const Number& rhs) const {
		return num % rhs.num;
	}

	friend std::ostream&
	operator<<(std::ostream& out, const Number& n) {
		out << n.num;
		return out;
	}
};

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

#endif /* PRISM_NUMBER_H_ */












