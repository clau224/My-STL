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
		cout<<*item<<" ";
	}
}

void dequeTest(){
	cout << "\n\n********************************" << endl;
	cout << "**           deque            **" << endl;
	cout << "********************************" << endl;

	MySTL::deque<int> test;

	cout<<"向deque尾部依次插入1,2,3，向头部依次插入4,5:\n";
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_front(4);
	test.push_front(5);
	cout<<"此时duque内元素依次为:";
	show(test);
	cout<<"  "<<"此时deque的size为:"<<test.size();
	cout<<endl;

	cout<<"将deque后四个pop出来,此时deque内的元素依次为:";
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	show(test);
	cout<<endl;

	test.clear();
	cout<<"将deque清空后，size为:"<<test.size();
	cout<<endl;
}
