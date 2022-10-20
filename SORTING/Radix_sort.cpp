#include <iostream>
#include <vector>
#include <algorithm>


/***Поразрядная сортировка - radix_sort_V1.0****/
int get_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void counting_sort(int arr[], int size, int div) {
    int* output = new int[size];
    int count[10] = { 0 };

    for (int i = 0; i < size; i++) {
        count[(arr[i] / div) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / div) % 10] - 1] = arr[i];
        count[(arr[i] / div) % 10]--;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}

void radix_sort(int arr[], int size) {
    int m = get_max(arr, size);
    for (int div = 1; m / div > 0; div *= 10)
        counting_sort(arr, size, div);
}
/***********************************************/

/***Поразрядная сортировка - radix_sort_V2.0****/
template<typename Type>
void radix_sort2(std::vector<Type>& source) {
    const int BUCKETS = 10;
    std::vector<std::vector<int>> buckets(BUCKETS);

    for (int pos = 0; pos <= 2; ++pos)
    {
        int denominator = static_cast<int>(pow(10, pos));
        for (int& tmp : source)
            buckets[(tmp / denominator) % 10].push_back(tmp);

        int index = 0;

        for (auto& theBucket : buckets)
        {
            for (int& k : theBucket)
                source[index++] = k;

            theBucket.clear();
        }
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
    radix_sort2(v_array);
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
