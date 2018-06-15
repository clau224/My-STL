/*
 * main.cpp
 *
 *  Created on: 2018年6月13日
 *      Author: garvin
 */

#include <iostream>
#include "vector.h"

int main() {
	MySTL::vector<int> test;
	std::cout << test.capacity() << std::endl;
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	std::cout << test.capacity() << std::endl;
	test.reserve(10);
	std::cout << test.capacity() << std::endl;

	for(int* item=test.begin();item!=test.end();item++){
		std::cout<<*item<<" ";
	}
	std::cout<<std::endl;

	test.resize(10, 0);
	for(int* item=test.begin();item!=test.end();item++){
			std::cout<<*item<<" ";
		}

	return 0;
}
