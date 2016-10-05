// Sorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

template <typename T>
size_t median(T* data, size_t start, size_t midpoint, size_t end) {
	if (data[start] < data[midpoint]) {
		if (data[midpoint] < data[end])
			return midpoint;
		else if (data[start] < data[end])
			return end;
		else
			return start;
	} else if (data[start] < data[end])
		return start;
	else if (data[midpoint] < data[end])
		return end;
	else
		return midpoint;
}

template <typename T>
size_t ninther(T* data, size_t end) {
	size_t length = 1 + end;
	if (length < 3) {
		return 0;
	} else {
		size_t third_length = length / 3;
		if (third_length < 3) {
			size_t midpoint = size_t(0.5f * end);
			return median(data, 0, midpoint, end);
		} else {
			--third_length;
			return median(
				data,
				median(data, 0, third_length / 2, third_length),
				median(data, third_length + 1, size_t(third_length * 1.5f) + 1, third_length * 2 + 2),
				median(data, third_length * 2 + 2, size_t(third_length * 2.5f) + 2, third_length * 3 + 2)
			);
		}
	}
}

// Uses Hoare partition scheme with added fat partition
template <typename T>
void fat_partition(T* data, size_t end, size_t& pivot_start_out, size_t& pivot_end_out) {
	T pivot = data[ninther(data, end)];
	size_t i = 0, j = end;
	while (true) {
		while (i < end && data[i] < pivot)
			++i;
		while (j > 0 && data[j] >= pivot)
			--j;

		if (i >= j) {
			pivot_start_out = i;
			while (data[i] == pivot)
				++i;
			for (j = i + 1; j <= end; ++j) {
				if (data[j] == pivot) {
					T temp = data[i];
					data[i] = data[j];
					data[j] = temp;
					++i;
				}
			}
			pivot_end_out = i - 1;
			return;
		}

		T temp = data[i];
		data[i] = data[j];
		data[j] = temp;
	}
}

template <typename T>
void quicksort(T* data, size_t length) {
	if (length > 1) {
		size_t pivot_start, pivot_end;
		fat_partition(data, length - 1, pivot_start, pivot_end);
		quicksort(data, pivot_start);
		if (pivot_end < length - 1)
			quicksort(data + pivot_end + 1, length - pivot_end - 1);
	}
}

template <typename T>
void print_data(T* data, size_t length) {
	for (size_t i = 0; i < length; ++i) {
		cout << data[i];
		if (i < length - 1)
			cout << ", ";
	}
	cout << endl;
}

using namespace std;
int main() {
	static const size_t length = 5000u;
	srand((unsigned int)time(nullptr));
	int data[length];
	for (size_t i = 0; i < length; ++i) {
		data[i] = rand()%2000;
	}

	quicksort(data, length);

	print_data(data, length);
	system("pause");

	return 0;
}
