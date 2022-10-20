#include <iostream>

/*************Вялая сортировка - slow_sort************/
template <typename Type>
void slow_rec(Type *parray, int i, int j) {
    if (i >= j) {
        return;
    }
    int mid = (i + j) / 2;
    slow_rec(parray, i, mid);
    slow_rec(parray, mid + 1, j);
    if (parray[mid] > parray[j]) {
        std::swap(parray[mid], parray[j]);
    }
    slow_rec(parray, i, j - 1);
}

template <typename Type>
void slow_sort(Type *parr, int size) {
    slow_rec(parr, 0, size - 1);
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
    slow_sort(my_array, size);
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
    sort_test(2'00);
	return 0;   
}
