#include <iostream>

/********Бисерная (гравитационная) сортировка - bead_sort********/
void bead_sort(int* parray, int size) {
    // Поиск максимального элемента
    int max = parray[0];
    for (int i = 1; i < size; i++)
        if (parray[i] > max)
            max = parray[i];
   
    unsigned char* beads = new unsigned char[max * size];
    memset(beads, 0, static_cast<size_t>(max) * size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < parray[i]; j++) {
            beads[i * max + j] = 1;
        }
    }
    for (int j = 0; j < max; j++) {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += beads[i * max + j];
            beads[i * max + j] = 0;
        }
        for (int i = size - sum; i < size; i++) {
            beads[i * max + j] = 1;
        }
    }
    for (int i = 0; i < size; i++) {
        int j;
        for (j = 0; j < max && beads[i * max + j]; j++) {}
        parray[i] = j;
    }
    delete[] beads;
}
/****************************************************************/


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
    bead_sort(my_array, size);
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
    sort_test(1'000);
	return 0;
}