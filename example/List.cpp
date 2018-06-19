/*
 * List.cpp
 *
 *  Created on: Jun 19, 2018
 *      Author: garvin
 */

#include <iostream>
#include "../list.h"

using namespace std;

void listTest(){
	cout << "\n\n********************************" << endl;
	cout << "**            list            **" << endl;
	cout << "********************************" << endl;

	MySTL::list<int> test;
	MySTL::list<int>::iterator item;
	MySTL::list<int> test2;
	MySTL::list<int>::iterator item2;

	cout<<"list当前尺寸大小为:"<<test.size()<<endl;
	cout<<"在list的尾部放入2,3"<<endl;
	test.push_back(2);
	test.push_back(3);
	cout<<"list当前尺寸大小为:"<<test.size()<<endl;
	cout<<"在list的头部放入4,5,6"<<endl;
	test.push_front(4);
	test.push_front(5);
	test.push_front(6);

	cout<<"当前list中，元素依次为:";
	for(item=test.begin();item!=test.end();item++){
		cout<<*item<<" ";
	}
	cout<<endl;

	cout<<"将list由小到大排列"<<endl;
	test.sort();

	cout<<"当前list中，元素依次为:";
		for(item=test.begin();item!=test.end();item++){
			cout<<*item<<" ";
		}
		cout<<endl;

	cout<<"创建list2,向其中插入1,2,3,4"<<endl;
	test2.push_back(1);
	test2.push_back(2);
	test2.push_back(3);
	test2.push_back(4);

	cout<<"将list1和list2合并"<<endl;
	test.merge(test2);

	cout<<"当前list中，元素依次为:";
		for(item=test.begin();item!=test.end();item++){
			cout<<*item<<" ";
		}
		cout<<endl;
}


