/*
 * multiset.h
 *
 *  Created on: 2018年7月17日
 *      Author: garvin
 */

#ifndef MULTISET_H_
#define MULTISET_H_

#include "rbtree.h"
#include "functional.h"

namespace MySTL{
template<class Key, class Compare = less<Key>, class Alloc = alloc>
class multiset{
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
	multiset() : rbt(Compare()){}
	explicit multiset(const Compare& comp) : rbt(comp) {}
	template<class InputIterator>
	multiset(InputIterator first, InputIterator last) : rbt(Compare()){
		rbt.insert_equal(first, last);
	}
	template<class InputIterator>
	multiset(InputIterator first, InputIterator last, const Compare& comp) : rbt(comp){
		rbt.insert_equal(first, last);
	}

public:
	iterator begin() const{
		return rbt.begin();
	}
	iterator end() const{
		return rbt.end();
	}
	bool empty() const {
		return rbt.empty();
	}
	size_type size() const{
		return rbt.size();
	}

	void clear(){
		rbt.clear();
	}
	iterator find(const key_type& x) const{
		return rbt.find(x);
	}

	iterator insert(const value_type& x){
		return rbt.insert_equal(x);
	}
	template<class InputIterator>
	void insert(InputIterator first, InputIterator last){
		rbt.insert_equal(first, last);
	}
};
}



#endif /* MULTISET_H_ */
