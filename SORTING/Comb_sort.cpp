#include <iostream>

/*******Сортировка расческой - comb_sort********/
template <typename Type>
void comb_sort(Type* array, int size) {
    int jump = size;
    bool swapped = true;

    while (jump > 1 || swapped) {
        if (jump > 1) {
            jump = (int)(jump / 1.25);
        }
        swapped = false;
        for (int i = 0; i + jump < size; i++) {
            if (array[i] > array[i + jump]) {
                std::swap(array[i], array[i + jump]);
                swapped = true;
            }
        }
    }
}
/***********************************************/

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
    comb_sort(my_array, size);
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
    sort_test(1'000'000);
	return 0;
}
