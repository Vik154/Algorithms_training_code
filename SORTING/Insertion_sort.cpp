#include <iostream>
#include <ctime>

/***********Сортировка вставками - insertion_sort*********/
template <typename Type>
void insertion_sort(Type *parray, size_t size) {
	Type key;
	int id;
	for (int i = 1; i < size; ++i) {
		key = parray[i];
		id = i - 1;
		while (id >= 0 && parray[id] > key) {
			parray[id + 1] = parray[id];
			parray[id] = key;
			id--;
		}
	}
}
/**********************************************************/

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
	insertion_sort(my_array, size);
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
}

int main() {
	sort_test(30000);
	return 0;
}