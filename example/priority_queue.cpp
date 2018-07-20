/*
 * priority_queue.cpp
 *
 *  Created on: 2018年7月20日
 *      Author: garvin
 */

#include "../priority_queue.h"
#include <iostream>

using namespace std;

void priority_queueTest(){
	cout << "\n\n********************************" << endl;
	cout << "**       priority_queue       **" << endl;
	cout << "********************************" << endl;

	cout<<"创建一个priority_queue, 依次放入1-10，堆顶为最大值"<<endl;
	MySTL::priority_queue<int> test;
	for(int i=1; i<=10; i++){
		test.push(i);
	}
	cout<<"依次将元素从priority_queue中弹出，值分别为:";
	while(!test.empty()){
		cout<<test.top()<<" ";
		test.pop();
	}
	cout<<endl;
}


