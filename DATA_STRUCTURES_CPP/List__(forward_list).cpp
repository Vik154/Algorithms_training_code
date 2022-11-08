/*--Реализация односвязного списка - forward_list--*/
#include <iostream>
#include <forward_list>			                        // Односвязный список

using std::forward_list;
using std::cout;

template <typename Type>
class Forward_list {
private:
    class Node {                                        // Forward - односвязный список
    public:                                             // Node - Узел односвязного списка
        Type  data;                                     // Поле - данные
        Node* next;                                     // Указатель на следующий узел
        Node() : next(nullptr) {}                       // Конструктор без параметров
        Node(Type d, Node* n = nullptr) :               // Конструктор с параметрами
            data(d), next(n) {}
    };
    Node* head;                                         // Указатель на начало списка
    Node* tail;                                         // Указатель на конец списка
    int64_t count;                                      // Кол-во элементов в списке
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
    Forward_list();                                     // Конструктор класса без параметров
    Forward_list(const Type& data);                     // Конструктор класса с параметром
    Forward_list(const Forward_list& list);             // Конструктор копирования
    ~Forward_list();                                    // Деструктор

    void push_front(const Type&);                       // Добавление узла в начало список
    void push_back(const Type&);                        // Добавление узла в конец списка
    void insert_after(Iterator ins, const Type&);       // Добавляет элементы в прямой список после указанной позиции.
    void pop_front();                                   // Удаление узла с начала списка
    void pop_back();                                    // Удаление узла с конца списка
    void clear();                                       // Удаляет все элементы прямого списка.
    void remove(const Type& val);                       // Удаляет все элементы в списке, по заданному значению, если оно есть.
    bool empty();                                       // Проверяет, пуст ли прямой список.
    void print();						                // Распечатать список
    void reverse();							            // Развернуть список в обратном порядке
    void sort_bubble();					                // Сортировка пузырьком
    void sort_insertion();  			                // Сортировка вставками
    void sort_selection();  			                // Сортировка выбором
    void sort_merge();		                            // Вызов сортировки слиянием 
    size_t size() const;                                                // Получить размер списка
    size_t find(const Type&) const;                                     // Поиск элемента в списке по значению (возвращает индекс элемента).
    Type& front();                                                      // Возвращает ссылку на первый элемент списке.
    Type& back();                                                       // Возвращает ссылку на последний элемент списке.    
    Type operator [] (const int64_t index); 			                // Вернуть значение по индексу
    Forward_list<Type>& operator + (const Forward_list<Type>& list);	// Сложение списков
    Forward_list<Type>& operator = (const Forward_list<Type>& list);	// Присваивание списков
	bool operator == (const Forward_list<Type>& list);			        // Проверка на равенство
	bool operator != (const Forward_list<Type>& list);			        // Проверка на неравенство
	bool operator >= (const Forward_list<Type>& list);			        // Больше или равно 
	bool operator <= (const Forward_list<Type>& list);			        // Меньше или равно
	bool operator >  (const Forward_list<Type>& list);			        // Больше
	bool operator <  (const Forward_list<Type>& list);			        // Меньше
private:
    Node* _merge_sort(Node*);                           // Сортировка слиянием
    Node* _get_middle(Node*);                           // Получение середины списка, для функции сортировки
    Node* _merge(Node*, Node*);                         // Слияние отсортированных массивов
};


template <typename Type>
Forward_list<Type>::Forward_list(){
    head  = tail = nullptr;
    count = 0;
}

template <typename Type>
Forward_list<Type>::Forward_list(const Type& data) {
    Node *new_node = new Node(data);
    head = tail = new_node;
    count = 1;
}

template <typename Type>
Forward_list<Type>::Forward_list(const Forward_list &list) {
    if (list.head != nullptr) {
        Node *tmp = list.head;
        while (tmp) {
            push_front(tmp->data);
            tmp = tmp->next;
        }
    }
    else {
        this->Forward_list<Type>::Forward_list();
    }
}

template <typename Type>
Forward_list<Type>::~Forward_list() {
    clear();
}

template <typename Type>
void Forward_list<Type>::push_front(const Type& data) {
    if (count == 0) {
        Node* new_node = new Node(data);
        head = tail = new_node;
        count++;
    }
    else {
        Node* new_node = new Node(data, head);
        head = new_node;
        count++;
    }
}

template <typename Type>
void Forward_list<Type>::push_back(const Type &data) {
    if (!head) {
        push_front(data);
        return;
    }
    Node *new_node = new Node(data);
    tail->next = new_node;
    tail = new_node;
    count++;
}

template <typename Type>
void Forward_list<Type>::insert_after(Iterator insert, const Type &data) {
    if (!head) {
        push_front(data);                       // Если элементов нет в списке, просто вставить в начало
    }
    else {
        Node *new_node = new Node(data);        // Создать новый узел
        Node *tmp = head;                       // Временный указатель на голову
        Iterator search = Iterator(head);       // Итератор на первый элемент
        while (tmp) {                           // Пока есть элементы в списке, сравнивать итераторы
            if (search == insert) {             // Если адреса ==, тошда
                new_node->next = tmp->next;
                tmp->next = new_node;
                count++;
                return;
            }
            else {
                tmp = tmp->next;
                search++;
            }
        }
        tail->next = new_node;
        tail = new_node;
        count++;
    }
}

template <typename Type>
void Forward_list<Type>::pop_front() {
    if (!head) return;
    Node *temp = head;
    head = head->next;
    delete temp;
    count--;
}

template <typename Type>
void Forward_list<Type>::pop_back() {
    if (!head) return;
    if (head == tail) {
        delete tail;
        tail = head = nullptr;
        count--;
        return;
    }
    Node *slow = head;
    Node *fast = head->next;
    while (fast) {
        if (!fast->next) {
            delete fast;
            slow->next = nullptr;
            tail = slow;
            count--;
            return;
        }
        else {
            slow = slow->next;
            fast = fast->next;
        }
    }
}

template <typename Type>
void Forward_list<Type>::clear() {
    while (head) {
        pop_front();
    }
    head = tail = nullptr;
}

template <typename Type>
bool Forward_list<Type>::empty() {
    return count > 0;
}

template <typename Type>
void Forward_list<Type>::remove(const Type &val) {
    if (head == nullptr) return;    // Если список пуст - вернуться
    if (head->next == nullptr) {    // Если один элемент в списке
        if (head->data == val) {    // Если он равен значению удаляемому
            delete head;            // Удалить это значение
            head = nullptr;         // Присвоть ничего - голове и хвосту
            tail = nullptr;         // Чтобы не ломалось при обращении к полям, когда список пуст
            count = 0;              // Счётчик обнулить
            return;                 // Вернуться
        }
    }
    Node *slow = head;              // Медленный указатель, который будет идти позади быстрого
    Node *fast = head->next;        // Быстрый, который идет со второго элемента и тащит за собой медленный
    // Есть 4 варианта совпадения - несовпадения элементов, когда в списке всего 2 элемента
    // Либо элемент равен и первому и второму элементу в списке, либо не равен ни первому ни второму
    // Либо элемент равен только первому и не равен второму, либо равен только второму и не равен первому
    // 1. == elm ==  2. == elm !=  3. != elm == 4. != elm != 
    // Вид списка head-->[Node]-->[Node]-->[Узел]-->[Узел]<-->>tail-->null
    while (fast) {
        if (head == slow && slow->data == val) {        // Если оказался элемент первым, который надо удалить
            if (fast->data == val && fast->next) {      // Больше 2-х элементов в списке и второй тоже оказался удаляемым
                Node* tmp = fast;                       // Временный указатель для, перемещения адресов
                slow = fast->next;                      // Через один перепрыгнул сразу и указывает на следующий за удаляемым
                fast = fast->next;                      // Пока что тоже указывает туда же куда и слоу, т.к неизвестно есть ли дальше узлы 
                delete head, tmp;                       // Удалил значения и первое и второе
                head = slow;                            // Теперь голова списка указывает на 3ий элемент
                count -= 2;                             // Счетчик обновил
                if (fast->next != nullptr) {            // Если четвертый элемент есть
                    fast = fast->next;                  // Тогда сдвинуть на шаг вперед быстрый указатель
                }                                       // Теперь медленный на 3-м элементе, а быстрый на 4-м
                else {                                  // Если 4-го элемента не оказалось, то надо проверить 3-ий, т.е текущий
                    if (fast->data == val) {            // Если оказалось, что и 3ий элемент равен удаляемому, то список станет пуст
                        delete fast;                    // Удалить 3ий элемент
                        head = tail = nullptr;          // Проинициализировать указатели, чтобы обращаться без ошибок к ним дальше
                        count--;                        // Обновить счетчик
                        return;                         // вернуться
                    }
                    else {
                        return;                         // Раз 4-го элемента нет и 3-ий не подходит для удаления, вернуться
                    }
                }
            }
            if (fast->data == val && fast == tail) {    // Когда 2 элемента в списке и оба на удаление, то
                delete slow, fast;                      // Удалить найденный значения
                head = tail = nullptr;                  // Раз список пуст, проинициализировать указатели
                count -= 2;                             // Обновить счетчик
                return;                                 // Вернуться
            }
            else {                                      // Если первый элемент удаляется, а второй нет, то
                slow = fast;                            // Сдвинуть указатель удаляемого элемента на след узел
                fast = fast->next;                      // Сдвинуть быстрый на следующий элемент
                delete head;                            // Удалить значение первого элемента
                head = slow;                            // Голова теперь указывает на второй элемент
                count--;                                // Обновить счетчик
                if (fast == nullptr) {                  // Если оказалось, что в списке 2 элемента было, и значение fast
                    return;                             // не подошло под условие удаления, тогда остался один элемент
                }
            }
        }
        if (fast->data == val) {                        // Если первый элемент списка не удаляется, тогда идём в этот блок
            if (fast->next != nullptr) {                // Если следующий элемент есть, после текущего на котором fast
                Node* tmp = fast;                       // Создать временный указатель для запоминания адреса
                slow->next = fast->next;                // Медленный остался на своем месте, а вот указатель ноды перепрыгнул через удаляемую ноду
                fast = fast->next;                      // Быстрый переместился на следующий узел за удаляемым
                delete tmp;                             // Удалили ноду
                count--;                                // Обновился счетчик элементов в списке
            }
            else {                                      // Если следующего элемента нет, после текущего, куда указывает fast
                slow->next = nullptr;                   // Если непонятно, а зачем эта строчка, просто закомментируй её и запусти
                delete fast;                            // - если не проинициализировать поле в ноде, а оставить мусор, будет краш
                count--;                                // Обновить счетчик
                tail = slow;                            // Теперь в списке один элемент, и head и tail указывают на одну ноду
                return;                                 // Вернуться
            }
        }
        else {                                          // Если ни slow ни fast не указывают на искомое значение, то
            if (fast->next) {                           // Проверить есть ли, следующий узел, если да, тогда
                fast = fast->next;                      // Перейти вперед на один шаг
                slow = slow->next;                      // Тоже самое
            }
            else {                                      // Если следующего элемента после fast нет, тогда закончить, т.к. slow проверен
                return;
            }
        }
    }
    
}

template <typename Type>
void Forward_list<Type>::print() {
    if (!head) {
        std::cout << "Is empty\n";
        return;
    }
    Node* tmp = head;
    std::cout << "Head --> ";
    while (tmp) {
        if (tmp->next)
            std::cout << tmp->data << " --> ";
        else
            std::cout << tmp->data << " <-- Tail\n";
        tmp = tmp->next;
    }
}

template <typename Type>
void Forward_list<Type>::reverse() {
    if (!head || head == tail) { return; }
    Node *prev = nullptr;
    Node *temp = nullptr;
    Node *curr = head;
    while (curr) {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    tail = head;
    head = prev;
}

template <typename Type>
void Forward_list<Type>::sort_bubble() {
    if (!head || !(head->next)) { return; }
    Node *prev = head;          // Предыдущий для хранения адреса, которые тащится за текущим (current)
    Node *curr = head;          // Текущий для сравнения значений со следующим (next)
    Node *next = curr->next;    // Следующий за текущим, т.е 3 указателя на 3 ноды, на каждую по одному
    Node *temp = nullptr;       // Временная переменная, для манипуляций с адресами
    Node *stand = head;
    while (stand) {
        prev = head;            // Для случая, когда 2 элемента в списке, цикл начинается с того, что curr и prev указвают на голову сначала
        for (curr = head, next = head->next;  next != nullptr; curr = curr->next, next = next->next) {
            if (next->data < curr->data) {
                if (prev == curr)           // Первая итерация, и оказалось что голова меняется с соседним
                    head = next;            // Тогда голове присвоить значение свапнутое, чтобы корректно потом обращаться
                prev->next = next;          // Самый левый указывает на самый правый теперь [1]>--[2]-->[3]
                curr->next = next->next;    // Средний теперь указывает на следующий за 3-ьим [1]--[2]>--[3]-->[4]
                next->next = curr;          // Правый самый, тоесть 3-ий теперь указывает на средний [1]--[2]--<[3]
                temp = curr;                // Запомнить адресс среднего потому что вид сейчас [1]--[3]--[2]
                curr = next;                // Теперь в средний запоминть правый 
                next = temp;                // В правый запомнить средний, т.е перекинуть указатели свапнутых узлов (нод)
            }
            prev = curr;                    // После первой итерации, указатели расходятся - 3 узла на каждом указатель
        }
        stand = stand->next;                // Стандартная i в пузырьке, которая каждый шаг увеличивается на 1 после того как j отработал
    }
}

template <typename Type>
void Forward_list<Type>::sort_insertion() {
    Node *a, *b, *p, *h = nullptr;
    for (Node* i = head; i != nullptr; ) {
        a = i;
        i = i->next;
        b = h;
        for (p = nullptr; (b != nullptr) && (a->data > b->data); ) {
            p = b;
            b = b->next;
        }
        if (p == nullptr) {
            a->next = h;
            h = a;
        }
        else {
            a->next = b;
            p->next = a;
        }
    }
    if (h != nullptr)
        head = h;
}

template <typename Type>
void Forward_list<Type>::sort_selection() {
    Node *min, *tmp;
    Node* p1, * p2, * r1, * r2;
    for (p1 = r1 = head; p1 != nullptr; p1 = p1->next) {
        min = p2 = r2 = p1;
        for (tmp = p1->next; tmp != nullptr; tmp = tmp->next) {
            if (tmp->data < p2->data) {
                r2 = min;
                p2 = tmp;
            }
            min = tmp;
        }
        if (p1 != p2) {
            if (p1 == head)
                head = p2;
            else
                r1->next = p2;

            tmp = p2->next;
            if (p1 == r2) {
                p2->next = p1;
                p1->next = tmp;
            }
            else {
                min = p1->next;
                r1->next = p2;
                r2->next = p1;
                p1->next = tmp;
                p2->next = min;
            }
            p1 = p2;
        }
        r1 = p1;
    }
}

template <typename Type>
typename Forward_list<Type>::Node* Forward_list<Type>::_merge_sort(Node* node) {
    if (node == nullptr || node->next == nullptr)
        return node;
    Node* middle = _get_middle(node);
    Node* left_head = node;
    Node* right_head = middle->next;
    middle->next = nullptr;
    return _merge(_merge_sort(left_head), _merge_sort(right_head));
}

template <typename Type>
typename Forward_list<Type>::Node* Forward_list<Type>::_get_middle(Node *node) {
    if (node == nullptr)
        return node;
    Node* slow, * fast;
    slow = fast = node;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

template <typename Type>
typename Forward_list<Type>::Node* Forward_list<Type>::_merge(Node *left, Node *right) {
    Node imitation_head;
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
void Forward_list<Type>::sort_merge() {
    head = _merge_sort(head);
}

template <typename Type>
Type Forward_list<Type>::operator [] (const int64_t index) {
    if (index >= count || index < 0) { 
        cout << "Некорректный индекс\n";
        return Type(0); 
    }
    Node *tmp = head;
    for (int64_t i = 0; i != index; ++i, tmp = tmp->next);
    return tmp->data;
}

template <typename Type>
Type& Forward_list<Type>::front() {
    //if (head) { return head->data; }
    //else { cout << "Нет элементов в списке\n"; }
    return head->data;
}

template <typename Type>
Type& Forward_list<Type>::back() {
    //if (tail) { return tail->data; }
    //else { cout << "Нет элементов в списке\n"; }
    return tail->data;
}

template <typename Type>
size_t Forward_list<Type>::size() const {
    return count;
}

template <typename Type>
size_t Forward_list<Type>::find(const Type& find_elm) const {
    if (!head) {
        cout << "List is empty!\n";
        return 0;
    }
    Node* tmp = head;
    size_t count = 0;
    while (tmp) {
        if (tmp->data == find_elm) {
            return count;
        }
        count++;
        tmp = tmp->next;
    }
    cout << "Element not found\n";
    return 0;
}

template <typename Type>
typename Forward_list<Type>::Iterator Forward_list<Type>::begin() const {
    return Iterator(head);
}

template <typename Type>
typename Forward_list<Type>::Iterator Forward_list<Type>::end() const {
    return Iterator(nullptr);
}

template<typename Type>
bool Forward_list<Type>::Iterator::operator==(const Iterator& other) const {  
    if (this == &other) {
        return true;
    }
    return node == other.node;
}

template<typename Type>
bool Forward_list<Type>::Iterator::operator!=(const Iterator& other) const {
    return !operator==(other);
}

template <typename Type>
void Forward_list<Type>::Iterator::operator ++ () {
    if (node) {
        node = node->next;
    }
}

template<typename Type>
void Forward_list<Type>::Iterator::operator ++ (Type) {
    if (node) {
        node = node->next;
    }
}

template<typename Type>
Type Forward_list<Type>::Iterator::operator*() const {
    if (node) {
        return node->data;
    }
    return Type();
}

template <typename Type>
Forward_list<Type>& Forward_list<Type>::operator + (const Forward_list<Type>& list) {
    if (!list.head) { return *this; }
    Node *tmp = list.head;
    while (tmp) {
        this->push_front(tmp->data);
        tmp = tmp->next;
    }
    return *this;
}

template <typename Type>
Forward_list<Type>& Forward_list<Type>::operator = (const Forward_list<Type>& list) {
    if (!list.head) {
        this->clear();
        return *this;
    }
    this->clear();
    Node *tmp = list.head;
    while (tmp) {
        this->push_back(tmp->data);
        tmp = tmp->next;
    }
    return *this;
}

template <typename Type>
bool Forward_list<Type>::operator < (const Forward_list<Type>& list) {
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
bool Forward_list<Type>::operator == (const Forward_list<Type>& list) {
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
bool Forward_list<Type>::operator > (const Forward_list<Type>& list) {
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
bool Forward_list<Type>::operator != (const Forward_list<Type>& list) {
    return !(*this == list);
}

template <typename Type>
bool Forward_list<Type>::operator >= (const Forward_list<Type>& list) {
    return *this > list || *this == list;
}

template <typename Type>
bool Forward_list<Type>::operator <= (const Forward_list<Type>& list) {
    return *this < list || *this == list;
}



// Функция для мини-теста
void testing(size_t size) {
    srand(time(NULL));
    size_t i, list_size = size;
	Forward_list<int64_t> my_list;
	forward_list<int64_t> stl_list;
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