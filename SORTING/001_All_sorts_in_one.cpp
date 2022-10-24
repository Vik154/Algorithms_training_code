#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <string>


double sort_test(int size_array);                               // Тест сортировок

template <typename Type> void bubble_sort(Type*, size_t);       // Обменами - Сортировка пузырьком
template <typename Type> void odd_even_sort(Type*, int);        // Обменами - Чётно/нечетная сортировка
template <typename Type> void shaker_sort(Type*, int);          // Обменами - Сортировка перемешиванием
template <typename Type> void comb_sort(Type*, int);            // Обменами - Сортировка расческой (OK)
template <typename Type> void gnome_sort(Type*, int);           // Обменами - Гномья сортировка
template <typename Type> void slow_rec(Type*, int, int);        // Обменами - Вялая сортировка
template <typename Type> void slow_sort(Type*, int);            // Обменами - Вялая сортировка
template <typename Type> void quick_sort(Type*, int);           // Обменами - Быстрая сортировка (OK)

template <typename Type> void shell_sort(Type*, int);           // Вставками - Сортировка Шелла (OK)
template <typename Type> void insertion_sort(Type*, size_t);    // Вставками - Сортировка вставками
int binary_search(int[], int, int, int);                        // Вставками - Двоичная сортировка вставками
void binary_insertion_sort(int[], int);                         // Вставками - Двоичная сортировка вставками

struct Node;                                                    // Вставками - Сортировка двоичным деревом
Node* new_node(int);                                            // Вставками - Сортировка двоичным деревом
Node* insert_node(Node*, int);                                  // Вставками - Сортировка двоичным деревом
void store_sorted(Node*, int[], int&);                          // Вставками - Сортировка двоичным деревом
void tree_sort(int[], int);                                     // Вставками - Сортировка двоичным деревом

template <typename Type> void flip(Type*, int);                 // Выбором - Блинная сортировка 
template <typename Type> int  find_maxe(Type*, int);            // Выбором - Блинная сортировка
template <typename Type> void pancake_sort(Type*, int);         // Выбором - Блинная сортировка
template <typename Type> void heap_create(Type*, int, int);     // Выбором - Сортировка кучей (пирамидальная) (OK)
template <typename Type> void heap_sort(Type*, int);            // Выбором - Сортировка кучей (пирамидальная) (OK)
template <typename Type> void cycle_sort(Type*, int);           // Выбором - Цикличная сортировка
template <typename Type> void selection_sort(Type*, size_t);    // Выбором - Сортировка выбором

template <typename Type> void radix_sort2(std::vector<Type>&);  // Распределением - Поразрядная сортировка V 2.0 (OK)
template <typename Type> void count_sort(std::vector<Type>&);   // Распределением - Сортировка подсчётом (OK)
int  get_max(int[], int);                                       // Распределением - Поразрядная сортировка V 1.0 (OK)
void counting_sort(int[], int, int);                            // Распределением - Поразрядная сортировка V 1.0 (OK)
void radix_sort(int[], int);                                    // Распределением - Поразрядная сортировка V 1.0 (OK)
int  find_max(int[], int);                                      // Распределением - Блочная (ведёрная) сортировка V 1.0 (OK)
void bucket_sort(int[], int);                                   // Распределением - Блочная (ведёрная) сортировка V 1.0 (OK)
void bucket_sort2(int[], int);                                  // Распределением - Блочная (ведёрная) сортировка V 2.0 (OK)
void bead_sort(int*, int);                                      // Распределением - Бисерная сортировка (переполнение буфера при int == 100000)
void pigeonhole_sort(int*, int);                                // Распределением - Голубинная сортировка (OK++)

template <typename Type> void strand_sort(std::list<Type>&);    // Слиянием - Нитевидная сортировка
template <typename Type> void merge_sort(Type*, size_t);        // Слиянием - Сортировка слиянием V 1.0 (OK)
template <typename Type> void merge_sort2(Type*, size_t);       // Слиянием - Сортировка слиянием V 2.0 (OK)

template <class Type> void compare(Type*, int, int, int);         // Параллельные - Битонная сортировка (версия для степеней двойки)
template <class Type> void bitonic_merge(Type*, int, int, bool);  // Параллельные - Битонная сортировка (версия для степеней двойки)
template <class Type> void bitonic_sort(Type*, int, int, bool);   // Параллельные - Битонная сортировка (версия для степеней двойки)
template <class Type> void bitonic_sort(Type* items, int size);   // Параллельные - Битонная сортировка (версия для степеней двойки)

void insertion_sort(int[], int, int);                           // Гибридные - Сортировка Тима Питерса (OK)
void merge(int[], int, int, int);                               // Гибридные - Сортировка Тима Питерса (OK)
void tim_sort(int[], int);                                      // Гибридные - Сортировка Тима Питерса (OK)

void swap_value(int*, int*);                                    // Гибридные - Интроспективная сортировка (quick + heap) (OK)
void insertion_isort(int[], int*, int*);                        // Гибридные - Интроспективная сортировка (quick + heap) (OK)
int* partition_isort(int[], int, int);                          // Гибридные - Интроспективная сортировка (quick + heap) (OK)
int* median_three(int*, int*, int*);                            // Гибридные - Интроспективная сортировка (quick + heap) (OK)
void introsort_util(int[], int*, int*, int);                    // Гибридные - Интроспективная сортировка (quick + heap) (OK)
void intro_sort(int[], int*, int*);                             // Гибридные - Интроспективная сортировка (quick + heap) (OK)


/*************Чтение - запись в файл (логи)************/
class File_reader {
private:
    FILE* file;
public:
    explicit File_reader(const char* path) { file = std::fopen(path, "rb"); }
    void close() {
        if (file == NULL) return;
        std::fclose(file);
        file = NULL;
    }
    File_reader& operator >> (char* ch) {
        *ch = 0;
        if (file != NULL) {
            std::fgets(ch, CHAR_MAX, file);
        }
        return *this;
    }
    bool eof() { return file == NULL || std::feof(file); }
    ~File_reader() { close(); }
};

class File_writer {
private:
    FILE* file;
public:
    explicit File_writer(const char* path, bool append = false) {
        file = std::fopen(path, append ? "a" : "w");
    }
    void close() {
        if (file == NULL) return;
        std::fclose(file);
        file = NULL;
    }
    File_writer& operator << (const char* ch) {
        if (file != NULL) { std::fputs(ch, file); }
        return *this;
    }
    bool eof() { return file == NULL || std::feof(file); }
    ~File_writer() { close(); }
};
/******************************************************/


int main() {
	const char path[] = "C:\\Users\\user\\Desktop\\Sorting_test_CPP.txt";
    // Для тестов -- 1000, 10'000, 100'000, 1'000'000, 10'000'000, 100'000'000
    int size_test = 1'000;
    double result = sort_test(size_test);
    
    std::string sort_name = "\"STD::Qsort\" ---> ";
    std::string sort_size = "size: " + std::to_string(size_test) + "; \t";
    std::string sort_time = "time: " + std::to_string(result) + " сек.;\n";
    std::string sort_log  = sort_name + sort_size + sort_time;
    const char* info = sort_log.c_str();
    
    File_writer file_write(path, true);
	file_write << info;
	file_write.close();
    
    for (int i = 0; i < 55; ++i)
        std::cout << info[i];
}



double sort_test(int size_array) {
    setlocale(LC_ALL, "Russian");
    if (size_array < 1) { std::cout << "AAA";  return 0; }
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
    std::qsort(my_array, size, sizeof(my_array[0]), [](const void* a, const void* b) {
        const int* x = (int*)a;
        const int* y = (int*)b;
        if (*x > *y)
            return 1;
        else if (*x < *y)
            return -1;
        return 0;
        });
    time = clock() - time;
    std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
    double res = double(time) / CLOCKS_PER_SEC;
    /*
    for (int i = 0; i < size; ++i) {
        std::cout << my_array[i] << " ";
    }
    */
    delete[] my_array;
    return double(time) / CLOCKS_PER_SEC;
}


/*--------------------------------------------------*/
/*---------------СОРТИРОВКИ ОБМЕНАМИ----------------*/
/*--------------------------------------------------*/

/*********Сортировка пузырьком - bubble_sort**********/
template <typename Type>
void bubble_sort(Type* parray, size_t size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            if (parray[j] > parray[j + 1]) {
                Type temp = parray[j];
                parray[j] = parray[j + 1];
                parray[j + 1] = temp;
            }
        }
    }
}
/*****************************************************/

/******Чётно-нечётная сортировка - odd_even_sort******/
template <typename Type>
void odd_even_sort(Type* parray, int size) {
    int len = size;
    int is_sorted = 0;
    while (is_sorted == 0) {
        is_sorted = 1;
        int temp = 0;
        for (int i = 1; i <= len - 2; i = i + 2) {
            if (parray[i] > parray[i + 1]) {
                std::swap(parray[i], parray[i + 1]);
                is_sorted = 0;
            }
        }
        for (int i = 0; i <= len - 2; i = i + 2) {
            if (parray[i] > parray[i + 1]) {
                std::swap(parray[i], parray[i + 1]);
                is_sorted = 0;
            }
        }
    }
}
/*****************************************************/

/****Сортировка перемешиванием - shaker_sort****/
template <typename Type>
void shaker_sort(Type* parray, int size) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        for (int i = right; i >= left; --i) {
            if (parray[i - 1] > parray[i]) {
                Type temp = parray[i];
                parray[i] = parray[i - 1];
                parray[i - 1] = temp;
            }
        }
        left++;
        for (int i = left; i <= right; ++i) {
            if (parray[i - 1] > parray[i]) {
                Type temp = parray[i];
                parray[i] = parray[i - 1];
                parray[i - 1] = temp;
            }
        }
        right--;
    }
}
/***********************************************/

/*******Сортировка расческой - comb_sort********/
template <typename Type>
void comb_sort(Type* array, int size) {
    int jump = size;
    bool swapped = true;

    while (jump > 1 || swapped) {
        if (jump > 1) {
            jump = (int)(jump / 1.25);
        }
        swapped = false;
        for (int i = 0; i + jump < size; i++) {
            if (array[i] > array[i + jump]) {
                std::swap(array[i], array[i + jump]);
                swapped = true;
            }
        }
    }
}
/***********************************************/

/********Гномья сортировка - gnome_sort*********/
template <typename Type>
void gnome_sort(Type* parray, int size) {
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

/*************Вялая сортировка - slow_sort************/
template <typename Type>
void slow_rec(Type* parray, int i, int j) {
    if (i >= j) {
        return;
    }
    int mid = (i + j) / 2;
    slow_rec(parray, i, mid);
    slow_rec(parray, mid + 1, j);
    if (parray[mid] > parray[j]) {
        std::swap(parray[mid], parray[j]);
    }
    slow_rec(parray, i, j - 1);
}

template <typename Type>
void slow_sort(Type* parr, int size) {
    slow_rec(parr, 0, size - 1);
}
/*****************************************************/

/****Быстрая сортировка - quick_sort V_1.0****/
template <typename Type>
void quick_sort(Type* parray, int size) {
    int left = 0;
    int right = size - 1;
    Type middle = parray[size / 2];

    do {
        while (parray[left] < middle) {
            left++;
        }
        while (parray[right] > middle) {
            right--;
        }
        if (left <= right) {
            Type tmp = parray[left];
            parray[left] = parray[right];
            parray[right] = tmp;
            left++;
            right--;
        }
    } while (left <= right);

    if (right > 0) {
        quick_sort(parray, right + 1);
    }
    if (left < size) {
        quick_sort(&parray[left], size - left);
    }
}
/**********************************************/

/*****Быстрая сортировка - quick_sort V_2.0****/
template <typename Type>
void quick_sort2(Type* arr, int size) {
    int left = 0;
    int right = size - 1;
    Type pivot = arr[size / 2];

    while (left <= right) {
        while (arr[left] < pivot) {
            left++;
        }
        while (arr[right] > pivot) {
            right--;
        }
        if (left <= right) {
            Type temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
    if (right > 0) {
        quick_sort2(arr, right + 1);
    }
    if (left < size) {
        quick_sort2(&arr[left], size - left);
    }
}
/**********************************************/


/*--------------------------------------------------*/
/*---------------СОРТИРОВКИ ВСТАВКАМИ---------------*/
/*--------------------------------------------------*/


/********Сортировка Шелла - shell_sor_V1.0**********/
template <typename Type>
void shell_sort(Type* parray, int size) {
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

template<class Type>
void shell_sort2(Type a[], long size) {
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
            Type temp = a[i];
            // сдвигаем элементы до тех пор, пока не дойдем до конца или не упорядочим в нужном порядке
            for (j = i - inc; (j >= 0) && (a[j] > temp); j -= inc)
                a[j + inc] = a[j];
            // после всех сдвигов ставим на место j+inc элемент, который находился на i месте
            a[j + inc] = temp;
        }
    }
}
/***************************************************/

/*******Сортировка вставками - insertion_sort*********/
template <typename Type>
void insertion_sort(Type* parray, size_t size) {
    Type key;
    int id;
    for (int i = 1; i < size; ++i) {
        key = parray[i];
        id = i - 1;
        while (id >= 0 && parray[id] > key) {
            parray[id + 1] = parray[id];
            parray[id] = key;
            id--;
        }
    }
}
/*****************************************************/

/*Двоичная сортировка вставками - binary_insertion_sort.cpp*/
int binary_search(int sarray[], int item, int low, int high) {
    if (high <= low) {
        return (item > sarray[low]) ? (low + 1) : low;
    }
    int mid = (low + high) / 2;

    if (item == sarray[mid]) {
        return mid + 1;
    }
    if (item > sarray[mid]) {
        return binary_search(sarray, item, mid + 1, high);
    }
    return binary_search(sarray, item, low, mid - 1);
}

void binary_insertion_sort(int sarray[], int n) {

    int i, loc, j, k, selected;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = sarray[i];
        loc = binary_search(sarray, selected, 0, j);
        while (j >= loc) {
            sarray[j + 1] = sarray[j];
            j--;
        }
        sarray[j + 1] = selected;
    }
}
/***********************************************************/

/********Сортировка бинарным деревом - tree_sort*******/
struct Node {
    int key;
    Node* left, * right;
};

// A utility function to create a new BST Node
Node* new_node(int item) {
    struct Node* temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Stores inorder traversal of the BST in arr[]
void store_sorted(Node* root, int arr[], int& i) {
    if (root != NULL) {
        store_sorted(root->left, arr, i);
        arr[i++] = root->key;
        store_sorted(root->right, arr, i);
    }
}

/* A utility function to insert a new
   Node with given key in BST */
Node* insert_node(Node* node, int key) {
    /* If the tree is empty, return a new Node */
    if (node == NULL) return new_node(key);

    /* Otherwise, recur down the tree */
    if (key <= node->key)
        node->left = insert_node(node->left, key);
    else if (key >= node->key)
        node->right = insert_node(node->right, key);

    /* return the (unchanged) Node pointer */
    return node;
}

// This function sorts arr[0..n-1] using Tree Sort
void tree_sort(int arr[], int n) {
    struct Node* root = NULL;
    // Construct the BST
    root = insert_node(root, arr[0]);
    for (int i = 1; i < n; i++)
        root = insert_node(root, arr[i]);

    int i = 0;
    store_sorted(root, arr, i);
}
/*******************************************************/


/*--------------------------------------------------*/
/*---------------СОРТИРОВКИ ВЫБОРОМ-----------------*/
/*--------------------------------------------------*/


/**********Блинная сортировка - pancake_sort**********/
template <typename Type>
void flip(Type* arr, int i) {
    int temp, start = 0;
    while (start < i) {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

template <typename Type>
int find_maxe(Type* arr, int n) {
    int min_id, id;
    for (min_id = 0, id = 0; id < n; ++id)
        if (arr[id] > arr[min_id])
            min_id = id;
    return min_id;
}

template <typename Type>
void pancake_sort(Type* arr, int n) {
    for (int curr_size = n; curr_size > 1; --curr_size) {
        int mi = find_maxe(arr, curr_size);
        if (mi != curr_size - 1) {
            flip(arr, mi);
            flip(arr, curr_size - 1);
        }
    }
}
/*****************************************************/

/*********Сортировка выбором - selection_sort*********/
template <typename Type>
void selection_sort(Type* parray, size_t size) {
    int min_index;
    for (int i = 0; i < size - 1; ++i) {
        min_index = i;
        for (int j = i + 1; j < size; ++j) {
            if (parray[j] < parray[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            Type temp = parray[min_index];
            parray[min_index] = parray[i];
            parray[i] = temp;
        }
    }
}
/*****************************************************/

/**Сортировка кучей (пирамидальная) - heap_sort**/
template <typename Type>
void heap_create(Type* parray, int size, int index) {
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
void heap_sort(Type* parray, int size) {
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

/*************Цикличная сортировка - cycle_sort************/
template <typename Type>
void cycle_sort(Type* parray, int size) {
    Type element;
    int small;
    for (int i = 0; i <= size - 2; i++) {
        element = parray[i];
        small = i;
        for (int j = i + 1; j < size; j++) {
            if (parray[j] < element) {
                small++;
            }
        }
        if (small == i) {
            continue;
        }
        while (element == parray[small]) {
            small++;
        }
        if (small != i) {
            std::swap(parray[small], element);
        }
        while (small != i) {
            small = i;
            for (int j = i + 1; j < size; j++) {
                if (parray[j] < element) {
                    small += 1;
                }
            }
            while (element == parray[small]) {
                small += 1;
            }
            if (element != parray[small]) {
                std::swap(parray[small], element);
            }
        }
    }
}
/**********************************************************/


/*--------------------------------------------------*/
/*------------СОРТИРОВКИ РАСПРЕДЕЛЕНИЕМ-------------*/
/*--------------------------------------------------*/


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

/*******Сортировка подсчетом - count_sort*******/
template <typename Type>
void count_sort(std::vector<Type>& arr) {

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

/********Бисерная сортировка - bead_sort********/
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
/***********************************************/

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
    int** bucket = new int* [10];
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

/*******Голубинная сортировка - pigeonhole_sort*******/
void pigeonhole_sort(int* arr, int length) {
    //const int MAX_ELEMENTS = 10'000;
    //int  pigeon_array[MAX_ELEMENTS] = { 0 };
    int* temp_array = arr;
    int max_element = 0;
    int min_element = 0;
    int range = 0;
    int i;
    // Get the min_element and max_element from the given array
    for (i = 0; i < length; i++) {
        if (arr[i] < min_element)
            min_element = arr[i];
        if (arr[i] > max_element)
            max_element = arr[i];
    }
    // Get the range
    range = (max_element - min_element) + 1;
    // Initialize the pigeonHoleArray with zero
    int* pigeon_array = new int[range];
    for (i = 0; i < range; i++) {
        pigeon_array[i] = 0;
    }
    // place the elements in pigeonHoleArray
    for (i = 0; i < length; i++, temp_array++) {
        pigeon_array[*temp_array - min_element] += 1;
    }
    // copy from pigeonHoleArray to original array
    for (i = 0, temp_array = &arr[0]; i < range; i++) {
        while (pigeon_array[i] > 0) {
            pigeon_array[i]--;
            *temp_array++ = i + min_element;
        }
    }
}
/*****************************************************/


/*--------------------------------------------------*/
/*-------------СОРТИРОВКИ СЛИЯНИЕМ------------------*/
/*--------------------------------------------------*/


/*********Нитевидная сортировка - strand_sort*********/
template <typename Type>
void strand_sort(std::list<Type>& lst) {
    //std::list<T> strandSort(std::list<T> lst) {
    if (lst.size() <= 1)
        return;
    //return lst;
    std::list<Type> result;
    std::list<Type> sorted;
    while (!lst.empty()) {
        sorted.push_back(lst.front());
        lst.pop_front();
        for (typename std::list<Type>::iterator it = lst.begin(); it != lst.end(); ) {
            if (sorted.back() <= *it) {
                sorted.push_back(*it);
                it = lst.erase(it);
            }
            else
                it++;
        }
        result.merge(sorted);
    }
    lst = result;
    //return result;
}
/*****************************************************/

/****Сортировка слиянием - merge_sort version_1.0*****/
template <typename Type>
void merge_sort(Type* arr, size_t size) {
    if (size == 1) { return; }
    merge_sort(arr, size / 2);
    merge_sort(&arr[size / 2], size - size / 2);

    size_t liter = 0;
    size_t riter = 0;
    Type* tmp = new Type[size];

    for (size_t i = 0; i < size; i++) {
        if (arr[liter] < arr[size / 2 + riter])
            tmp[i] = arr[liter++];
        else
            tmp[i] = arr[size / 2 + riter++];

        if (liter == size / 2) {
            while (riter < size - size / 2)
                tmp[++i] = arr[size / 2 + riter++];
            break;
        }
        else if (riter == size - size / 2) {
            while (liter < size / 2)
                tmp[++i] = arr[liter++];
            break;
        }
    }
    for (size_t i = 0; i < size; i++) {
        arr[i] = tmp[i];
    }
    delete[] tmp;
}
/*****************************************************/

/****Сортировка слиянием - merge_sort version_2.0*****/
template <typename Type>
void merge_sort2(Type* arr, size_t size) {
    if (size < 2) { return; }
    merge_sort2(arr, size / 2);
    merge_sort2(&arr[size / 2], size - (size / 2));
    Type* temp_array = new Type[size];
    size_t id_temp = 0, id_left = 0, id_right = size / 2;
    while ((id_left < size / 2) && (id_right < size)) {
        if (arr[id_left] < arr[id_right]) {
            temp_array[id_temp++] = arr[id_left++];
        }
        else {
            temp_array[id_temp++] = arr[id_right++];
        }
    }
    while (id_left < size / 2) {
        temp_array[id_temp++] = arr[id_left++];
    }
    while (id_right < size) {
        temp_array[id_temp++] = arr[id_right++];
    }
    for (id_left = 0; id_left < size; id_left++) {
        arr[id_left] = temp_array[id_left];
    }
    delete[] temp_array;
}
/*****************************************************/


/*--------------------------------------------------*/
/*-------------ГИБРИДНЫЕ СОРТИРОВКИ-----------------*/
/*--------------------------------------------------*/


/***********Гибридная сортировка - tim_sort***********/
void insertion_sort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void merge(int arr[], int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    int* left = new int[len1];
    int* right = new int[len2];

    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }
    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
}

void tim_sort(int arr[], int n) {
    const int RUN = 32;
    for (int i = 0; i < n; i += RUN) {
        insertion_sort(arr, i, std::min((i + RUN - 1), (n - 1)));
    }
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}
/*****************************************************/

/************Интроспективная сортировка - intro_sort*************/
void swap_value(int* a, int* b) {
    int* temp = a;
    a = b;
    b = temp;
    return;
}

// Сортировка вставками, при определенных условиях
void insertion_isort(int arr[], int* begin, int* end) {
    int left = begin - arr;
    int right = end - arr;

    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    return;
}

// Поиск средней опорной точки
int* partition_isort(int arr[], int low, int high) {
    int pivot = arr[high];  // pivot
    int i = (low - 1);      // Index of smaller element
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (arr + i + 1);
}

// Поиск среднего медианного значения
int* median_three(int* a, int* b, int* c) {
    if (*a < *b && *b < *c)
        return (b);
    if (*a < *c && *c <= *b)
        return (c);
    if (*b <= *a && *a < *c)
        return (a);
    if (*b < *c && *c <= *a)
        return (c);
    if (*c <= *a && *a < *b)
        return (a);
    if (*c <= *b && *b <= *a)
        return (b);
}

// Служебная функция для сортировки
void introsort_util(int arr[], int* begin, int* end, int depth_limit) {

    int size = end - begin;
    if (size < 16) {
        insertion_isort(arr, begin, end);
        return;
    }
    if (depth_limit == 0) {
        std::make_heap(begin, end + 1);
        std::sort_heap(begin, end + 1);
        return;
    }
    int* pivot = median_three(begin, begin + size / 2, end);
    swap_value(pivot, end);
    int* partitionPoint = partition_isort(arr, begin - arr, end - arr);
    introsort_util(arr, begin, partitionPoint - 1, depth_limit - 1);
    introsort_util(arr, partitionPoint + 1, end, depth_limit - 1);
    return;
}

void intro_sort(int arr[], int* begin, int* end) {
    int depthLimit = 2 * log(end - begin);
    introsort_util(arr, begin, end, depthLimit);
    return;
}
/*****************************************************************/


/*--------------------------------------------------*/
/*-------------ПАРАЛЛЕЛЬНЫЕ СОРТИРОВКИ--------------*/
/*--------------------------------------------------*/


/*************Битонная сортировка - bitonic_sort************/
/*Реализация для степеней двойки (иначе будет нарушена логика)*/
template <class Type>
void compare(Type* items, int i, int j, int dir) {
    if (dir == 1 && (items[i] > items[j]) || (dir == 0 && items[i] < items[j])) {
        std::swap(items[i], items[j]);
    }
}
// Sorts a bitonic sequence in the specified order.
template <class Type>
void bitonic_merge(Type* items, int lo, int n, bool dir) {
    if (n > 1) {
        int m = n / 2;
        for (int i = lo; i < lo + m; ++i) {
            compare(items, i, (i + m), dir);
        }
        bitonic_merge(items, lo, m, dir);
        bitonic_merge(items, lo + m, m, dir);
    }
}
// Sorts the given sequence in the specified order.
template <class Type>
void bitonic_sort(Type* items, int lo, int n, bool dir) {
    if (n > 1) {
        // Divide the array into two partitions and then sort 
        // the partitions in different directions.
        int m = n / 2;
        bitonic_sort(items, lo, m, 1);
        bitonic_sort(items, lo + m, m, 0);
        // Merge the results.
        bitonic_merge(items, lo, n, dir);
    }
}
// Sorts the given sequence in increasing order.
template <class Type>
void bitonic_sort(Type* items, int size) {
    bitonic_sort(items, 0, size, 1);
}
/***********************************************************/



/*###########################--ТЕСТЫ--#########################*/
/*
"Bubble_sort" ---> 		size: 1000; 	    time: 0,018000 сек.;
"Bubble_sort" ---> 		size: 10000; 	    time: 1,050000 сек.;
"Bubble_sort" ---> 		size: 100000; 	    time: 88,943000 сек.;

"Odd_even_sort" ---> 	size: 1000; 	    time: 0,043000 сек.;
"Odd_even_sort" ---> 	size: 10000; 	    time: 2,281000 сек.;
"Odd_even_sort" ---> 	size: 100000; 	    time: 224,592000 сек.;

"Shaker_sort" ---> 		size: 1000; 	    time: 0,012000 сек.;
"Shaker_sort" ---> 		size: 10000; 	    time: 0,588000 сек.;
"Shaker_sort" ---> 		size: 100000; 	    time: 59,966000 сек.;

"Comb_sort" ---> 		size: 1000; 	    time: 0,009000 сек.;
"Comb_sort" ---> 		size: 10000; 	    time: 0,014000 сек.;
"Comb_sort" ---> 		size: 100000; 	    time: 0,132000 сек.;
"Comb_sort" ---> 		size: 1000000; 	    time: 1,182000 сек.;
"Comb_sort" ---> 		size: 10000000;	    time: 11,245000 сек.;

"Gnome_sort" ---> 		size: 1000; 	    time: 0,009000 сек.;
"Gnome_sort" ---> 		size: 10000; 	    time: 0,309000 сек.;
"Gnome_sort" ---> 		size: 100000; 	    time: 15,550000 сек.;
"Gnome_sort" ---> 		size: 1000000; 	    time: 2508,594000 сек.;

"Slow_sort" ---> 		size: 100;		    time: 0,102000 сек.;
"Slow_sort" ---> 		size: 200;		    time: 5,203000 сек.;

"Quick_sort" ---> 		size: 1000; 	    time: 0,005000 сек.;
"Quick_sort" ---> 		size: 10000; 	    time: 0,010000 сек.;
"Quick_sort" ---> 		size: 100000; 	    time: 0,047000 сек.;
"Quick_sort" --->		size: 1000000; 	    time: 0,332000 сек.;
"Quick_sort" --->		size: 10000000;	    time: 3,209000 сек.;
"Quick_sort" --->		size: 100000000;    time: 30,969000 сек.;

"Shell_sort" ---> 		size: 1000; 	    time: 0,006000 сек.;
"Shell_sort" ---> 		size: 10000; 	    time: 0,010000 сек.;
"Shell_sort" ---> 		size: 100000; 	    time: 0,090000 сек.;
"Shell_sort" ---> 		size: 1000000; 	    time: 0,944000 сек.;
"Shell_sort" ---> 		size: 10000000;     time: 12,683000 сек.;
"Shell_sort" ---> 		size: 100000000;    time: 175,856000 сек.;

"Insertion_sort" ---> 	size: 1000; 	    time: 0,008000 сек.;
"Insertion_sort" ---> 	size: 10000; 	    time: 0,266000 сек.;
"Insertion_sort" ---> 	size: 100000; 	    time: 24,322000 сек.;

"Binary_insertion_sort" size: 1000;      	time: 0,006000 сек.;
"Binary_insertion_sort" size: 10000; 	    time: 0,211000 сек.;
"Binary_insertion_sort" size: 100000; 	    time: 16,977000 сек.;

"Pancake_sort" ---> 	size: 1000; 	    time: 0,015000 сек.;
"Pancake_sort" ---> 	size: 10000; 	    time: 0,658000 сек.;
"Pancake_sort" ---> 	size: 100000; 	    time: 50,251000 сек.;

"Heap_sort" ---> 		size: 1000; 	    time: 0,005000 сек.;
"Heap_sort" ---> 		size: 10000; 	    time: 0,025000 сек.;
"Heap_sort" ---> 		size: 100000; 	    time: 0,224000 сек.;
"Heap_sort" ---> 		size: 1000000; 	    time: 2,486000 сек.;
"Heap_sort" ---> 		size: 10000000; 	time: 30,463000 сек.;
"Heap_sort" ---> 		size: 100000000; 	time: 442,094000 сек.;

"Cycle_sort" ---> 		size: 1000; 	    time: 0,023000 сек.;
"Cycle_sort" ---> 		size: 10000; 	    time: 1,393000 сек.;
"Cycle_sort" ---> 		size: 100000; 	    time: 130,259000 сек.;

"Selection_sort" ---> 	size: 1000; 	    time: 0,009000 сек.;
"Selection_sort" ---> 	size: 10000; 	    time: 0,353000 сек.;
"Selection_sort" ---> 	size: 100000; 	    time: 33,686000 сек.;

"Pigeonhole_sort" ---> 	size: 1000;     	time: 0,004000 сек.;
"Pigeonhole_sort" ---> 	size: 10000; 	    time: 0,006000 сек.;
"Pigeonhole_sort" ---> 	size: 100000; 	    time: 0,012000 сек.;
"Pigeonhole_sort" ---> 	size: 1000000; 	    time: 0,031000 сек.;
"Pigeonhole_sort" ---> 	size: 10000000; 	time: 0,275000 сек.;
"Pigeonhole_sort" ---> 	size: 100000000; 	time: 1,960000 сек.;
"Pigeonhole_sort" ---> 	size: 1000000000; 	time: 174,459000 сек.;

"Bead_sort" ---> 		size: 1000; 	    time: 1,221000 сек.;
"Bead_sort" ---> 		size: 10000; 	    time: 12,980000 сек.;
"Bead_sort" ---> 		size: 100000; 	    time: ERROR - Переполнение буфера;

"Bucket_sort" --->		size: 1000; 	    time: 0,017000 сек.;
"Bucket_sort" ---> 		size: 10000; 	    time: 0,012000 сек.;
"Bucket_sort" ---> 		size: 100000; 	    time: 0,037000 сек.;
"Bucket_sort" ---> 		size: 1000000; 	    time: 0,312000 сек.;
"Bucket_sort" ---> 		size: 10000000; 	time: 2,588000 сек.;
"Bucket_sort" ---> 		size: 100000000; 	time: 45,854000 сек.;
"Bucket_sort" ---> 		size: 1000000000; 	time: ERROR - Переполнение;

"Bucket_sort_V2" --->	size: 1000; 	    time: 0,013000 сек.;
"Bucket_sort_V2" ---> 	size: 10000; 	    time: 0,013000 сек.;
"Bucket_sort_V2" ---> 	size: 100000; 	    time: 0,074000 сек.;
"Bucket_sort_V2" ---> 	size: 1000000; 	    time: 0,673000 сек.;
"Bucket_sort_V2" ---> 	size: 10000000; 	time: 6,230000 сек.;
"Bucket_sort_V2" ---> 	size: 100000000; 	time: 79,333000 сек.;

"Radix_sort" ---> 		size: 1000; 	    time: 0,017000 сек.;
"Radix_sort" ---> 		size: 10000; 	    time: 0,015000 сек.;
"Radix_sort" ---> 		size: 100000; 	    time: 0,099000 сек.;
"Radix_sort" ---> 		size: 1000000; 	    time: 0,683000 сек.;
"Radix_sort" ---> 		size: 10000000; 	time: 5,524000 сек.;
"Radix_sort" ---> 		size: 100000000; 	time: 64,526000 сек.;

"Radix_sort_V2" ---> 	size: 1000; 	    time: 0,012000 сек.;
"Radix_sort_V2" ---> 	size: 10000; 	    time: 0,025000 сек.;
"Radix_sort_V2" ---> 	size: 100000; 	    time: 0,137000 сек.;
"Radix_sort_V2" ---> 	size: 1000000; 	    time: 0,874000 сек.;
"Radix_sort_V2" ---> 	size: 10000000; 	time: 8,474000 сек.;
"Radix_sort_V2" ---> 	size: 100000000; 	time: 84,104000 сек.;

"Count_sort" ---> 		size: 1000; 	    time: 0,014000 сек.;
"Count_sort" ---> 		size: 10000; 	    time: 0,007000 сек.;
"Count_sort" ---> 		size: 100000;    	time: 0,019000 сек.;
"Count_sort" ---> 		size: 1000000; 	    time: 0,227000 сек.;
"Count_sort" ---> 		size: 10000000; 	time: 2,702000 сек.;
"Count_sort" ---> 		size: 100000000; 	time: 32,195000 сек.;

"Strand_sort" ---> 		size: 1000; 	    time: 0,075000 сек.;
"Strand_sort" ---> 		size: 10000; 	    time: 1,333000 сек.;
"Strand_sort" ---> 		size: 100000; 	    time: 48,934000 сек.;

"Merge_sort" ---> 		size: 1000; 	    time: 0,010000 сек.;
"Merge_sort" ---> 		size: 10000; 	    time: 0,023000 сек.;
"Merge_sort" ---> 		size: 100000; 	    time: 0,230000 сек.;
"Merge_sort" ---> 		size: 1000000; 	    time: 2,140000 сек.;
"Merge_sort" ---> 		size: 10000000; 	time: 22,954000 сек.;
"Merge_sort" ---> 		size: 100000000; 	time: 265,275000 сек.;

"Merge_sort_V2" ---> 	size: 1000; 	    time: 0,007000 сек.;
"Merge_sort_V2" ---> 	size: 10000; 	    time: 0,018000 сек.;
"Merge_sort_V2" ---> 	size: 100000; 	    time: 0,175000 сек.;
"Merge_sort_V2" ---> 	size: 1000000; 	    time: 1,498000 сек.;
"Merge_sort_V2" ---> 	size: 10000000; 	time: 15,081000 сек.;
"Merge_sort_V2" ---> 	size: 100000000; 	time: 163,070000 сек.;

"Tim_sort" ---> 		size: 1000; 	    time: 0,006000 сек.;
"Tim_sort" ---> 		size: 10000; 	    time: 0,015000 сек.;
"Tim_sort" ---> 		size: 100000; 	    time: 0,063000 сек.;
"Tim_sort" ---> 		size: 1000000; 	    time: 0,593000 сек.;
"Tim_sort" ---> 		size: 10000000; 	time: 6,586000 сек.;
"Tim_sort" ---> 		size: 100000000; 	time: 92,469000 сек.;

"Bitonic_sort" --->		size: 8; 		     time: 0,007000 сек.;
"Bitonic_sort" --->		size: 16; 		     time: 0,006000 сек.;
"Bitonic_sort" --->		size: 1024; 	     time: 0,021000 сек.;
"Bitonic_sort" --->		size: 16384; 	     time: 0,082000 сек.;
"Bitonic_sort" --->		size: 131072; 	     time: 0,706000 сек.;
"Bitonic_sort" --->		size: 1048576; 	     time: 6,886000 сек.;
"Bitonic_sort" --->		size: 16777216;      time: 138,450000 сек.;

"Intro_sort" ---> 		size: 1000;      	time: 0,005000 сек.;
"Intro_sort" ---> 		size: 10000; 	    time: 0,014000 сек.;
"Intro_sort" ---> 		size: 100000; 	    time: 0,149000 сек.;
"Intro_sort" ---> 		size: 1000000; 	    time: 1,645000 сек.;
"Intro_sort" ---> 		size: 10000000; 	time: 17,179000 сек.;
"Intro_sort" ---> 		size: 100000000; 	time: 137,566000 сек.;

"Tree_sort" ---> 		size: 1000; 	    time: 0,009000 сек.;
"Tree_sort" ---> 		size: 10000; 	    time: 0,026000 сек.;
"Tree_sort" ---> 		size: 100000; 	    time: 0,303000 сек.;
"Tree_sort" ---> 		size: 1000000; 	    time: 7,213000 сек.;
"Tree_sort" ---> 		size: 10000000; 	time: 592,230000 сек.;

"STD::Sort" ---> 		size: 1000; 	    time: 0,004000 сек.;
"STD::Sort" ---> 		size: 10000; 	    time: 0,021000 сек.;
"STD::Sort" ---> 		size: 100000; 	    time: 0,212000 сек.;
"STD::Sort" ---> 		size: 1000000; 	    time: 1,598000 сек.;
"STD::Sort" ---> 		size: 10000000; 	time: 15,297000 сек.;
"STD::Sort" ---> 		size: 100000000; 	time: 105,975000 сек.;

"STD::Stable_sort" --> 	size: 1000; 	    time: 0,006000 сек.;
"STD::Stable_sort" --> 	size: 10000; 	    time: 0,019000 сек.;
"STD::Stable_sort" --> 	size: 100000; 	    time: 0,155000 сек.;
"STD::Stable_sort" --> 	size: 1000000; 	    time: 1,397000 сек.;
"STD::Stable_sort" --> 	size: 10000000; 	time: 15,348000 сек.;
"STD::Stable_sort" --> 	size: 100000000; 	time: 159,469000 сек.;

"STD::Partial_sort" -> 	size: 1000; 	    time: 0,007000 сек.;
"STD::Partial_sort" -> 	size: 10000; 	    time: 0,019000 сек.;
"STD::Partial_sort" -> 	size: 100000; 	    time: 0,132000 сек.;
"STD::Partial_sort" -> 	size: 1000000; 	    time: 1,696000 сек.;
"STD::Partial_sort" -> 	size: 10000000; 	time: 22,185000 сек.;
"STD::Partial_sort" -> 	size: 100000000; 	time: 306,363000 сек.;

"STD::Sort_heap" ---> 	size: 1000; 	    time: 0,007000 сек.;
"STD::Sort_heap" ---> 	size: 10000; 	    time: 0,021000 сек.;
"STD::Sort_heap" ---> 	size: 100000; 	    time: 0,182000 сек.;
"STD::Sort_heap" ---> 	size: 1000000; 	    time: 1,756000 сек.;
"STD::Sort_heap" ---> 	size: 10000000; 	time: 22,982000 сек.;
"STD::Sort_heap" ---> 	size: 100000000; 	time: 309,567000 сек.;

"STD::Qsort" ---> 		size: 1000; 	    time: 0,007000 сек.;
"STD::Qsort" ---> 		size: 10000; 	    time: 0,013000 сек.;
"STD::Qsort" ---> 		size: 100000; 	    time: 0,104000 сек.;
"STD::Qsort" ---> 		size: 1000000; 	    time: 0,924000 сек.;
"STD::Qsort" ---> 		size: 10000000; 	time: 6,067000 сек.;
"STD::Qsort" ---> 		size: 100000000; 	time: 83,812000 сек.;
*/
/*#############################################################*/
