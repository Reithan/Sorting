#pragma once
#include <memory>

template <typename T>
T* merge(T* first_block, size_t first_length, T* second_block, size_t second_length) {
	if (first_length + second_length < 1)
		return nullptr;
	
	static size_t output_length = first_length + second_length;
	static std::unique_ptr<T> output(new T[output_length]);
	if (first_length + second_length > output_length) {
		output_length = first_length + second_length;
		output.reset(new T[output_length]);
	}
	
	size_t i = 0, j = 0, k = 0;
	while (i < first_length || j < second_length) {
		if (j >= second_length || first_block[i] <= second_block[j] && i < first_length)
			output.get()[k++] = first_block[i++];
		else
			output.get()[k++] = second_block[j++];
	}
	return output.get();
}

template <typename T>
void mergesort(T* data, size_t length) {
	if (length > 1) {
		size_t midpoint = length / 2;
		mergesort(data, midpoint);
		mergesort(data + midpoint, length - midpoint);
		memcpy_s(data, length * sizeof(T), merge(data, midpoint, data + midpoint, length - midpoint), length * sizeof(T));
	}
}
