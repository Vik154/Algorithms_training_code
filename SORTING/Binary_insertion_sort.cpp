#include <iostream>

/*Двоичная сортировка вставками - binary_insertion_sort.cpp*/
int binary_search(int sarray[], int item, int low, int high) {
    if (high <= low) {
        return (item > sarray[low]) ? (low + 1) : low;
    }
    int mid = (low + high) / 2;

    if (item == sarray[mid]) {
        return mid + 1;
    }
    if (item > sarray[mid]) {
        return binary_search(sarray, item, mid + 1, high);
    }
    return binary_search(sarray, item, low, mid - 1);
}

void binary_insertion_sort(int sarray[], int n) {
    
    int i, loc, j, k, selected;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = sarray[i];
        loc = binary_search(sarray, selected, 0, j);
        while (j >= loc) {
            sarray[j + 1] = sarray[j];
            j--;
        }
        sarray[j + 1] = selected;
    }
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
    binary_insertion_sort(my_array, size);
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
