cmake_minimum_required(VERSION 3.5)

project(MySTL)

set(SOURCE_FILES 
	../algorithm.h
	../alloc.cpp
	../alloc.h
	../allocator.h
	../construct.h
	../iterator.h
	../typetraits.h
	../uninitialized.h
	../vector.h
	../listnode.h
	../iterator_list.h
	../list.h
	../iterator_deque.h
	../deque.h
	../queue.h
	../stack.h
	../functional.h
	../pair.h
	../iterator_rbtree.h
	../rbtree.h
	../set.h
	../map.h
	test.h
	Vector.cpp
	List.cpp
	Deque.cpp
	queue&stack.cpp
	RBtree.cpp
	set&map.cpp
	main.cpp
        )

add_executable(MySTL ${SOURCE_FILES})
