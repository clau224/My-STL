#include "alloc.h"

namespace MySTL {
char *alloc::start_free = 0;
char *alloc::end_free = 0;
size_t alloc::heap_size = 0;

alloc::obj * volatile alloc::free_list[alloc::_NFREELIST] = { 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

void *alloc::allocate(size_t bytes) {
	if (bytes > _MAX_BYTES) {
		return malloc(bytes);
	}

	size_t index = FREELIST_INDEX(bytes);

	obj * my_list = free_list[index];

	if (my_list == 0) {
		void *r = refill(ROUND_UP(bytes));
		return r;
	}
	free_list[index] = my_list->free_list_next;
	return my_list;
}

void alloc::deallocate(void *ptr, size_t bytes) {
	if (bytes > _MAX_BYTES) {
		free(ptr);
		return;
	}

	size_t index = FREELIST_INDEX(bytes);
	obj* node = static_cast<obj *>(ptr);
	node->free_list_next = free_list[index];
	free_list[index] = node;
}

void *alloc::reallocate(void *ptr, size_t old_sz, size_t new_sz) {
	deallocate(ptr, old_sz);
	ptr = allocate(new_sz);

	return ptr;
}

void *alloc::refill(size_t bytes) {
	size_t nobjs = _NOBJS;

	char *chunk = chunk_alloc(bytes, nobjs);
	obj * volatile *my_list = 0;
	obj *result = 0;
	obj *current_obj = 0, *next_obj = 0;

	if (nobjs == 1) {
		//只获取了一个区块
		return chunk;
	}

	my_list = free_list + FREELIST_INDEX(bytes);

	result = (obj *) (chunk);

	*my_list = next_obj = (obj *) (chunk + bytes);

	for (int i = 1;; ++i) {
		current_obj = next_obj;
		next_obj = (obj *) ((char *) next_obj + bytes);
		if (nobjs - 1 == i) {
			current_obj->free_list_next = 0;
			break;
		}

		current_obj->free_list_next = next_obj;
	}

	return result;
}

char *alloc::chunk_alloc(size_t bytes, size_t& nobjs) {
	char *result = 0;
	size_t bytes_need = bytes * nobjs;
	size_t bytes_left = end_free - start_free;

	if (bytes_left > bytes_need) {
		result = start_free;
		start_free = start_free + bytes_need;
		return result;
	} else if (bytes_left >= bytes) {
		nobjs = bytes_left / bytes;
		bytes_need = nobjs * bytes;
		result = start_free;
		start_free = start_free + bytes_need;
		return result;
	} else {
		size_t bytes_to_get = 2 * bytes_need + ROUND_UP(heap_size >> 4);
		if (bytes_left > 0) {
			obj * volatile * my_list = free_list + FREELIST_INDEX(bytes_left);
			((obj *) start_free)->free_list_next = *my_list;
			*my_list = (obj *) start_free;
		}

		start_free = (char *) malloc(bytes_to_get);
		if (0 == start_free) {
			obj * volatile * my_list = 0, *p = 0;

			for (int i = 0; i <= _MAX_BYTES; i += _ALIGN) {
				my_list = free_list + FREELIST_INDEX(i);
				p = *my_list;
				if (0 != p) {
					*my_list = p->free_list_next;
					start_free = (char *) p;
					end_free = start_free + i;
					return chunk_alloc(bytes, nobjs);
				}
			}
			end_free = 0;
		}

		heap_size += bytes_to_get;
		end_free = start_free + bytes_to_get;
		return chunk_alloc(bytes, nobjs);
	}
}
}
