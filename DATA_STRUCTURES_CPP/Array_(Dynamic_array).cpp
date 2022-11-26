/*Динамический массив - имитация вектора*/
#include <iostream>
#include <vector>

using std::vector;
using std::cout;


template <typename Type>
class Darray {											// Класс описывающий динамический массив
	size_t capac;										// Вместимость
	size_t count;										// Размер массива
	Type *darr;											// Динамический массив
public:
	Darray();											// Конструктор без параметров
	Darray(const size_t &cnt, const Type &elem);		// Конструктор с кол-вом элементов и значением
	Darray(const Darray<Type> &obj);					// Конструктор копирования
	~Darray();											// Деструктор
	void insert(const Type& elm, const size_t& id);		// Вставляет элемент по заданной позиции со сдвигом остальных вправо
	void resize(const size_t &sz, const Type &elm);		// Определяет новый размер массива.
	void reserve(const size_t &sz);						// Резервирует минимальную длину хранилища для объекта
	void push_back(const Type &elm);					// Добавляет элемент в конец
	void erase(const Type &elm);						// Удаляет элемент по значению (без перевыделения памяти, т.е размер массива остается)
	void pop_back();									// Удаляет элемент в конце
	void clear();										// Очищает массив
	void show();										// Печать массива
	bool empty();										// Проверяет, пуст ли массив
	const Type& back() const;							// Возвращает ссылку на последний элемент
	const Type& front() const;							// Возвращает ссылку на первый элемент
	const Type* data() const;							// Возвращает указатель на первый элемент
	const Type& at(const size_t &pos);					// Возвращает ссылку на элемент в заданном положении в массиве.
	size_t capacity() {return capac;}   				// Число элементов, которое массив может содержать без перевыделения
	size_t size()	  {return count;}					// Количество элементов в массиве.
	Type& operator[] (const size_t& id) const;  		// [id]	 - Обращение по индексу
};


template <typename Type>
Darray<Type>::Darray() {
	capac = 2;				// Вместимость - 2 будет по умолчанию
	count = 0;				// Счетчик при создании == 0
	darr  = new Type[2];    // Выделение памяти для 2 элементов типа Type
}

template <typename Type>
Darray<Type>::Darray(const size_t& cnt, const Type& elem) {
	this->Darray<Type>::Darray();
	for (size_t i = 0; i < cnt; i++)
		push_back(elem);
}

template <typename Type>
Darray<Type>::Darray(const Darray<Type>& obj) {
	capac = obj.capac;				// Скопировать вместимость
	count = obj.count;				// Скопировать кол-во элементов
	darr = new Type[count+capac];	// Выделить память для нового массива
	for (size_t i = 0; i < obj.count; ++i)
		darr[i] = obj.darr[i];		// Скопировать элементы
}

template <typename Type>
Darray<Type>::~Darray() {
	clear();
}

template <typename Type>
void Darray<Type>::resize(const size_t& sz, const Type& elm) {
	if (count == 0) {							// Если элементов нет, тогда
		for (size_t i = 0; i < sz; i++)			// Заполнить элементами массив
			push_back(elm);
		return;
	}
	if (sz <= count)							// Если надо перевыделить меньше, чем есть в массиве
		return;									// Ничего не делать, вернуться
	for (size_t i = count; i < sz; i++) {		// Если все ок, то начать за последним элементом в массиве
		push_back(elm);							// И добавить необходимое количество элементов
	}
}

template <typename Type>
void Darray<Type>::reserve(const size_t& sz) {
	if (sz <= capac)								// Если текущая вместитльность больше или равна переданной 
		return;										// Ничего не делать, вернуться, а иначе
	Type *new_arr = new Type[count + capac + sz];	// Создать новый массив, размером старый + новая вместительность
	size_t n = count;								// Запомнить кол_во элементов в массиве
	for (size_t i = 0; i < count; i++)				// Скопировать старый массив в новый
		new_arr[i] = darr[i];
	clear();										// Очистить старый
	darr = new_arr;									// Перекинуть указатель
	capac = sz;										// Вместительность стала равна той, которую передали
	count = n;										// Кол-во элементов осталось столько же
}

template <typename Type>
void Darray<Type>::push_back(const Type& elm) {
	if (capac > 0) {							// Если еще есть элемент в массиве, тогда
		darr[count] = elm;						// Добавить за последним существующим
		capac--;								// Уменьшить вместимость
		count++;								// Увеличить счетчик
	}
	else {										// Если capacity == 0, нужно увеличить массив
		Type *new_array = new Type[count * 2];	// Создать массив в 2 раза больше 
		for (size_t i = 0; i < count; i++)		// Скопировать все элементы в новый массив
			new_array[i] = darr[i];
		delete[] darr;							// Удалить старый массив
		darr = new_array;						// В старый массив положить новый
		darr[count] = elm;						// Добавить элемент в конец
		capac = count - 1;						// Уменьшить вмещаемость
		count++;								// Увеличить счетчик
	}
}

template <typename Type>
void Darray<Type>::insert(const Type& elm, const size_t& id) {
	if (id >= count) {								// Если индекс больше кол-ва элементов, 
		push_back(elm);								// просто вставить элемент в конец массива
		return;										// вернуться
	}
	if (id < 0)										// Если индекс меньше 0 - вернуться
		return;
	Type *tmp_arr = new Type[capac + count + 1];	// Временный массив, для копирования элементов
	bool fl = true;									// Флаг, указывающий на найденный индекс
	for (size_t i = 0; i < count; i++) {			// Обход всего массива
		if (!fl)									// Если false, значит уже добавился элемент по нужному индексу
			tmp_arr[i + 1] = darr[i];				// И тогда нужно делать сдвиг всех элементов на 1 элемент вправо
		if (fl && i != id) {						// Если не дошел до нужного индекса
			tmp_arr[i] = darr[i];					// Копировать элементы в новый массив
		}
		if (fl && i == id) {						// Если индекс совпал, по которому надо вставить элемент
			tmp_arr[i] = elm;						// Добавить его по нужному индексу
			tmp_arr[i + 1] = darr[i];				// Следующий элемент добавляется уэе со сдвигом вправо
			fl = false;								// Поднять флаг, что элемент встретился и выполнялся только 1ый шаг цикла
		}
	}
	size_t n = count, c = capac;					// Запомнить кол-во элементов в массиве + 1 добавленный и вместимость
	this->clear();									// Очистить старый массив
	if (c == 0) {									// Проверить, если он был полон, тогда перевыделить память
		for (size_t i = 0; i < n; i++)				// Пройти в цикле опять, добавить все элементы + перевыделить память
			push_back(tmp_arr[i]);					// Добавление в конец, сохранение порядка
		delete[] tmp_arr;							// Удалить временный массив
		return;										// Вернуться
	}
	darr = tmp_arr;									// Если еще было место в массиве, просто запомнить указатель
	count = n + 1;									// Обновить счетчик, т.к. clear() стер все данные
	capac = c - 1;									// Обновить вместимость
}

template <typename Type>
void Darray<Type>::pop_back() {
	if (count < 1)									// Если массив пуст - вернуться
		return;
	darr[count] = static_cast<Type>(NULL);			// Заполнять удаленные ячейки NULL-ами, и не позволять к ним обращаться потом
	count--;										// Уменьшить счетчик
	capac++;										// Увеличить вмещаемость
}

template <typename Type>
void Darray<Type>::erase(const Type& elm) {
	if (count == 0)
		return;
	size_t id = -1;									// id для найденного элемента
	for (size_t i = 0; i < count; i++) {			// Перебрать массив и найти элемент
		if (elm == darr[i]) {						// Если элемент есть, запомнить id
			id = i;
			break;
		}
	}
	if (id >= 0 && id < count) {					// Если Id корректный, тогда
		Type *tmp_arr = new Type[capac + count];	// Создать временный массив
		for (size_t i = 0; i < count; i++)			// Скопировать в него все значения старого
			tmp_arr[i] = darr[i];					
		tmp_arr[id] = static_cast<Type>(NULL);		// В новом массиве удалить по индексу значение
		size_t n = count;							// Запомнить кол-во элементов
		clear();									// Очистить старый полностью
		for (size_t i = 0; i < n; i++) {			// И заново заполнить уже валидными значениями
			if (tmp_arr[i] != static_cast<Type>(NULL))
				push_back(tmp_arr[i]);
		}
		delete[] tmp_arr;
	}
}

template <typename Type>
void Darray<Type>::clear(){
	while (count != 0)
		pop_back();
}

template <typename Type>
bool Darray<Type>::empty() { return count == 0; }

template <typename Type>
void Darray<Type>::show() {
	if (count < 1)
		return;
	for (size_t i = 0; i < count; i++)
		cout << "[" << i << "] = " << darr[i] << " ";
	cout << '\n';
}

template <typename Type>
const Type& Darray<Type>::back() const {
	return darr[count - 1];
}

template <typename Type>
const Type& Darray<Type>::front() const {
	return darr[0];
}

template <typename Type>
const Type* Darray<Type>::data() const {
	return &darr[0];
}

template <typename Type>
const Type& Darray<Type>::at(const size_t& pos) {
	return darr[pos];
}

template<typename Type>
Type& Darray<Type>::operator [] (const size_t& id) const {
	return darr[id];
}


int main() {
	setlocale(0, "");
	Darray<int> inarr;
	Darray<char> charr;
	Darray<double> flarr;

	cout << "Size : Capacity -> " << inarr.size() << ":" << inarr.capacity() << '\n';
	for (int i = 0; i < 10; i++) {
		cout << inarr.size() << ":";
		cout << inarr.capacity() << "; ";
		inarr.push_back(i * 2);
		charr.insert(char(i + 65), i);
		flarr.push_back(i * 0.24);
	}
	cout << "\n=======================\n";
	cout << "Integer: "; inarr.show();
	cout << "Char:    "; charr.show();
	cout << "Double:  "; flarr.show();
	cout << "Size arr:     " << inarr.size()     << '\n';
	cout << "Capacity arr: " << inarr.capacity() << '\n';
}