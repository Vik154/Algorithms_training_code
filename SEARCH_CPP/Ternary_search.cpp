#include <iostream>

// Функция поиска размера массива
template <typename Type>
size_t len(Type *begin, Type *end) {
	Type *cur = begin;
	size_t count = 0;
	if (begin == end) { return 1; }
	while (cur != end) {
		count++;
		cur++;
	}
	return count;
}

/************Тернарный поиск - ternary_search************/
template <typename Type>
uint64_t ternary_search(Type *first, Type *last, Type elem) {

	uint64_t left_id = 0, mid_1, mid_2;
	uint64_t right_id = len(first, last) - 1;

	while (right_id >= left_id) {
		mid_1 = left_id  + (right_id - left_id) / 3;
		mid_2 = right_id - (right_id - left_id) / 3;

		if (first[mid_1] == elem)
			return mid_1;
		if (first[mid_2] == elem)
			return mid_2;
		if (first[mid_1] > elem)
			right_id = mid_1 - 1;
		else if (first[mid_2] < elem)
			left_id = mid_2 + 1;
		else {
			left_id  = mid_1 + 1;
			right_id = mid_2 - 1;
		}
	}
	return -1;
}
/********************************************************/

/**********Рекурсивная версия - ternary_search***********/
template <typename Type>
uint64_t ternary_search_rec(Type *arr, Type elem, uint64_t begin = 0, uint64_t end = 0) {
		
	if (end >= begin) {
		uint64_t mid_1 = begin + (end - begin) / 3;
		uint64_t mid_2 = end - (end - begin) / 3;

		if (arr[mid_1] == elem)
			return mid_1;
		if (arr[mid_2] == elem)
			return mid_2;
		if (arr[mid_1] > elem)
			return ternary_search_rec(arr, elem, begin, mid_1 - 1);
		else if (arr[mid_2] < elem)
			return ternary_search_rec(arr, elem, mid_2 + 2, end);
		else
			return ternary_search_rec(arr, elem, mid_1 + 1, mid_2 - 1);
	}
	return -1;
}
/********************************************************/

int main() {
	int  arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto fel = 8;
	auto ptt = ternary_search(arr, arr + 10, fel);
	auto ptr = ternary_search_rec(arr, fel, 0, 10);

	std::cout << "Index of " << fel << " is " << ptt << std::endl;
	std::cout << "Index of " << fel << " is " << ptr << std::endl;
	return 0;
}