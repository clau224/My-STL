/*
 * algorithm.h
 *
 *  Created on: 2018年6月12日
 *      Author: garvin
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "iterator.h"
#include "typetraits.h"
#include <string.h>

namespace MySTL {
template<class T>
T max(T t1, T t2) {
	return t1 > t2 ? t1 : t2;
}
template<class T>
T min(T t1, T t2) {
	return t1 < t2 ? t1 : t2;
}

template<class Iterator, class T>
void fill(Iterator first, Iterator last, const T& t) {
	while (first != last) {
		*first = t;
		first++;
	}
}

template<class T>
void fill(char* first, char* last, const char& c) {
	memset(first, static_cast<unsigned char>(c), last - first);
}
template<class T>
void fill(wchar_t* first, wchar_t* last, const wchar_t& wc) {
	memset(first, static_cast<unsigned char>(wc),
			(last - first) * sizeof(wchar_t));
}

template<class Iterator, class Size, class T>
Iterator fill_n(Iterator first, Size n, const T& t) {
	while (n--) {
		*first = t;
		++first;
	}
	return first;
}

template<class Size>
char* fill_n(char* first, Size n, const char* c) {
	memset(first, static_cast<unsigned char>(c), n);
	first += n;
	return first;
}

template<class Size>
wchar_t* fill_n(char* first, Size n, const wchar_t* wc) {
	memset(first, static_cast<unsigned char>(wc), n * sizeof(wchar_t));
	first += n;
	return first;
}

template<class InputIterator, class Distance>
void _advance(InputIterator& it, Distance n, input_iterator_tag) {
	assert(n >= 0);
	while (n--) {
		++it;
	}
}
template<class BidirectionIterator, class Distance>
void _advance(BidirectionIterator& it, Distance n, bidirectional_iterator_tag) {
	if (n < 0) {
		while (n++) {
			--it;
		}
	} else {
		while (n--) {
			++it;
		}
	}
}
template<class RandomIterator, class Distance>
void _advance(RandomIterator& it, Distance n, random_access_iterator_tag) {
	if (n < 0) {
		it -= (-n);
	} else {
		it += n;
	}
}

template<class InputIterator, class Distance>
void advance(InputIterator& it, Distance n) {
	typedef typename iterator_traits<InputIterator>::iterator_category iterator_category;
	_advance(it, n, iterator_category());
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type _distance(Iterator first,
		Iterator last, input_iterator_tag) {
	typename iterator_traits<Iterator>::difference_type d = 0;
	while (first != last) {
		d++;
		first++;
	}
	return d;
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type _distance(Iterator first,
		Iterator last, random_access_iterator_tag) {
	return last - first;
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type distance(Iterator first,
		Iterator last) {
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	return _distance(first, last, iterator_category());
}

template<class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last,
		OutputIterator result, _true_type) {
	typename iterator_traits<InputIterator>::difference_type d = distance(first,
			last);
	memcpy(result, first, sizeof(*first) * d);
	advance(result, d);
	return result;
}

template<class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last,
		OutputIterator result, _false_type) {
	while (first != last) {
		*result = *first;
		first++;
		result++;
	}
	return result;
}

template<class InputIterator, class OutputIterator, class T>
OutputIterator _copy(InputIterator first, InputIterator last,
		OutputIterator result, T*) {
	typedef typename _type_traits<T>::is_POD_type is_pod;
	return __copy(first, last, result, is_pod());
}

template<class InputIterator, class OutputIterator>
OutputIterator copy_backward(InputIterator first, InputIterator last,
		OutputIterator result) {
	return _copy(first, last, result - (last - first), value_type(first));
}

template<class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last,
		OutputIterator result) {
	return _copy(first, last, result, value_type(first));
}


/*
 * 2018-7-18
 * 下面是heap算法部分
 */

template<class iterator>
inline void push_heap(iterator first, iterator last){
	_push_heap_aux(first, last, difference_type(first), value_type(first));
}

template<class iterator, class Distance, class T>
inline void _push_heap_aux(iterator first, iterator last, Distance*, T*){
	_push_heap(first, Distance(last-first+1), Distance(0), T(*(last-1)));
}

template<class iterator, class Distance, class T>
void _push_heap(iterator first, Distance holeIndex, Distance topIndex, T value) {
	Distance parent = (holeIndex-1)/2;
	while(holeIndex>topIndex && *(first+parent)<value) {
		*(first+holeIndex) = *(first+parent);
		holeIndex = parent;
		parent = (holeIndex-1)/2;
	}
	*(first + holeIndex) = value;
}

template<class iterator>
inline void pop_heap(iterator first, iterator last){
	_pop_head_aux(first, last, value_type(first));
}

template<class iterator, class T>
inline void _pop_heap_aux(iterator first, iterator last, T*){
	_pop_heap(first, last-1, last-1, T(*(last-1)));
}

template<class iterator, class T, class Distance>
inline void _pop_heap(iterator first, iterator last, iterator result, T value, Distance*){
	*result = *first;
	_adjust_heap(first, Distance(0), Distance(last-first), value);
}

template<class iterator, class Distance, class T>
void _adjust_heap(iterator first, Distance holeIndex, Distance len, T value){
	Distance topIndex = holeIndex;
	Distance secondChild = 2*holeIndex + 2;
	while(secondChild < len){
		if(*(first + secondChild) < *(first+(secondChild-1)))
			secondChild--;
		*(first+holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild+1);
	}
	if(secondChild == len){
		*(first+holeIndex) = *(first + (secondChild-1));
		holeIndex = secondChild-1;
	}
	_push_heap(first, holeIndex, topIndex, value);
}

template<class iterator>
void sort_heap(iterator first, iterator last){
	while(last-first > 1)
		pop_heap(first, last--);
}

template<class iterator, class T, class Distance>
void _make_heap(iterator first, iterator last, T*, Distance*){
	if(last - first < 2)
		return;
	Distance len = last - first;
	Distance parent = (len-2)/2;
	while(true){
		_adjust_heap(first, parent, len, T(*(first+parent)));
		if(parent == 0)
			return;
		parent--;
	}
}

template<class iterator>
inline void make_heap(iterator first, iterator last){
	_make_heap(first, last, value_type(first), difference_type(first));
}

}

#endif /* ALGORITHM_H_ */
