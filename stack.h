/*
 * stack.h
 *
 *  Created on: 2018年6月28日
 *      Author: garvin
 */

#ifndef STACK_H_
#define STACK_H_

#include "deque.h"

namespace MySTL{
template<class T, class Sequence = deque<T> >
class stack{
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;

protected:
	Sequence seq;
public:
	bool empty() const{
		return seq.empty();
	}
	size_type size() const{
		return seq.size();
	}
	reference top() const{
		return seq.back();
	}
	void push(const value_type& x){
		seq.push_back(x);
	}
	void pop(){
		seq.pop_back();
	}
};
}



#endif /* STACK_H_ */
