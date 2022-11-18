/*Красно-черное дерево - Red-Black tree*/
#include <iostream>
#include <string>
#include <stack>
#include <queue>

using std::string;
using std::stack;
using std::queue;
using std::cout;
using std::endl;


template <typename Type>
class RB_tree {										// Класс описывающий красно - черное дерево
private:
	enum RBC { black, red };						// Цвет узла
	class Node {									// Класс описывающий узел дерева
	public:
		Type  data;									// Данные (ключ)
		Node* parent;								// Указатель на родителя
		Node* left;									// Указатель на левого потомка
		Node* right;								// Указатель на правого потомка
		RBC   color;								// black = 0, red = 1
		Node(Type d, RBC col = red, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) :
			data(d), color(col), left(l), right(r), parent(p) {};
	};
	Node *root;										// Указатель на корень дерева
	Node *nil;										// Указатель на фиктивную черную вершину
	void _left_rotate(Node *x);						// Вращение влево
	void _right_rotate(Node *x);					// Вращение вправо
	void _fix_insert(Node *x);						// Корректировка цветов при добавлении ключей, поддержание сбалансированности
	void _fix_delete(Node *x);						// Корректировка цветов при удалении элемента, поддержание сбалансированности
	void _swap(Node *x, Node *y);					// Служебная функция для замены элемента
	void _delete_key(Node *n, Type k);				// Служебная функция для удаления элемента
	Node* _imin_key(Node* n);						// Наименьший элемент в дереве  <-- Итеративный поиск
	Node* _imax_key(Node* n);						// Наибольший элемент в дереве  <-- Итеративный поиск
	Node* _rmin_key(Node* n);						// Наименьший элемент в дереве  <-- Рекурсивный поиск
	Node* _rmax_key(Node* n);						// Наибольший элемент в дереве  <-- Рекурсивный поиск
	Node* _rsearch_key(Node* n, Type k);			// Рекурсивный поиск элемента по значению
	Node* _isearch_key(Node* n, Type k);			// Итеративный поиск элемента по значению
	Node* _successor(Node* x);						// Приемник переданного ключа, т.е следующий больший ключ
	Node* _predecessor(Node* x);					// Предшественник переданного ключа, т.е. ближайший наименьший по отношению к переданному
	void _preorder(Node *n);						// Префиксный обход		<-- Рекурсивный вариант
	void _inorder(Node* n);							// Инфиксный обход		<-- Рекурсивный вариант
	void _postorder(Node* n);						// Постфиксный обход	<-- Рекурсивный вариант
	void _destroy(Node *n);							// Удаление дерева
	size_t _size(Node *n);							// Рекурсивный подсчёт кол-ва элементов в дереве
	size_t _depth(Node *n);							// Глубина дерева, возвращает размер самой длинной ветки 
	void _pretty_print(Node*, string, bool);		// Аккуратная печать (представление дерева)
public:
	RB_tree();										// Конструктор по умолчанию
	RB_tree(const Type &key);						// Конструктор с параметром
	RB_tree(const RB_tree<Type> &tree);				// Конструктор копирования
	~RB_tree();										// Деструктор
	void clear();									// Очистка дерева
	bool empty();									// Есть ли элементы в дереве
	bool search(const Type &key);					// Поиск по ключу
	void insert(const Type &key);					// Добавление элемента (ключа)
	void erase (const Type &key);					// Удаление по значению
	Type successor(const Type& key);				// Приемник (самый ближний наибольший элемент относительно переданного)
	Type predecessor(const Type& key);				// Предшественник (самый ближний наименьший элемент от переданного)
	Type get_root();								// Получить значение в корне
	Type min_key();									// Наименьший элемент в дереве
	Type max_key();									// Максимальный элемент в дереве
	void preorder_rec();							// Префиксный обход		<-- Рекурсивный вариант
	void inorder_rec();								// Инфиксный обход		<-- Рекурсивный вариант
	void postorder_rec();							// Постфиксный обход	<-- Рекурсивный вариант
	void preorder_iter();							// Префиксный обход		<-- Итеративный вариант
	void postorder_iter();							// Постфиксный обход	<-- Итеративный вариант
	void inorder_iter();							// Инфиксный обход		<-- Итеративный вариант
	void pretty_print();							// Представление дерева
	size_t depth();									// Глубина дерева с учетом фиктивных nil листов (черная высота)
	size_t size();									// Кол-во элеметов в дереве, рекурсивное вычисление с учетом nil листов
};


template <typename Type>
RB_tree<Type>::RB_tree() {
	nil = new Node(0, black);
	nil->left = nullptr;
	nil->right = nullptr;
	root = nil;
}

template <typename Type>
RB_tree<Type>::RB_tree(const Type& key) {
	this->RB_tree<Type>::RB_tree();
	insert(key);
}

template <typename Type>
RB_tree<Type>::RB_tree(const RB_tree<Type> &tree) {
	this->RB_tree<Type>::RB_tree();
	Node *from = tree.root;
	queue<Node*> q;
	if (from) {
		q.push(from);
		while (!q.empty()) {
			Node* top = q.front();
			q.pop();
			if (top != tree.nil)
				insert(top->data);
			if (top->left)
				q.push(top->left);
			if (top->right)
				q.push(top->right);
		}
	}
}

template <typename Type>
RB_tree<Type>::~RB_tree() {
	_destroy(root);
}

template <typename Type>
void RB_tree<Type>::_left_rotate(Node* x) {	// Левое вращение
	Node* y = x->right;						// Временный указатель на правое поддерево узла х
	x->right = y->left;						// В указателе на правое поддерево запоминается все левое поддерево нижнего узла
	if (y->left != nil) {					// Если левое поддерево вершины 'х' не лист и есть потомки, тогда
		y->left->parent = x;				// Теперь у 'х' в правом поддереве лежит левое поддерево его нижнего узла
	}
	y->parent = x->parent;					// Родителем правого потомка х становится тот же родитель что и у х
	if (x->parent == nullptr) {				// Если 'х' был корнем, тогда вытаскиваемый узел и 'у' станет корнем
		this->root = y;
	}
	else if (x == x->parent->left) {		// Если 'х' это левый потом в дереве, тогда
		x->parent->left = y;				// Тогда левым потомком станет вытаскиваемый узел
	}
	else {									// Если 'х' это правый потомок
		x->parent->right = y;				// Тогда правым потомком станет 'у', как бы всплывет наверх
	}
	y->left = x;							// Вытаскиваемый узел в левом потомке содержит х (т.к. он был больше х и лежал справа)
	x->parent = y;							// Родителем х становится у
}

template <typename Type>
void RB_tree<Type>::_right_rotate(Node *x) {// Вращение вправо
	Node* y = x->left;						// Указатель на узел, который будет переподвешан
	x->left = y->right;						// В 'х' в левое поддерево сохраняется указатель на правое поддерево извлекаемого узла
	if (y->right != nil) {					// Если у извлекаемого узла 'y', у его правого поддерева есть потомки
		y->right->parent = x;				// Тогда его родителем становится 'х'
	}
	y->parent = x->parent;					// Запоминаем родителя 'х'
	if (x->parent == nullptr) {				// Если родителя нет, значит это корень
		this->root = y;						// Тогда извлекаемый узел становится корнем
	}
	else if (x == x->parent->right) {		// Если 'х' это не корень и 'х' лежит в правом поддереве, тогда
		x->parent->right = y;				// Тогда к родителю 'х' в правое поддерево подвешивается извлекаемый узел
	}
	else {									// Если 'х' это левое поддерево своего родителя
		x->parent->left = y;				// Тогда к родителю 'х' в левого потомка подвешивается 'у'
	}
	y->right = x;							// Перекуинуть оставшиеся указатели, в правое поддерево извлекаемого пойдет 'х'
	x->parent = y;							// Родителем х станет извлеченный (переподвешанный) узел 'у'
}

template <typename Type>
void RB_tree<Type>::_fix_insert(Node *x) {				// Поддержание сбалансированности
	Node* tmp;											// Временный указатель
	while (x->parent->color == red) {					// Пока у родителя цвет красный, проверять черную высоту
		if (x->parent == x->parent->parent->right) {	// Если родитель текущего узла это правое поддерево, тогда
			tmp = x->parent->parent->left;				// Временный указатель на левое поддерево относительно узла
			if (tmp->color == red) {					// Если в поддереве левый узел красный
				tmp->color = black;						// Перекрасить его в черный
				x->parent->color = black;				// Перекрасить правый тоже в черный
				x->parent->parent->color = red;			// Перекрасить родителя этих узлов в красный
				x = x->parent->parent;					// Поднять узел 
			}
			else {										// Если левый узел черный
				if (x == x->parent->left) {				// Для случая, когда узел левое поддерево
					x = x->parent;						// Поднять узел
					_right_rotate(x);					// Сделать вращение вправо
				}
				x->parent->color = black;				// Есди узел правое поддерево, покрасить родителя в черный
				x->parent->parent->color = red;			// А родителя родителя в красный
				_left_rotate(x->parent->parent);		// Сделать левый поворот, такое правило
			}
		}
		else {											// Если родитель текущего узла это левое поддерево, тогда
			tmp = x->parent->parent->right;				// Временный указатель на правое поддерево относительно узла
			if (tmp->color == red) {					// Если он красный
				tmp->color = black;						// Перекрасить
				x->parent->color = black;				// Перекрасить родителя
				x->parent->parent->color = red;			// И родителя родителя
				x = x->parent->parent;					// Поднять узел
			}
			else {
				if (x == x->parent->right) {
					x = x->parent;
					_left_rotate(x);
				}
				x->parent->color = black;
				x->parent->parent->color = red;
				_right_rotate(x->parent->parent);
			}
		}
		if (x == root) {
			break;
		}
	}
	root->color = black;
}

template <typename Type>
void RB_tree<Type>::_fix_delete(Node *x) {
	Node* s;
	while (x != root && x->color == black) {
		if (x == x->parent->left) {
			s = x->parent->right;
			if (s->color == red) {
				s->color = black;
				x->parent->color = red;
				_left_rotate(x->parent);
				s = x->parent->right;
			}
			if (s->left->color == black && s->right->color == black) {
				s->color = red;
				x = x->parent;
			}
			else {
				if (s->right->color == black) {
					s->left->color = black;
					s->color = red;
					_right_rotate(s);
					s = x->parent->right;
				}
				s->color = x->parent->color;
				x->parent->color = black;
				s->right->color = black;
				_left_rotate(x->parent);
				x = root;
			}
		}
		else {
			s = x->parent->left;
			if (s->color == red) {
				s->color = black;
				x->parent->color = red;
				_right_rotate(x->parent);
				s = x->parent->left;
			}
			if (s->right->color == black && s->right->color == black) {
				s->color = red;
				x = x->parent;
			}
			else {
				if (s->left->color == black) {
					s->right->color = black;
					s->color = red;
					_left_rotate(s);
					s = x->parent->left;
				}
				s->color = x->parent->color;
				x->parent->color = black;
				s->left->color = black;
				_right_rotate(x->parent);
				x = root;
			}
		}
	}
	x->color = black;
}

template <typename Type>
void RB_tree<Type>::_swap(Node *x, Node *y) {
	if (x->parent == nullptr) {
		root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->parent = x->parent;
}

template <typename Type>
void RB_tree<Type> ::_delete_key(Node* n, Type k) {
	Node* z = nil;
	Node* x, * y;
	while (n != nil) {
		if (n->data == k) {
			z = n;
		}
		if (n->data <= k) {
			n = n->right;
		}
		else {
			n = n->left;
		}
	}
	if (z == nil) {
		return;
	}
	y = z;
	int origin_color = y->color;
	if (z->left == nil) {
		x = z->right;
		_swap(z, z->right);
	}
	else if (z->right == nil) {
		x = z->left;
		_swap(z, z->left);
	}
	else {
		y = _imin_key(z->right);
		origin_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		}
		else {
			_swap(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		_swap(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (origin_color == black) {
		_fix_delete(x);
	}
}

template <typename Type>
typename RB_tree<Type>::Node* RB_tree<Type>::_imin_key(Node *n) {
	while (n->left != nil) {
		n = n->left;
	}
	return n;
}

template <typename Type>
typename RB_tree<Type>::Node* RB_tree<Type>::_imax_key(Node *n) {
	while (n->right != nil) {
		n = n->right;
	}
	return n;
}

template <typename Type>
typename RB_tree<Type>::Node* RB_tree<Type>::_rmin_key(Node* n) {
	if (n == nil || n == nullptr)
		return nullptr;
	if (n->left == nil || n->left == nullptr)
		return n;
	else
		return _rmin_key(n->left);
}

template <typename Type>
typename RB_tree<Type>::Node* RB_tree<Type>::_rmax_key(Node* n) {
	if (n == nil || n == nullptr)
		return nullptr;
	if (n->right == nil || n->right == nullptr)
		return n;
	else
		return _rmax_key(n->right);
}

template <typename Type>
typename RB_tree<Type>::Node* RB_tree<Type>::_rsearch_key(Node* n, Type k) {
	if (k == n->data)
		return n;
	if (n == nil || n == nullptr)
		return nullptr;
	if (k < n->data)
		return _rsearch_key(n->left, k);
	if (k > n->data)
		return _rsearch_key(n->right, k);
}

template <typename Type>
typename RB_tree<Type>::Node* RB_tree<Type>::_isearch_key(Node* n, Type k) {
	Node* z = n;
	while (z) {
		if (k > z->data) 
			z = z->right;
		else if (k < z->data) 
			z = z->left;
		else 
			return z;
	}
	return nullptr;
}

template <typename Type>
typename RB_tree<Type>::Node* RB_tree<Type>::_successor(Node* x) {
	if (x->right != nil) {				// Если есть правое поддерево, тогда
		return _imin_key(x->right);		// Нужно найти наименьший элемент в левой ветке - это приемник
	}
	if (x->data == max_key()) {			// Если ключ это самый максимальный элемент в дереве, тогда
		cout << "Данный ключ - это наибольший элемент в дереве\n";
		return nullptr;					// Нет у него приемника (т.к приемник - это следующий больший элемент)
	}
	else {
		Node* y = x->parent;			// Если правого поддерева нет, тогда
		while (y && x == y->right) {	// Подниматься вверх по родителям
			x = y;
			y = y->parent;
		}
		return y;
	}
}

template <typename Type>
typename RB_tree<Type>::Node* RB_tree<Type>::_predecessor(Node* x) {
	if (x->left != nil) {
		return _imax_key(x->left);
	}
	if (x->data == min_key()) {
		cout << "Данный ключ наименьший элемент в дереве, у него нет предшественника\n";
		return nullptr;
	}
	Node* y = x->parent;
	while (y && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;

}

template <typename Type>
void RB_tree<Type> ::_preorder(Node* n) {
	if (n != nil) {
		cout << n->data << " ";
		_preorder(n->left);
		_preorder(n->right);
	}
}

template <typename Type>
void RB_tree<Type> ::_inorder(Node* n) {
	if (n != nil) {
		_inorder(n->left);
		cout << n->data << " ";
		_inorder(n->right);
	}
}

template <typename Type>
void RB_tree<Type> ::_postorder(Node* n) {
	if (n != nil) {
		_postorder(n->left);
		_postorder(n->right);
		cout << n->data << " ";
	}
}

template <typename Type>
void RB_tree<Type>::_destroy(Node *n) {
	if (n != nullptr && n != nil) {
		_destroy(n->left);
		_destroy(n->right);
		delete n;
	}
}

template <typename Type>
size_t RB_tree<Type>::_depth(Node* n) {
	size_t left_num  = 0;
	size_t right_num = 0;
	if (!n)
		return 0;
	if (n->left)
		left_num += _depth(n->left);
	if (n->right)
		right_num += _depth(n->right);
	return (left_num > right_num ? left_num : right_num) + 1;
}

template <typename Type>
size_t RB_tree<Type>::_size(Node *n) {
	if (n == nullptr || n == nil)
		return 0;
	return _size(n->left) + _size(n->right) + 1;
}

template <typename Type>
void RB_tree<Type>::clear() {
	_destroy(root);
	// Очистка - повторная инициализация для работы
	this->RB_tree<Type>::RB_tree();
}

template <typename Type>
bool RB_tree<Type>::empty() {
	if (root == nullptr || root == nil)
		return true;
	else
		return false;
}

template <typename Type>
bool RB_tree<Type>::search(const Type& key) {
	return _isearch_key(root, key) != nullptr;
}

template <typename Type>
void RB_tree<Type>::insert(const Type &key) {
	Node* node = new Node(key, red);
	node->parent = nullptr;
	node->left = nil;
	node->right = nil;

	Node* y = nullptr;
	Node* x = root;

	while (x != nil) {
		y = x;
		if (node->data < x->data) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	node->parent = y;
	if (y == nullptr) {
		root = node;
	}
	else if (node->data < y->data) {
		y->left = node;
	}
	else {
		y->right = node;
	}

	if (node->parent == nullptr) {
		node->color = black;
		return;
	}

	if (node->parent->parent == nullptr) {
		return;
	}
	_fix_insert(node);
}

template <typename Type>
void RB_tree<Type>::erase(const Type &key) {
	_delete_key(root, key);
}

template <typename Type>
Type RB_tree<Type>::get_root() {
	return root ? root->data : Type(0);
}

template <typename Type>
Type RB_tree<Type>::min_key() {
	Node *tmp = _imin_key(root);
	if (tmp != nullptr && tmp != nil)
		return tmp->data;
	else
		return Type(0);
}

template <typename Type>
Type RB_tree<Type>::max_key() {
	Node* tmp = _imax_key(root);
	if (tmp != nullptr && tmp != nil)
		return tmp->data;
	else
		return Type(0);
}

template <typename Type>
Type RB_tree<Type>::successor(const Type& key) {
	Node *tmp = _isearch_key(root, key);
	if (tmp != nullptr && tmp != nil) {
		Node* tm = _successor(tmp);
		return tm ? tm->data : Type(0);
	}
	else {
		std::cout << "Нет такого ключа\n";
		return Type(0);
	}
}

template <typename Type>
Type RB_tree<Type>::predecessor(const Type& key) {
	Node* tmp = _isearch_key(root, key);
	if (tmp != nullptr && tmp != nil) {
		Node* tm = _predecessor(tmp);
		return tm ? tm->data : Type(0);
	}
	else {
		std::cout << "Нет такого ключа\n";
		return Type(0);
	}
}

template <typename Type>
size_t RB_tree<Type>::depth() {
	return _depth(root);
}

template <typename Type>
size_t RB_tree<Type>::size() {
	return _size(root);
}

template <typename Type>
void RB_tree<Type>::inorder_iter() {
	stack<Node*> s;
	Node* cur = root;
	while (cur || !s.empty()) {
		while (cur) {
			s.push(cur);
			cur = cur->left;
		}
		Node* top = s.top();
		s.pop();
		if (top != nil)
			cout << top->data << " ";
		cur = top->right;
	}
	cout << std::endl;
}

template <typename Type>
void RB_tree<Type>::preorder_iter() {
	stack<Node*> s;
	Node* cur = root;
	while (cur || !s.empty()) {
		while (cur) {
			if (cur != nil)
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

template <typename Type>
void RB_tree<Type>::postorder_iter() {
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
			if (top != nil)
				cout << top->data << " ";
		}
		else {
			cur = top->right;
		}
	}
	cout << std::endl;
}

template <typename Type>
void RB_tree<Type>::_pretty_print(Node* rt, string str, bool ls) {
	if (rt != nil) {
		cout << str;
		if (ls) {
			cout << "R----";
			str += "     ";
		}
		else {
			cout << "L----";
			str += "|    ";
		}
		string scol = rt->color ? "RED" : "BLACK";
		cout << rt->data << "(" << scol << ")" << endl;
		_pretty_print(rt->left, str, false);
		_pretty_print(rt->right, str, true);
	}
}

template <typename Type>
void RB_tree<Type>::pretty_print() {
	if (root) {
		_pretty_print(root, "", true);
	}
}

template <typename Type>
void RB_tree<Type>::preorder_rec() {
	_preorder(root);
	cout << "\n";
}

template <typename Type>
void RB_tree<Type>::inorder_rec() {
	_inorder(root);
	cout << "\n";
}

template <typename Type>
void RB_tree<Type>::postorder_rec() {
	_postorder(root);
	cout << "\n";
}

void test_tree(int64_t size) {
	RB_tree<int64_t> rbt;
	for (int64_t i = 0; i < size; ++i) {
		auto ins = static_cast<int64_t>(rand() % 100);
		rbt.insert(ins);
	}
	cout << "IN-order recursive:\t";	rbt.inorder_rec();
	cout << "PRE-order recursive:\t";	rbt.preorder_rec();
	cout << "POST-order recursive:\t";	rbt.postorder_rec();
	cout << "Succes random key:\t"   <<	rbt.successor(int64_t(rand() % 100))   << "\n";
	cout << "Predeces random key:\t" << rbt.predecessor(int64_t(rand() % 100)) << "\n";
	cout << "MAXIMUM:\t"			 << rbt.max_key() << "\n";
	cout << "MINIMUM:\t"			 << rbt.min_key() << "\n";
	cout << "Depth tree:\t"			 << rbt.depth()   << "\n";
	cout << "Size tree:\t"			 << rbt.size()    << "\n";

	RB_tree<int64_t> rbt_copy(rbt);
	cout << "Copy tree:\n";
	cout << "IN-order iterative:\t";	rbt_copy.inorder_iter();
	cout << "PRE-order iterative:\t";	rbt_copy.preorder_iter();
	cout << "POST-order iterative:\t";	rbt_copy.postorder_iter();
	cout << "===================================================\n";
	cout << "Delete random key:\n";
	for (int64_t i = 0; i < size * 2; ++i)
		rbt.erase(rand() % 100);
	cout << "Result:\t";
	rbt.inorder_iter();
	rbt.pretty_print();
}


int main() {
	setlocale(0, "");
	test_tree(20);
	return 0;
}