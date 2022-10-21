#include <iostream>

/*******Голубинная сортировка - pigeonhole_sort*******/
void pigeonhole_sort(int *arr, int length) {
    //const int MAX_ELEMENTS = 10'000;
    //int  pigeon_array[MAX_ELEMENTS] = { 0 };
    int* temp_array = arr;
    int max_element = 0;
    int min_element = 0;
    int range = 0;
    int i;
    // Get the min_element and max_element from the given array
    for (i = 0; i < length; i++)    {
        if (arr[i] < min_element)
            min_element = arr[i];
        if (arr[i] > max_element)
            max_element = arr[i];
    }
    // Get the range
    range = (max_element - min_element) + 1;
    // Initialize the pigeonHoleArray with zero
    int* pigeon_array = new int[range];
    for (i = 0; i < range; i++) {
        pigeon_array[i] = 0;
    }
    // place the elements in pigeonHoleArray
    for (i = 0; i < length; i++, temp_array++) {
        pigeon_array[*temp_array - min_element] += 1;
    }
    // copy from pigeonHoleArray to original array
    for (i = 0, temp_array = &arr[0]; i < range; i++) {
        while (pigeon_array[i] > 0) {
            pigeon_array[i]--;
            *temp_array++ = i + min_element;
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
    pigeonhole_sort(my_array, size);
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
    sort_test(10'000'000);
	return 0;
}
