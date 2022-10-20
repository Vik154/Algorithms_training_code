#include <iostream>

/********Гномья сортировка - gnome_sort*********/
template <typename Type>
void gnome_sort(Type *parray, int size) {
    int i = 1, j = 2;
    while (i < size) {
        if (parray[i - 1] < parray[i]) {
            i = j;
            j++;
        }
        else {
            int temp = parray[i];
            parray[i] = parray[i - 1];
            parray[i - 1] = temp;
            i--;
            if (i == 0) {
                i = j;
                j++;
            }
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
    gnome_sort(my_array, size);
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
    sort_test(10'000);
	return 0;
}
