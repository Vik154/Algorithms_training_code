/*Декартово дерево - Treap*/
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;


template <typename Type>
class Treap {										// Класс описывающий декартово дерево
private:
	class Node {									// Класс описывющий узел дерева
	public:
		Type data;									// Данные
		int priority;								// Приоритет
		Node *left;									// Левый потомок
		Node *right;								// Правый потомок
		Node *parent;								// Родитель
		Node(Type d, int pr, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) :
			data(d), priority(pr), left(l), right(r), parent(p) {};
	};
	Node *root;										// Корень
	void _left_rotate(Node *x);						// Вращение влево
	void _right_rotate(Node *x);					// Вращение вправо
	void _travel_up(Node *x);						// Обход приоритетов по родителям
	void _travel_down(Node *x);						// Обход приоритетов по потомкам
	void _delete_key(Node* node, const Type &elm);	// Удаление элемента
	void _inorder(Node *n);							// Инфиксный обход
	Node* _min_key(Node *n);						// Наименьший элемент в дереве
	Node* _max_key(Node *n);						// Наибольший элемент в дереве
	void _pretty_print(Node*, string, bool);		// Печать (представление дерева)
public:
	Treap() : root(nullptr) {};						// Конструктор
	void insert(const Type &val, int pri);			// Вставка элемента и задание ему приоритета
	void split(int spl, Treap *tr1, Treap *tr2);	// Разбивка дерева по значению 'int spl' (Можно Type написать)
	void merge(Treap tree1, Treap tree2);			// Сдияние двух деревьев в одно
	void erase(const Type &elm);					// Удаление элемента
	void show();									// Прямой обход
	void pretty_print();							// Представление дерева
};


template <typename Type>
void Treap<Type>::_left_rotate(Node* x) {	
	Node* y = x->right;						
	x->right = y->left;						
	if (y->left != nullptr) {					
		y->left->parent = x;				
	}
	y->parent = x->parent;			
	if (x->parent == nullptr) {		
		this->root = y;
	}
	else if (x == x->parent->left) {	
		x->parent->left = y;				
	}
	else {									
		x->parent->right = y;				
	}
	y->left = x;
	x->parent = y;							
}

template <typename Type>
void Treap<Type>::_right_rotate(Node *x) { 
	Node* y = x->left;						
	x->left = y->right;						
	if (y->right != nullptr) {					
		y->right->parent = x;				
	}
	y->parent = x->parent;					
	if (x->parent == nullptr) {				
		this->root = y;					
	}
	else if (x == x->parent->right) {		
		x->parent->right = y;				
	}
	else {								
		x->parent->left = y;			
	}
	y->right = x;							
	x->parent = y;							
}

template <typename Type>
void Treap<Type>::_travel_up(Node *x) {
	if (x->parent == nullptr)
		return;
	if (x->parent != nullptr && x->priority >= x->parent->priority)
		return;
	if (x == x->parent->left)
		_right_rotate(x->parent);
	else
		_left_rotate(x->parent);
	
	_travel_up(x);
}

template <typename Type>
void Treap<Type>::_travel_down(Node *x) {
	if (x->left == nullptr && x->right == nullptr)
		return;
	if (x->left != nullptr && x->right != nullptr) {
		if (x->left->priority < x->right->priority)
			_right_rotate(x);
		else
			_left_rotate(x);
	}
	else if (x->left != nullptr)
		_right_rotate(x);
	else
		_left_rotate(x);
	
	_travel_down(x);
}

template <typename Type>
void Treap<Type>::_delete_key(Node *node, const Type &elm) {
	Node *x = nullptr;
	while (node != nullptr) {
		if (node->data == elm) {
			x = node;
			break;
		}
		if (node->data <= elm) {
			node = node->right;
		}
		else {
			node = node->left;
		}
	}
	if (x == nullptr) {
		cout << "Такого элемента нет в дереве --> " << elm << endl;
		return;
	}
	_travel_down(x);

	if (x == x->parent->left)
		x->parent->left = nullptr;
	else
		x->parent->right = nullptr;
	delete x;
	x = nullptr;
}

template <typename Type>
void Treap<Type>::insert(const Type &key, int prior) {
	Node *node = new Node(key, prior);
	Node *y = nullptr;
	Node *x = root;

	while (x != nullptr) {
		y = x;
		if (node->data < x->data) 
			x = x->left;
		else         			  
			x = x->right;
	}
	node->parent = y;
	if (y == nullptr)
		root = node;
	else if (node->data < y->data)
		y->left = node;
	else
		y->right = node;
	if (node->parent != nullptr)
		_travel_up(node);
}

template <typename Type>
void Treap<Type>::split(int dummy, Treap *tree1, Treap* tree2) {
	this->insert(dummy, -99);

	tree1->root = this->root->left;
	tree2->root = this->root->right;

	this->root->left = nullptr;
	this->root->right = nullptr;
	delete this->root;
	this->root = nullptr;
}

template <typename Type>
void Treap<Type>::merge(Treap tree1, Treap tree2) {
	Node *largest  = tree1._max_key(tree1.root);			
	Node *smallest = tree2._min_key(tree2.root);			

	Type data = (largest->data >= smallest->data) ? largest->data : smallest->data;
	Node *new_root = new Node(data, 99);						
	new_root->left = tree1.root;
	new_root->right = tree2.root;

	_travel_down(new_root);					

	Node *curr = new_root;
	while (curr->parent != nullptr)
		curr = curr->parent;

	this->root = curr;

	if (new_root == new_root->parent->left)
		new_root->parent->left = nullptr;
	else 
		new_root->parent->right = nullptr;

	delete(new_root);
	new_root = nullptr;
}

template <typename Type>
typename Treap<Type>::Node* Treap<Type>::_min_key(Node *n) {
	while (n->left != nullptr) {
		n = n->left;
	}
	return n;
}

template <typename Type>
typename Treap<Type>::Node* Treap<Type>::_max_key(Node *n) {
	while (n->right != nullptr) {
		n = n->right;
	}
	return n;
}

template <typename Type>
void Treap<Type> ::_inorder(Node* n) {
	if (n != nullptr) {
		_inorder(n->left);
		cout << n->data << " ";
		_inorder(n->right);
	}
}

template <typename Type>
void Treap<Type> ::erase(const Type &elm) {
	_delete_key(root, elm);
}

template <typename Type>
void Treap<Type>::show() {
	_inorder(root);
	cout << "\n";
}

template <typename Type>
void Treap<Type>::_pretty_print(Node* rt, string str, bool ls) {
	if (rt != nullptr) {
		cout << str;
		if (ls) {
			cout << "R----";
			str += "     ";
		}
		else {
			cout << "L----";
			str += "|    ";
		}
		cout << rt->data << "(" << rt->priority << ")" << endl;
		_pretty_print(rt->left, str, false);
		_pretty_print(rt->right, str, true);
	}
}

template <typename Type>
void Treap<Type>::pretty_print() {
	if (root) {
		_pretty_print(root, "", true);
	}
}



int main() {
	setlocale(0, "");
	Treap<int> mtr;
	for (int i = 0; i < 20; ++i)
		mtr.insert(rand() % 100, rand() % 10);
	mtr.show();
	cout << "================================\n";
	Treap<int> m1, m2;
	mtr.split(50, &m1, &m2);
	m1.pretty_print();
	m2.pretty_print();
	cout << "=================================\n";
	mtr.merge(m2, m1);
	mtr.pretty_print();
	mtr.show();
	return 0;
}