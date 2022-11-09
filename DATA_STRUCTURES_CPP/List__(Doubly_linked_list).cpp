/*--Реализация двусвязного списка - Doubly linked list--*/
#include <iostream>
#include <list>     			                        // Двусвязный список

using std::list;
using std::cout;

template <typename Type>
class List {
private:
    class Node {                                        // List - двусвязный список
    public:                                             // Node - Узел двусвязного списка
        Type  data;                                     // Поле - данные
        Node* next;                                     // Указатель на следующий узел
        Node* prev;                                     // Указатель на следующий узел
        Node(Type d, Node *n = nullptr, Node *p = nullptr) :
            data(d), next(n), prev(p) {}                // Конструктор с параметрами
    };
    Node *head;                                         // Указатель на начало списка
    Node *tail;                                         // Указатель на конец списка
    size_t count;                                       // Кол-во элементов в списке
    Type flag;                                          // Пустая переменная (муляж)
public:
    class Iterator {                                    // Класс итераторов 
    private:
        Node* node;                                     // Указатель на узел, для манипуляций	
    public:
        Iterator(Node* node) : node(node) {}            // Конструктор с параметром
        bool operator==(const Iterator& other) const;   // Проверка на равенство
        bool operator!=(const Iterator& other) const;   // Проверка на неравенство
        void operator++();                              // Префиксный Инкремент слева от операнда (Переход к следующему узлу)
        void operator++(Type);                          // Постфиксный Инкремент справа от операнда	
        Type operator*() const;                         // Получение значения текущего узла, оператор разыменовывания	
    };
    Iterator begin() const;                             // Получить итератор на начало списка
    Iterator end() const;                               // Получить итератор на конец списка
    List();                                             // Конструктор класса без параметров
    List(const Type& data);                             // Конструктор класса с параметром
    List(const List& list);                             // Конструктор копирования
    ~List();                                            // Деструктор

    void push_front(const Type &elm);                   // Добавление узла в начало список (Слева вставка  O<--[]--[] )
    void push_back(const Type &elm);                    // Добавление узла в конец списка  (Справа вставка []--[]-->O )
    void insert(const Iterator &pos, const Type &elm);  // Добавление узла в указанную релевантную позицию
    void insert(size_t pos, const Type &elm);           // Добавление элемента по указанному индексу
    void pop_front();                                   // Удаление узла с начала списка
    void pop_back();                                    // Удаление узла с конца списка
    void clear();                                       // Удаляет все элементы прямого списка.
    void remove(Type elm);                              // Удаляет все элементы в списке, по заданному значению, если оно есть.
    bool empty();                                       // Проверяет, пуст ли прямой список.
    void print();						                // Распечатать список
    void reverse();							            // Развернуть список в обратном порядке
    void sort_bubble();					                // Сортировка пузырьком
    void sort_insertion();  			                // Сортировка вставками
    void sort_selection();  			                // Сортировка выбором
    void sort_merge();		                            // Вызов сортировки слиянием 
    size_t size() const;                                // Получить размер списка
    size_t find(const Type &elm) const;                 // Поиск элемента в списке по значению (возвращает индекс элемента).
    Type& front();                                      // Возвращает ссылку на первый элемент списке.
    Type& back();                                       // Возвращает ссылку на последний элемент списке.    
    Type operator [] (const size_t index);              // Вернуть значение по индексу
    List<Type>& operator + (const List<Type>& list);	// Сложение списков
    List<Type>& operator = (const List<Type>& list);	// Присваивание списков
	bool operator == (const List<Type>& list);	        // Проверка на равенство
	bool operator != (const List<Type>& list);	        // Проверка на неравенство
	bool operator >= (const List<Type>& list);	        // Больше или равно 
	bool operator <= (const List<Type>& list);	        // Меньше или равно
	bool operator >  (const List<Type>& list);	        // Больше
	bool operator <  (const List<Type>& list);	        // Меньше
private:
    Node* _merge_sort(Node*);                           // Сортировка слиянием
    Node* _get_middle(Node*);                           // Получение середины списка, для функции сортировки
    Node* _merge(Node*, Node*);                         // Слияние отсортированных массивов
};


template<typename Type>
List<Type>::List() {
    head = tail = nullptr;
    count = 0;
}

template<typename Type>
List<Type>::List(const Type &data) {
    push_front(data);
}

template <typename Type>
List<Type>::List(const List &list) {
    Node *tmp = list.head;
    while (tmp) {
        push_front(tmp->data);
        tmp = tmp->next;
    }
}

template <typename Type>
List<Type>::~List() {
    clear();
}

template <typename Type>
void List<Type>::push_front(const Type &elm) {
    // (insert)()<--[]--[]--[]--[]<--tail
    Node *new_node = new Node(elm);
    if (head == nullptr) {
        head = tail = new_node;
        count++;
    }
    else {
        head->prev = new_node;
        new_node->next = head;
        head = new_node;
        count++;
    }
}

template <typename Type>
void List<Type>::push_back(const Type& elm) {
    // Head-->[]--[]--[]--[]<--(insert)()
    Node* new_node = new Node(elm);
    if (head == nullptr) {
        head = tail = new_node;
        count++;
    }
    else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
        count++;
    }
}

template <typename Type>
void List<Type>::print() {
    if (!head) {
        std::cout << "List is empty\n";
        return;
    }
    Node *tmp = head;
    std::cout << "Head --> ";
    while (tmp) {
        if (tmp->next) {
            std::cout << tmp->data << " --> ";
            tmp = tmp->next;
        }
        else {
            std::cout << tmp->data << " <-- Tail\n";
            tmp = tmp->next;
        }
    }
}

template <typename Type>
size_t List<Type>::size() const {
    return count;
}

template <typename Type>
void List<Type>::pop_front() {
    if (!head) { return; }
    else if (!head->next) {
        delete head;
        head = tail = nullptr;
        count = 0;
    }
    else {
        Node *tmp  = head->next;
        delete head;
        head = tmp;
        head->prev = nullptr;
        count--;
    }
}

template <typename Type>
void List<Type>::pop_back() {
    if (!head) { return; }
    else if (!head->next) {
        delete head;
        head = tail = nullptr;
        count = 0;
    }
    else {
        Node* tmp = tail->prev;
        delete tail;
        tail = tmp;
        tail->next = nullptr;
        count--;
    }
}

template <typename Type>
void List<Type>::clear() {
    while (head) {
        pop_front();
    }
}

template <typename Type>
void List<Type>::remove(Type elm) {
    if (!head) { return; }
    if (!head->next) {
        if (head->data == elm) {
            pop_back();
        }
        return;
    }
    Node* tmp = head->next;
    while (tmp) {
        cout << "TEMP == " << tmp->data << "\n";
        if (tmp->data == elm) {
            if (tmp == tail) {
                tmp->prev->next = nullptr;
                delete tail;
                tail = tmp->prev;
                count--;
                break;
            }
            else {
                Node* del = tmp;
                tmp->next->prev = tmp->prev;
                tmp->prev->next = tmp->next;
                delete del;
                count--;
            }
        }
        tmp = tmp->next;
    }
    if (head->data == elm) {
        pop_front();
    }

}

// Итератор передается
template <typename Type>
void List<Type>::insert(const Iterator &pos, const Type& elm) {
    Node *new_node = new Node(elm);         // Создать новый узел
    Iterator search = Iterator(head);       // Итератор на первый элемент
    Node* tmp = head;                       // Временный указатель на голову
    while (tmp) {                           // Пока есть элементы в списке, сравнивать итераторы
        if (search == pos) {                // Если адреса ==, тошда
            if (tmp == head) {
                push_front(elm);
                return;
            }
            else {
                tmp->prev->next = new_node;
                new_node->prev = tmp->prev;
                new_node->next = tmp;
                tmp->prev = new_node;
                count++;
                return;
            }
        }
        else {
            tmp = tmp->next;
            search++;
        }
    }
    push_back(elm);
}

// Номер индекса
template <typename Type>
void List<Type>::insert(size_t pos, const Type &elm) {
    if (pos >= count) {
        push_back(elm);
        std::cout << "Индекс > или == кол-ву элементов, поэтому вставка в конец списка\n";
        return;
    }
    if (pos <= 0) {
        push_front(elm);
        std::cout << "Индекс < кол-ва элементов, поэтому вставка в начало списка\n";
        return;
    }
    Node *new_node = new Node(elm);
    Node *tmp = head;
    for (size_t i = 0; i < pos-1; ++i) {
        tmp = tmp->next;
    }
    new_node->next = tmp->next;
    new_node->prev = tmp;
    tmp->next->prev = new_node;
    tmp->next = new_node;
    count++;
}

template <typename Type>
size_t List<Type>::find(const Type& elm) const {
    if (!head) {
        std::cout << "Not found!\n";
        return 0;
    }
    Node *tmp = head;
    size_t search = 0;
    while (tmp) {
        if (tmp->data == elm) {
            return search;
        }
        search++;
        tmp = tmp->next;
    }
    std::cout << "Not found!\n";
    return 0;
}

template <typename Type>
bool List<Type>::empty() {
    return count;
}

template <typename Type>
Type& List<Type>::front() {
    if (head)
        return head->data;
    else {
        std::cout << "List is empty!\n";
        return flag;
    }
}

template <typename Type>
Type& List<Type>::back() {
    if (tail)
        return tail->data;
    else {
        std::cout << "List is empty!\n";
        return flag;
    }
}

template <typename Type>
Type List<Type>::operator [] (const size_t index) {
    if (index < 0 || index >= count) {
        std::cout << "Некорректный индекс\n";
        return 0;
    }
    Node *tmp = head;
    for (size_t i = 0; i < index; ++i) {
        tmp = tmp->next;
    }
    return tmp->data;
}

template <typename Type>
List<Type>& List<Type>::operator + (const List<Type>& list) {
    if (!list.head) { return *this; }
    Node *tmp = list.head;
    while (tmp) {
        this->push_front(tmp->data);
        tmp = tmp->next;
    }
    return *this;
}

template <typename Type>
List<Type>& List<Type>::operator = (const List<Type>& list) {
    this->clear();
    Node *tmp = list.head;
    while (tmp) {
        push_back(tmp->data);
        tmp = tmp->next;
    }
    return *this;
}

template <typename Type>
bool List<Type>::operator < (const List<Type>& list) {
    if (count != list.count) {
        return false;
    }
    Node *source = head;
    Node *incoming = list.head;
    while (source) {
        if (source->data >= incoming->data) {
            return false;
        }
        source = source->next;
        incoming = incoming->next;
    }
    return true;
}

template <typename Type>
bool List<Type>::operator == (const List<Type>& list) {
    if (count != list.count) {
        return false;
    }
    Node* source = head;
    Node* incoming = list.head;
    while (source) {
        if (source->data != incoming->data) {
            return false;
        }
        source = source->next;
        incoming = incoming->next;
    }
    return true;
}

template <typename Type>
bool List<Type>::operator > (const List<Type>& list) {
    if (count != list.count) {
        return false;
    }
    Node* source = head;
    Node* incoming = list.head;
    while (source) {
        if (source->data <= incoming->data) {
            return false;
        }
        source = source->next;
        incoming = incoming->next;
    }
    return true;
}

template <typename Type>
bool List<Type>::operator != (const List<Type>& list) {
    return !(*this == list);
}

template <typename Type>
bool List<Type>::operator >= (const List<Type>& list) {
    return *this > list || *this == list;
}

template <typename Type>
bool List<Type>::operator <= (const List<Type>& list) {
    return *this < list || *this == list;
}

template <typename Type>
void List<Type>::reverse() {
    Node* temp = nullptr;
    Node* current = head;
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp)
        head = temp->prev;
}

template <typename Type>
void List<Type>::sort_bubble() {
    if (count < 1) { return; }
	Node* left  = head;
	Node* rigth = head->next;
	Node* temp  = new Node(0);

	while (left->next) {
		while (rigth) {
			if (left->data > rigth->data) {
				temp->data = left->data;
				left->data = rigth->data;
				rigth->data = temp->data;
			}
			rigth = rigth->next;
		}
		left  = left->next;
		rigth = left->next;
	}
    delete temp;
}

template <typename Type>
void List<Type>::sort_insertion() {
    if (count < 2) { return; }
	Node *curr = head->next;
	Node *prev = head;

    for (curr; curr; curr = curr->next) {
		Type tmp = curr->data;
		prev = curr->prev;

		while (prev && tmp <= prev->data) {
			prev->next->data = prev->data;
			prev->data = tmp;
			prev = prev->prev;
		}
	}
}

template <typename Type>
void List<Type>::sort_selection() {
    if (count < 2) { return; }
	Node *current = head;
	Node *min_id  = head;
	Node *src_id  = head;
	Node *iterator = head;
	Type tmp_data;
	for (current; current; current = current->next) {
		min_id = current;
		for (src_id = iterator; src_id; src_id = src_id->next) {
			if (src_id->data < min_id->data) {
				min_id = src_id;
			}
		}
		if (current->data != min_id->data) {
			tmp_data = current->data;
			current->data = min_id->data;
			min_id->data = tmp_data;
		}
		iterator = iterator->next;
	}
}

template <typename Type>
typename List<Type>::Node* List<Type>::_get_middle(Node *node) {
    if (!node)
        return node;
    Node *slow, *fast;
    slow = fast = node;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

template <typename Type>
typename List<Type>::Node* List<Type>::_merge_sort(Node* node) {
    if (!node || !node->next)
        return node;
    Node *middle = _get_middle(node);
    Node* left   = node;
    Node* right  = middle->next;
    middle->next = nullptr;
    return _merge(_merge_sort(left), _merge_sort(right));
}

template <typename Type>
typename List<Type>::Node* List<Type>::_merge(Node *left, Node *right) {
 /*
    Рекурсивный вариант - не подходит для больших данных
    if (!left)
        return right;
    if (!right)
        return left;
    if (left->data < right->data) {
        left->next = _merge(left->next, right);
        left->next->prev = left;
        left->prev = nullptr;
        return left;
    }
    else {
        right->next = _merge(left, right->next);
        right->next->prev = right;
        right->prev = nullptr;
        return right;
    }
*/
    Node imitation_head(0);
    Node* current = &imitation_head;
    while (left != nullptr && right != nullptr) {
        if (left->data < right->data) {
            current->next = left;
            left = left->next;
        }
        else {
            current->next = right;
            right = right->next;
        }
        current = current->next;
    }
    current->next = (left == nullptr) ? right : left;
    return imitation_head.next;
}

template <typename Type>
void List<Type>::sort_merge() {
    head = _merge_sort(head);
}

template <typename Type>
typename List<Type>::Iterator List<Type>::begin() const {
    return Iterator(head);
}

template <typename Type>
typename List<Type>::Iterator List<Type>::end() const {
    return Iterator(nullptr);
}

template<typename Type>
bool List<Type>::Iterator::operator==(const Iterator& other) const {  
    if (this == &other) {
        return true;
    }
    return node == other.node;
}

template<typename Type>
bool List<Type>::Iterator::operator!=(const Iterator& other) const {
    return !operator==(other);
}

template <typename Type>
void List<Type>::Iterator::operator ++ () {
    if (node) {
        node = node->next;
    }
}

template<typename Type>
void List<Type>::Iterator::operator ++ (Type) {
    if (node) {
        node = node->next;
    }
}

template<typename Type>
Type List<Type>::Iterator::operator*() const {
    if (node) {
        return node->data;
    }
    return Type();
}


// Функция для мини-теста
void testing(size_t size) {
    srand(time(NULL));
    size_t i, list_size = size;
	List<int64_t> my_list;
	list<int64_t> stl_list;
    clock_t time = clock();

    std::cout << "Начало теста собственный список\nИдёт заполнение списка\n";
    for (i = 0; i < list_size; ++i)
        my_list.push_front(rand() % RAND_MAX);
    time = clock() - time;
    std::cout << "Довавление элементов в начало списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

	time = clock(); my_list.clear(); time = clock() - time;
	std::cout << "Удаление элементов из начала списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	std::cout << "====================Тест завершился====================\n";

    if (list_size < 20'000) {
        std::cout << "Начало теста собственный список\n";
        time = clock();
        for (i = 0; i < list_size; ++i) {
            my_list.push_back(rand() % RAND_MAX);
        }
        time = clock() - time;
        std::cout << "Довавление элементов в конец списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

        time = clock();
        while (my_list.size()) { my_list.pop_back(); }
        time = clock() - time;
        std::cout << "Удаление элементов с конца списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
        std::cout << "====================Тест завершился====================\n";
    }

	std::cout << "\n===STL===STL===STL===STL===STL===STL===STL===STL===STL===STL===\n\n";
	std::cout << "Начало теста STL (List) список\n";
	time = clock();
	for (i = 0; i < list_size; ++i) {
		stl_list.push_front(rand() % RAND_MAX);
	}
	time = clock() - time;
	std::cout << "Довавление элементов в начало списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

	time = clock();
	while (!stl_list.empty()) { stl_list.pop_front(); }
	time = clock() - time;
	std::cout << "Удаление элементов c начала списка: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	std::cout << "====================Тест завершился====================\n";

	std::cout << "\n********************Тесты сортировок********************\n";
	std::cout << "Идёт добавление " << list_size << " рандомных элементов ";
    if (list_size < 15'010) {
        for (i = 0; i < list_size; ++i) {
		    my_list.push_front(rand() % RAND_MAX);
	    }    
        std::cout << "\nИдёт сортировка пузырьком (bubble sort) --> ";
        time = clock();
        my_list.sort_bubble();
        time = clock() - time;
        std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
        std::cout << "Идёт очистка списка\n";
        my_list.clear();
    }
    if (list_size < 30'000) {
        std::cout << "Идёт добавление " << list_size << " рандомных элементов ";
        for (i = 0; i < list_size; ++i) {
            my_list.push_front(rand() % RAND_MAX);
        }
        std::cout << "\nИдёт сортировка вставками (insertion sort) --> ";
        time = clock();
        my_list.sort_insertion();
        time = clock() - time;
        std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

        std::cout << "Идёт очистка списка\n";
        my_list.clear();

        std::cout << "Идёт добавление " << list_size << " рандомных элементов ";
        for (i = 0; i < list_size; ++i) {
            my_list.push_front(rand() % RAND_MAX);
        }
        std::cout << "\nИдёт сортировка выбором (selection sort) --> ";
        time = clock();
        my_list.sort_selection();
        time = clock() - time;
        std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
        
        std::cout << "Идёт очистка списка\n";
        my_list.clear();
    }

    std::cout << "Идёт добавление " << list_size << " рандомных элементов ";
    for (i = 0; i < list_size; ++i) {
        my_list.push_front(rand() % RAND_MAX);
    }
    std::cout << "\nИдёт сортировка слиянием (Merge sort) --> ";
    time = clock();
    my_list.sort_merge();
    time = clock() - time;
    std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
    
	std::cout << "\nТест функции реверса (разворота) списка: ";
	time = clock();
	my_list.reverse();
	time = clock() - time;
	std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	my_list.clear();

	std::cout << "\n==================Тест STL сортировки==================\n";
	std::cout << "Идёт добавление " << list_size << " рандомных элементов ";
	for (i = 0; i < list_size; ++i) {
		stl_list.push_front(rand() % RAND_MAX);
	}
	std::cout << "\nИдёт сортировка встроенная в класс list (sort) --> ";
	time = clock();
	stl_list.sort();
	time = clock() - time;
	std::cout << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	stl_list.clear();
    std::cout << "====================Тест завершился====================\n\n";
}


int main() {
    setlocale(0, "ru");
    testing(1'000'000);
    testing(15'000);
}