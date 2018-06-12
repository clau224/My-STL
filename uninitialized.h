#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_

#include "construct.h"
#include "algorithm.h"
namespace MySTL {

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _unitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, _true_type) {
		  memcpy(result, first, (last - first) * sizeof(*first));
		  return result + (last - first);
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _unitialized_copy_aux(InputIterator first, InputIterator last,
		ForwardIterator result, _false_type) {
		  int i = 0;
		  for (; first != last; ++first, ++i) {
		  	 construct(result + i, *first);
		  }
		  return (result + i);
	}

    template<class InputIterator, class ForwardIterator, class T>
    ForwardIterator _unitialized_copy(InputIterator first, InputIterator last,
		ForwardIterator result, T) {
        typedef typename _type_traits<T>::is_POD_type isPOD;
		return _unitialized_copy_aux(first, last, result, isPOD());
    }

	template<class InputIterator, class ForwardIterator>
	ForwardIterator unitialized_copy(InputIterator first, InputIterator last,
		ForwardIterator result) {
		_unitialized_copy(first, last, result, value_type(result));

	}

	template<class ForwardIterator, class T>
	void _unitialized_fill_aux(ForwardIterator first, ForwardIterator last,
		const T& value, _true_type) {
        fill(first, last, value);
	}

	template<class ForwardIterator, class T>
	void _unitialized_fill_aux(ForwardIterator first, ForwardIterator last,
		const T& value, _false_type) {
        for (;first != last; ++first) {
        	construct(first, value);
        }
	}

    template<class ForwardIterator, class T>
    void unitialized_fill(ForwardIterator first, ForwardIterator last,
    	const T& value) {
    	typedef typename _type_traits<T>::is_POD_type isPOD;
    	_unitialized_fill_aux(first, last, value, isPOD());
    }


    template<class ForwardIterator, class Size, class T>
    ForwardIterator _unitialized_fill_n_aux(ForwardIterator first, Size n,
    	const T& x, _true_type) {
        return fill_n(first, n, x);
    }

    template<class ForwardIterator, class Size, class T>
    ForwardIterator _unitialized_fill_n_aux(ForwardIterator first, Size n,
    	const T& x, _false_type) {
        int i = 0;
        for(; i != n; ++i) {
        	construct((T*)(first + i), x);
        }
        return (first + i);
    }

    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator unitialized_fill_n(ForwardIterator first ,Size n,
    	const T& x) {
    	typedef typename _type_traits<T>::is_POD_type isPOD;
        _unitialized_fill_n_aux(first, n, x, isPOD());
    }
}
#endif
