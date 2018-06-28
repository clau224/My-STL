/*
 * queue.h
 *
 *  Created on: 2018年6月28日
 *      Author: garvin
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "deque.h"

namespace MySTL{
template<class T, class Sequence = deque<T> >
class queue{
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
protected:
	Sequence seq;
public:
	bool empty(){
		return seq.empty();
	}
	size_type size() const{
		return seq.size();
	}
	reference front() const{
		return seq.front();
	}
	reference back(){
		return seq.back();
	}
	void push(const value_type& x){
		seq.push_back(x);
	}
	void pop(){
		seq.pop_front();
	}
};
}



#endif /* QUEUE_H_ */
