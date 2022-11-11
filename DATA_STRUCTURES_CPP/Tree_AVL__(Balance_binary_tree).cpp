/*--AVL Tree - Сбалансированное двоичное дерево--*/
#include <iostream>
using std::cout;

template <typename Type>
class AVL {
private:
	class Node {
	public:
		Type data;						// Поле с данными (ключ)
		int height;						// Высота поддерева (либо 0, либо -1, либо 1)
		Node *left;						// Указатель на левый лист
		Node *right;					// Указатель на правы лист
		// Конструктор с параметрами
		Node(Type dat) : data(dat), height(1), left(nullptr), right(nullptr) {}
	};
	Node  *root;						// Указатель на корень дерева
	int   height(Node *p);				// Спектр высоты (Возвращает высоту для текущего поддерева, для пустого = 0)
	int   bfactor(Node* p);				// Вычисление баланса узла (Возвращает разницу высоты между левым и правым поддеревом)
	void  fixheight(Node* p);			// Установка поля высоты узла (Обновляет поле height для текущего узла)
	Node* rotate_right(Node *p);		// Правый поворот вокруг p
	Node* rotate_left(Node *q);			// Левый поворот вокруг q
	Node* balance(Node *p);				// Балансировка узла p
	Node* insert(Node *p, Type k);		// Вставка ключа к в дерево с корнем p	
	Node* find_min(Node *n);			// Служебная функция поиска минимума для функции удаления узла
	Node* remove_min(Node *n);			// Служебная функция удаления узла с минимальным ключа
	Node* remove_value(Node *n, Type k);// Удаление ключа из дерева
	void  print(Node* p, int level);	// Печать структуры дерева
	void  del_tree(Node *n);			// Для деструктора, рекурсивное освобождение памяти
public:
	AVL(): root(nullptr) {};			// Конструктор
	~AVL();								// Деструктор
	void insert(Type key);				// Вставка
	void remove(Type key);				// Удаление по значению
	void print();						// Вывод на экран
};


template <typename Type>
int AVL<Type>::height(Node* p) {
	return p ? p->height : 0;
}

template <typename Type>
int AVL<Type>::bfactor(Node* p) {
	return height(p->right) - height(p->left);
}

// Запрашиваются выстоы поддеревьев выбирается наибольшая и к ней прибавляется 1
template<typename Type>
void AVL<Type>::fixheight(Node* p) {
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

template<typename Type>
typename AVL<Type>::Node* AVL<Type>::rotate_right(Node* p) {
	Node *q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

template<typename Type>
typename AVL<Type>::Node* AVL<Type>::rotate_left(Node* q) {
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

template<typename Type>
typename AVL<Type>::Node* AVL<Type>::balance(Node* p) {
	fixheight(p);
	if (bfactor(p) == 2) {
		if (bfactor(p->right) < 0)
			p->right = rotate_right(p->right);
		return rotate_left(p);
	}
	if (bfactor(p) == -2) {
		if (bfactor(p->left) > 0)
			p->left = rotate_left(p->left);
		return rotate_right(p);
	}
	return p;
}

template<typename Type>
typename AVL<Type>::Node* AVL<Type>::insert(Node* p, Type k) {
	if (!p)
		return new Node(k);
	if (k < p->data)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

template<typename Type>
void AVL<Type>::print(Node* p, int level) {
	int i;
	if (p == nullptr)
		return;
	for (i = 0; i < level; ++i)
		cout << "---";
	cout << p->data << "\n";
	print(p->left, level + 1);
	//cout << p->data << "\n";
	print(p->right, level + 1);
	//cout << p->data << "\n";
}

template<typename Type>
typename AVL<Type>::Node* AVL<Type>::find_min(Node* n) {
	return n->left ? find_min(n->left) : n;
}

template<typename Type>
typename AVL<Type>::Node* AVL<Type>::remove_min(Node* n) {
	if (n->left == nullptr)
		return n->right;
	n->left = remove_min(n->left);
	return balance(n);
}

template<typename Type>
typename AVL<Type>::Node* AVL<Type>::remove_value(Node* n, Type k) {
	if (!n)
		return nullptr;
	if (k < n->data)
		n->left = remove_value(n->left, k);
	else if (k > n->data)
		n->right = remove_value(n->right, k);
	else {	// k == n->data
		Node *q = n->left;
		Node *r = n->right;
		delete n;
		if (!r)
			return q;
		Node *min = find_min(r);
		min->right = remove_min(r);
		min->left = q;
		return balance(min);
	}
	return balance(n);
}

template<typename Type>
void AVL<Type>::del_tree(Node* n) {
	if (n) {
		del_tree(n->left);
		del_tree(n->right);
		delete n;
	}
}

template<typename Type>
AVL<Type>::~AVL() {
	del_tree(root);
}

template<typename Type>
void AVL<Type>::insert(Type key) {
	root = insert(root, key);
}

template<typename Type>
void AVL<Type>::remove(Type key) {
	remove_value(root, key);
}

template<typename Type>
void AVL<Type>::print() {
	print(root, 0);
}


int main() {
	AVL<int> avl;
	for (int i = 0; i < 10; ++i) {
		avl.insert(i);
		//avl.print();
	}
	avl.print();
	avl.remove(5);
	avl.remove(8);
	avl.remove(1);
	avl.print();
	return 0;
}