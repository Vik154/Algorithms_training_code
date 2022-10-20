#include <iostream>
#include <vector>
#include <algorithm>


/*****Блочная сортировка - bucket_sort_V1.0*****/
int find_max(int arr[], int n) {
    int i, max = arr[0], cnt = 0;
    for (i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    while (max > 0) {
        cnt++;
        max = max / 10;
    }
    return cnt;
}

void bucket_sort(int arr[], int n) {
    int** bucket = new int* [10];
    for (int i = 0; i < 10; ++i) {
        bucket[i] = new int[n + 1];
    }

    int i, j[10], k, l, d = 1;
    int c;
    c = find_max(arr, n);

    for (int m = 0; m < c; m++) {
        for (i = 0; i < 10; i++)
            j[i] = 0;
        for (i = 0; i < n; i++) {
            k = (arr[i] / d) % 10;
            bucket[k][j[k]] = arr[i];
            j[k]++;
        }
        l = 0;
        for (i = 0; i < 10; i++) {
            for (k = 0; k < j[i]; k++) {
                arr[l] = bucket[i][k];
                l++;
            }
        }
        d *= 10;
    }
}
/***********************************************/

/*****Блочная сортировка - bucket_sort_V2.0*****/
void bucket_sort2(int parray[], int array_size) {
    const int max = array_size;
    int **bucket = new int*[10];
    for (int i = 0; i < 10; ++i) {
        bucket[i] = new int[max + 1];
    }
    for (int x = 0; x < 10; x++) bucket[x][max] = 0;
    for (int digit = 1; digit <= 1000000000; digit *= 10) {
        for (int i = 0; i < max; i++) {
            int dig = (parray[i] / digit) % 10;
            bucket[dig][bucket[dig][max]++] = parray[i];
        }
        int idx = 0;
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < bucket[x][max]; y++) {
                parray[idx++] = bucket[x][y];
            }
            bucket[x][max] = 0;
        }
    }
}
/***********************************************/

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
    bucket_sort2(my_array, size);
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
