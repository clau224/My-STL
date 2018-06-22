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

	typedef simple_alloc<listnode, Alloc> data_allocator;

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
		destroy(&l->value);
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
		newnode->next=position.node;
		newnode->prev=position.node->prev;
		position.node->prev->next=newnode;
		position.node->prev=newnode;
		return newnode;
	}
	iterator erase(iterator position){
		link_type prevnode = position.node->prev;
		link_type nextnode = position.node->next;
		nextnode->prev = prevnode;
		prevnode->next = nextnode;
		destroynode(position.node);
		return iterator(nextnode);
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

	void transfer(iterator position, iterator first, iterator last){
		if(last == position){
			return;
		}
		iterator prev = position.node->prev;
		iterator rear = last.node->prev;
		first.node->prev->next = last.node;
		last.node->prev = first.node->prev;
		prev.node->next = first.node;
		first.node->prev = prev.node;
		rear.node->next = position.node;
		position.node->prev = rear.node;

	}

	void splice(iterator position, list& l){
		if(l.empty())
			return;
		transfer(position, l.begin(), l.end());
	}
	void splice(iterator position, iterator item){
		transfer(position, item, item+1);
	}
	void splice(iterator position, iterator start, iterator finish){
		transfer(position, start, finish);
	}

	void swap(list& l){
		link_type tmp = this->node;
		this->node = l.node;
		l.node = tmp;
	}

	void reverse(){
		if(this->size()==0 || this->size()==1)
			return;
		iterator start = begin();
		size_t s = size()+1;
		while(s--){
			link_type tmp = start.node->prev;
			start.node->prev = start.node->next;
			start.node->next = tmp;
			start--;
		}
	}

	void merge(list& l){
		iterator start1 = this->begin();
		iterator start2 = l.begin();
		while(start1!=this->end() && start2!=l.end()){
			if(*start1<*start2){
				++start1;
			}
			else{
				iterator tmp = start2+1;
				this->splice(start1, start2);
				start2=tmp;
			}
		}
		if(!this->empty()){
			this->splice(start1, l);
		}
	}

	void sort(){
		if(this->size()==0 || this->size()==1){
			return;
		}
		list<T> tmp;
		iterator start1, start2;
		while(!this->empty()){
			start1 = this->begin();
			start2 = start1;
			while(start1!=this->end()){
				if(*start1 < *start2)
					start2 = start1;
				start1++;
			}

			tmp.splice(tmp.end(), start2);
		}
		this->swap(tmp);
		//destroynode(tmp.node);
	}
};

}

#endif /* LIST_H_ */
