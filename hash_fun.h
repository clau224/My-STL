/*
 * hash_fun.h
 *
 *  Created on: 2018年8月8日
 *      Author: garvin
 */

#ifndef HASH_FUN_H_
#define HASH_FUN_H_

namespace MySTL{
	template<class Key> struct hash{};

	inline size_t _stl_hash_string(const char* s){
		unsigned long h = 0;
		for( ; *s; ++s){
			h = 5*h + *s;
		}
		return size_t(h);
	}

	template<>
	struct hash<char*>{
		size_t operator()(const char* s) const {
			return _stl_hash_string(s);
		}
	};

	template<>
	struct hash<const char*>{
		size_t operator()(const char* s) const {
			return _stl_hash_string(s);
		}
	};

	template<>
	struct hash<char>{
		size_t operator()(char ch) const {
			return ch;
		}
	};

	template<>
	struct hash<unsigned char>{
		size_t operator()(unsigned char uch) const{
			return uch;
		}
	};

	template<>
	struct hash<signed char>{
		size_t operator()(signed char ch) const{
			return ch;
		}
	};

	template<>
	struct hash<short>{
		size_t operator()(short s) const{
			return s;
		}
	};

	template<>
	struct hash<unsigned short>{
		size_t operator()(unsigned short us) const{
			return us;
		}
	};

	template<>
	struct hash<int>{
		size_t operator()(int i) const{
			return i;
		}
	};

	template<>
	struct hash<unsigned int>{
		size_t operator()(unsigned int i) const{
			return i;
		}
	};

	template<>
	struct hash<long>{
		size_t operator()(long l) const{
			return l;
		}
	};

	template<>
	struct hash<unsigned long>{
		size_t operator()(unsigned long ul) const{
			return ul;
		}
	};
}

#endif /* HASH_FUN_H_ */
