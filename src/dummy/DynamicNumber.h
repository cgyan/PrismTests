/*
 * Number.h
 * v0.*
 *
 *  Created on: 5 Feb 2017
 *      Author: iainhemstock
 */

/*
 	-fno-elide-constructors
 	By default the compiler is allowed to perform copy elision which optimizes away unnecessary
 	calls to constructors. To turn off this optimization use this flag in the g++ statement

	Foo f("Harley");	// calls Foo(name)
	Foo g(f);			// calls Foo ctor
	Foo h = f;			// calls Foo ctor

	// without optimization: calls Foo(name) then Foo move ctor
	// with optimizatio: only calls Foo(name)
	Foo i = Foo("Davidson");

	// without optimization: calls Foo(name) then Foo move ctor
	// with optimizatio: only calls Foo(name)
	Foo j(Foo("Davidson"));

	// without optimization: calls Foo(name) then Foo move ctor
	// with optimization: same
	Foo k(std::move(Foo("Davidson")));
 */

#ifndef PRISM_DYNAMIC_NUMBER_H_
#define PRISM_DYNAMIC_NUMBER_H_

#include <prism/h/global.h>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

//#define PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME

class DynamicNumber {
public:
	int * p;
public:
	~DynamicNumber() {
	#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "~DynamicNumber() \n";
	#endif
		delete p;
	}

	DynamicNumber()
	: p(new int(-1))
	{
	#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "DynamicNumber() \n";
	#endif
	}

	DynamicNumber(const int num)
	: p(new int(num))
	{
	#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "DynamicNumber(const int num) \n";
	#endif
	}

	DynamicNumber(const DynamicNumber& rhs)
	: p(new int(*rhs.p))
	{
	#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "DynamicNumber(const DynamicNumber& rhs) \n";
	#endif
	}

	DynamicNumber&
	operator=(const DynamicNumber& rhs) {
	#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "DynamicNumber::operator=(const DynamicNumber& rhs) \n";
	#endif
		if (this != &rhs) {
			delete p;
			p = new int(*rhs.p);
		}
		return *this;
	}

	DynamicNumber(DynamicNumber&& rhs) noexcept
	: p(rhs.p)
	{
	#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "DynamicNumber(DynamicNumber&& rhs) \n";
	#endif
		rhs.p = nullptr;
	}

	DynamicNumber&
	operator=(DynamicNumber&& rhs) noexcept {
	#ifdef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME
		cout << "DynamicNumber::operator(DynamicNumber&& rhs) \n";
	#endif
		if (this != &rhs) {
			delete p;
			p = rhs.p;
			rhs.p = nullptr;
		}
		return *this;
	}

	friend std::ostream&
	operator<<(std::ostream& out, const DynamicNumber & n) {
		out << *n.p;
		return out;
	}

	const bool
	operator==(const DynamicNumber& rhs) const {
		return *p == *rhs.p;
	}

	const bool
	operator!=(const DynamicNumber& rhs) const {
		return !(*this == rhs);
	}

	const int
	operator%(const int rhs) {
		return *p % rhs;
	}

	const bool
	operator<(const DynamicNumber& rhs) const {
		return *p < *rhs.p;
	}
};

#undef PRISM_SHOULD_OUTPUT_CONSTRUCTOR_NAME

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

#endif /* PRISM_DYNAMIC_NUMBER_H_ */












