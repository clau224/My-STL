/*
 * listnode.h
 *
 *  Created on: Jun 17, 2018
 *      Author: garvin
 */

#ifndef LISTNODE_H_
#define LISTNODE_H_

namespace MySTL {
template<class T>
struct list_node {
	typedef list_node* void_pointer;
	T value;
	void_pointer prev;
	void_pointer next;
};
}

#endif /* LISTNODE_H_ */
