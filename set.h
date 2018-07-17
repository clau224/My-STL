/*
 * set.h
 *
 *  Created on: 2018年7月13日
 *      Author: garvin
 */

#ifndef SET_H_
#define SET_H_

#include "rbtree.h"
#include "functional.h"

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

	key_compare key_comp() const {
		return rbt.key_comp();
	}
	value_compare value_comp() const {
		return rbt.key_comp();
	}
	iterator begin() const{
		return rbt.begin();
	}
	iterator end() const{
		return rbt.end();
	}
	bool empty() const{
		return rbt.empty();
	}
	size_type size() const{
		return rbt.size();
	}

	pair<iterator, bool> insert(const value_type& x){
		pair<typename rep_type::iterator, bool> tmp = rbt.insert_unique(x);
		return pair<iterator, bool>(tmp.first, tmp.second);
	}
	template<class InputIterator>
	void insert(InputIterator first, InputIterator last){
		return rbt.insert_unique(first, last);
	}
	void clear(){
		rbt.clear();
	}
	iterator find(const key_type& x) const {
		return rbt.find(x);
	}
};
}



#endif /* SET_H_ */
