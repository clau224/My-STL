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
	MySTL::list<int>::iterator item, item1, item2;
	MySTL::list<int> test2;

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
	for(item=test.begin();item!=test.end();item++){
			cout<<*item<<" ";
		}
		cout<<endl;

	cout<<"对list进行倒置:                                   ";
	test.reverse();
	for(item=test.begin();item!=test.end();item++){
			cout<<*item<<" ";
		}
	cout<<endl;

	cout<<"将begin后的第2-3的list节点插入到begin节点前       ";
	test.transfer(test.begin(), test.begin()+2, test.begin()+4);
	for(item=test.begin();item!=test.end();item++){
				cout<<*item<<" ";
			}
	cout<<endl;

	cout<<"将list中的节点按照从大到小排序:                   ";
	test.sort();
	for(item=test.begin();item!=test.end();item++){
					cout<<*item<<" ";
				}
		cout<<endl;
}


