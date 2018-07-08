/*
 * rbtree.h
 *
 *  Created on: 2018年7月1日
 *      Author: garvin
 */

#ifndef RBTREE_H_
#define RBTREE_H_

#include "iterator_rbtree.h"
#include "construct.h"
#include "allocator.h"
#include "pair.h"

namespace MySTL{
template<class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
class rbtree{
protected:
	typedef void* void_pointer;
	typedef _rbtree_node_base* base_ptr;
	typedef _rbtree_node<Value> rbtree_node;
	typedef simple_alloc<rbtree_node, Alloc> rbtree_node_allocator;

public:
	typedef Key key_type;
	typedef Value value_type;
	typedef Value* pointer;
	typedef Value& reference;
	typedef const Value* const_pointer;
	typedef const Value& const_reference;
	typedef rbtree_node* link_type;
	typedef _rbtree_color_type color_t;

	typedef size_t size_type;
	typedef ptrdiff_t diference_type;

protected:
	link_type getnode(){
		return rbtree_node_allocator::allocate();
	}
	void put_node(link_type p){
		rbtree_node_allocator::deallocate(p);
	}

	link_type create_node(const value_type& x){
		link_type tmp = getnode();
		construct(&tmp->value_field, x);
		return tmp;
	}
	link_type clone_node(link_type x){
		link_type tmp = create_node(x->value_field);
		tmp->color=x->color;
		tmp->left = NULL;
		tmp->right = NULL;
		return tmp;
	}
	void destroy_node(link_type x){
		destroy(&x->value_field);
		put_node(x);
	}

protected:
	size_type node_count;
	link_type header;
	Compare key_compare;

	link_type& root() const {
		return (link_type&)header->parent;
	}
	link_type& leftmost() const{
		return (link_type&)header->left;
	}
	link_type& rightmost() const{
		return (link_type&)header->right;
	}

	static link_type& left(link_type x){
		return (link_type&)x->left;
	}
	static link_type& right(link_type x){
		return (link_type&)x->right;
	}
	static link_type& parent(link_type x){
		return (link_type&)x->parent;
	}
	static color_t& color(link_type x){
		return (color_t&)x->color;
	}
	static reference value(link_type x){
		return ((link_type)x)->value_field;
	}
	static const Key& key(link_type x){
		return KeyOfValue() (value(x));
	}

	static link_type& left(base_ptr x) {
		return (link_type&) (x->left);
	}
	static link_type& right(base_ptr x) {
		return (link_type&) (x->right);
	}
	static link_type& parent(base_ptr x) {
		return (link_type&) (x->parent);
	}
	static reference value(base_ptr x) {
		return ((link_type) x)->value_field;
	}
	static const Key& key(base_ptr x) {
		return KeyOfValue()(value(link_type(x)));
	}
	static color_t& color(base_ptr x) {
		return (color_t&) (link_type(x)->color);
	}

	static link_type minimum(link_type x){
		return (link_type) _rbtree_node_base::minimum(x);
	}
	static link_type maximum(link_type x){
		return (link_type) _rbtree_node_base::maximum(x);
	}

public:
	typedef _rbtree_iterator<value_type, reference, pointer> iterator;
	typedef _rbtree_iterator<value_type, const_reference, const_pointer> const_iterator;

private:
	iterator _insert(base_ptr xx, base_ptr yy, const Value& v) {
		link_type x = (link_type) xx;
		link_type y = (link_type) yy;
		link_type z;
		z = create_node(v);
		if (y == header || x != NULL || key_compare(KeyOfValue()(v), key(y))) {
			left(y) = z;
			if (y == header) {
				root() = z;
				rightmost() = z;
			} else if (y == leftmost()) {
				leftmost() = z;
			}
		} else {
			right(y) = z;
			if (y == rightmost()) {
				rightmost() = z;
			}
		}
		parent(z) = y;
		left(z) = NULL;
		right(z) = NULL;
		_rebalance(z, header->parent);
		++node_count;
		return iterator(z);
	}

	void init(){
		header = getnode();
		color(header) = _rbtree_red;
		root() = 0;
		leftmost() = header;
		rightmost() = header;
	}

public:
	rbtree(const Compare& comp = Compare()) :node_count(0), key_compare(comp) {
		init();
	}
	~rbtree(){
		clear();
		put_node(header);
	}
	rbtree<Key, Value, KeyOfValue, Compare, Alloc>& operator = (const rbtree<Key, Value, KeyOfValue, Compare, Alloc>& x);

public:
	iterator begin(){
		return leftmost();
	}
	iterator end(){
		return rightmost();
	}
	bool empty(){
		return node_count == 0;
	}
	size_type size() const{
		return node_count;
	}
	Compare key_comp() const{
		return key_compare;
	}
	void clear(){
		/*while(!empty()){
			destroy_node((link_type)begin().node);
		}*/
	}

	iterator insert_equal(const Value& v){
		link_type y =header;
		link_type x = root();
		while( x!=NULL ){
			y = x;
			x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
		}
		return _insert(x, y, v);
	}

	pair<iterator, bool> insert_unique(const Value& v){
		link_type y = header;
		link_type x = root();
		bool comp = true;
		while( x!=NULL ){
			y =x;
			comp = key_compare(KeyOfValue()(v), key(x));
			x = comp ? left(x) : right(x);
		}
		iterator j = iterator(y);
		if(comp){
			if(j == begin())
				return pair<iterator, bool> (_insert(x, y, v), true);
			else
				--j;
		}
		if(key_compare(key(j.node), KeyOfValue()(v)))
			return pair<iterator, bool> (_insert(x, y, v), true);
		return pair<iterator, bool> (j, false);
	}

protected:
	inline void _rebalance(_rbtree_node_base* x, _rbtree_node_base*& root){
		x->color = _rbtree_red;
		while(x!=root && x->parent->color==_rbtree_red){
			if(x->parent == x->parent->parent->left){
				_rbtree_node_base* y = x->parent->parent->right;
				if(y!=NULL && y->color==_rbtree_red){
					x->parent->color = _rbtree_black;
					y->color = _rbtree_black;
					x->parent->parent->color = _rbtree_red;
					x = x->parent->parent;
				}
				else{
					if(x == x->parent->parent){
						x = x->parent;
						_rotate_left(x, root);
					}
					x->parent->color = _rbtree_black;
					x->parent->parent->color = _rbtree_red;
					_rotate_right(x->parent->parent, root);
				}
			}
			else{
				_rbtree_node_base* y = x->parent->parent->left;
				if(y!=NULL && y->color==_rbtree_red){
					x->parent->color = _rbtree_black;
					y->color = _rbtree_black;
					x->parent->parent->color = _rbtree_red;
					x = x->parent->parent;
				}
				else{
					if(x == x->parent->left){
						x = x->parent;
						_rotate_right(x, root);
					}
					x->parent->color = _rbtree_black;
					x->parent->parent->color = _rbtree_red;
					_rotate_left(x->parent->parent, root);
				}
			}
		}
		root->color = _rbtree_black;
	}

	inline void _rotate_left(_rbtree_node_base* x, _rbtree_node_base*& root){
		_rbtree_node_base* y = x->right;
		x->right = y->left;
		if(y->left != 0)
			y->left->parent = x;
		y->parent = x->parent;

		if(x == root)
			root = y;
		else if(x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	inline void _rotate_right(_rbtree_node_base* x, _rbtree_node_base*& root){
		_rbtree_node_base* y = x->left;
		x->left = y->right;
		if(y->right != NULL)
			y->right->parent = x;
		y->parent = x->parent;
		if(x == root)
			root = y;
		else if(x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}


public:
	iterator find(const Key& k){
		link_type y = header;
		link_type x = root();
		while(x!=NULL){
			if(!key_compare(key(x), k)){
				y = x;
				x = left(x);
			}
			else
				x = right(x);
		}
		iterator j = iterator(y);
		return (j == end() || key_compare(k, key(j.node))) ? end(): j;
	}
};
}



#endif /* RBTREE_H_ */
