/*
 * hash_multiset.h
 *
 *  Created on: 2018年8月20日
 *      Author: garvin
 */

#ifndef HASH_MULTISET_H_
#define HASH_MULTISET_H_

#include "hashtable.h"

namespace MySTL{
template<class Value, class HashFcn = hash<Value>, class EqualKey = equal_to<Value>, class Alloc=alloc>
class hash_multiset{
private:
	typedef hashtable<Value, HashFcn, identity<Value>, EqualKey, Alloc> ht;
	ht rep;

public:
	typedef typename ht::key_type key_type;
	typedef typename ht::value_type value_type;
	typedef typename ht::hasher hasher;
	typedef typename ht::key_equal key_equal;
	typedef typename ht::size_type size_type;
	typedef typename ht::difference_t difference_type;

	typedef typename ht::const_pointer pointer;
	typedef typename ht::const_pointer const_pointer;
	typedef typename ht::const_reference reference;
	typedef typename ht::const_reference const_reference;
	typedef typename ht::const_iterator iterator;
	typedef typename ht::const_iterator const_iterator;

	hasher hash_funct() const{
		return rep.hash_funct();
	}
	key_equal key_eq() const{
		return rep.key_eq();
	}

public:
	hash_multiset():rep(100, hasher(), key_equal()) {}
	explicit hash_multiset(size_type n) : rep(n, hasher(), key_equal()) {}
	hash_multiset(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
	hash_multiset(size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql) {}

public:
	size_type size() const{
		return rep.size();
	}
	bool empty() const{
		return rep.empty();
	}
	void swap(hash_multiset& hs) {
		rep.swap(hs.rep);
	}

	iterator begin(){
		return rep.begin();
	}
	iterator end(){
		return rep.end();
	}

public:
	iterator insert(const value_type& obj){
		return rep.insert_equal(obj);
	}
	iterator insert_noresize(const value_type& obj){
		return rep.insert_equal_noresize(obj);
	}
	iterator find(const key_type& key) const{
		return rep.find(key);
	}
	size_type count(const key_type& key) const{
		return rep.count(key);
	}

	void erase(iterator item){
		rep.erase(item);
	}
	void clear(){
		rep.clear();
	}
	void resize(size_type hint){
		rep.resize(hint);
	}
	size_type bucket_count(){
		return rep.bucket_count();
	}
};
}



#endif /* HASH_MULTISET_H_ */
