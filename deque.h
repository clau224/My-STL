/*
 * deque.h
 *
 *  Created on: 2018年6月26日
 *      Author: garvin
 */

#ifndef DEQUE_H_
#define DEQUE_H_

#include "iterator_deque.h"

namespace MySTL{
template<class T, class Alloc = alloc, size_t BufSize = 0>
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
	typedef simple_alloc<value_type, Alloc> data_alloctor;
	typedef simple_alloc<pointer, Alloc> map_allocator;

	static size_t deque_bufsize(size_t BufSize, size_t sz){
		return BufSize!=0 ? BufSize : (sz<512 ? 512/sz : 1);
	}
	static size_t buffer_size(){
		return deque_bufsize(BufSize, sizeof(T));
	}
	pointer allocate_node(){
		return data_alloctor::allocate(buffer_size());
	}


	void fill_initialize(size_type n, const value_type& value){

	}
	void push_back_aux(const value_type& value){

	}
	void push_front_aux(const value_type& value){

	}
	void pop_back_aux(){

	}
	void pop_front_aux(){

	}
	void create_map_and_nodes(size_type n){

	}


protected:
	iterator start;
	iterator finish;
	map_pointer map;
	size_t map_size;


public:
	deque():start(),finish(){
		create_map_and_nodes(0);
	}
	deque(int n, const value_type& d):start(),finish(), map(NULL), map_size(0){
		fill_initialized(n, d);
	}
	~deque();

	void push_back(const value_type& value){
		if(finish.cur!=finish.last-1){
			construct(finish.cur, t);
			++finish.cur;
		}
		else{
			push_back_aux(value);
		}
	}
};
}



#endif /* DEQUE_H_ */
