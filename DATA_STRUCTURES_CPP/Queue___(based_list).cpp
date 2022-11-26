/*Queue FIFO - очередь на основе списка*/
#include <iostream>
#include <list>
#include <queue>

using std::list;
using std::queue;
using std::cout;


template <typename Type>
class Queue {							// Класс описывающий очередь
	list<Type> node;					// Класс описывающий узел очереди
	size_t cnt;							// Кол-во элементов
public:
	Queue();							// Конструктор
	Queue(const Type &elm);				// Конструктор с параметром
	Queue(const Queue<Type> &obj);		// Конструктор копирования
	~Queue();							// Деструктор
	void push(const Type &elm);			// Добавить в конец
	void pop();							// Вытащить первый элемент из очереди
	void show();						// Вывод на экран
	void empty() {return cnt == 0;}		// true если пуста, иначе false
	void size()  {return cnt;}			// Кол-во элементов
	const Type& back()  const { return node.back(); }	// Последний элемент в очереди
	const Type& front() const { return node.front(); }  // Первый элемент в очереди
};


template <typename Type>
Queue<Type>::Queue() : cnt(0) {};

template <typename Type>
Queue<Type>::Queue(const Type& elm) {
	cnt = 1;
	node.push_back(elm);
}

template <typename Type>
Queue<Type>::Queue(const Queue<Type>& obj) {
	if (obj.node.size() == 0) {
		this->Queue<Type>::Queue();
		return;
	}
	for (auto iter = obj.node.begin(); iter != obj.node.end(); ++iter)
		push(*iter);
}

template <typename Type>
Queue<Type>::~Queue() {
	node.clear();
	cnt = 0;
}

template <typename Type>
void Queue<Type>::push(const Type &elm) {
	node.push_back(elm);
	cnt++;
}

template <typename Type>
void Queue<Type>::pop() {
	if (node.size() == 0)
		return;
	node.pop_back();
	cnt--;
}

template <typename Type>
void Queue<Type>::show() {
	if (cnt == 0)
		return;
	for (auto iter = node.begin(); iter != node.end(); ++iter)
		cout << "-------";
	cout << '\n';
	for (auto iter = node.begin(); iter != node.end(); ++iter)
		cout << '(' << * iter << ")<-";
	cout << '\n';
	for (auto iter = node.begin(); iter != node.end(); ++iter)
		cout << "-------";
	cout << '\n';
}


int main() {
	Queue<int> mq;
	for (int i = 1; i <= 15; ++i)
		mq.push(i);
	mq.show();
	for (int i = 0; i < 5; ++i)
		mq.pop();
	mq.show();
}