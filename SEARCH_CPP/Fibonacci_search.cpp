#include <iostream>
#include <algorithm>


// Поиск фибоначи (в упорядоченном массиве по возрастанию)
int64_t fibonacci_search(int64_t* arr, int64_t size, int64_t value) {
	/*Инициализация чисел фибоначчи*/
	int64_t fibo_1 = 0;					// Первое число фибоначчи
	int64_t fibo_2 = 1;					// Второе число фибоначчи
	int64_t fibo_3 = fibo_1 + fibo_2;	// Третье число фибоначчи
	int64_t length = size;				// Длина массива

	while (fibo_3 < length) {			// Пока 3-ье число фибоначчи меньше длины массива
		fibo_1 = fibo_2;				// Искать последовательность чисел
		fibo_2 = fibo_3;
		fibo_3 = fibo_1 + fibo_2;
	}
	// Смещение - это конец исключенного диапазона спереди
	int64_t offset = -1;
	int64_t index;
	/*Цикл выполняется до тех пор, пока есть элементы для проверки*/
	while (fibo_3 > 1) {
		// Проверка на валидность, принадлежит ли индекс заданному диапозону 
		index = std::min(offset + fibo_1, length - 1);
		// Если искомое значение больше чем значение массива по этому индексу 
		// тогда сократить массив на данный индекс
		if (arr[index] < value) {
			fibo_3 = fibo_2;
			fibo_2 = fibo_1;
			fibo_1 = fibo_3 - fibo_2;
			offset = index;
		}
		// Если искомое значение меньше, значения по заданному индексу
		// тогда обрезать массив справа и сместиться левее
		else if (arr[index] > value) {
			fibo_3 = fibo_1;
			fibo_2 = fibo_2 - fibo_1;
			fibo_1 = fibo_3 - fibo_2;
		}
		// Если элемент найден вернуть его индекс
		else {
			return index;
		}
	}
	// Сравнение последнего элемента
	if (fibo_2 && arr[offset + 1] == value) {
		return offset + 1;
	}
	// Если элемент не найден вернуть -1
	return -1;
}


int main() {

	const int64_t size64 = 20;
	int64_t arr64[size64]{};

	for (int i = 0; i < size64; ++i) { arr64[i] = rand(); }
	std::sort(arr64, arr64 + size64);
	
	for (int i = 0; i < size64; ++i) { std::cout << arr64[i] << " "; }
	std::cout << "\n";
	int64_t id = fibonacci_search(arr64, size64, 19912);
	std::cout << id << "\n";
}