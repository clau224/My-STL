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
#include <iostream>

namespace MySTL{
class string{
public:
	typedef char 				value_type;
	typedef value_type* 		iterator;
	typedef const value_type* 	const_iterator;
	typedef value_type& 		reference;
	typedef const value_type& 	const_reference;
	typedef size_t 				size_type;
	typedef ptrdiff_t 			difference_type;
	typedef simple_alloc<value_type, alloc> data_allocator;
	static const size_type npos = -1;

private:
	iterator start;
	iterator finish;
	iterator end_of_storage;

private:
	template<class Iterator>
	void allocate_and_copy(const Iterator first, const Iterator last){
		size_type len = last - first;
		start = data_allocator::allocate(len);
		finish = uninitialized_copy(first, last, start);
		end_of_storage = finish;
	}
	void allocate_and_fill_n(size_type len, value_type& x){
		start = data_allocator::allocate(len);
		finish = uninitialized_fill_n(start, len, x);
		end_of_storage = finish;
	}
	void destroy_and_deallocate(){
		destroy(start, finish);
		data_allocator::deallocate(start, end_of_storage-start);
	}

public:
	string() : start(NULL), finish(NULL), end_of_storage(NULL){}
	string(size_type len, value_type x){
		allocate_and_fill_n(len, x);
	}
	string(const string& x){
		allocate_and_copy(x.start, x.finish);
	}
	string(const string& x, size_type pos, size_type len = npos){
		len = (len==npos || len>x.size()-pos) ? x.size()-pos : len;
		allocate_and_copy(x.start + pos, x.start + pos +len);
	}
	string(const_iterator str){
		size_type len = strlen(str);
		allocate_and_copy(str, str+len);
	}
	string(const_iterator str, size_type size){
		allocate_and_copy(str, str+size);
	}
	template<class Iterator>
	string(Iterator first, Iterator last){
		allocate_and_copy(first, last);
	}

	~string(){};

	string& operator= (const string& str){
		if(*this != str){
			destroy_and_deallocate();
			allocate_and_copy(str.start, str.finish);
		}
		return *this;
	}
	string& operator= (const_iterator str){
		destroy_and_deallocate();
		allocate_and_copy(str, str+strlen(str));
		return *this;
	}
	string& operator= (value_type& ch){
		destroy_and_deallocate();
		allocate_and_fill_n(1, ch);
		return *this;
	}


public:
	iterator begin(){
		return start;
	}
	iterator end(){
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
		resize(new_size, value_type());
	}
	void resize(size_type new_size, value_type c){
		if(new_size<size()){
			destroy(start+new_size, finish);
			finish = start+new_size;
		}
		else if(new_size>=size() && new_size<capacity()){
			size_type len = new_size-size();
			finish = uninitialized_fill_n(finish, len, c);
		}
		else{
			size_type len = new_size-size();
			iterator newstart = data_allocator::allocate(new_size);
			iterator newfinish = uninitialized_copy(start, finish, newstart);
			newfinish = uninitialized_fill_n(finish, len, c);

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

	reference operator[] (size_type pos){
		return *(start+pos);
	}
	const_reference operator[] (size_type pos) const{
		return *(start+pos);
	}
	reference front(){
		return *start;
	}
	const_reference front() const{
		return *start;
	}
	reference back(){
		return *(finish-1);
	}
	const_reference back() const{
		return *(finish-1);
	}

private:
	template<class InputIterator>
	iterator insert_aux(iterator pos, InputIterator first, InputIterator last){
		size_type insert_len = distance(first, last);
		size_type newsize = insert_len + size();
		iterator newstart = data_allocator::allocate(newsize);
		iterator newfinish = uninitialized_copy(start, pos, newstart);
		newfinish = uninitialized_copy(first, last, newfinish);
		newfinish = uninitialized_copy(pos, finish, newfinish);
		destroy_and_deallocate();

		start = newstart;
		finish = newfinish;
		end_of_storage = newstart+newsize;
		return pos+insert_len;
	}
	iterator insert_aux_fill_n(iterator pos, size_type insert_len, value_type c){
		size_type newsize = insert_len +size();
		iterator newstart = data_allocator::allocate(newsize);
		iterator newfinish = uninitialized_copy(start, pos, newstart);
		newfinish = uninitialized_fill_n(newfinish, insert_len, c);
		newfinish = uninitialized_copy(pos, finish, newfinish);
		destroy_and_deallocate();

		start = newstart;
		finish = newfinish;
		end_of_storage = newstart + newsize;
		return pos+insert_len;
	}


public:
	template<class InputIterator>
	iterator insert(iterator pos, InputIterator first, InputIterator last){
		size_type left_len = capacity()-size();
		size_type insert_len = last-first;
		if(left_len>=insert_len){
			for(iterator item = finish-1; item>=pos; item--){
				*(item+insert_len) = *item;
			}
			uninitialized_copy(first, last, pos);
			finish += insert_len;
			return pos+insert_len;
		}
		else{
			return insert_aux(pos, first, last);
		}
	}
	string& insert(size_type pos, const string& str){
		insert(start+pos, str.begin(), str.end());
		return *this;
	}
	string& insert(size_type pos, const char* cit){
		size_type len = strlen(cit);
		insert(start+pos, cit, cit+len);
		return *this;
	}
	string& insert(size_type pos, const char* cit, size_type len){
		insert(start+pos, cit, cit+len);
		return *this;
	}
	string& insert(size_type pos, size_type num, value_type c){
		insert(begin()+pos, num, c);
		return *this;
	}
	iterator insert(iterator pos, size_type insert_len, value_type c){
		size_type left_len = capacity() - size();
		if(left_len >= insert_len){
			for(iterator item = finish-1; item>=pos; item++){
				*(item+insert_len) = *item;
			}
			uninitialized_fill_n(pos, insert_len, c);
			finish += insert_len;
			return pos+insert_len;
		}
		else
			return insert_aux_fill_n(pos, insert_len, c);
	}
	iterator insert(iterator pos, value_type c){
		return insert(pos, 1, c);
	}

	string& operator+= (const string& str){
		insert(size(), str);
		return *this;
	}
	string& operator+= (const char* str){
		insert(size(), str);
		return *this;
	}
	string& operator+= (value_type ch){
		insert(end(), ch);
		return *this;
	}

	string& append(const string& str){
		(*this)+=str;
		return *this;
	}
	string& append(const char* str){
		(*this)+=str;
		return *this;
	}
	string& append(const string& str, size_type pos, size_type len){
		len = (pos+len > str.size()) ? size()-pos : len;
		insert(end(), str.begin()+pos, str.begin()+pos+len);
		return *this;
	}
	string& append(size_type num, value_type x){
		insert(end(), num, x);
		return *this;
	}

	iterator erase(iterator first, iterator last){
		size_type move_len = last - first;
		copy(last, finish, first);
		destroy(finish-move_len, finish);
		finish = finish-move_len;
		return first;
	}
	iterator erase(iterator first){
		return erase(first, first+1);
	}
	string& erase(size_type pos, size_type len){
		len = (pos+len > size()) ? size()-pos : len;
		erase(begin()+pos, begin()+pos+len);
		return *this;
	}

	template<class InputIterator>
	string& replace(iterator first1, iterator last1, InputIterator first2, InputIterator last2){
		iterator tmp = erase(first1, last1);
		insert(tmp, first2, last2);
		return *this;
	}
	string& replace(size_type pos, size_type len, const string& str){
		return replace(begin()+pos, begin()+pos+len, str.begin(), str.end());
	}
	string& replace(iterator first, iterator last, const string& str){
		return replace(first, last, str.begin(), str.end());
	}
	string& replace(size_type pos, size_type len, const string& str, size_type pos2, size_type len2){
		len2 = (pos2 + len2 > str.size()) ? str.size()-pos2 : len2;
		return replace(begin()+pos, begin()+pos+len, str.begin()+pos2, str.begin()+pos2+len2);
	}
	string& replace(size_type pos, size_type len, const char* str){
		return replace(begin()+pos, begin()+pos+len, str, str+strlen(str));
	}
	string& replace(iterator first, iterator last, size_type num, value_type x){
		iterator tmp = erase(first, last);
		insert(tmp, num, x);
		return *this;
	}


public:
	friend bool operator== (const string& str1, const string& str2){
		if(str1.size() != str2.size())
			return false;
		for(const_iterator it1 = str1.begin(), it2 = str2.begin(); it1!=str1.end() && it2!=str2.end(); it1++, it2++){
			if(*it1!=*it2)
				return false;
		}
		return true;
	}
	friend bool operator== (const string& str1, const char* str2){
		if(str1.size() != strlen(str2))
			return false;
		for(const_iterator it1 = str1.begin(), it2 = str2; it1 != str1.end() && *it2!='\0'; it1++, it2++){
			if(*it1!=*it2)
				return false;
		}
		return true;
	}
	friend bool operator== (const char* str1, const string& str2){
		return str2 == str1;
	}
	friend bool operator!= (const string& str1, const string& str2){
		return !(str1 == str2);
	}
	friend bool operator!= (const string& str1, const char* str2){
		return !(str1 == str2);
	}
	friend bool operator!= (const char* str1, const string& str2){
		return !(str1 == str2);
	}

};
}



#endif /* STRING_H_ */
