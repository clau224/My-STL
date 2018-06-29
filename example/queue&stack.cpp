/*
 * queue&stack.cpp
 *
 *  Created on: 2018年6月28日
 *      Author: garvin
 */

#include "../queue.h"
#include "../stack.h"
#include "../list.h"
#include <iostream>

using namespace std;

void queueTest(){
	cout << "\n\n********************************" << endl;
	cout << "**           queue            **" << endl;
	cout << "********************************" << endl;

	cout<<"***以默认的deque为底层容器***"<<endl;
	MySTL::queue<int> q1;
	cout<<"依次向queue中插入1,2,3,4,5";
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	q1.push(5);

	cout<<"当前队列的首元素为:"<<q1.front()<<endl;
	cout<<"弹出队列首元素"<<endl;
	q1.pop();
	cout<<"当前队列的首元素为:"<<q1.front()<<"当前队列的尾元素为:" << q1.back() << endl;

	cout << "***以list为底层容器***" << endl;
	MySTL::queue<int, MySTL::list<int> > q2;
	cout << "依次向queue中插入6,7,8,9,10";
	q2.push(6);
	q2.push(7);
	q2.push(8);
	q2.push(9);
	q2.push(10);

	cout << "当前队列的首元素为:" << q2.front() << endl;
	cout << "弹出队列首元素" << endl;
	q2.pop();
	cout << "当前队列的首元素为:" << q2.front() <<"当前队列的尾元素为:"<<q2.back()<< endl;
}

void stackTest(){
	cout << "\n\n********************************" << endl;
	cout << "**           stack            **" << endl;
	cout << "********************************" << endl;

	cout<<"***以默认的deque为底层容器***"<<endl;
	MySTL::stack<int> s1;
	cout<<"依次向queue中插入1,2,3,4,5";
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	s1.push(5);

	cout<<"当前栈的栈顶元素为:"<<s1.top()<<endl;
	cout<<"弹出栈顶元素"<<endl;
	s1.pop();
	cout<<"当前栈的栈顶元素为:"<<s1.top()<< endl;

	cout << "***以list为底层容器***" << endl;
	MySTL::stack<int, MySTL::list<int> > s2;
	cout << "依次向queue中插入6,7,8,9,10";
	s2.push(6);
	s2.push(7);
	s2.push(8);
	s2.push(9);
	s2.push(10);

	cout << "当前栈的栈顶元素为:" << s2.top() << endl;
	cout << "弹出栈顶元素" << endl;
	s2.pop();
	cout << "当前栈的栈顶元素为:" << s2.top()<< endl;
}
