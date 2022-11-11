/*--Двоичное дерево поиска - Binary_search_tree--*/
#include <iostream>
#include <queue>
#include <stack>

using std::queue;
using std::stack;
using std::cout;

template <typename Type>
class BST {											// Класс описывающий двоичное дерево
private:
	class Node {									// Класс описывающий узел дерева
	public:
		Type data;									// Поле данных
		Node *left;									// Указатель на левого потомка
		Node *right;								// Указатель на правого потомка
		Node(Type d, Node *l = nullptr, Node *r = nullptr) : 
			data(d), left(l), right(r) {}			// Конструктор с параметром
	};
	Node *root;										// Указатель на корень дерева 
	size_t count;									// Кол-во элементов в дереве
	size_t _size(Node*);							// Рекурсивный подсчёт кол-ва элементов в дереве
	size_t _depth(Node*);							// Глубина дерева, возвращает наибольший размер 
	void _print_inord(Node *current);				// Инфиксный					<-- Рекурсивный вариант
	void _print_preord(Node *current);				// Префиксный					<-- Рекурсивный вариант
	void _print_postord(Node *current);				// Постфиксный					<-- Рекурсивный вариант
	void _delete_bst(Node *current);				// Рекурсивное удаление всех элементов дерева					
	void _copy_tree(Node*);							// Итеративное копирование дерева для конструктора копирования
	Type _max_elem(Node* curr);						// Рекурсивный поиск максимального элемента от заданного узла
	Type _min_elem(Node* curr);						// Рекурсивный поиск минимального элемента от заданного узла
public:
	BST();											// Конструктор без параметров
	BST(const Type &data);							// Конструктор с параметрами
	BST(const BST<Type> &btree);			        // Конструктор копирования
	~BST();											// Деструктор

	void print_inord();								// Инфиксный обход (упорядоченный)  <-- Рекурсивный вариант
	void print_preord();							// Префиксный обход					<-- Рекусривный вариант
	void print_postord();							// Постфиксный обход				<-- Рекусривный вариант
	void show_inord();								// Инфиксный обход (упорядоченный)  <-- Итеративный вариант
	void show_preord();								// Префиксный обход					<-- Итеративный вариант
	void show_postord();							// Постфиксный обход				<-- Итеративный вариант
	void insert(const Type &elem);					// Вставка элемента
	void erase(Type elm);							// Удаление элемента, если он есть
	bool find(const Type &elem);					// Вернет true если элемент есть, иначе 0
	bool empty();									// Если пуст true, иначе false
	size_t size();									// Кол-во элементов в дереве
	size_t depth();									// Глубина дерева
	size_t size_rec();								// Кол-во элеметов в дереве, рекурсивное вычисление
	Type max_elem();								// Возвращает максимальный элемент	<-- Итеративный поиск
	Type min_elem();								// Возвращает минимальный элемент   <-- Итеративный поиск
	Type successor(const Type &elem);				// Поиск преемника (больший ключ по сравнению с оригинальным ключом)
};


template <typename Type>
BST<Type>::BST() {
	root = nullptr;
	count = 0;
}

template <typename Type>
BST<Type>::BST(const Type &data) {
	Node *rt = new Node(data);
	root  = rt;
	count = 1;
}

template <typename Type>
BST<Type>::BST(const BST<Type> &btree) {
	_copy_tree(btree.root);
}

template <typename Type> 
BST<Type>::~BST() {
	_delete_bst(root);
}

template <typename Type>
void BST<Type>::_delete_bst(Node* current) {
	if (current) {
		_delete_bst(current->left);
		_delete_bst(current->right);
		delete current;
	}
}

template <typename Type>
void BST<Type>::_print_inord(Node *current) {
	if (current) {
		_print_inord(current->left);
		std::cout << current->data << " ";
		_print_inord(current->right);
	}
}

template <typename Type>
void BST<Type>::print_inord() {
	_print_inord(root);
	std::cout << "\n";
}

template <typename Type>
void BST<Type>::_print_preord(Node *current) {
	if (current) {
		std::cout << current->data << " ";
		_print_preord(current->left);
		_print_preord(current->right);
	}
}

template <typename Type>
void BST<Type>::print_preord() {
	_print_preord(root);
	std::cout << "\n";
}

template <typename Type>
void BST<Type>::_print_postord(Node* current) {
	if (current) {
		_print_preord(current->left);
		_print_preord(current->right);
		std::cout << current->data << " ";
	}
}

template <typename Type>
void BST<Type>::print_postord() {
	_print_postord(root);
	std::cout << "\n";
}

template <typename Type>
bool BST<Type>::find(const Type &elem) {
	Node *tmp = root;
	while (tmp && tmp->data != elem) {
		if (tmp->data > elem)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return tmp != nullptr;
}

template <typename Type>
bool BST<Type>::empty() {
	return count > 0;
}

template <typename Type>
void BST<Type>::insert(const Type& elem) {
	Node *curr = root;
	if (!root) {
		this->BST<Type>::BST(elem);
		return;
	}
	while (curr && curr->data != elem) {
		if (curr->data > elem && curr->left == nullptr) {
			curr->left = new Node(elem);
			++count;
			return;
		}
		if (curr->data < elem && curr->right == nullptr) {
			curr->right = new Node(elem);
			++count;
			return;
		}
		if (curr->data > elem)
			curr = curr->left;
		else
			curr = curr->right;
	}
}

template <typename Type>
void BST<Type>::erase(Type elem) {
	if (!root)
		return;
	Node *curr = root;
	Node *parent = nullptr;
	while (curr && curr->data != elem) {
		parent = curr;
		if (elem < curr->data)
			curr = curr->left;
		else
			curr = curr->right;
	}
	if (!curr)
		return;
	if (curr->left == nullptr) {               // Вместо curr подвешивается его правое поддерево
		if (parent && parent->left == curr)
			parent->left = curr->right;
		if (parent && parent->right == curr)
			parent->right = curr->right;
		--count;
		delete curr;
		return;
	}
	if (curr->right == nullptr) {				// Вместо curr подвешивается его левое поддерево
		if (parent && parent->left == curr)
			parent->left = curr->left;
		if (parent && parent->right == curr)
			parent->right = curr->left;
		--count;
		delete curr;
		return;
	}
	// У элемента есть два потомка, тогда на место элемента поставим наименьший элемент из его правого поддерева
	Node *replace = curr->right;
	while (replace->left)
		replace = replace->left;
	Type replace_value = replace->data;
	erase(replace_value);
	curr->data = replace_value;
}

template <typename Type>
size_t BST<Type>::size() {
	return count;
}

template <typename Type>
Type BST<Type>::max_elem() {
	if (!root) { return Type(0); }
	if (!root->right) { return root->data; }
	Node *curr = root;
	while (curr->right) {
		curr = curr->right;
	}
	return curr->data;
}

template <typename Type>
Type BST<Type>::min_elem() {
	if (!root) { return Type(0); }
	if (!root->left) { return root->data; }
	Node* curr = root;
	while (curr->left) {
		curr = curr->left;
	}
	return curr->data;
}

template <typename Type>
Type BST<Type>::_min_elem(Node *curr) {
	if (!curr)
		return Type(0);
	else if (!curr->left)
		return curr->data;
	else
		return _min_elem(curr->left);
}

template <typename Type>
Type BST<Type>::_max_elem(Node* curr) {
	if (!curr)
		return Type(0);
	else if (!curr->right)
		return curr->data;
	else
		return _max_elem(curr->right);
}

template <typename Type>
Type BST<Type>::successor(const Type &elem) {
	Node *curr = root;
	Node *succ = nullptr;
	while (curr) {
		if (curr->data > elem) {
			succ = curr;
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
	return (succ) ? succ->data : Type(0);
}

template <typename Type>
void BST<Type>:: _copy_tree(Node* from) {
	queue<Node*> q;
	if (from) {
		q.push(from);
		while (!q.empty()) {
			Node* top = q.front();
			q.pop();
			this->insert(top->data);
			//cout << top->data << " ";
			if (top->left)
				q.push(top->left);
			if (top->right)
				q.push(top->right);
		}
	}
	//cout << std::endl;
}

// Инфиксный (упорядоченный) обход
template <typename Type>
void BST<Type>::show_inord() {
	stack<Node*> s;
	Node* cur = root;
	while (cur || !s.empty()) {
		while (cur) {
			s.push(cur);
			cur = cur->left;
		}
		Node* top = s.top();
		s.pop();
		cout << top->data << " ";
		cur = top->right;
	}
	cout << std::endl;
}

// Префиксный обход - с помощью стека
template <typename Type>
void BST<Type>::show_preord() {
	stack<Node*> s;
	Node* cur = root;
	while (cur || !s.empty()) {
		while (cur) {
			cout << cur->data << " ";
			s.push(cur);
			cur = cur->left;
		}
		Node* top = s.top();
		s.pop();
		cur = top->right;
	}
	cout << std::endl;
}

// Постфикчный обход
template <typename Type>
void BST<Type>::show_postord() {
	stack<Node*> s;
	Node* cur = root;
	Node* prev = nullptr;
	while (cur || !s.empty()) {
		while (cur) {
			s.push(cur);
			cur = cur->left;
		}
		Node* top = s.top();
		if (top->right == nullptr || prev == top->right) {
			s.pop();
			prev = top;
			cout << top->data << " ";
		}
		else {
			cur = top->right;
		}
	}
	cout << std::endl;
}

// Глубина
template <typename Type>
size_t BST<Type>::depth() {
	return _depth(root);
}

template <typename Type>
size_t BST<Type>::_depth(Node* node) {
	size_t left_num  = 0;
	size_t right_num = 0;
	if (!node)
		return 0;
	if (node->left)
		left_num += _depth(node->left);
	if (node->right)
		right_num += _depth(node->right);
	return (left_num > right_num ? left_num : right_num) + 1;
}

// Рекурсивное вычисление размера дерева
template <typename Type>
size_t BST<Type>::_size(Node *node) {
	if (!node)
		return 0;
	return _size(node->left) + _size(node->right) + 1;
}

template <typename Type>
size_t BST<Type>::size_rec() {
	return _size(root);
}


int main() {
	setlocale(0, "ru");
	BST<int>  bst;
	BST<char> chbst;
	for (int i = 0; i < 20; ++i) {
		bst.insert(rand() % 1000);
		chbst.insert(char(rand() % 100));
	}
	cout << "-------------Integer--------------\n";
	cout << "In -->    \t";    bst.print_inord();
	cout << "Pref -->  \t";    bst.print_preord();
	cout << "Postf --> \t";    bst.print_postord();
	cout << "--------------Char----------------\n";
	cout << "In -->    \t";    chbst.show_inord();
	cout << "Pref -->  \t";    chbst.show_preord();
	cout << "Postf --> \t";    chbst.show_postord();
	return 0;
}