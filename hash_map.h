/*
 * hash_map.h
 *
 *  Created on: 2018年8月13日
 *      Author: garvin
 */

#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include "hashtable.h"

namespace MySTL{
template<class Key, class T, class HashFcn = hash<Key>, class EqualKey = equal_to<Key>, class Alloc = alloc>
class hash_map{
private:
	typedef hashtable<pair<const Key, T>, Key, HashFcn, select1st<pair<const Key, T> >, EqualKey, Alloc> ht;
	ht rep;
public:
	typedef typename ht::key_type key_type;
	typedef typename ht::value_type value_type;
	typedef typename ht::hasher hasher;
	typedef typename ht::key_equal key_equal;
	typedef T data_type;
	typedef T mapped_type;

	typedef typename ht::size_type size_type;
	typedef typename ht::difference_t difference_t;
	typedef typename ht::pointer pointer;
	typedef typename ht::const_pointer const_pointer;
	typedef typename ht::reference reference;
	typedef typename ht::const_reference const_reference;
	typedef typename ht::iterator iterator;
	typedef typename ht::const_iterator const_iterator;

	hasher hash_funct() const{
		return rep.hash_funct();
	}
	key_equal key_eq() const{
		return rep.key_eq();
	}

public:
	hash_map() : rep(100, hasher(), key_equal()) {}
	explicit hash_map(size_type n) : rep(n, hasher(), key_equal()) {}
	hash_map(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
	hash_map(size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql) {}

public:
	size_type size() const{
		return rep.size();
	}
	bool empty() const{
		return rep.empty();
	}

	iterator begin(){
		return rep.begin();
	}
	iterator end(){
		return rep.end();
	}
	const_iterator begin() const{
		return rep.begin();
	}
	const_iterator end() const{
		return rep.end();
	}

public:
	pair<iterator, bool> insert(const value_type& obj){
		return rep.insert_unique(obj);
	}
	pair<iterator, bool> insert_nooresize(const value_type& obj){
		return rep.insert_unique_noresize(obj);
	}
	iterator find(const key_type& key){
		return rep.find(key);
	}
	const_iterator find(const key_type& key) const{
		return rep.find(key);
	}
	T& operator[] (const key_type& key) {
		return rep.find_or_insert(value_type(key, T())).second;
	}
	void resize(size_type hint) {
		rep.resize(hint);
	}
	size_type bucket_count() const {
		return rep.bucket_count();
	}
	void erase(iterator& item){
		rep.erase(item);
	}
};
}



#endif /* HASH_MAP_H_ */
