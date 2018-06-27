/*
 * Deque.cpp
 *
 *  Created on: 2018年6月27日
 *      Author: garvin
 */

#include <iostream>
#include "../deque.h"

using namespace std;

void show(const MySTL::deque<int> test){
	for(MySTL::deque<int>::iterator item = test.begin();item!=test.end();item++){
		cout<<*item<<" "<<&(*item)<<endl;
	}
}

void dequeTest(){
	cout << "\n\n********************************" << endl;
	cout << "**           deque            **" << endl;
	cout << "********************************" << endl;

	MySTL::deque<int> test;

	cout<<"向deque尾部依次插入1,2,3，向头部依次插入4,5"<<endl;
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	cout<<test.front()<<endl;
	test.push_front(4);
	cout<<test.front()<<endl;
	test.push_front(5);
	cout<<test.front()<<endl;
	test.push_back(6);
	test.push_front(7);
	show(test);
}
