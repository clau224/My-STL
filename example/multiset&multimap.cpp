/*
 * multiset&multimap.cpp
 *
 *  Created on: 2018年7月17日
 *      Author: garvin
 */

#include "../multiset.h"
#include "../multimap.h"
#include <iostream>

using namespace std;

void multisetTest(){
	cout << "\n\n********************************" << endl;
	cout << "**          multiset          **" << endl;
	cout << "********************************" << endl;

	typedef MySTL::multiset<int>::const_iterator iterator;
	MySTL::multiset<int> test1;

	cout << "向multiset中插入10，然后再次插入10" << endl;
	test1.insert(10);
	test1.insert(10);
	cout << "当前multiset的尺寸大小为:" << test1.size() << endl;
	cout << "向multiset中依次插入0,40,30,20" << endl;
	test1.insert(0);
	test1.insert(40);
	test1.insert(30);
	test1.insert(20);
	cout << "此时multiset的尺寸为:" << test1.size() << endl;
	cout << "multiset中的元素按中序遍历的顺序依次为:";
	for (iterator item = test1.begin(); item != test1.end();
			item++) {
		cout << *item << " ";
	}
	cout << endl;
}

void multimapTest(){
	cout << "\n\n********************************" << endl;
	cout << "**          multimap          **" << endl;
	cout << "********************************" << endl;
	MySTL::multimap<char, int> test2;
	typedef typename MySTL::multimap<char, int>::value_type value_type;
	typedef typename MySTL::multimap<char, int>::iterator iterator;

	cout<<"本例中，multimap的键值为char型，multimap的实值为int型"<<endl;
	cout<<"依次插入键值实值对: ";
	cout<<" e' 5, 'b' 2, 'd' 4, 'c' 3,'a' 1' "<<endl;
	test2['e'] = 5;
	test2['b'] = 2;
	test2['d'] = 4;
	test2['c'] = 3;
	test2['a'] = 1;
	cout<<"当前multimap的尺寸大小为:"<<test2.size()<<endl;
	cout<<"将multimap中键值为'a'的实值改为6"<<endl;
	test2['a'] = 6;
	cout<<"当前multimap中的键值对依次为:";
	for(iterator item2 = test2.begin(); item2!=test2.end(); item2++){
		cout<< (*item2).first <<" "<<(*item2).second<< "   ";
	}
	cout<<endl;
}
