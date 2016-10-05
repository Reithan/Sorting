// Sorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "quicksort.hpp"
#include "mergesort.hpp"

using namespace std;

template <typename T>
void print_data(T* data, size_t length) {
	for (size_t i = 0; i < length; ++i) {
		cout << data[i];
		if (i < length - 1)
			cout << ", ";
	}
	cout << endl;
}

int main() {
	static const size_t length = 50u;
	srand((unsigned int)time(nullptr));
	int data[length];
	for (size_t i = 0; i < length; ++i) {
		data[i] = rand()%20;
	}

	mergesort(data, length);

	print_data(data, length);
	system("pause");

	return 0;
}
