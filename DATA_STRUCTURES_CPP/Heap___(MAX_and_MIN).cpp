/* MAX HEAP - Максимальная куча (самый большой ключ находится в корне) */
// Ключи родительских узлов всегда больше или равны ключам дочерних узлов
/* MIN HEAP - Минимальная куча (самый меньший ключ находится в корне) */
// Ключи родительских узлов меньше или равны ключам дочерних узлов
#include <iostream>
#include <stdexcept>
#include <vector>

using std::vector;
using std::out_of_range;
using std::swap;
using std::cout;
using std::endl;


template <typename Type>
class Heap_max {
protected:
    vector<Type> heap_elem;                                   // vector для хранения элементов кучи
    int get_parent_id(const int& id) { return (id - 1) / 2;}  // Возвращает индекс родителя
    int get_rchild_id(const int& id) { return (2 * id + 2);}  // Возвращает индекс правого потомка
    int get_lchild_id(const int& id) { return (2 * id + 1);}  // Возвращает индекс левого потомка
    void heapify_down(const int& id);                         // Рекурсивно перемещает элемент Array[id] вниз по дереву
    void heapify_up(const int& id);                           // Перемещает Array[id] вверх по дереву
public:
    const size_t size() const { return heap_elem.size(); }    // Возвращаем размер кучи
    bool empty() const { return heap_elem.size() == 0; }      // true если пуста, иначе false
    void push(const Type &key);                               // Добавить элемент в кучу
    void pop();                                               // Удалить элемент из кучи с наивысшим приоритетом
    Type top();                                               // Получить элемент с наивысшим приоритетом
};

template <typename Type>
class Heap_min {
private:
    vector<Type> heap_elem;                                   // vector для хранения элементов кучи
    int get_parent_id(const int& id) { return (id - 1) / 2;}  // Возвращает индекс родителя
    int get_rchild_id(const int& id) { return (2 * id + 2);}  // Возвращает индекс правого потомка
    int get_lchild_id(const int& id) { return (2 * id + 1);}  // Возвращает индекс левого потомка
    void heapify_down(const int& id);                         // Рекурсивно перемещает элемент Array[id] вниз по дереву
    void heapify_up(const int& id);                           // Перемещает Array[id] вверх по дереву
public:
    const size_t size() const { return heap_elem.size(); }    // Возвращаем размер кучи
    bool empty() const { return heap_elem.size() == 0; }      // true если пуста, иначе false
    void push(const Type& key);                               // Добавить элемент в кучу
    void pop();                                               // Удалить элемент из кучи с наивысшим приоритетом
    Type top();                                               // Получить элемент с наивысшим приоритетом
};

/************************MAX HEAP************************/
template <typename Type>
void Heap_max<Type>::heapify_down(int const &id) {
    int left = get_lchild_id(id);          // Получить левого потомка узла с индексом 'id'
    int right = get_rchild_id(id);        // Получить правого потомка узла с индексом 'id'
    int largest = id;                       // Запомнить 'id' наибольшего узла

    // Cравниваем Array[id] с его левым и правым дочерними элементами и находим наибольшее значение
    if (left < size() && heap_elem[left] > heap_elem[id])
        largest = left;
    if (right < size() && heap_elem[right] > heap_elem[largest])
        largest = right;
    if (largest != id) {                         // Если индекс наибольшего и найденого не равны, иначе ничего не делать
        swap(heap_elem[id], heap_elem[largest]); // Поменять местами потомка и родителя
        heapify_down(largest);                   // И вызвать рекурсивно heapify-down для потомка
    }
}

template <typename Type>
void Heap_max<Type>::heapify_up(const int &id) {
    if (id && heap_elem[get_parent_id(id)] < heap_elem[id]) {  // Ели узел с индексом 'id' и его родитель нарушают свойство кучи
        swap(heap_elem[id], heap_elem[get_parent_id(id)]);     // Поменять их местами, если свойство кучи нарушено
        heapify_up(get_parent_id(id));                         // Вызвать heapify-up для родителя
    }
}

template <typename Type>
void Heap_max<Type>::push(const Type &key) {
    heap_elem.push_back(key);                   // Вставить новый элемент в конец вектора
    int index = static_cast<int>(size() - 1);   // Получить индекс элемента
    heapify_up(index);                          // Вызов heapify-up от index
}

template <typename Type>
void Heap_max<Type>::pop() {
    try {
        if (size() == 0) {
            throw out_of_range("Heap is emty!");    // Если в куче нет элементов, бросить исключение, иначе
        }
        heap_elem[0] = heap_elem.back();            // Заменить корень кучи последним элементом вектора
        heap_elem.pop_back();                       // И удалить заменённый элемент
        heapify_down(0);                            // Вызвать heapify-down для корня
    }
    catch (const out_of_range& msg) {               // Ловим и печатаем исключение
        cout << endl << msg.what();
    }
}

template <typename Type>
Type Heap_max<Type>::top() {
    try {
        if (size() == 0) {              // Если в куче нет элементов, бросить исключение,
            throw out_of_range("Heap is empty, stupid man!");
        }
        return heap_elem.at(0);         // Иначе возвращаем верхний (первый) элемент
    }
    catch (const out_of_range& msg) {   // ловим и печатаем исключение
        cout << endl << msg.what();
        return Type(0);
    }
}

/************************MIN HEAP************************/
template <typename Type>
void Heap_min<Type>::heapify_down(int const& id) {
    int left = get_lchild_id(id);         // Получить левого потомка узла с индексом 'id'
    int right = get_rchild_id(id);        // Получить правого потомка узла с индексом 'id'
    int smallest = id;                    // Запомнить 'id' НАИМЕНЬШЕГО узла

    // Cравниваем Array[id] с его левым и правым дочерними элементами и находим наибольшее значение
    if (left < size() && heap_elem[left] < heap_elem[id])
        smallest = left;
    if (right < size() && heap_elem[right] < heap_elem[smallest])
        smallest = right;
    if (smallest != id) {                         // Если индекс наибольшего и найденого не равны, иначе ничего не делать
        swap(heap_elem[id], heap_elem[smallest]); // Поменять местами потомка и родителя
        heapify_down(smallest);                   // И вызвать рекурсивно heapify-down для потомка
    }
}

template <typename Type>
void Heap_min<Type>::heapify_up(const int& id) {
    if (id && heap_elem[get_parent_id(id)] > heap_elem[id]) {  // Ели узел с индексом 'id' и его родитель нарушают свойство кучи
        swap(heap_elem[id], heap_elem[get_parent_id(id)]);     // Поменять их местами, если свойство кучи нарушено
        heapify_up(get_parent_id(id));                         // Вызвать heapify-up для родителя
    }
}

template <typename Type>
void Heap_min<Type>::push(const Type& key) {
    heap_elem.push_back(key);                   // Вставить новый элемент в конец вектора
    int index = static_cast<int>(size() - 1);   // Получить индекс элемента
    heapify_up(index);                          // Вызов heapify-up от index
}

template <typename Type>
void Heap_min<Type>::pop() {
    try {
        if (size() == 0) {
            throw out_of_range("Heap is emty!");    // Если в куче нет элементов, бросить исключение, иначе
        }
        heap_elem[0] = heap_elem.back();            // Заменить корень кучи последним элементом вектора
        heap_elem.pop_back();                       // И удалить заменённый элемент
        heapify_down(0);                            // Вызвать heapify-down для корня
    }
    catch (const out_of_range& msg) {               // Ловим и печатаем исключение
        cout << endl << msg.what();
    }
}

template <typename Type>
Type Heap_min<Type>::top() {
    try {
        if (size() == 0) {              // Если в куче нет элементов, бросить исключение,
            throw out_of_range("Heap is empty, stupid man!");
        }
        return heap_elem.at(0);         // Иначе возвращаем верхний (первый) элемент
    }
    catch (const out_of_range& msg) {   // ловим и печатаем исключение
        cout << endl << msg.what();
        return Type(0);
    }
}


int main() {
    setlocale(0, "");
    Heap_max<int> iheap;    Heap_max<double> dheap;
    Heap_min<int> imin;     Heap_min<double> dmin;

    for (int i = 0; i < 20; ++i) {
        iheap.push(rand() % 100);   dheap.push(i * 0.28);
        imin.push(rand() % 100);    dmin.push(i * 0.28);
    }
    cout << "Int max heap: ";
    for (int i = 0; i < 20; ++i) {
        cout << iheap.top() << " ";
        iheap.pop();
    }
    cout << "\nInt min heap: ";
    for (int i = 0; i < 20; ++i) {
        cout << imin.top() << " ";
        imin.pop();
    }
    cout << "\nDouble max heap: ";
    for (int i = 0; i < 20; ++i) {
        cout << dheap.top() << " ";
        dheap.pop();
    }
    cout << "\nDouble min heap: ";
    for (int i = 0; i < 20; ++i) {
        cout << dmin.top() << " ";
        dmin.pop();
    }
    cout << "\nChecking for emptiness:";
    dheap.top();
    iheap.top();
    return 0;
}