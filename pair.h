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
	T1 first_type;
	T2 second_type;
	pair():first_type(T1()),second_type(T2()){
	}
	pair(const T1& a, const T2& b):first_type(a),second_type(b){
	}
};
}



#endif /* PAIR_H_ */
