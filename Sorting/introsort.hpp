#pragma once

#include "quicksort.hpp"
#include "mergesort.hpp"

template <typename T>
void try_quicksort(T* data, size_t length, size_t depth) {
	if (length > 1) {
		if (depth > log2(length))
			return mergesort(data, length);

		size_t pivot_start, pivot_end;
		fat_partition(data, length - 1, pivot_start, pivot_end);
		try_quicksort(data, pivot_start, depth + 1);
		if (pivot_end < length - 1)
			try_quicksort(data + pivot_end + 1, length - pivot_end - 1, depth + 1);
	}
}

template <typename T>
void introsort(T* data, size_t length) {
	try_quicksort(data, length, 0);
}
