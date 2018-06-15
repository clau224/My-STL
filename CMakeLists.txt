cmake_minimum_required(VERSION 3.5)

project(MySTL)

set(SOURCE_FILES 
	algorithm.h
	alloc.cpp
	alloc.h
	allocator.h
	construct.h
	iterator.h
	typetraits.h
	uninitialized.h
	vector.h
	main.cpp
        )

add_executable(MySTL ${SOURCE_FILES})
