/*
 * hashtable_node.h
 *
 *  Created on: 2018年8月6日
 *      Author: garvin
 */

#ifndef HASHTABLE_NODE_H_
#define HASHTABLE_NODE_H_

template<class Value>
struct hashtable_node{
	hashtable_node* next;
	Value val;
};



#endif /* HASHTABLE_NODE_H_ */
