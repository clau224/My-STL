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
	T value;
	list_node* prev;
	list_node* next;
};
}

#endif /* LISTNODE_H_ */
