/*
 * hashtable.h
 *
 *  Created on: 2018年8月6日
 *      Author: garvin
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "allocator.h"
#include "construct.h"
#include "algorithm.h"
#include "vector.h"
#include "pair.h"
#include "hash_fun.h"
#include "functional.h"
#include "iterator_hashtable.h"

namespace MySTL {
template<class Value, class Key, class HashFunction, class ExtractKey,
			class EqualKey, class Alloc=alloc>
class hashtable {
	public:
		typedef HashFunction 	hasher;
		typedef EqualKey 		key_equal;
		typedef Value 			value_type;
		typedef Key 			key_type;
		typedef size_t 			size_type;
		typedef ptrdiff_t   	difference_t;
		typedef hashtable_iterator<Value, Key, HashFunction, ExtractKey, EqualKey, Alloc> iterator;
		typedef const iterator 	const_iterator;
		typedef value_type* 	pointer;
		typedef const pointer   const_pointer;
		typedef value_type& 	reference;
		typedef const reference const_reference;

	private:
		typedef hashtable_node<Value> 		node;
		typedef simple_alloc<node, Alloc> 	node_allocator;
		hasher hash;
		key_equal equals;
		ExtractKey get_key;

		vector<node*, Alloc> buckets;
		size_type num_elements;

	private:
		node* new_node(const value_type& obj){
			node* nd = node_allocator::allocate();
			nd->next = NULL;
			construct(&nd->val, obj);
			return nd;
		}
		void delete_node(node* nd){
			destroy(&nd->val);
			node_allocator::deallocate(nd);
		}
		void initialize_buckets(size_type n){
			const size_type n_buckets = _next_prime(n);
			buckets.reserve(n_buckets);
			buckets.insert(buckets.end(), n_buckets, NULL);
		}
		size_type bkt_num(const value_type& obj, size_type n) const{
			return bkt_num_key(get_key(obj), n);
		}
		size_type bkt_num(const value_type& obj) const{
			return bkt_num_key(get_key(obj));
		}
		size_type bkt_num_key(const key_type& key) const{
			return bkt_num_key(key, buckets.size());
		}
		size_type bkt_num_key(const key_type& key, size_t n) const{
			return hash(key) % n;
		}

	private:
		#define _stl_num_primes 28
		const unsigned long _stl_prime_list[_stl_num_primes]=
		{
				53,		97, 	193,	389,	769,
				1543,	3079,	6151,	12289,	24593,
				49157,	98317,	196613,	393241,	786433,
				1572869,	3145739,	6291469,	12582917,	25165843,
				50331653,	100663319,	201326611,	402653189,	805306457,
				1610612741,	3221225473ul,	4294967291ul
		};

		inline unsigned long _next_prime(unsigned long n){
			const unsigned long *first = _stl_prime_list;
			const unsigned long *last = _stl_prime_list + _stl_num_primes;
			const unsigned long *pos = lower_bound(first, last, n);
			return pos == last ? *(last-1) : *pos;
		}

	private:
		void resize(size_type num_element_hint){
			const size_type old_n = buckets.size();
			if(num_element_hint > old_n){
				const size_type n = _next_prime(num_element_hint);
				if(n>old_n){
					vector<node*, Alloc> tmp(n, NULL);
					for(size_type bucket = 0; bucket<old_n; bucket++){
						node* first = buckets[bucket];
						while(first){
							size_type new_bucket = bkt_num(first->val, n);
							buckets[bucket] = first->next;
							first->next = tmp[new_bucket];
							tmp[new_bucket] = first;
							first = buckets[bucket];
						}
					}
					buckets.swap(tmp);
				}
			}
		}

		pair<iterator, bool> insert_unique_noresize(const value_type& obj){
			const size_type n = bkt_num(obj);
			node* first = buckets[n];
			for(node* cur = first; cur; cur = cur->next){
				if(equals(get_key(cur->val), get_key(obj)))
					return pair<iterator, bool>(iterator(cur, this), true);
			}
			node* tmp = new_node(obj);
			tmp->next = first;
			buckets[n] = tmp;
			++num_elements;
			return pair<iterator, bool>(iterator(tmp, this), true);
		}
		iterator insert_equal_noresize(const value_type& obj){
			const size_type n = bkt_num(obj);
			node* first = buckets[n];
			for(node* cur = first; cur; cur = cur->next){
				if(equals(get_key(cur->val), get_key(obj))){
					node* tmp = new_code(obj);
					tmp->next = cur->next;
					cur->next = tmp;
					++num_elements;
					return iterator(tmp, this);
				}
			}
			node* tmp = new_node(obj);
			tmp->next = first;
			buckets[n] = tmp;
			++num_elements;
			return iterator(tmp, this);
		}

	public:
		hashtable(size_type n, const HashFunction& hf, const EqualKey& eql) : hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0){
			initialize_buckets(n);
		}

		iterator begin() const {
			for(int i=0; i<buckets.size(); i++){
				if(buckets[i] != NULL)
					return iterator(buckets[i], this);
			}
			return end();
		}
		iterator end() const {
			return iterator(NULL, this);
		}
		size_type bucket_count() const{
			return buckets.size();
		}
		size_type size() const{
			return num_elements;
		}
		bool empty() const{
			return num_elements == 0;
		}

		hasher hash_funct() const {
			return this->hash;
		}
		key_equal key_eq() const {
			return this->equals;
		}

		pair<iterator, bool> insert_unique(const value_type& obj){
			resize(num_elements+1);
			return insert_unique_noresize(obj);
		}
		iterator insert_equal(const value_type& obj){
			resize(num_elements+1);
			return insert_equal_noresize(obj);
		}
		void clear(){
			for(size_type i = 0; i<buckets.size(); i++){
				node* cur = buckets[i];
				while(cur!=NULL){
					node* next = cur->next;
					delete_nod(cur);
					cur = next;
				}
				buckets[i] = NULL;
			}
			num_elements = 0;
		}
		iterator find(const key_type& val) const{
			size_type Index = bkt_num_key(val);
			for(node* n = buckets[Index]; n; n= n->next){
				if(equals(val, get_key(n->val)))
					return iterator(n, this);
			}
			return end();
		}
	};
}

#endif /* HASHTABLE_H_ */
