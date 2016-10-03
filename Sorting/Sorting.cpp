// Quicksort.cpp : Defines the entry point for the console application.
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
	}
	else if (data[start] < data[end])
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
	}
	else {
		size_t third_length = length / 3;
		if (third_length < 3) {
			size_t midpoint = size_t(0.5f * end);
			return median(data, 0, midpoint, end);
		}
		else {
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

// Uses Hoare partition scheme - add fat partition?
template <typename T>
size_t partition(T* data, size_t end) {
	T pivot = data[ninther(data, end)];
	size_t i = 0, j = end;
	while (true) {
		while (data[i] < pivot)
			++i;
		while (data[j] > pivot)
			--j;

		if (i >= j)
			return j;

		T temp = data[i];
		data[i] = data[j];
		data[j] = temp;

		++i;
		--j;
	}
}

template <typename T>
void quicksort(T* data, size_t length) {
	if (length > 1) {
		size_t pivot = partition(data, length - 1);
		quicksort(data, pivot + 1);
		if (pivot < length - 1)
			quicksort(data + pivot + 1, length - pivot - 1);
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
	static const size_t length = 50u;
	srand((unsigned int)time(nullptr));
	int data[length];
	for (size_t i = 0; i < length; ++i) {
		data[i] = rand();
	}

	quicksort(data, length);

	print_data(data, length);

	system("pause");

	return 0;
}