/*
 * hash_set.h
 *
 *  Created on: 2018年8月8日
 *      Author: garvin
 */

#ifndef HASH_SET_H_
#define HASH_SET_H_

#include "hashtable.h"

namespace MySTL{
template<class Value, class HashFun = hash<Value>, class EqualKey = equal_to<Value>, class Alloc = alloc>
class hash_set{
private:
	typedef hashtable<Value, Value, HashFun, identity<Value>, EqualKey, Alloc> ht;
	ht rep;

public:
	typedef typename ht::key_type 			key_type;
	typedef typename ht::value_type 		value_type;
	typedef typename ht::hasher 			hasher;
	typedef typename ht::key_equal 			key_equal;
	typedef typename ht::size_type 			size_type;
	typedef typename ht::const_pointer 		pointer;
	typedef typename ht::const_pointer 		const_pointer;
	typedef typename ht::const_reference 	reference;
	typedef typename ht::const_reference 	const_reference;
	typedef typename ht::const_iterator		iterator;
	typedef typename ht::const_iterator 	const_iterator;

public:
	hash_set() : rep(100, hasher(), key_equal()) {}
	explicit hash_set(size_type n) : rep(n, hasher(), key_equal()) {}
	hash_set(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
	hash_set(size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql) {}

public:
	size_type size() const{
		return rep.size();
	}
	size_type max_size() const{
		return rep.bucket_count();
	}
	bool empty() const{
		return rep.empty();
	}
	iterator begin() const {
		return rep.begin();
	}
	iterator end() const {
		return rep.end();
	}
	pair<iterator, bool> insert(const value_type& obj){
		pair<typename ht::iterator, bool> p = rep.insert_unique(obj);
		return pair<iterator, bool>(p.first, p.second);
	}
	iterator find(const key_type& key) const{
		return rep.find(key);
	}
	void clear(){
		rep.clear();
	}

	void resize(size_type hint) {
		rep.resize(hint);
	}
	size_type bucket_count () const {
		return rep.bucket_count();
	}

};
}



#endif /* HASH_SET_H_ */
