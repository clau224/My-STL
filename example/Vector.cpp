/*
 * vector.cpp
 *
 *  Created on: Jun 16, 2018
 *      Author: garvin
 */


#include "../vector.h"
#include<iostream>


void vectorTest() {
	std::cout<<"********************************"<<std::endl;
	std::cout<<"**           vector           **"<<std::endl;
	std::cout<<"********************************"<<std::endl;

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

	for (int* item = test.begin(); item != test.end(); item++) {
		std::cout << *item << " ";
	}
	std::cout << std::endl;

	test.resize(10, 0);
	for (int* item = test.begin(); item != test.end(); item++) {
		std::cout << *item << " ";
	}
	std::cout << std::endl;
}

