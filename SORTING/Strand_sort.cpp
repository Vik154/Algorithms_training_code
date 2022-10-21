#include <iostream>
#include <list>

/*********Нитевидная сортировка - strand_sort*********/
template <typename T>
void strand_sort(std::list<T> &lst) {
//std::list<T> strandSort(std::list<T> lst) {
    if (lst.size() <= 1)
        return;
        //return lst;
    std::list<T> result;
    std::list<T> sorted;
    while (!lst.empty()) {
        sorted.push_back(lst.front());
        lst.pop_front();
        for (typename std::list<T>::iterator it = lst.begin(); it != lst.end(); ) {
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

void sort_test(int size_array) {
	setlocale(LC_ALL, "Russian");
	if (size_array < 1) { std::cout << "AAA";  return; }
	clock_t time = clock();
	int size = size_array;
	//int* my_array = new int[size];
    std::list<int> lst;
    std::cout << "Идёт заполнение массива: ";
	for (int i = 0; i < size; ++i) {
		//my_array[i] = rand() % 1'000'000;
        lst.push_back(rand() % 1'000'000);
    }
	time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
	time = clock();
	std::cout << "Идёт сортировка массива на " << size << " элементов: ";
    //pigeonhole_sort(my_array, size);
    strand_sort(lst);
    time = clock() - time;
	std::cout << double(time) / CLOCKS_PER_SEC << " сек." << std::endl;
    /*
    for (int i = 0; i < size_array; ++i) {
        std::cout << my_array[i] << " ";
    }
    */
    //delete[] my_array;
    /*
    for (auto const& value : lst) {
        std::cout << value << " ";
    }
    */
    lst.clear();
}

int main() {
    sort_test(10'000);
	return 0;
}
