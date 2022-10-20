#include <iostream>

/********Сортировка Шелла - shell_sor_V1.0**********/
template <typename Type>
void shell_sort(Type *parray, int size) {
    for (int interval = size / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < size; i += 1) {
            Type temp = parray[i];
            int j;
            for (j = i; j >= interval && parray[j - interval] > temp; j -= interval) {
                parray[j] = parray[j - interval];
            }
            parray[j] = temp;
        }
    }
}
/***************************************************/

/********Сортировка Шелла - shell_sort_V2.0*********/
int increment(long inc[], long size) {
    // inc[] массив, в который заносятся инкременты
    // size размерность этого массива
    int p1 = 1, p2 = 1, p3 = 1, s = -1;

    do {// заполняем массив элементов по формуле Роберта Седжвика
        if (++s % 2) {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
        // заполняем массив, пока текущая инкремента хотя бы в 3 раза меньше количества элементов в массиве
    } while (3 * inc[s] < size);

    return s > 0 ? --s : 0;// возвращаем количество элементов в массиве
}

template<class T>
void shell_sort2(T a[], long size) {
    // inc инкремент, расстояние между элементами сравнения
    // i и j стандартные переменные цикла
    // seq[40] массив, в котором хранятся инкременты
    long inc, i, j, seq[40];
    int s;//количество элементов в массиве seq[40]

    // вычисление последовательности приращений
    s = increment(seq, size);
    while (s >= 0) {
        //извлекаем из массива очередную инкременту
        inc = seq[s--];
        // сортировка вставками с инкрементами inc
        for (i = inc; i < size; i++) {
            T temp = a[i];
            // сдвигаем элементы до тех пор, пока не дойдем до конца или не упорядочим в нужном порядке
            for (j = i - inc; (j >= 0) && (a[j] > temp); j -= inc)
                a[j + inc] = a[j];
            // после всех сдвигов ставим на место j+inc элемент, который находился на i месте
            a[j + inc] = temp;
        }
    }
}
/***************************************************/

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
    shell_sort(my_array, size);
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
