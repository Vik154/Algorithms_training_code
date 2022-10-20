#include <iostream>
#include <ctime>

/********Сортировка слиянием - merge_sort version_1.0******/
template <typename Type>
void merge_sort(Type *arr, size_t size) {
	if (size == 1) { return; }
	merge_sort(arr, size / 2);
	merge_sort(&arr[size / 2], size - size / 2);
	
	size_t liter = 0; 
	size_t riter = 0; 
	Type *tmp = new Type[size];

	for (size_t i = 0; i < size; i++) {
		if (arr[liter] < arr[size / 2 + riter])
			tmp[i] = arr[liter++];
		else
			tmp[i] = arr[size / 2 + riter++];

		if (liter == size / 2) {
			while (riter < size - size / 2)
				tmp[++i] = arr[size / 2 + riter++];
			break;
		}
		else if (riter == size - size / 2) { 
			while (liter < size / 2)
				tmp[++i] = arr[liter++];
			break;
		}
	}
	for (size_t i = 0; i < size; i++) {
		arr[i] = tmp[i];
	}
	delete[] tmp;
}
/***************************************************************/
/**********Сортировка слиянием - merge_sort version_2.0*********/
template <typename Type>
void merge_sort2(Type *arr, size_t size) {
	if (size < 2) { return; }
	merge_sort2(arr, size / 2);
	merge_sort2(&arr[size / 2], size - (size / 2));
	Type* temp_array = new Type[size];
	size_t id_temp = 0, id_left = 0, id_right = size / 2;
	while ((id_left < size / 2) && (id_right < size)) {
		if (arr[id_left] < arr[id_right]) {
			temp_array[id_temp++] = arr[id_left++];
		}
		else {
			temp_array[id_temp++] = arr[id_right++];
		}
	}
	while (id_left < size / 2) {
		temp_array[id_temp++] = arr[id_left++];
	}
	while (id_right < size) {
		temp_array[id_temp++] = arr[id_right++];
	}
	for (id_left = 0; id_left < size; id_left++) {
		arr[id_left] = temp_array[id_left];
	}
	delete[] temp_array;
}
/***************************************************************/

void sort_test(int size_array) {
	setlocale(LC_ALL, "Russian");
	if (size_array < 1) { std::cout << "AAA";  return; }
	clock_t time = clock();
	size_t size = size_array;
	size_t* my_array = new size_t[size];
	std::cout << "Идёт заполнение массива: ";
	for (size_t i = 0; i < size; ++i) {
		my_array[i] = rand() % 1'000'000;
	}
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
	time = clock();
	std::cout << "Идёт сортировка массива на " << size << " элементов: ";
	merge_sort(my_array, size);
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
	delete[] my_array;

	time = clock();
	my_array = new size_t[size];
	std::cout << "Идёт заполнение массива: ";
	for (size_t i = 0; i < size; ++i) {
		my_array[i] = rand() % 1'000'000;
	}
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
	time = clock();
	std::cout << "Идёт сортировка массива на " << size << " элементов: ";
	merge_sort2(my_array, size);
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
	delete[] my_array;
}

int main() {
	sort_test(1'000'000);
	return 0;
}
