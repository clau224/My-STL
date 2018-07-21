/*
 * string.h
 *
 *  Created on: 2018年7月21日
 *      Author: garvin
 */

#ifndef STRING_H_
#define STRING_H_

#include "allocator.h"
#include "uninitialized.h"
#include "construct.h"
#include "pair.h"

namespace MySTL{
class string{
	typedef char value_type;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef simple_alloc<value_type, alloc> data_allocator;
	static const size_type npos = -1;

private:
	iterator start;
	iterator finish;
	iterator end_of_storage;

public:
	string() : start(NULL), finish(NULL), end_of_storage(NULL){}
	string(const string& x){
		start = data_allocator::allocate(x.finish-x.start);
		finish = uninitialized_copy(x.start, x.finish, this->start);
		end_of_storage = finish;
	}
	string(const string& x, size_type pos, size_type len = npos){
		len = (len==npos || len>x.size()-pos) ? x.size()-pos : len;
		start = data_allocator::allocate(len);
		finish = uninitialized_copy(x.start, x.finish, this->start);
		end_of_storage = finish;
	}



public:
	iterator begin() const {
		return start;
	}
	iterator end() const {
		return finish;
	}
	const_iterator begin() const{
		return start;
	}
	const_iterator end() const{
		return finish;
	}
	size_type size() const{
		return finish-start;
	}
	size_type length() const{
		return finish-start;
	}
	size_type capacity() const{
		return end_of_storage - start;
	}
	void clear(){
		destroy(start, finish);
		finish = start;
	}
	bool empty() const{
		return begin() == end();
	}
	void resize(size_type new_size){
		resize(new_size, size_type());
	}
	void resize(size_type new_size, value_type& c){
		if(new_size<size()){
			destroy(start+new_size, finish);
			finish = start+n;
		}
		else if(new_size>=size() && new_size<capacity()){
			size_type len = new_size-size();
			finish = uninitialized_fill_n(finish, len, c);
		}
		else{
			size_type len = new_size-size();
			iterator newstart = data_allocator::allocate(new_size);
			iterator newfinish = uninitialized_copy(start, finish, newstart);
			iterator newfinish = uninitialized_fill_n(finish, len, c);

			destroy(start, finish);
			data_allocator::deallocate(start, end_of_storage-start);
			start = newstart;
			finish = newfinish;
			end_of_storage = finish;
		}
	}
	void reserve(size_type newsize){
		if(newsize<size())
			return;
		iterator newstart = data_allocator::allocate(newsize);
		iterator newfinish = uninitialized_copy(start, finish, newstart);
		destroy(start, finish);
		data_allocator::deallocate(start, end_of_storage-start);
		start = newstart;
		finish = newfinish;
		end_of_storage = start + newsize;
	}
};
}



#endif /* STRING_H_ */
