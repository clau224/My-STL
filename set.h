/*
 * set.h
 *
 *  Created on: 2018年7月13日
 *      Author: garvin
 */

#ifndef SET_H_
#define SET_H_

#include "rbtree.h"

namespace MySTL{
template<class Key, class Compare = less<int>, class Alloc = alloc>
class set{
public:
	typedef Key key_type;
	typedef Key value_type;
	typedef Compare key_compare;
	typedef Compare value_compare;

private:
	typedef rbtree<key_type, value_type, identity<value_type>, key_compare, Alloc> rep_type;
	rep_type rbt;

public:
    typedef typename rep_type::const_pointer pointer;
    typedef typename rep_type::const_pointer const_pointer;
    typedef typename rep_type::const_reference reference;
    typedef typename rep_type::const_reference const_reference;
    typedef typename rep_type::const_iterator iterator;
    typedef typename rep_type::const_iterator const_iterator;

    typedef typename rep_type::size_type size_type;
    typedef typename rep_type::difference_type difference_type;

public:
    set() : rbt(Compare()) {}
    explicit set(const Compare& comp) : rbt(comp) {}

    template<class InputIterator>
    set(InputIterator first, InputIterator last, const Compare& comp) : rbt(comp){
    	rbt.insert_unique(first, last);
    }
	set(const set<Key, Compare, Alloc>& x) :
			rbt(x.rbt) {
	}
	set<Key, Compare, Alloc>& operator=(const set<Key, Compare, Alloc>& x) {
		rbt = x.rbt;
		return *this;
	}

};
}



#endif /* SET_H_ */
