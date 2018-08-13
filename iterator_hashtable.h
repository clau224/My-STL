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

namespace MySTL {
template<class Value, class Key, class HashFunction, class ExtractKey,
			class EqualKey, class Alloc>
class hashtable;


template<class Value, class Key, class HashFunction, class ExtractKey, class EqualKey, class Alloc>
struct hashtable_iterator {

	typedef hashtable<Value, Key, HashFunction, ExtractKey, EqualKey, Alloc> hashtable_;
	typedef hashtable_iterator<Value, Key, HashFunction, ExtractKey, EqualKey,
			Alloc> iterator;
	typedef hashtable_node<Value> node;

	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef Value& reference;
	typedef Value* pointer;

	node* cur;
	hashtable_ *ht;

	hashtable_iterator(node* n, hashtable_* tab) :cur(n), ht(tab) {}
	hashtable_iterator() {}
	reference operator*() const {
		return cur->val;
	}
	pointer operator->() const {
		return &(operator*());
	}
	iterator& operator++() {
		const node* old = cur;
		cur = cur->next;
		if(cur == NULL) {
			size_type bucket = ht->bkt_num(old->val);
			while(!cur && ++bucket<ht->buckets.size()){
				cur = ht->buckets[bucket];
			}
		}
		return *this;
	}
	iterator operator++(int) {
		iterator tmp = *this;
		++*this;
		return tmp;
	}
	bool operator==(const iterator& it) const {
		return cur == it.cur;
	}
	bool operator!=(const iterator& it) const {
		return cur != it.cur;
	}
};
}

#endif /* ITERATOR_HASHTABLE_H_ */
