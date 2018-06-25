/*
 * iterator_deque.h
 *
 *  Created on: 2018年6月25日
 *      Author: garvin
 */

#ifndef ITERATOR_DEQUE_H_
#define ITERATOR_DEQUE_H_

namespace MySTL{
template<class T, class Ref, class Ptr, size_t BufSize>
struct deque_iterator{
	typedef deque_iterator<T, T&, T*> iterator;
	typedef deque_iterator<const T, const T&, const T*> const_iterator;

};
}



#endif /* ITERATOR_DEQUE_H_ */
