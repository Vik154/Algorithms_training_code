#include <iostream>
#include <cmath>

/****************Поиск прыжками - jump_search****************/
template <typename Type>
uint64_t jump_search(Type *arr, Type elem, uint64_t size) {

	//uint64_t step = static_cast<uint64_t>(std::sqrt(size));
	uint64_t step = std::sqrt(size);
	uint64_t prev = step;

	while (arr[std::min(step, size) - 1] < elem) {
		prev  = step;
		//step += static_cast<uint64_t>(std::sqrt(size));
		step += std::sqrt(size);
		if (prev >= size) {
			return -1;
		}
	}
	while (arr[prev] < elem) {
		prev++;
		if (prev == std::min(step, size))
			return -1;
	}
	if (arr[prev] == elem)
		return prev;

	return -1;
}
/************************************************************/


int main() {
	int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
	int x = 55;
	int n = sizeof(arr) / sizeof(arr[0]);
	auto id = jump_search(arr, 144, n);
	std::cout << "\nNumber " << x << " is at index " << id;
	return 0;
}