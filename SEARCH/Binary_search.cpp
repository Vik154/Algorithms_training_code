#include <iostream>
#include <algorithm>
#include <cmath>

// Определение разера массива по указателям
template <typename Type>
size_t len(Type *begin, Type *end) {
	Type *cur = begin;
	size_t count = 0;
	if (begin == end) { return 1; }
	while (cur != end) {
		count++;
		cur++;
	}
	return count;
}

 /***************Бинарный поиск - binary_search***************/
template <typename Type>
size_t binary_search(Type *first, Type *last, const Type &elm) {
	
	size_t mid;
	size_t id_beg = 0;
	size_t id_end = len(first, last);

	while (id_beg <= id_end) {
		mid = id_beg + (id_end - id_beg) / 2;
		if (elm == first[mid]) {
			return mid;
		}
		else if (elm > first[mid]) {
			id_beg = mid + 1;
		}
		else {
			id_end = mid - 1;
		}
	}
	return 0;
}
/**************************************************************/
// Рекурсивынй вариант
template <typename Type>
size_t binary_search_rec(Type *arr, const Type &value, size_t begin = 0, size_t end = 0) {

	if (begin > end) { return -1; }
	size_t mid = begin + (end - begin) / 2;	// Формула, чтобы не было переполнения
	if (value == arr[mid]) {
		return mid;
	}
	if (value < arr[mid]) {
		return binary_search_rec(arr, value, begin, mid - 1);
	}
	return binary_search_rec(arr, value, mid + 1, end);
}

// Для контейнеров с логикой итераторов
template<class ForwardIt, class T>
bool spbinary_search(ForwardIt first, ForwardIt last, const T& value) {
	first = std::lower_bound(first, last, value);
	return (!(first == last) && !(value < *first));
}

// Генерация случайных чаров для теста
char random_char(int range) {
	const int MAX = 26;
	char alpha[MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
						  'h', 'i', 'j', 'k', 'l', 'm', 'n',
						  'o', 'p', 'q', 'r', 's', 't', 'u',
						  'v', 'w', 'x', 'y', 'z' };
	std::string result = "";
	for (int i = 0; i < range; i++)
		result = result + alpha[rand() % MAX];

	return result[range % MAX];
}

// Тесты времени пойска в отсортированных контейнерах
void time_test(size_t length) {
	setlocale(LC_ALL, "Ru");
	size_t  size = length;
	size_t *uint_array = new size_t[size];
	double *doub_array = new double[size];
	char   *char_array = new char[size];
	char	ch = 'a';

	for (size_t i = 0; i < size; ++i) {
		uint_array[i] = rand() % RAND_MAX;
		doub_array[i] = round(rand() % RAND_MAX * 0.003) / 100;
		char_array[i] = char(ch);
		if (ch != 'z') { ch++; }
		else ch = 'a';
	}
	// Сортировка массивов
	std::sort(uint_array, uint_array + size);
	std::sort(doub_array, doub_array + size);
	std::sort(char_array, char_array + size);
	// Тесты итеративных версий
	clock_t timer = clock();
	size_t uarr = binary_search(uint_array, uint_array + size, static_cast<size_t>(rand() % RAND_MAX));
	clock_t ui_time = clock() - timer;
	
	timer = clock();
	size_t darr = binary_search(doub_array, doub_array + size, round(rand() % RAND_MAX * 0.003) / 100);
	clock_t do_time = clock() - timer;
	
	timer = clock();
	size_t carr = binary_search(char_array, char_array + size, random_char(50));
	clock_t ch_time = clock() - timer;

	std::cout << "1. Integer_id = " << uarr << "; Time_search: " << double(ui_time) / CLOCKS_PER_SEC << " sec.\n";
	std::cout << "2. Float_id = "   << darr << "; Time_search: " << double(do_time) / CLOCKS_PER_SEC << " sec.\n";
	std::cout << "3. Char_id = "    << carr << "; Time_search: " << double(ch_time) / CLOCKS_PER_SEC << " sec.\n";
}


int main() {

	time_test(1'000'000);
}
