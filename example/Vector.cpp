/*
 * vector.cpp
 *
 *  Created on: Jun 16, 2018
 *      Author: garvin
 */

#include<iostream>
#include "../vector.h"

void vectorTest() {
	std::cout << "\n\n********************************" << std::endl;
	std::cout << "**           vector           **" << std::endl;
	std::cout << "********************************" << std::endl;

	MySTL::vector<int> test;

	std::cout << "vector当前容量为: " << test.capacity() << std::endl;
	std::cout << "依次放入1，2,3,4,5" << std::endl;
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	std::cout << "vector当前容量为: " << test.capacity() << std::endl;

	std::cout << "调用reserve函数，将容量设置为10..." << std::endl;
	test.reserve(10);
	std::cout << "vector当前容量为: " << test.capacity() << std::endl;

	MySTL::vector<int>::iterator item;
	std::cout << "此时vector内数据依次为: ";
	for (item = test.begin(); item != test.end(); item++) {
		std::cout << *item << " ";
	}
	std::cout << std::endl;

	std::cout << "调用resize函数，resize（10， 0）" << std::endl;
	test.resize(10, 0);
	std::cout << "此时vector内数据依次为: ";
	for (item = test.begin(); item != test.end(); item++) {
		std::cout << *item << " ";
	}
	std::cout << std::endl << std::endl << std::endl;

}

