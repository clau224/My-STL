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
#include "listnode.h"

namespace MySTL {
template<class T, class Alloc = alloc>
class list {
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef list_node<T> listnode;
	typedef listnode* link_type;

	typedef list_iterator<T, T&, T*> iterator;

	typedef simple_alloc<value_type, Alloc> data_allocator;

	link_type allocnode(){
		return data_allocator::allocate();
	}
	void deallocnode(link_type l){
		data_allocator::deallocate(l);
	}

	link_type createnode(const T& l){
		link_type newnode = allocnode();
		construct(&newnode->value, l);
		return newnode;
	}
	void destroynode(link_type l){
		destroy(l->value);
		deallocnode(l);
	}

protected:
	link_type node;

public:
	list(){
		node = allocnode();
		node->next = node;
		node->prev = node;
	}
	~list(){
		clear();
		erase(this->end());
	}

	iterator begin() const {
		return node->next;
	}
	iterator end() const {
		return node;
	}
	bool empty() const {
		return node->next == node ;
	}
	reference front() const {
		return *node;
	}
	reference back() const {
		return *(node->prev);
	}
	size_t size(){
		return distance(begin(), end());
	}

	void push_front(const T& l){
		insert(begin(), l);
	}
	void push_back(const T& l){
		insert(end(), l);
	}
	void pop_front(){
		erase(begin());
	}
	void pop_back(){
		erase(--end());
	}

	iterator insert(iterator position, const T& l){
		link_type newnode = createnode(l);
		position.node->prev->next=newnode;
		newnode->next=position.node;
		newnode->prev=position.node->prev;
		position.node->prev=newnode;
		return newnode;
	}
	iterator erase(iterator position){
		link_type prevnode = position.node->prev;
		link_type nextnode = position.node->next;
		nextnode->prev = position.node->prev;
		prevnode->next = position.node->next;
		if(!this->empty()){
			destroy_node(position.node);
		}
		return nextnode;
	}
	void clear(){
		iterator tmp = this->begin();
		while(!this->empty()){
			erase(this->begin());
		}
	}
	void remove(const T& value){
		iterator tmp = begin();
		while(tmp!=this->end()){
			if(*tmp == value)
				tmp = erase(tmp);
			else
				++tmp;
		}
	}


};

}

#endif /* LIST_H_ */
