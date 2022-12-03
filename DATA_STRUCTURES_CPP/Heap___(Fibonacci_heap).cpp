/*Фибоначчиева куча - Fibonacci heap — структура данных, отвечающая интерфейсу приоритетная очередь.
Эта структура имеет меньшую амортизированную сложность, чем биномиальная куча и двоичная куча.*/
#include <iostream>
using std::cout;


template <typename Type>
class FHeap {				// Класс описывающий фибоначчиеву кучу
    class Node {			// Класс описывающий один узел (биномиального дерева)
    public:
        Node *left;         // Указатель на левый узел того же предка
        Node *right;        // Указатель на правый узел того же предка
        Node *child;        // Указатель на один из дочерних узлов
        Node *parent;       // Указатель на родителя
        int64_t degree;     // Кол-во дочерних узлов
        int64_t key;        // Ключ
        Type value;         // Значение
        bool marked;        // Был ли перемещен (вырезан) дочерний узел
        
        Node(const int64_t& key, const Type& val) :
            left(nullptr), right(nullptr), child(nullptr), parent(nullptr),
            degree(0), key(key), value(val), marked(false) {};
    };
    Node *root;                                         // Список корней деревьев, указатель на минимальный корень
    size_t cnt;                                         // Кол-во элементов в куче
    Node* _insert(const int64_t& key, const Type& val); // Добавление элемента, служебная функция
    Node* _merge_roots(Node *a, Node *b);               // Объединяет в одно дерево переданные узлы и обновляет список корней
    Node* _find(Node *heap, const int64_t &key);        // Поиск узла по ключу, вернет указатель если есть ключ, иначе null
	Node* _decrease_key(Node* heap, Node* n, const int64_t& value);	// Понизить приоритет ключа до заданного
	Node* _cut(Node* heap, Node* n);					// Вырезание узла из дерева
	Node* _delete_min(Node* n);							// Удалить минимальный ключ
	void  _delete_all(Node* n);							// Очистить полностью кучу
	void  _add_child(Node* parent, Node* child);		// Объединение в одно дерево child и parent
	void  _reset_parent_nodes(Node* n);					// Сброс всех указателей на родителей в null
	void  _show(Node* n);								// Вывод на экран
public:
    FHeap();											// Конструктор
    ~FHeap();											// Деструктор
	void merge(const FHeap& other);						// Объединить текущую и входящую кучи в одну
    void insert(const int64_t& key, const Type& val);	// Добавить узел в кучу
	void decrease_key(const int64_t& old, const int64_t& nnew);	// Понизить приоритет ключа
    bool find(const int64_t &key);						// Поиск по ключу
	bool empty() { return cnt == 0; }					// Проверка на заполненность
	void clear();										// Очистка всей кучи
	void show();										// Отображение
	int64_t get_min();									// Получить минимальный ключ в куче
	int64_t delete_min();								// Удалить минимальный ключ
	int64_t size() { return cnt; }						// Получить размер кучи
};

template <typename Type>
FHeap<Type>::FHeap() : root(nullptr), cnt(0) {};

template <typename Type>
FHeap<Type>::~FHeap() {
	clear();
}

template <typename Type>
void FHeap<Type>::merge(const FHeap &other) {
	root = _merge_roots(root, other.root);
	other.root = nullptr;
}

template <typename Type>
typename FHeap<Type>::Node* FHeap<Type>::_insert(const int64_t& key, const Type& val) {
	Node* n = new Node(key, val);
	n->left = n->right = n;
	root = _merge_roots(root, n);
	cnt++;
	return n;
}

template <typename Type>
void FHeap<Type>::insert(const int64_t& key, const Type& val) {
    _insert(key, val);
}

template <typename Type>
typename FHeap<Type>::Node* FHeap<Type>::_merge_roots(Node* a, Node* b) {
	if (a == nullptr)
		return b;
	if (b == nullptr)
		return a;
	if (a->key > b->key) {
		Node* temp = a;
		a = b;
		b = temp;
	}
	Node* aright = a->right;
	Node* bleft  = b->left;
	a->right = b;
	b->left  = a;
	aright->left = bleft;
	bleft->right = aright;
	return a;
}

template <typename Type>
void FHeap<Type>::_show(Node* n) {
	Node* x = n;
	do {
		if (x->child == nullptr) {
			cout << "(" << x->key << ":" << x->value << ") -> ";
		}
		else {
			cout << "(" << x->key << ":" << x->value << ") -> ";
			_show(x->child);
		}
		x = x->right;
	} while (x != n);
}

template <typename Type>
void FHeap<Type>::show() {
	if (root)
		_show(root);
	else
		cout << "Heap is empty!";
}

template<typename Type>
int64_t FHeap<Type>::get_min() {
    if (root != nullptr)
        return root->key;
    else {
        cout << "Heap is empty!\n";
        return 0ll;
    }
}

template <typename Type>
typename FHeap<Type>::Node* FHeap<Type>::_find(Node* heap, const int64_t& key) {
	Node* n = heap;
	if (n == nullptr)
		return nullptr;
	do {
		if (n->key == key)
			return n;
		Node* res = _find(n->child, key);
		if (res)
			return res;
		n = n->right;
	} while (n != heap);
	return nullptr;

}

template <typename Type>
bool FHeap<Type>::find(const int64_t& key) {
    return _find(root, key) != nullptr;
}

template <typename Type>
void FHeap<Type>::_delete_all(Node* n) {
	if (n != nullptr) {
		Node* c = n;
		do {
			Node* d = c;
			c = c->right;
			_delete_all(d->child);
			delete d;
		} while (c != n);
	}
}

template <typename Type>
void FHeap<Type>::clear() {
	if (root)
		_delete_all(root);
	root = nullptr;
	cnt = 0;
}

template <typename Type>
int64_t FHeap<Type>::delete_min() {
	if (cnt < 1) {
		delete root;
		cnt = 0;
		root = nullptr;
		return 0ll;
	}
	Node* old = root;
	root = _delete_min(root);
	int64_t ret = old->key;
	delete old;
	cnt--;
	return ret;
}

template <typename Type>
typename FHeap<Type>::Node* FHeap<Type>::_delete_min(Node* n) {
	_reset_parent_nodes(n->child);
	if (n->right == n) {
		n = n->child;
	}
	else {
		n->right->left = n->left;
		n->left->right = n->right;
		n = _merge_roots(n->right, n->child);
	}
	if (n == nullptr)
		return n;
	Node** trees = new Node*[cnt];
	for (size_t i = 0; i < cnt; ++i)
		trees[i] = nullptr;

	while (true) {
		if (trees[n->degree] != nullptr) {
			Node* t = trees[n->degree];
			if (t == n)
				break;
			trees[n->degree] = nullptr;
			t->left->right = t->right;
			t->right->left = t->left;
			if (n->key < t->key) {
				_add_child(n, t);
			}
			else {
				if (n->right == n) {
					t->right = t->left = t;
				}
				else {
					n->left->right = t;
					n->right->left = t;
					t->right = n->right;
					t->left  = n->left;
				}
				_add_child(t, n);
				n = t;
			}
			continue;
		}
		else {
			trees[n->degree] = n;
		}
		n = n->right;
	}
	Node* min = n;
	do {
		if (n->key < min->key)
			min = n;
		n = n->right;
	} while (n != n);
	delete[] trees;
	return min;
}

template <typename Type>
void FHeap<Type>::_add_child(Node* parent, Node* child) {
	child->left = child;
	child->right = child;
	child->parent = parent;
	parent->degree++;
	parent->child = _merge_roots(parent->child, child);
}

template <typename Type>
void FHeap<Type>::_reset_parent_nodes(Node* n) {
	if (n == nullptr)
		return;
	Node* c = n;
	do {
		c->marked = false;
		c->parent = nullptr;
		c = c->right;
	} while (c != n);
}

template <typename Type>
void FHeap<Type>::decrease_key(const int64_t &old, const int64_t &nnew) {
	Node *n = _find(root, old);
	if (n == nullptr) {
		cout << "Key not found!";
		return;
	}
	root = _decrease_key(root, n, nnew);
}

template <typename Type>
typename FHeap<Type>::Node* FHeap<Type>::_decrease_key(Node* heap, Node* n, const int64_t &key) {
	if (n->key < key)
		return heap;
	n->key = key;
	Node* parent = n->parent;
	if (parent != nullptr && n->key < parent->key) {
		heap = _cut(heap, n);
		n->parent = nullptr;
		while (parent != nullptr && parent->marked) {
			heap = _cut(heap, parent);
			n = parent;
			parent = n->parent;
			n->parent = nullptr;
		}
		if (parent != nullptr && parent->parent != nullptr)
			parent->marked = true;
		if (n->key < heap->key)
			heap = n;
	}
	return heap;
}

template <typename Type>
typename FHeap<Type>::Node* FHeap<Type>::_cut(Node* heap, Node* n) {
	if (n->right == n) {
		n->parent->child = nullptr;
	}
	else {
		n->right->left = n->left;
		n->left->right = n->right;
		n->parent->child = n->right;
	}
	n->right = n->left = n;
	n->marked = false;
	n->parent->degree--;
	return _merge_roots(heap, n);
}


int main() {
    FHeap<char> hp;
	for (int64_t i = 0; i < 10; i++)
		hp.insert(i, char(i + 65));
	hp.show();
	cout << "\nMIN_KEY == " << hp.get_min() << '\n';
	cout << "SIZE == " << hp.size() << '\n';
	hp.delete_min();
	hp.delete_min();
	hp.delete_min();
	hp.decrease_key(5, -88);
	hp.decrease_key(9, -66);
	hp.show();
	hp.clear();
	hp.show();
}