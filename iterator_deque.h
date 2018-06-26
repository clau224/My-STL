/*
 * iterator_deque.h
 *
 *  Created on: 2018年6月25日
 *      Author: garvin
 */

#ifndef ITERATOR_DEQUE_H_
#define ITERATOR_DEQUE_H_

#include "iterator.h"

namespace MySTL{
template<class T, class Ref, class Ptr, size_t BufSize>
struct deque_iterator{
	typedef deque_iterator<T, T&, T*, BufSize> iterator;
	typedef deque_iterator<const T, const T&, const T*, BufSize> const_iterator;

	typedef random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef size_t tize_type;
	typedef ptrdiff_t difference_type;
	typedef T** map_pointer;

	typedef deque_iterator self;

	T* cur;
	T* first;
	T* last;
	map_pointer node;
	static size_t deque_bufsize(size_t n, size_t sz){
		return n!=0 ? n : (sz<512 ? sz/512 : 1);
	}
	static size_t buffer_size(){
		return deque_bufsize(BufSize, sizeof(T));
	}

	void set_node(map_pointer newnode){
		this->node = newnode;
		this->first = *newnode;
		this->last = this->first + difference_type(BufSize);
	}

	reference operator*() const{
		return *cur;
	}
	pointer operator->() const{
		return &(operator*());
	}
	self& operator++(){
		++cur;
		if(cur == last){
			set_node(node+1);
			cur = first;
		}
		return *this;
	}
	self operator++(int){
		self tmp = *this;
		++(*this);
		return tmp;
	}
	self& operator--(){
		if(cur == first){
			set_node(node-1);
			cur = last;
		}
		--cur;
		return *this;
	}
	self operator--(int){
		self tmp = *this;
		--(*this);
		return tmp;
	}
	self& operator+=(difference_type n){
		difference_type d = cur-first+n;
		if(n>=0 && n<BufSize){
			cur+=n;
			return *this;
		}
		if(n>=0){
			difference_type dis = n-(last-cur);
			difference_type num = dis/BufSize;
			set_node(node+num);
			cur = first+dis%BufSize;
			return *this;
		}
		if(n<0){
			difference_type dis = n-(cur-first);
			difference_type num = dis/BufSize;
			set_node(node-num);
			cur = last-dis%BufSize;
			return *this;
		}
	}
	self& operator -=(difference_type n){
		return (*this) += (-n);
	}
	self operator+(difference_type n){
		self tmp = *this;
		tmp+=n;
		return tmp;
	}
	self operator-(difference_type n){
		self tmp = *this;
		tmp-=n;
		return tmp;
	}
	bool operator==(const self& d) const{
		return cur == d.cur;
	}
	bool operator!=(const self& d) const{
		return cur != d.cur;
	}
	bool operator<(const self& d) const{
		return node == d.node ? cur<d.cur : node<d.node ;
	}
};
}



#endif /* ITERATOR_DEQUE_H_ */
