#include <iostream>

/******Чётно-нечётная сортировка - odd_even_sort******/
template <typename Type>
void odd_even_sort(Type *parray, int size) {
    int len = size;
    int is_sorted = 0;
    while (is_sorted == 0) {
        is_sorted = 1;
        int temp = 0;
        for (int i = 1; i <= len - 2; i = i + 2) {
            if (parray[i] > parray[i + 1]) {
                std::swap(parray[i], parray[i + 1]);
                is_sorted = 0;
            }
        }
        for (int i = 0; i <= len - 2; i = i + 2) {
            if (parray[i] > parray[i + 1]) {
                std::swap(parray[i], parray[i + 1]);
                is_sorted = 0;
            }
        }
    }
}
/*****************************************************/

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
    odd_even_sort(my_array, size);
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
    sort_test(10'000);
	return 0;
}
