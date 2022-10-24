#include <iostream>
#include <algorithm>


/************Интроспективная сортировка - intro_sort*************/
void swap_value(int* a, int* b) {
    int* temp = a;
    a = b;
    b = temp;
    return;
}

// Сортировка вставками, при определенных условиях
void insertion_isort(int arr[], int* begin, int* end) {
    int left = begin - arr;
    int right = end - arr;

    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    return;
}

// Поиск средней опорной точки
int* partition_isort(int arr[], int low, int high) {
    int pivot = arr[high];  // pivot
    int i = (low - 1);      // Index of smaller element
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (arr + i + 1);
}

// Поиск среднего медианного значения
int* median_three(int* a, int* b, int* c) {
    if (*a < *b && *b < *c)
        return (b);
    if (*a < *c && *c <= *b)
        return (c);
    if (*b <= *a && *a < *c)
        return (a);
    if (*b < *c && *c <= *a)
        return (c);
    if (*c <= *a && *a < *b)
        return (a);
    if (*c <= *b && *b <= *a)
        return (b);
}

// Служебная функция для сортировки
void introsort_util(int arr[], int* begin, int* end, int depth_limit) {

    int size = end - begin;
    if (size < 16) {
        insertion_isort(arr, begin, end);
        return;
    }
    if (depth_limit == 0) {
        std::make_heap(begin, end + 1);
        std::sort_heap(begin, end + 1);
        return;
    }
    int* pivot = median_three(begin, begin + size / 2, end);
    swap_value(pivot, end);
    int* partitionPoint = partition_isort(arr, begin - arr, end - arr);
    introsort_util(arr, begin, partitionPoint - 1, depth_limit - 1);
    introsort_util(arr, partitionPoint + 1, end, depth_limit - 1);
    return;
}

void intro_sort(int arr[], int* begin, int* end) {
    int depthLimit = 2 * log(end - begin);
    introsort_util(arr, begin, end, depthLimit);
    return;
}
/*****************************************************************/

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
    intro_sort(my_array, my_array ,size - 1);
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