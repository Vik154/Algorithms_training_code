#include <iostream>

/****Быстрая сортировка - quick_sort V_1.0****/
template <typename Type>
void quick_sort(Type* parray, int size) {
    int left = 0;
    int right = size - 1;
    Type middle = parray[size / 2];

    do {
        while (parray[left] < middle) {
            left++;
        }
        while (parray[right] > middle) {
            right--;
        }
        if (left <= right) {
            Type tmp = parray[left];
            parray[left] = parray[right];
            parray[right] = tmp;
            left++;
            right--;
        }
    } while (left <= right);

    if (right > 0) {
        quick_sort(parray, right + 1);
    }
    if (left < size) {
        quick_sort(&parray[left], size - left);
    }
}
/**********************************************/

/*****Быстрая сортировка - quick_sort V_2.0****/
template <typename Type>
void quick_sort2(Type *arr, int size) {
    int left  = 0;
    int right = size-1;
    Type pivot = arr[size / 2];

    while (left <= right) {
        while (arr[left] < pivot) {
            left++;
        }
        while (arr[right] > pivot) {
            right--;
        }
        if (left <= right) {
            Type temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
    if (right > 0) {
        quick_sort2(arr, right+1);
    }
    if (left < size) {
        quick_sort2(&arr[left], size - left);
    }
}
/**********************************************/

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
	quick_sort2(my_array, size);
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
    sort_test(5'000'000);
	return 0;
}
