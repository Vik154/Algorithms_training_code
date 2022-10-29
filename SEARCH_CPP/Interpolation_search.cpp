#include <iostream>


template <typename Type>
int64_t len(Type *begin, Type *end) {
	Type *cur = begin;
	int64_t count = 0;
	if (begin == end) { return 1; }
	while (cur != end) {
		count++;
		cur++;
	}
	return count;
}

/*******Интерполяционный поиск - interpolation_search********/
template <typename Type>
int64_t interpolation_search(Type *first, Type *last, const Type &elm) {
	
	int64_t mid;
	int64_t low = 0;
	int64_t high = len(first, last) - 1;

    while (low <= high && elm >= first[low] && elm <= first[high]) {
        if (low == high) {
            if (first[low] == elm) {
                return low;
            }
            return -1;
        }
        int64_t pos = low + ((static_cast<int64_t>(high - low) /
            (first[high] - first[low])) * (elm - first[low]));
        if (first[pos] == elm) {
            return pos;
        }
        if (first[pos] < elm) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }
    return -1;
}
/************************************************************/

// Рекурсивынй вариант
template <typename Type>
size_t interpolation_search_rec(Type *arr, const Type &value, size_t begin = 0, size_t end = 0) {

    size_t pos;
    if (begin <= end && value >= arr[begin] && value <= arr[end]) {
        pos = begin + (((double)(end - begin) / (arr[end] - arr[begin])) * (value - arr[begin]));

        if (arr[pos] == value)
            return pos;
        if (arr[pos] < value)
            return interpolation_search_rec(arr, value, pos + 1, end);
        if (arr[pos] > value)
            return interpolation_search_rec(arr, value, begin, pos - 1);
    }
    return -1;
}
/************************************************************/

int main() {

    int arr[] = { 10, 12, 13, 16, 18 };
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << interpolation_search(arr, arr + n, 18)      << "\n";
    std::cout << interpolation_search_rec(arr, 16, 0, n - 1) << "\n";

    return 0;
}