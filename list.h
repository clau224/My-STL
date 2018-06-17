/*
 * list.h
 *
 *  Created on: Jun 17, 2018
 *      Author: garvin
 */

#ifndef LIST_H_
#define LIST_H_

#include "construct.h"
#include "allocator.h"
#include "algorithm.h"
#include "iterator_list.h"

namespace MySTL {
template<class T, class Alloc = alloc>
class list {
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef list_node<T> list_node;
	typedef list_node<T>* link_type;

protected:
	link_type node;

public:
	iterator begin() {
		return (link_type) node->next;
	}
	iterator end() {
		return node;
	}

};

}

#endif /* LIST_H_ */
