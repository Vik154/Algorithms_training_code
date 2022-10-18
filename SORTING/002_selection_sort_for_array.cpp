#include <iostream>
#include <ctime>

// Сортировка выбором - selection_sort
/************************************************************/
template <typename Type>							    /****/
void selection_sort(Type *parray, size_t size) {		/****/
	int min_index;										/****/
	for (int i = 0; i < size - 1; ++i) {				/****/
		min_index = i;									/****/
		for (int j = i + 1; j < size; ++j) {			/****/
			if (parray[j] < parray[min_index]) {		/****/
				min_index = j;							/****/
			}											/****/
		}												/****/	
		if (min_index != i) {							/****/
			Type temp = parray[min_index];				/****/
			parray[min_index] = parray[i];				/****/	
			parray[i] = temp;							/****/
		}												/****/
	}													/****/
}														/****/
/************************************************************/
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
	selection_sort(my_array, size);
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
}

int main() {	
	sort_test(20000);
	return 0;
}
