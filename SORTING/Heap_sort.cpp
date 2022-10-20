#include <iostream>

/**Сортировка кучей (пирамидальная) - heap_sort**/
template <typename Type>
void heap_create(Type parray[], int size, int index) {
    int largest = index;            // Наибольший элемент массива
    int l_child = 2 * index + 1;    // Левый наследник 
    int r_child = 2 * index + 2;    // Правый наследник
    // Если левый узел больше наибольшего - запомнить его индекс 
    if (l_child < size && parray[l_child] > parray[largest])
        largest = l_child;
    // Если правый узел больше наибольшего  - запомнить его индекс 
    if (r_child < size && parray[r_child] > parray[largest])
        largest = r_child;
    // Если индекс наибольшего элемента не равен индексу корня
    if (largest != index) {
        std::swap(parray[index], parray[largest]);
        // Рекурсивный вызов
        heap_create(parray, size, largest);
    }
}

template <typename Type>
void heap_sort(Type parray[], int size) {
    // Построить кучу с заданным диапозоном
    for (int i = size / 2 - 1; i >= 0; --i)
        heap_create(parray, size, i);
    // Извлечение элементов один за другим из кучи
    for (int i = size - 1; i >= 0; --i) {
        // Перемещение текущего корня в конец
        std::swap(parray[0], parray[i]);    
        // Вызов для уменьшенной кучи
        heap_create(parray, i, 0);
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
    heap_sort(my_array, size);
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
