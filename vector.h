/*
 * vector.h
 *
 *  Created on: 2018年6月11日
 *      Author: garvin
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "iterator.h"
#include "allocator.h"
#include "construct.h"
#include "algorithm.h"
#include "uninitialized.h"

namespace MySTL {
template<class T, class Alloc = alloc>
class vector {
public:
	typedef T 			value_type;
	typedef T* 			pointer;
	typedef T* 			iterator;
	typedef T& 			reference;
	typedef size_t 		size_type;
	typedef ptrdiff_t 	difference_type;

protected:
	typedef simple_alloc<value_type, Alloc> 	data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;

	void insert_aux(iterator position, const T& x);

	void deallocate(){
		if(start)
			data_allocator::deallocate(start, end_of_storage-start);
	}

	void fill_initialize(size_type n, const T& value)
	{
		start = allocate_and_fill(n, value);
		finish = start+n;
		end_of_storage = finish;
	}

	iterator allocate_and_fill(size_type new_size, const T& x){
		iterator result= data_allocator::allocate(new_size);
		uninitialized_fill_n(result, new_size, x);
		return result;
	}

public:
	iterator begin(){
		return start;
	}
	iterator end(){
		return finish;
	}

	size_type size() const{
		return size_type( finish - start );
	}

	size_type capacity() const {
		return size_type(end_of_storage - start);
	}

	bool empty(){
		return begin()==end();
	}

	reference operator [](size_type n){
		return *(begin()+n);
	}

	vector():start(0),finish(0),end_of_storage(0){};
	vector(size_type n, const T& value){ fill_initialize(n, value); }
	vector(int n, const T& value){ fill_initialize(n, value);}
	vector(long n, const T& value){ fill_initialize(n, value);}
	explicit vector(size_type n){fill_initialize(n, T());}

	~vector(){
		destroy(start, finish);
		this->deallocate();
	}

	reference front() { return *begin();}
	reference back() { return *(end()-1);}

	void push_back(const T& x){
		if(finish!=end_of_storage){
			construct(finish, x);
			++finish;
		}
		else{
			insert_aux(end(), x);
		}
	}

	void pop_back(){
		--finish;
		destroy(finish);
	}

	iterator erase(iterator position){
		if(position + 1 != end()){
			copy(position+1, finish, position);
		}
		--finish;
		destroy(finish);
		return position;
	}

	iterator erase(iterator start_position, iterator finish_position)
	{
		iterator i=copy(finish_position, finish, start_position);
		destroy(i, finish);
		finish=finish-(finish_position-start_position);
		return start_position;
	}

	void resize(size_type new_size, const T& x){
		if(new_size<size()){
			erase(begin()+new_size, end());
		}
		else{
			insert(end(), new_size-size(), x);
		}
	}

	void resize(size_type new_size){
		resize(new_size, T());
	}

	void reserve(size_type new_size){
		if(new_size<=end_of_storage-start){
			return;
		}
		iterator new_start = data_allocator::allocate(new_size);
		iterator new_finish = new_start;
		new_finish=uninitialized_copy(start, finish, new_start);
		destory(start, finish);
		deallocate();
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start+new_size;
	}

	void clear(){
		erase(begin(), end());
	}

	void insert(iterator position, size_type n, const T& x)
	{
		if(n==0) return;

		if( size_type( end_of_storage - finish >= n) ){
			iterator old_finish = finish;
			uninitialized_copy(finish-n, finish, finish);
			finish += n;
			copy_backward (position, old_finish, finish);
			fill(position, position+n, x);
		}
		else{
			const size_type old_size = size();
			const size_type len = old_size + max(old_size, n);
			iterator new_start = data_allocator::allocate(len);
			iterator new_finish = new_start;
			new_finish=uninitialized_copy(start, position, new_start);
			new_finish=uninitialized_fill_n(new_finish, n, x);
			new_finish=uninitialized_copy(position, finish, new_finish);

			destory(start, finish);
			deallocate();
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start+n;
		}
	}
};
}

#endif /* VECTOR_H_ */
