/*Stack - реализация стека на основе односвязного списка*/
#include <iostream>

using std::cout;
using std::move;

template <typename Type>
class Stack {
private:
	class Node {
	public:
		Type  data;										// Поле с данными, произвольного типа
		Node* next;										// Указатель на следующий узел списка
		Node(Type data, Node* next = nullptr):			// Конструктор узла, принимает на вход данные и указатель на следующий элемент
			data(data), next(next) {};
	};
	int64_t count;										// Количество элементов стека
	Node *ptr_top;										// Указаьель на вершину стека
public:
	Stack();											// Конструктор без параметров
	Stack(const Type &);								// Конструктор с параметром
	Stack(Stack<Type> &);								// Конструктор копирования
	~Stack();											// Деструктор
	void push(const Type& val);							// Добавляет элемент в стек.
	void pop();											// Удаляет элемент из верхней части стека.
	bool empty() const;									// Возвращает true - если стек пуст, иначе - false
	Type top();											// Возвращает значение самого верхнего элемента
	int64_t size() const;								// Возвращает количество элементов в стеке
	
	Stack<Type>& operator + (const Stack<Type> &stk);	// Сложение стеков
	bool operator == (const Stack<Type>& stk);			// Проверка на равенство
	bool operator != (const Stack<Type>& stk);			// Проверка на неравенство
	bool operator >= (const Stack<Type>& stk);			// Больше или равно 
	bool operator <= (const Stack<Type>& stk);			// Меньше или равно
	bool operator >  (const Stack<Type>& stk);			// Больше
	bool operator <  (const Stack<Type>& stk);			// Меньше 
};



template <typename Type>
Stack<Type>::Stack() {
	ptr_top = nullptr;					// Инициализация указателя, пока что никуда не указывает
	count = 0;							// Создание стека - элементов пока нет, инициализация полей
}

template <typename Type>
Stack<Type>::Stack(const Type &dat) {
	Node *new_node = new Node(dat);		// Создание нового узла и заполнение полей (данные, указатель на след узел)
	ptr_top = new_node;					// Вершина указывает на новый добавленный элемент
	count = 1;							// Создание стека - элементов теперь один есть
}

template <typename Type>
Stack<Type>::Stack(Stack<Type> &stk) {
	// Конструктор копирования, начинается с вершины входящего стека и идет поэлементно вниз
	for (Node* temp = stk.ptr_top; temp != nullptr; temp = temp->next) {
		push(temp->data);		
	}									// Push - Вставка элементов в стек, копирование и переход по указателю дальше
	Node *slow = nullptr;				// Медленный указатель (для разворота стека)
	Node *fast = ptr_top;				// Быстрый указатель идет на шаг вперед медленного

	while (fast != nullptr)  {			// Пока в стеке есть элементы продвигаться вниз
		Node *p = move(fast->next);		// Временный указатель на следующий узел от быстрого
		fast->next = move(slow);		// В следующий узел записать адрес предыдущего
		slow = move(fast);				// В предыдущий записать быстрый указатель
		fast = move(p);					// В быстрый передвинуть вперед (вглубь / вниз)
	}
	ptr_top = move(slow);				// Указатель на перевернутый стек

/*   slow   fast    */
/*    \/     \/     */
/*  |NULL| |HEAD|   */
/*    \/     \/     */
}

template <typename Type>
Stack<Type>::~Stack() {					// Деструктор
	while (ptr_top) {					// Пока есть элементы
		pop();							// Удалять поэлементно
	}
}

template <typename Type>
int64_t Stack<Type>::size() const {
	return count;						// Возвращает количество элементов в стеке
}

template <typename Type>
void Stack<Type>::push(const Type &val) {
	if (count == 0) {
		Node *new_node = new Node(val);
		ptr_top = new_node;
		count++;
	}
	else {
		Node* new_node = new Node(val, ptr_top);
		ptr_top = new_node;
		count++;
	}
}

template <typename Type>
void Stack<Type>::pop() {
	if (count > 0) {
		Node *tmp = ptr_top;
		ptr_top = ptr_top->next;
		delete tmp;
		count--;
	}
}

template <typename Type>
bool Stack<Type>::empty() const {
	return (count != 0) ? true : false;
}

template <typename Type>
Type Stack<Type>::top() {
	return (count != 0) ? ptr_top->data : NULL;
}


template <typename Type>
bool Stack<Type>::operator < (const Stack<Type>& stk) {
	if (count != stk.count)
		return false;
	int64_t cnt = 0;
	Node *temp = ptr_top;
	Node *tmp  = stk.ptr_top;
	for (tmp; tmp != nullptr; tmp = tmp->next, temp = temp->data) {
		if (temp->data > tmp->data) {
			return false;
		}
		else if (temp->data == tmp->data) {
			cnt++;
		}
	}
	return (cnt == count) ? false : true;
}

template <typename Type>
bool Stack<Type>::operator == (const Stack<Type>& stk) {
	if (count != stk.count)
		return false;
	Node* temp = ptr_top;
	Node* tmp = stk.ptr_top;
	for (temp; temp != nullptr; temp = temp->next, tmp = tmp->next) {
		if (temp->data != tmp->data)
			return false;
	}
	return true;
}

template <typename Type>
bool Stack<Type>::operator != (const Stack<Type>& stk) {
	return !(*this == stk);
}

template <typename Type>
bool Stack<Type>::operator > (const Stack<Type>& stk) {
	return (count != stk.count) ? false : !(*this < stk) && !(*this == stk);
}

template <typename Type>
bool Stack<Type>::operator <= (const Stack<Type>& stk) {
	return (count != stk.count) ? false : *this < stk || *this == stk;
}

template <typename Type>
bool Stack<Type>::operator >= (const Stack<Type>& stk) {
	return (count != stk.count) ? false : *this > stk || *this == stk;
}

template <typename Type>
Stack<Type>& Stack<Type>::operator + (const Stack<Type>& stk) {
	Node *tmp = stk.ptr_top;
	for (tmp; tmp != nullptr; tmp = tmp->next) {
		this->push(tmp->data);
	}
	return *this;
}


int main() {
	setlocale(0, "ru");
	Stack<int>  int_stack(1);
	Stack<char> char_stack('u');
	int64_t len = 10, i = 0;

	for (i = 0; i < len; ++i) {
		int_stack.push(rand() % 100);
		char_stack.push(rand() % 100);
	}
	cout << "STACK_INTEGER ---> ";
	for (i = 0; i < len + 1; ++i) {
		if (i != len - 1) {
			cout << int_stack.top() << " --> ";
			int_stack.pop();
		}
		else {
			cout << int_stack.top();
			int_stack.pop();
		}
	}
	cout << "\nSTACK_CHAR ---> ";
	for (i = 0; i < len; ++i) {
		if (i != len - 1) {
			cout << char_stack.top() << " --> ";
			char_stack.pop();
		}
		else {
			cout << char_stack.top();
			char_stack.pop();
		}
	}
	return 0;
}