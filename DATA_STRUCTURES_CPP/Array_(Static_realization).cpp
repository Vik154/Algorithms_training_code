/*Имитация статического массива*/
#include <iostream>
#include <array>

using std::ostream;
using std::array;
using std::cout;


template <typename Type, size_t asize>
class Array {
	Type *arr;
public:
	Array();									// Конструктор по умолчанию
	Array(const Type &elm);						// Конструктор с параметром (заполняет массив переданным значением)
	Array(const Array<Type, asize> &obj);		// Конструктор копирования
	~Array();									// Деструктор
	void show() const;							// Вывод на экран
	void fill(const Type& elm);					// fill  - Заменяет все элементы указанным значением.
	const Type* data() const;					// data	 - Получает адрес первого элемента.
	const size_t size() const;					// size	 - Подсчитывает количество элементов.
	const Type& front() const;					// front - Обращается к первому элементу.
	const Type& back() const;					// back	 - Обращается к последнему элементу.
	const Type& at(const size_t& id) const;		// at    - Обращается к элементу в указанной позиции.
	Type& operator[] (const size_t& id) const;  // [id]	 - Обращение по индексу
private:
	class Iterator {							// Класс итераторов
	public:
		Iterator(Type* ptr) : ptr(ptr) {};						// Конструктор
		Type&	  operator *  () const { return *ptr; }			// 
		Type*	  operator -> () const { return ptr; }			// 
		Iterator& operator ++ ()	   { ++ptr; return *this; }
		Iterator  operator ++ (Type)   { Iterator tmp = *this; ++(*this); return  tmp; }
		Iterator& operator -- ()	   { --ptr; return *this; }
		Iterator  operator -- (Type)   { Iterator tmp = *this; --(*this); return  tmp; }
		friend bool operator == (const Iterator& a, const Iterator& b) {
			return a.ptr == b.ptr;
		}
		friend bool operator!=(const Iterator& a, const Iterator& b) {
			return a.ptr != b.ptr;
		}
	private:
		Type* ptr;
	};
public:
	Iterator begin() { return Iterator(&arr[0]);}
	Iterator end()   { return Iterator(&arr[asize - 1]);}
};


template <typename Type, size_t asize>
Array<Type, asize>::Array() {
	arr = new Type[asize];
}

template <typename Type, size_t asize>
Array<Type, asize>::Array(const Type& elm) {
	this->Array<Type, asize>::Array();
	for (size_t i = 0; i < asize; ++i)
		arr[i] = elm;
}

template <typename Type, size_t asize>
Array<Type, asize>::~Array() {
	delete[] arr;
}

template <typename Type, size_t asize>
Array<Type, asize>::Array(const Array<Type, asize>& obj) {
	arr = new Type[asize];
	for (size_t i = 0; i < asize; ++i)
		arr[i] = obj.arr[i];
}

template<typename Type, std::size_t asize>
Type& Array<Type, asize>::operator[](const size_t& id) const {
	return arr[id];
}

template<typename Type, std::size_t asize>
const Type& Array<Type, asize>::at(const size_t& id) const {
	return arr[id];
}

template<typename Type, std::size_t asize>
const Type& Array<Type, asize>::front() const {
	return arr[0];
}

template<typename Type, std::size_t asize>
const Type& Array<Type, asize>::back() const {
	return arr[asize-1];
}

template<typename Type, std::size_t asize>
const size_t Array<Type, asize>::size() const {
	return asize;
}

template<typename Type, std::size_t asize>
const Type* Array<Type, asize>::data() const {
	return &arr[0];
}

template<typename Type, std::size_t asize>
void Array<Type, asize>::fill(const Type& elm) {
	for (size_t i = 0; i < asize; i++)
		arr[i] = elm;
}

template<typename Type, std::size_t asize>
void Array<Type, asize>::show() const {
	for (size_t i = 0; i < asize; i++)
		cout << "[" << i << "] = " << arr[i] << " ";
	cout << '\n';
}

template <typename Type, size_t asize>
ostream& operator << (ostream &stream, const Array<Type, asize> &array) {
	size_t i;
	stream << "{";
	for (i = 0; i < asize - 1; ++i)
		stream << array[i] << ", ";
	return stream << array[i] << "}";
}

template <size_t asize>
ostream& operator << (ostream &stream, const Array<char, asize> &array) {
	size_t i;
	for (i = 0; i < asize; ++i)
		stream << array[i];
	return stream;
}


int main() {
	setlocale(0, "");
	cout << "==============Test===============\n";
	Array<int, 20> inarr(1);
	Array<char, 20> charr('p');
	Array<double, 20> flarr(0.32);

	cout << "Integ = " << inarr << '\n';
	cout << "Float = " << flarr << '\n';
	cout << "Char  = " << charr << '\n';
	
	Array<int, 20> copy_arr(inarr);
	cout << "Copy array = " << copy_arr << '\n';
	cout << "Fill array on 99: ";
	inarr.fill(99);
	cout << inarr << '\n';
	cout << "Back  = " << inarr.back() << "\n";
	cout << "Front = " << inarr.front() << "\n";
	cout << "Size  = " << inarr.size() << "\n";
	cout << "DATA  = " << inarr.data() << "\n";
	cout << "Begin = " << *inarr.begin();
	cout << "\nEnd = " << *inarr.end();
}