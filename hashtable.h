/*
 * hashtable.h
 *
 *  Created on: 2018年8月6日
 *      Author: garvin
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

template<class Value, class Key, class HashFunction, class ExtractKey, class EqualKey, class Alloc>
class hashtable{
public:
	typedef HashFunction hasher;
	typedef EqualKey key_equal;
	typedef size_t size_type;

private:
	hasher hash;
	key_equal equals;
	ExtractKey get_key;

};



#endif /* HASHTABLE_H_ */
