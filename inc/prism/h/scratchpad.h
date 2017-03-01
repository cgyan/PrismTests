/*
 * scratchpad.h
 * v0.*
 *
 *  Created on: 26 Feb 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_SCRATCHPAD_H_
#define PRISM_SCRATCHPAD_H_

#include <prism/global>
#include <prism/Allocator>
#include <prism/Iterator>
#include <prism/type_traits>
#include <ostream>

PRISM_BEGIN_NAMESPACE

template <typename T>
struct PListNode {
	T value{};
	PListNode* next{nullptr};
	PListNode* previous{nullptr};
};

template <typename T>
PListNode<T>*
make_node(const T& value) {
	PListNode<T>* node = new PListNode<T>;
	node->value = value;
	return node;
}

template <typename T, bool IsConst>
struct PListIterator {
	using value_type 			= T;
	using reference 			= typename prism::ConditionalType<IsConst, const T&, T&>::type;
	using pointer 				= typename prism::ConditionalType<IsConst, const T*, T*>::type;
	using difference_type 		= std::ptrdiff_t;
	using iterator_category 	= std::bidirectional_iterator_tag;
};

template <typename T, typename Allocator = prism::Allocator<T>>
class PList {
private:
	using vt_alloc_traits 			= prism::AllocatorTraits<Allocator>;
	using Node						= PListNode<T>;
	using NodePtr					= Node*;
public:
	using allocator_type 			= Allocator;
	using value_type 				= typename vt_alloc_traits::value_type;
	using reference 				= typename vt_alloc_traits::reference;
	using const_reference 			= typename vt_alloc_traits::const_reference;
	using pointer 					= typename vt_alloc_traits::pointer;
	using const_pointer 			= typename vt_alloc_traits::const_pointer;
	using difference_type 			= typename vt_alloc_traits::difference_type;
	using size_type 				= typename vt_alloc_traits::size_type;
	using iterator					= prism::PListIterator<T, false>;
	using const_iterator			= prism::PListIterator<T, true>;
	using reverse_iterator			= prism::ReverseIterator<iterator>;
	using const_reverse_iterator	= prism::ReverseIterator<const_iterator>;
public:
	PList()
	: _m_header{new Node},
	  _m_tailer{new Node}
	{
		_m_header->next = _m_tailer;
		_m_tailer->previous = _m_header;
	}

	~PList() {
		NodePtr currentNode = _m_header;
		while (currentNode != nullptr) {
			NodePtr thisNode = currentNode;
			NodePtr nextNode = thisNode->next;
			delete thisNode;
			currentNode = nextNode;
		}
	}

	const bool
	empty() const {
		return size() == 0;
	}

	const int
	size() const {
		NodePtr current = _m_header->next;
		int distance = 0;
		while (current != _m_tailer) {
			++distance;
			current = current->next;
		}
		return distance;
	}

	void
	resize(const int size) {
		for (int i=0; i<size; ++i) {
			NodePtr node = make_node(T{});
			node->next = _m_tailer;
			node->previous = _m_tailer->previous;
			node->previous->next = node;
			node->next->previous = node;
		}
	}

	T
	front() {
		return _m_header->next->value;
	}
private:
	NodePtr _m_header;
	NodePtr _m_tailer;
};







PRISM_END_NAMESPACE

#endif /* PRISM_SCRATCHPAD_H_ */
