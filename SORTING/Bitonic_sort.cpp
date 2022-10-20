#include <iostream>

/*************Битонная сортировка - bitonic_sort************/
/*************Нестабильная версия***************************/
template <class T>
void compare(T* items, int i, int j, int dir) {
    if (dir == 1 && (items[i] > items[j]) || (dir == 0 && items[i] < items[j])) {
        std::swap(items[i], items[j]);
    }
}
// Sorts a bitonic sequence in the specified order.
template <class T>
void bitonic_merge(T* items, int lo, int n, bool dir) {
    if (n > 1) {
        int m = n / 2;
        for (int i = lo; i < lo + m; ++i) {
            compare(items, i, (i + m), dir);
        }
        bitonic_merge(items, lo, m, dir);
        bitonic_merge(items, lo + m, m, dir);
    }
}
// Sorts the given sequence in the specified order.
template <class T>
void bitonic_sort(T* items, int lo, int n, bool dir) {
    if (n > 1) {
        // Divide the array into two partitions and then sort 
        // the partitions in different directions.
        int m = n / 2;
        bitonic_sort(items, lo, m, 1);
        bitonic_sort(items, lo + m, m, 0);
        // Merge the results.
        bitonic_merge(items, lo, n, dir);
    }
}
// Sorts the given sequence in increasing order.
template <class T>
void bitonic_sort(T* items, int size) {
    bitonic_sort(items, 0, size, 1);
}
/***********************************************************/

void sort_test(int size_array) {
	setlocale(LC_ALL, "Russian");
	if (size_array < 1) { std::cout << "AAA";  return; }
	clock_t time = clock();
	int size = size_array;
	int* my_array = new int[size];
	std::cout << "Идёт заполнение массива: ";
	for (int i = 0; i < size; ++i) {
		my_array[i] = rand() % 1'000'000;
	}
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
	time = clock();
	std::cout << "Идёт сортировка массива на " << size << " элементов: ";
    bitonic_sort(my_array, size);
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
    /*
    for (int i = 0; i < size_array; ++i) {
        std::cout << my_array[i] << " ";
    }
    */
    delete[] my_array;
}

int main() {
    sort_test(100'000);
    return 0;
}
