/*
 * test.h
 *
 *  Created on: Jun 16, 2018
 *      Author: garvin
 */

#ifndef EXAMPLE_TEST_H_
#define EXAMPLE_TEST_H_

//对容器vector进行测试
void vectorTest();
//对双向链表list进行测试
void listTest();
//对双向队列进行测试
void dequeTest();
//对队列和栈进行测试
//分别以双向队列和双向链表作为底层容器
void queueTest();
void stackTest();
//对红黑树进行测试
void rbtreeTest();
//对set进行测试
void setTest();
//对map进行测试
void mapTest();
//对multiset进行测试
void multisetTest();
//对multimap进行测试
void multimapTest();
//对heap进行测试
void heapTest();
//对priority_queue进行测试
void priority_queueTest();

#endif /* EXAMPLE_TEST_H_ */
