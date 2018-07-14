/*
 * set&map.cpp
 *
 *  Created on: 2018年7月14日
 *      Author: garvin
 */

#include "../set.h"
#include "../map.h"
#include <iostream>

using namespace std;

void setTest(){
	cout << "\n\n********************************" << endl;
	cout << "**             set            **" << endl;
	cout << "********************************" << endl;
	MySTL::set<int> test1;
	cout<<"向set中插入10，然后再次插入10"<<endl;
	test1.insert(10);
	test1.insert(10);
	cout<<"当前set的尺寸大小为:"<<test1.size()<<endl;
	cout<<test1.size();
	cout<<"向set中依次插入0,40,30,20"<<endl;
	test1.insert(0);
	test1.insert(40);
	test1.insert(30);
	test1.insert(20);
	cout<<"此时set的尺寸为:"<<test1.size()<<endl;
	cout<<"set中的元素按中序遍历的顺序依次为:";
	for(MySTL::set<int>::iterator item = test1.begin(); item!=test1.end(); item++){
		cout<<*item<<" ";
	}
	cout<<endl;
}

void mapTest(){
	cout << "\n\n********************************" << endl;
	cout << "**             map            **" << endl;
	cout << "********************************" << endl;
	MySTL::map<char, int> test2;
	typedef MySTL::map<char, int>::value_type value_type;

	cout<<"本例中，map的键值为char型，map的实值为int型"<<endl;
	cout<<"依次插入键值实值对: ";
	cout<<" 'a' 1, 'b' 2, 'd' 4, 'c' 3, 'e' 5 "<<endl;
	test2['a'] = 1;
	test2['b'] = 2;
	test2['d'] = 4;
	test2['c'] = 3;
	test2.insert( value_type('e', 5) );
	cout<<"当前map的尺寸大小为:"<<test2.size()<<endl;
	cout<<"将map中键值为'a'的实值改为6"<<endl;
	test2['a'] = 6;
	cout<<"当前map中的键值对依次为:";
	for(MySTL::map<char, int>::iterator item2 = test2.begin(); item2!=test2.end(); item2++){
		cout<< (*item2).first <<" "<<(*item2).second<< "   ";
	}
	cout<<endl;
}


