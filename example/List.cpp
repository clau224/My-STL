/*
 * List.cpp
 *
 *  Created on: Jun 19, 2018
 *      Author: garvin
 */

#include <iostream>
#include "../list.h"

using namespace std;

void show(MySTL::list<int> &test){
	MySTL::list<int>::iterator item;
	for(item = test.begin() ; item != test.end() ; item++){
		cout << *item << " ";
	}
}

void listTest(){
	cout << "\n\n********************************" << endl;
	cout << "**            list            **" << endl;
	cout << "********************************" << endl;

	MySTL::list<int> test;
	MySTL::list<int>::iterator item, item1, item2;

	cout<<"list当前尺寸大小为:"<<test.size()<<endl;
	cout<<"在list的尾部放入2,3"<<endl;
	test.push_back(2);
	test.push_back(3);
	cout<<"list当前尺寸大小为:"<<test.size()<<endl;
	cout<<"在list的头部放入4,5,6"<<endl;
	test.push_front(4);
	test.push_front(5);
	test.push_front(6);

	cout<<"当前list中，元素依次为:                           ";
	show(test);
	cout<<endl;

	cout<<"对list进行倒置:                                   ";
	test.reverse();
	show(test);
	cout<<endl;

	cout<<"将begin后的第3和第4个list节点插入到begin节点前    ";
	test.transfer(test.begin(), test.begin()+2, test.begin()+4);
	show(test);
	cout<<endl;

	cout<<"将list中的节点按照从大到小排序:                   ";
	test.sort();
	show(test);
	cout<<endl;

	cout<<"创建一个节点依次为1，2，3，4，5的链表"<<endl;
	MySTL::list<int> test2;
	test2.push_back(1);
	test2.push_back(2);
	test2.push_back(3);
	test2.push_back(4);
	test2.push_back(5);

	cout<<"将两个已经升序排列的链表合并为一个链表:\t";
	test.merge(test2);
	show(test);
	cout<<endl;

	cout<<"移除数值为2的节点:\t";
	test.remove(2);
	show(test);
	cout<<endl;
}


