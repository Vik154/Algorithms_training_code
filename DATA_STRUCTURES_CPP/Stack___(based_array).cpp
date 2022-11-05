/*Stack - реализация стека на основе массива*/
#include <iostream>

using std::cout;

template <typename Type>
class Stack {
private:
	Type  *arrays;										// Массив для хранения элементов стека
	int64_t count;										// Количество элементов стека
	int64_t capacity;									// Размер (вместимость) стека
public:
	Stack();											// Конструктор без параметров
	Stack(int64_t);										// Конструктор с параметром, параметр - размер стека
	Stack(Stack<Type> &);								// Конструктор копирования
	~Stack();											// Деструктор
	void push(const Type& val);							// Добавляет элемент в стек.
	void pop();											// Удаляет элемент из верхней части стека.
	bool empty() const;									// Возвращает true - если стек пуст, иначе - false
	Type top();											// Возвращает значение самого верхнего элемента
	int64_t size() const;								// Возвращает количество элементов в стеке
	
	Stack<Type>& operator + (const Stack<Type> &stk);	// Сложение стеков
	Stack<Type>& operator = (const Stack<Type> &stk);	// Присваивание стека (копирование)
	bool operator == (const Stack<Type>& stk);			// Проверка на равенство
	bool operator != (const Stack<Type>& stk);			// Проверка на неравенство
	bool operator >= (const Stack<Type>& stk);			// Больше или равно 
	bool operator <= (const Stack<Type>& stk);			// Меньше или равно
	bool operator >  (const Stack<Type>& stk);			// Больше
	bool operator <  (const Stack<Type>& stk);			// Меньше 
};



template <typename Type>
Stack<Type>::Stack() {
	count = 0;										// Создание стека - элементов пока нет, инициализация полей
	capacity = int64_t(10);							// По умолчанию - размер будет 10 элементов
	arrays = new Type[capacity];					// Выделить память на 10 элементов типа "Type"
}

template <typename Type>
Stack<Type>::Stack(int64_t size) {
	count = 0;										// Создание стека - элементов пока нет, инициализация полей
	capacity = static_cast<int64_t>(size);			// По умолчанию - размер будет 10 элементов
	arrays = new Type[capacity];					// В куче выделяется память под заданное количество элементов
}

template <typename Type>
Stack<Type>::Stack(Stack<Type> &stk) {
	arrays = new Type[stk.capacity + stk.count];	// Выделить память для нового стека
	for (int64_t i = 0; i < stk.count; ++i) {		// Скопировать поэлементно (чтобы деструктором по
		arrays[i] = stk.arrays[i];					// одной области два раза не удалять, поэтому поэлементно
	}
	count    = stk.count;							// Положить в счетчик размер копируемого стека
	capacity = stk.capacity;						// Скопировать вместимость
}

template <typename Type>
Stack<Type>::~Stack() {
	delete[] arrays;								// Освобождает память (удаляет ссылку на область)
	count = 0;										// Обнуляет счетчик
	capacity = 0;									// Обнуляет вместимость
}

template <typename Type>
int64_t Stack<Type>::size() const {
	return count;									// Возвращает количество элементов в стеке
}

template <typename Type>
void Stack<Type>::push(const Type &val) {
	if (capacity != 0) {							// Если ещё не закончилась вместимость, то
		arrays[count] = val;						// Добавить в стек значение
		count++;									// Увеличить счетчик элементов
		capacity--;									// Уменьшить вместимость
	}
	else {											// Если размер закончился, то перевыделить память
		Type *new_arr = new Type[count * 2];		// Создать новый массив в 2 раза больше предыдущего
		for (int64_t i = 0; i < count; ++i) {		// Скопировать все элементы из старого массива
			new_arr[i] = arrays[i];
		}
		delete[] arrays;							// Освободить память
		arrays = new_arr;							// Присвоить указатель на новый массив
		capacity = count;							// Обновить значение вместительности
		arrays[count] = val;						// Добавить значение
		count++;									// Увеличить счетчик
		capacity--;									// Уменьшить вместимость
	}
}

template <typename Type>
void Stack<Type>::pop() {
	if (count > 0) {
		arrays[count - 1] = NULL;
		count--;
		capacity++;
	}
}

template <typename Type>
bool Stack<Type>::empty() const {
	return (count != 0) ? true : false;
}

template <typename Type>
Type Stack<Type>::top() {
	return (count != 0) ? arrays[count - 1] : NULL;
}

template <typename Type>
bool Stack<Type>::operator < (const Stack<Type>& stk) {
	if (count != stk.count)
		return false;
	int64_t cnt = 0;
	for (int64_t i = 0; i < count; ++i) {
		if (arrays[i] > stk.arrays[i]) {
			return false;
		}
		else if (arrays[i] == stk.arrays[i]) {
			cnt++;
		}
	}
	return (cnt == count) ? false : true;
}

template <typename Type>
bool Stack<Type>::operator == (const Stack<Type>& stk) {
	if (count != stk.count)
		return false;
	for (int64_t i = 0; i < count; ++i) {
		if (arrays[i] != stk.arrays[i])
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
Stack<Type>& Stack<Type>::operator = (const Stack<Type>& stk) {
	~Stack();
	Stack(Stack<Type> &stk);
	return *this;
}

template <typename Type>
Stack<Type>& Stack<Type>::operator + (const Stack<Type>& stk) {
	for (int64_t i = 0; i < stk.count; ++i) {
		this->push(stk.arrays[i]);
	}
	return *this;
}


int main() {
	setlocale(0, "ru");
	Stack<int>  int_stack(2);
	Stack<char> char_stack(2);
	int64_t len = 10, i = 0;

	for (i = 0; i < len; ++i) {
		int_stack.push(rand() % 100);
		char_stack.push(rand() % 100);
	}
	cout << "STACK_INTEGER ---> ";
	for (i = 0; i < len; ++i) {
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