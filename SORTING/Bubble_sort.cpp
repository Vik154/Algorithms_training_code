#include <iostream>
#include <ctime>

// Сортировка пузырьком - bubble_sort
template <typename Type>
void bubble_sort(Type *parray, size_t size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size - 1; ++j) {
			if (parray[j] > parray[j + 1]) {
				Type temp = parray[j];
				parray[j] = parray[j + 1];
				parray[j+1] = temp;
			}
		}
	}
}

// Функция потестить время
void sort_test(int size_array) {
	setlocale(LC_ALL, "Russian");
	if (size_array < 1) { std::cout << "AAA";  return; }
	clock_t time = clock();
	size_t size = size_array;
	size_t *my_array = new size_t[size];
	std::cout << "Идёт заполнение массива: ";
	for (size_t i = 0; i < size; ++i) {
		my_array[i] = rand() % 1'000'000;
	}
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
	time = clock();
	std::cout << "Идёт сортировка массива на " << size << " элементов: ";
	bubble_sort(my_array, size);
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
}

int main() {
	sort_test(10'000)
}