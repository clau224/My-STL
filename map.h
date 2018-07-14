/*
 * map.h
 *
 *  Created on: 2018年7月14日
 *      Author: garvin
 */

#ifndef MAP_H_
#define MAP_H_

#include "rbtree.h"
#include "functional.h"

namespace MySTL{
template<class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class map{
public:
	typedef Key key_type;
	typedef T data_type;
	typedef T mapped_type;
	typedef pair<const Key, T> value_type;
	typedef Compare key_compare;

	class value_compare : binary_function<value_type, value_type, bool>{
		friend class map<Key, T, Compare, Alloc>;
	protected:
		Compare comp;
		value_compare(Compare c) : comp(c){}
	public:
		bool operator()(const value_type& x, const value_type& y) const {
			return comp(x.first_type, y.first_type);
		}
	};

private:
	typedef rbtree<key_type, value_type, select1st<value_type>, key_compare, Alloc> rep_type;
	rep_type rbt;

public:
	typedef typename rep_type::pointer pointer;
	typedef typename rep_type::const_pointer const_pointer;
	typedef typename rep_type::reference reference;
	typedef typename rep_type::const_reference const_reference;
	typedef typename rep_type::iterator iterator;
	typedef typename rep_type::const_iterator const_iterator;
	typedef typename rep_type::size_type size_type;
	typedef typename rep_type::difference_type difference_type;

	map() : rbt(Compare()){}
	explicit map(const Compare& c) : rbt(c){}
	template<class InputIterator>
	map(InputIterator first, InputIterator last) : rbt(Compare()){
		rbt.insert_unique(first, last);
	}
	template<class InputIterator>
	map(InputIterator first, InputIterator last, const Compare& c) : rbt(c) {
		rbt.insert_unique(first, last);
	}
	map(const map<Key, T, Compare, Alloc>& m) : rbt(m.rbt){}
	map<Key, T, Compare, Alloc>& operator=(const map<Key, T, Compare, Alloc>& m){
		this->rbt = m.rbt;
		return *this;
	}

	key_compare key_comp() const{
		return rbt.key_comp();
	}
	value_compare value_comp() const{
		return value_compare(rbt.key_comp());
	}

	iterator begin(){
		return rbt.begin();
	}
	const_iterator begin() const{
		return rbt.begin();
	}
	iterator end(){
		return rbt.end();
	}
	const_iterator end() const{
		return rbt.end();
	}
	bool empty(){
		return rbt.empty();
	}
	size_type size(){
		return rbt.size();
	}

	data_type& operator[](const key_type& k){
		return ( *(  (  insert(  value_type(k, T())  )  ).first  )  ).second;
	}

	pair<iterator, bool> insert(const value_type& p){
		return rbt.insert_unique(p);
	}

	template<class InputIterator>
	void insert(InputIterator first, InputIterator last){
		rbt.insert_unique(first, last);
	}
	void clear(){
		rbt.clear();
	}
	iterator find(const key_type& x){
		return rbt.find(x);
	}
};
}



#endif /* MAP_H_ */
