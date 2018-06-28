/*
 * deque.h
 *
 *  Created on: 2018年6月26日
 *      Author: garvin
 */

#ifndef DEQUE_H_
#define DEQUE_H_

#include "iterator_deque.h"
#include "construct.h"
#include "allocator.h"
#include "uninitialized.h"
#include "algorithm.h"

namespace MySTL{
template<class T, class Alloc = alloc, size_t BufSize=0>
class deque{
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t diference_type;
	typedef deque_iterator<T, T&, T*, BufSize> iterator;
protected:
	typedef pointer* map_pointer;
	typedef simple_alloc<value_type, Alloc> data_allocator;
	typedef simple_alloc<pointer, Alloc> map_allocator;

	static size_t _deque_bufsize(size_t bufsize, size_t sz){
		return bufsize!=0 ? bufsize : (sz<512 ? size_t(512/sz) : size_t(1));
	}
	static size_t buffer_size(){
		return _deque_bufsize(BufSize, sizeof(T));
	}
	pointer allocate_node(){
		return data_allocator::allocate(buffer_size());
	}
	void deallocate_node(pointer ptr){
		//data_allocator::deallocate(ptr, buffer_size());
	}


	void fill_initialize(size_type n, const value_type& value){
		create_map_and_nodes(n);
		map_pointer cur;
		for(cur=start.node;cur<finish.node;cur++){
			uninitialize_fill(*cur, *cur+buffer_size(), value);
		}
		uninitialize_fill(*cur, finish.cur, value);
	}

	void push_back_aux(const value_type& value){
		value_type copy = value;
		reserve_map_at_back();
		*(finish.node+1) = allocate_node();
		construct(finish.cur, copy);
		finish.set_node(finish.node+1);
		finish.cur = finish.first;
	}
	void push_front_aux(const value_type& value){
		value_type copy = value;
		reserve_map_at_front();
		*(start.node-1) = allocate_node();
		start.set_node(start.node-1);
		start.cur = start.last-1;
		construct(start.cur, copy);
	}

	void pop_back_aux(){
		deallocate_node(*finish.node);
		finish.set_node(finish.node-1);
		finish.cur=finish.last-1;
		destroy(finish.cur);
	}
	void pop_front_aux(){
		destroy(start.cur);
		deallocate_node(*start.node);
		start.set_node(start.node+1);
		start.cur=start.first;
	}

	void create_map_and_nodes(size_type n){
		size_type num_nodes = n / buffer_size() + 1;
		map_size = max(size_t(8), num_nodes + 2);
		map = map_allocator::allocate(map_size);

		map_pointer nstart = map + (map_size - num_nodes) / 2;
		map_pointer nfinish = nstart + num_nodes - 1;
		map_pointer cur;

		for (cur = nstart; cur <= nfinish; cur++) {
			*cur = allocate_node();
		}
		start.set_node(nstart);
		finish.set_node(nfinish);
		start.cur = start.first;
		finish.cur = finish.first + n % buffer_size();
	}

	void reserve_map_at_back(size_t add_num=1){
		if(add_num > map_size-(finish.node+1-map)){
			reallocate_map(add_num, false);
		}
	}
	void reserve_map_at_front(size_t add_num=1){
		if(add_num > start.node-map){
			reallocate_map(add_num, true);
		}
	}

	void reallocate_map(size_type node_to_add,bool add_at_front) {
		size_type old_num_nodes = finish.node - start.node + 1;
		size_type new_num_nodes = old_num_nodes + node_to_add;

		map_pointer new_nstart;
		if (map_size > 2 * new_num_nodes) {
			//偏到一边去了，把他移到正中间来
			new_nstart = map + (map_size - new_num_nodes) / 2
			+ (add_at_front ? node_to_add : 0);
			if (new_nstart < start.node)
			copy(start.node, finish.node + 1, new_nstart);
			else
			copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
		} else {
			size_type new_map_size = map_size + max(map_size, node_to_add) + 2;
			map_pointer new_map = map_allocator::allocate(new_map_size);
			new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? node_to_add : 0);
			copy(start.node, finish.node + 1, new_nstart);
			map_allocator::deallocate(map, map_size);
			map = new_map;
			map_size = new_map_size;
		}

		start.set_node(new_nstart);
		finish.set_node(new_nstart + old_num_nodes - 1);
	}


protected:
	iterator start;
	iterator finish;
	map_pointer map;
	size_t map_size;


public:
	deque():start(),finish(),map_size(0), map(0){
		create_map_and_nodes(0);
	}
	deque(int n, const value_type& d):start(),finish(), map(NULL), map_size(0){
		fill_initialize(n, d);
	}
	~deque(){};


	iterator begin() const{
		return start;
	}
	iterator end() const{
		return finish;
	}
	reference front() const{
		return *start;
	}
	reference back() const{
		return *(finish-1);
	}
	bool empty() const{
		return finish==start;
	}


	void push_back(const value_type& value){
		if(finish.cur!=finish.last-1){
			construct(finish.cur, value);
			++finish.cur;
		}
		else{
			push_back_aux(value);
		}
	}
	void push_front(const value_type& value){
		if(start.cur!=start.first){
			--start.cur;
			construct(start.cur, value);
		}
		else{
			push_front_aux(value);
		}
	}
	void pop_back(){
		if(finish.cur!=finish.first){
			--finish.cur;
			destroy(finish.cur);
		}
		else{
			pop_back_aux();
		}
	}
	void pop_front(){
		if(start.cur!=start.last-1){
			++start.cur;
			destroy(start.cur);
		}
		else{
			pop_front_aux();
		}
	}


	void clear(){
		for(map_pointer nd = start.node+1; nd<finish.node; nd++){
			destroy(*nd, *nd+buffer_size());
			deallocate_node(*nd);
		}
		if(start.node == finish.node){
			destroy(start.cur, finish.cur);
		}
		else{
			destroy(start.cur, start.last);
			destroy(finish.first, finish.cur);
			deallocate_node(*finish.node);
		}
		finish = start;
	}

	size_t size(){
		return start.node == finish.node ? finish.cur-start.cur : (buffer_size()*(finish.node-start.node-1)+start.last-start.cur+finish.cur-finish.first);
	}

};
}



#endif /* DEQUE_H_ */
