/*
 * iterator_list.h
 *
 *  Created on: Jun 17, 2018
 *      Author: garvin
 */

#ifndef ITERATOR_LIST_H_
#define ITERATOR_LIST_H_

#include "listnode.h"
#include "iterator.h"

namespace MySTL {
template<class T, class Ref, class Ptr>
struct list_iterator {
	typedef list_iterator<T, T&, T*> iterator;
	typedef list_iterator<T, Ref, Ptr> self;

	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef list_node<T>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef bidirectional_iterator_tag iterator_category;

	link_type node;

	list_iterator(link_type x) :
			node(x) {
	}
	list_iterator() {}

	list_iterator(const iterator& x) :
			node(x.node) {
	}

	bool operator ==(const self& x) const {
		return node == x.node;
	}
	bool operator !=(const self& x) const {
		return node != x.node;
	}
	reference operator *() const {
		return (*node).value;
	}
	pointer operator ->() const {
		return &(operator *());
	}
	self operator + (int n) {
		self temp = *this;
		while(n--){
			temp = temp.node->next;
		}
		return temp;
	}
	self operator - (int n) {
		self temp = *this;
		while(n--){
			temp = temp.node->prev;
		}
		return temp;
	}
	self& operator ++() {
		this->node = this->node->next;
		return *this;
	}
	self operator ++(int) {
		self temp = *this;
		this->node = this->node->next;
		return temp;
	}
	self& operator --() {
		this->node = this->node->prev;
		return *this;
	}
	self operator --(int) {
		self temp = *this;
		this->node = this->node->prev;
		return temp;
	}
};
}

#endif /* ITERATOR_LIST_H_ */
