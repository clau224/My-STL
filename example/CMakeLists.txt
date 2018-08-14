cmake_minimum_required(VERSION 3.5)

project(MySTL)

set(SOURCE_FILES 
	../alloc.cpp
	test.h
	Vector.cpp
	List.cpp
	Deque.cpp
	queue&stack.cpp
	RBtree.cpp
	set&map.cpp
	multiset&multimap.cpp
	heap.cpp
	priority_queue.cpp
	string.cpp
	hash_set&hash_map.cpp
	main.cpp
        )

add_executable(MySTL ${SOURCE_FILES})
