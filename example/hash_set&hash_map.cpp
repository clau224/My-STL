/*
 * hash_set&hash_map.cpp
 *
 *  Created on: 2018年8月8日
 *      Author: garvin
 */

#include "../hash_set.h"
#include "../hash_map.h"
#include <iostream>
#include <string.h>

using namespace std;

namespace MySTL{
struct eqstr{
	bool operator() (const char* s1, const char* s2) const{
		return strcmp(s1, s2) == 0;
	}
};
}

void hash_setTest(){
	cout << "\n\n********************************" << endl;
	cout << "**          hash_set          **" << endl;
	cout << "********************************" << endl;
	MySTL::hash_set<const char*, MySTL::hash<const char*>, MySTL::eqstr> hashset;
	cout<<"向hashset中依次插入“hello”, “hello”，“world”~"<<endl;
	hashset.insert("hello");
	hashset.insert("hello");
	hashset.insert("world");
	cout<<"此时hashset的size为:"<<hashset.size()<<endl;
	cout<<"查找hashset中是否有hello,world”"<<endl;
	if(hashset.find("hello,world") == hashset.end())
		cout<<"没有找到“hello,world”"<<endl;
	else
		cout<<"找到“hello,world”！"<<endl;
	cout<<"查找hashset中是否有hello”"<<endl;
	MySTL::hash_set<const char*, MySTL::hash<const char*>, MySTL::eqstr>::iterator item = hashset.find("hello");
	if(item == hashset.end())
		cout<<"没有找到“hello”"<<endl;
	else
		cout<<"找到“hello”！"<<endl;
	cout<<"如果找到”hello“,将其删除"<<endl;
	if(item!=hashset.end())
		hashset.erase(item);
	cout<<"此时hashset的size为:"<<hashset.size()<<endl;
}

void hash_mapTest(){
	cout << "\n\n********************************" << endl;
	cout << "**          hash_map          **" << endl;
	cout << "********************************" << endl;
	MySTL::hash_map<const char*, int, MySTL::hash<const char*>, MySTL::eqstr> hashmap;
	hashmap["hello"] = 3;
	hashmap["world"] = 2;
	hashmap["i"] = 1;
	hashmap["am"] = 4;
	hashmap["cute"] = 5;
	cout<<"此时hashset的size为:"<<hashmap.size()<<endl;
	MySTL::hash_map<const char*, int, MySTL::hash<const char*>, MySTL::eqstr>::iterator item1 = hashmap.begin();
	MySTL::hash_map<const char*, int, MySTL::hash<const char*>, MySTL::eqstr>::iterator item2 = hashmap.end();
	cout<<"遍历hashmap的结果为:"<<endl;
	for(; item1!=item2; item1++){
		cout<<(*item1).first<<" "<<(*item1).second<<" | ";
	}
	cout<<endl;
	cout<<"将”am“除去"<<endl;
	item1 = hashmap.find("am");
	hashmap.erase(item1);
	item1 = hashmap.begin(), item2 = hashmap.end();
	cout << "遍历hashmap的结果为:" << endl;
	for (; item1 != item2; item1++) {
		cout << (*item1).first << " " << (*item1).second << " | ";
	}
	cout << endl;
}
