/*
 * heap.cpp
 *
 *  Created on: 2018年7月18日
 *      Author: garvin
 */

#include <iostream>
#include "../algorithm.h"
#include "../vector.h"

using namespace std;

void heapTest(){
	cout << "\n\n********************************" << endl;
	cout << "**            heap            **" << endl;
	cout << "********************************" << endl;
	MySTL::vector<int> vec;
	for(int i=1; i<=10; i++)
		vec.push_back(i);

	MySTL::make_heap(vec.begin(), vec.end());
	for(int i=0; i<vec.size(); i++)
		cout<<vec[i]<<" ";
	cout<<endl;

	MySTL::pop_heap(vec.begin(), vec.end());
	for(int i=0; i<vec.size(); i++)
			cout<<vec[i]<<" ";
		cout<<endl;

	MySTL::sort_heap(vec.begin(), vec.end());
	for(int i=0; i<vec.size(); i++)
		cout<<vec[i]<<" ";
	cout<<endl;

}
