/*
 * iterator_rbtree.h
 *
 *  Created on: 2018年6月30日
 *      Author: garvin
 */

#ifndef ITERATOR_RBTREE_H_
#define ITERATOR_RBTREE_H_

#include "iterator.h"

namespace MySTL{
typedef bool _rbtree_color_type;
const _rbtree_color_type _rbtree_red=false;
const _rbtree_color_type _rbtree_black=true;

struct _rbtree_node_base{
	typedef _rbtree_color_type color_t;
	typedef _rbtree_node_base* base_ptr;

	color_t color;
	base_ptr parent;
	base_ptr left;
	base_ptr right;

	static base_ptr minimum(base_ptr b){
		while(b->left!=NULL){
			b=b->left;
		}
		return b;
	}
	static base_ptr maximum(base_ptr b){
		while(b->right!=NULL){
			b=b->right;
		}
		return b;
	}
};

template<class Value>
struct _rbtree_node : public _rbtree_node_base{
	typedef _rbtree_node<Value>* link_type;
	Value value_field;
};

struct _rbtree_base_iterator{
	typedef _rbtree_node_base::base_ptr base_ptr;
	typedef bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t differnece_type;
	base_ptr node;

	void increment(){
		if(node->right!=NULL){
			node=node->right;
			while(node->left!=NULL)
				node=node->left;
		}
		else{
			base_ptr tmp = node->parent;
			while(tmp->right==node && tmp->parent!=NULL){
				node = node->parent;
				tmp = tmp->parent;
			}
			if(node->right!=tmp)
				node = tmp;
		}
	}
	void decrement(){
		if(node->color == _rbtree_red && node->parent->parent==node)
			node = node->right;
		else if(node->left != NULL){
			base_ptr b = node->left;
			while(b->right!=NULL)
				b = b->right;
			node = b;
		}
		else{
			base_ptr b = node->parent;
			while(b->left==node)
			{
				node = b;
				b=b->parent;
			}
			node = b;
		}
	}
};

template<class Value, class Ref, class Ptr>
struct _rbtree_iterator: public _rbtree_base_iterator {
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef _rbtree_iterator<Value, Value&, Value*> iterator;
	typedef _rbtree_iterator<Value, const Value&, const Value*> const_iterator;
	typedef _rbtree_iterator<Value, Ref, Ptr> self;
	typedef _rbtree_node<Value>* link_type;

	_rbtree_iterator() {
	}
	_rbtree_iterator(link_type x) {
		node = x;
	}
	_rbtree_iterator(const iterator& item) {
		node = item.node;
	}

	reference operator*() const {
		return link_type(node)->value_field;
	}
	pointer operator->() const {
		return &(operator*());
	}

	self& operator++() {
		increment();
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}
	self& operator--() {
		decrement();
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
		--*this;
		return tmp;
	}

	bool operator==(const iterator& item){
		return this->node == item.node;
	}
	bool operator!=(const iterator& item){
		return this->node != item.node;
	}
};

}



#endif /* ITERATOR_RBTREE_H_ */
