#include <iostream>
#include <vector>
#include <algorithm>

/*******Сортировка подсчетом - count_sort*******/
template <typename T>
void count_sort(std::vector<T>& arr) {
    
    int max_value = arr.front();
    for (auto value : arr) {
        if (value > max_value) {
            max_value = value;
        }
    }
    int len = arr.size();
    if (len < 1)
        return;
    std::vector<int> count(max_value + 1, 0);
    std::vector<int> tmp(arr);
    for (auto x : arr)
        count[x]++;
    for (int i = 1; i <= max_value; ++i)
        count[i] += count[i - 1];
    for (int i = len - 1; i >= 0; --i) {
        arr[count[tmp[i]] - 1] = tmp[i];
        count[tmp[i]]--;
    }
}
/***********************************************/

void sort_test(int size_array) {
	setlocale(LC_ALL, "Russian");
	if (size_array < 1) { std::cout << "AAA";  return; }
	clock_t time = clock();
	int size = size_array;
	//int* my_array = new int[size];
    std::vector<int> v_array;
	std::cout << "Идёт заполнение массива: ";
	for (int i = 0; i < size; ++i) {
		//my_array[i] = rand() % 1'000'000;
		v_array.push_back(rand() % 1'000'000);
	}
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
	time = clock();
	std::cout << "Идёт сортировка массива на " << size << " элементов: ";
    count_sort(v_array);
    //radix_sort(my_array, size);
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
    /*
    for (int i = 0; i < size_array; ++i) {
        //std::cout << my_array[i] << " ";
        std::cout << v_array[i] << " ";
    }
    */
    //delete[] my_array;
    v_array.clear();
}

int main() {
    sort_test(1'000'000);
	return 0;
}
