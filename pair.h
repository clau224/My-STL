/*
 * pair.h
 *
 *  Created on: 2018年7月1日
 *      Author: garvin
 */

#ifndef PAIR_H_
#define PAIR_H_

namespace MySTL{
template<class T1, class T2>
struct pair{
	typedef T1 first_type;
	typedef T2 second_type;
	first_type first;
	second_type second;
	pair():first(T1()),second(T2()){
	}
	pair(const T1& a, const T2& b):first(a),second(b){
	}
};
}



#endif /* PAIR_H_ */
