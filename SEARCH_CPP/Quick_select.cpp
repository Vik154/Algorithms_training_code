#include <iostream>

/* Функция partition - группирует список (от индексов left до right) на две части,
то есть, которые меньше определенного элемента, и те, которые больше или равны элементу.
Это известно как схема разбиения Ломуто , которая проще,
но менее эффективна, чем исходная схема разбиения Хоара */
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int id = left;
	for (int j = left; j <= right - 1; j++) {
		if (arr[j] <= pivot) {
			std::swap(arr[id], arr[j]);
			id++;
		}
	}
	std::swap(arr[id], arr[right]);
	return id;
}

// Возвращает k-й наименьший элемент в списке в пределах `left…right`
// (т.е. left <= k <= right). Пространство поиска в массиве
// меняется для каждого раунда, но размер списка остается прежним.
// Таким образом, `k` не нужно обновлять с каждым раундом.
int quick_select(int arr[], int left, int right, int k_th) {
	// Если k_th - это наименьший элемент в массиве
	if (k_th > 0 && k_th <= right - left + 1) {

        // Разделить массив и получить индекс сводного элемента в отсортированном массиве
        int index = partition(arr, left, right);
		// Если позиция та же, что и у k_th, вернуть значение
		if (index - left == k_th - 1)
			return arr[index];
		// Если позиция больше, то повторить рекурсивно для левого подмассива
		if (index - left > k_th - 1)
			return quick_select(arr, left, index - 1, k_th);
		// Иначе, повторит рекурсивно для правой части массива
		return quick_select(arr, index + 1, right,
			k_th - index + left - 1);
	}
	// Если k больше, чем количество элементов в массиве
	return INT_MAX;
}

int main() {
	int arr[] = { 10, 4, 5, 8, 6, 11, 26 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int k = 10;
	std::cout << "K-th smallest element is " << quick_select(arr, 0, n - 1, k);
	return 0;
}