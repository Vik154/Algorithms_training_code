/*Priority Queue FIFO -- Очередь с приоритетом на основе связного списка*/
#include <iostream>

using std::cout;


template <typename Type>
class Pqueue {								// Класс описывающий очередь с приоритетом
private:
	class Node {							// Класс описывающий узел очереди
	public:
		Type data;							// Поле данных
		Node* next;							// Указатель на следующий узел списка
		int priority;						// Приоритет элемента
		Node(const Type& d, const int& p) : // Конструктор
			data(d), priority(p), next(nullptr) {};
	};
	Node* head;								// Начало очереди
	Node* tail;								// Конец очереди
	int count;								// Кол-во элементов
public:
	Pqueue();								// Конструктор
	Pqueue(const Type &elm, const int& pri);// Конструктор с параметром
	Pqueue(const Pqueue<Type> &obj);		// Конструктор копирования
	~Pqueue();								// Деструктор
	void show();							// Вывод очереди
	void pop();								// Удалить верхний (первый) элемент
	void clear();							// Очистка очереди
	const Type& front() const;				// Вернуть 1-ый элемент
	const Type& back()  const;				// Вернуть последний элемент
	int size() { return count; }			// Вернуть размер очереди
	bool empty() { return count == 0; }		// Вернуть 0 если очередь пустая, иначе 1
	void push(const Type& elm, const int& pri);		// Добавление в очередь элемента по приоритету

};

template <typename Type>
Pqueue<Type>::Pqueue() {
	head = tail = nullptr;
	count = 0;
}

template <typename Type>
Pqueue<Type>::Pqueue(const Type& elm, const int& pri) {
	Node *new_node = new Node(elm, pri);
	head = tail = new_node;
	count = 1;
}

template <typename Type>
Pqueue<Type>::Pqueue(const Pqueue<Type>& obj) {
	Node *tmp = obj.head;
	while (tmp) {
		push(tmp->data, tmp->priority);
		tmp = tmp->next;
	}
	head = obj.head;
	tail = obj.tail;
}

template <typename Type>
Pqueue<Type>::~Pqueue() {
	clear();
}

template <typename Type>
void Pqueue<Type>::push(const Type &elm, const int &prior) {
	Node* new_node = new Node(elm, prior);  // Создать новый элемент очереди
	if (head == nullptr) {					// Если очередь пустая, тогда элемент будет 1-ым
		head = new_node;					// Голова указывает на новый добавленный элемент
		tail = new_node;					// Хвост указывает на новый добавленный элемент
		count++;							// Увеличить счетчик
		return;								// Вернуться
	}
	Node* temp = head;						// Временный указатель для обхода и поиска приоритета в цикле
	Node* prev = nullptr;					// Указатель на предыдущий элеменет от temp
	// Итерироваться по очереди, пока не закончится или пока не встретится меньший приоритет
	while (temp != nullptr && temp->priority > prior) {
		prev = temp;						// В предыдущий запомнить значение текущего
		temp = temp->next;					// Текущий продвинуть вперед по очереди
	}
	if (temp == nullptr) {					// Если дошли до конца очереди и не встретился приоритет ниже чем у добавляемого
		prev->next = new_node;				// Добавить элемент в конец очереди
		tail = new_node;					// Хвост указывает на последний элемент
	}
	else {
		if (prev == nullptr) {				// Если предыдущий указвает на 0, значит итераций не было т.к приоритет выше
			new_node->next = head;			// Новый элемент встает вперед очереди
			head = new_node;				// Голова указывает на новый элемент
		}
		else {								// Если итерации были, тогда настроить указатели
			new_node->next = temp;			// Новый элемент будет указывать на найденное значение
			prev->next = new_node;			// А предыдущий будет указывать на новый
		}
	}
	count++;
}

template <typename Type>
void Pqueue<Type>::show() {
	if (count == 0) { std::cout << "Queue is empty\n"; }
	Node* tmp = head;
	for (int i = 0; i < count; ++i) {
		cout << "(" << tmp->data << ":" << tmp->priority << ")<-";
		tmp = tmp->next;
	}
}

template <typename Type>
const Type& Pqueue<Type>::front() const {
	return (count == 0) ? Type(0) : head->data;
}

template <typename Type>
const Type& Pqueue<Type>::back() const {
	return (count == 0) ? Type(0) : tail->data;
}

template <typename Type>
void Pqueue<Type>::pop() {
	if (head == nullptr) { return; }
	Node* tmp = head;
	head = head->next;
	delete tmp;
	count--;
}

template <typename Type>
void Pqueue<Type>::clear() {
	while (count) {
		pop();
	}
}


int main() {
	setlocale(0, "Ru");
	srand(static_cast<unsigned int>(time(NULL)));
	clock_t time = clock();
	Pqueue<int> pqueue;
	std::cout << "=====Начало теста=====\n";
	for (int i = 0; i < 10'000; ++i) {
		pqueue.push(rand() % 100'000, rand() % 10);
	}
	time = clock() - time;
	std::cout << "Добавление элементов: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;
	time = clock();
	pqueue.clear();
	time = clock() - time;
	std::cout << "Извлечение элементов: " << (double)time / CLOCKS_PER_SEC << " сек." << std::endl;

	for (int i = 0; i < 15; i++)
		pqueue.push(i, i % 10);
	pqueue.show();
	return 0;
}