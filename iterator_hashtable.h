/*
 * iterator_hashtable.h
 *
 *  Created on: 2018年8月6日
 *      Author: garvin
 */

#ifndef ITERATOR_HASHTABLE_H_
#define ITERATOR_HASHTABLE_H_

#include "hashtable_node.h"
#include "iterator.h"

template<class Value, class Key, class HashFunction, class ExtractKey, class EqualKey, class Alloc>
struct hashtable_iterator{
	typedef hashtable<Value, Key, HashFunction, ExtractKey, EqualKey, Alloc> hashtable;
	typedef hashtable_iterator<Value, Key, HashFunction, ExtractKey, EqualKey, Alloc> iterator;
	typedef hashtable_node<Value> node;

	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef Value& reference;
	typedef Value* pointer;

	node* cur;
	hashtable *ht;
};



#endif /* ITERATOR_HASHTABLE_H_ */
