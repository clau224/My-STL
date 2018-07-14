/*
 * RBtree.cpp
 *
 *  Created on: 2018年7月8日
 *      Author: garvin
 */

#include <iostream>
#include "../rbtree.h"
#include "../functional.h"

using namespace std;

void rbtreeTest(){
	cout << "\n\n********************************" << endl;
	cout << "**           rbtree           **" << endl;
	cout << "********************************" << endl;

	MySTL::rbtree<int, int, MySTL::identity<int>, MySTL::less<int> > test;
	MySTL::rbtree<int, int, MySTL::identity<int>, MySTL::less<int> >::iterator item;

	cout<<"向rbtree中插入10, 然后再次插入10"<<endl;
	test.insert_unique(10);
	test.insert_unique(10);
	cout<<"此时rbtree的尺寸为:"<<test.size()<<endl;
	cout<<"再次向rbtree中依次插入40,20,30,0"<<endl;
	test.insert_unique(40);
	test.insert_unique(20);
	test.insert_unique(30);
	test.insert_unique(0);
	cout<<"此时rbtree的尺寸为:"<<test.size()<<endl;
	cout<<"此时rbtree的遍历结果(中序)为:";
	for(item = test.begin(); item!=test.end(); item++){
		cout<<*item<<" ";
	}
	cout<<endl;
	cout<<"将rbtree清空,此时的尺寸大小为:";
	test.clear();
	cout<<"将rbtree清空,此时的尺寸大小为:"<<test.size()<<endl;
}

