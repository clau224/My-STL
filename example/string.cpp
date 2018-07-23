/*
 * string.cpp
 *
 *  Created on: 2018年7月22日
 *      Author: garvin
 */

#include <iostream>
#include "../string.h"

using namespace std;

void stringTest(){
	cout << "\n\n********************************" << endl;
	cout << "**           string           **" << endl;
	cout << "********************************" << endl;

	cout<<"生成string对象test1为‘aaa'，然后使用复制构造函数，生成test2(复制test1)"<<endl;
	MySTL::string test1(3, 'a');
	MySTL::string test2(test1);
	cout<<"在test2后面追加字符串’bb‘"<<endl;
	test2.append(2, 'b');
	cout<<"此时test1为:"<<test1<<"  test2为:"<<test2<<endl;
	cout<<"string对象test3为test1与test2的相接"<<endl;
	MySTL::string test3;
	test3 += test1;
	test3 += test2;
	cout<<"此时test3的尺寸为:"<<test3.size()<<"  此时test3的内容为:"<<test3<<endl;
	cout<<"将test3中，第6个字符到第8个字符(不含)删除"<<endl;
	test3.erase(test3.begin()+5,test3.begin()+7);
	cout<<"此时test3的尺寸为:"<<test3.size()<<"  此时test3的内容为:"<<test3<<endl;
	cout<<"将test3中，第3个字符到第5个字符(替换)为'cde'"<<endl;
	test3.replace(test3.begin()+2, test3.begin()+4, "cde");
	cout<<"此时test3的内容为:"<<test3<<endl;
}


