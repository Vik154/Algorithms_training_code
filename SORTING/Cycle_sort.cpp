#include <iostream>

/*************Цикличная сортировка - cycle_sort************/
template <typename Type>
void cycle_sort(Type *parray, int size) {
    Type element;
    int small;
    for (int i = 0; i <= size - 2; i++) {
        element = parray[i]; 
        small = i;
        for (int j = i + 1; j < size; j++) {
            if (parray[j] < element) {
                small++;
            }
        }
        if (small == i) {
            continue;
        }
        while (element == parray[small]) {
            small++;
        }
        if (small != i) {
            std::swap(parray[small], element);
        }
        while (small != i) {
            small = i;
            for (int j = i + 1; j < size; j++) {
                if (parray[j] < element) {
                    small += 1;
                }
            }
            while (element == parray[small]) {
                small += 1;
            }
            if (element != parray[small]) { 
                std::swap(parray[small], element);
            }
        }
    }
}
/**********************************************************/

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
    cycle_sort(my_array, size);
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
