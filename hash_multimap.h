/*
 * hash_multimap.h
 *
 *  Created on: 2018年8月21日
 *      Author: garvin
 */

#ifndef HASH_MULTIMAP_H_
#define HASH_MULTIMAP_H_

namespace MySTL{
template<class Key, class T, class HashFcn = hash<Key>, class EqualKey = equal_to<Key>, class Alloc = alloc>
class hash_multimap{
private:
	typedef hashtable<pair<const Key, T>, Key, HashFcn, select1st<pair<const Key, T> >, EqualKey, Alloc> ht;
	ht rep;

public:
	typedef typename ht::key_type key_type;
	typedef T data_type;
	typedef T mapped_type;
	typedef typename ht::value_type value_type;
	typedef typename ht::hasher hasher;
	typedef typename ht::key_equal key_equal;
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
	hash_multimap() : rep(100, hasher(), key_equal()) {}
	explicit hash_multimap(size_type n) : rep(n, hasher(), key_equal()) {}
	hash_multimap(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
	hash_multimap(size_type n, const hasher& hf, const key_equal& eq) : rep(n, hf, eq) {}

public:
	size_type size() const{
		return rep.size();
	}
	bool empty() const{
		return rep.empty();
	}
	void swap(hash_multimap& hs) {
		rep.swap(hs);
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
	iterator find(const key_type& key){
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
	size_type bucket_count() const{
		return rep.bucket_count();
	}
};
}



#endif /* HASH_MULTIMAP_H_ */
