/*Splay tree - Расширяющееся (косое) самобалансирующееся двоичное дерево поиска*/
#include <iostream>
#include <queue>

using std::queue;
using std::cout;

template <typename Type>
class Splay_tree {
private:
    class Node {
    public:
        Type data;                              // Данные (ключ)
        Node *left, *right, *parent;            // Левый, правый листы и родитель
        Node(const Type& data) :
            data(data), left(nullptr), right(nullptr), parent(nullptr) {};
    };
    Node *root;                                 // Корень
    size_t count;                               // Счетчик элементов
    void  _left_rotate(Node *n);                // Разворот поддерева с корнем n влево
    void  _right_rotate(Node *n);               // Разворот поддерева с корнем n вправо
    void  _splay(Node *n);                      // Поднимет ключ в корень, если он присутствует в дереве, иначе поднимет 
    // в корень самый последний элемент к которому был осуществлен доступ и возвращает новый корень.
    void  _replace(Node* u, Node* v);           // Замена вершин для функции erase, для удаления по ключу
    Node* _subtree_minimum(Node* u);            // Наименьший
    Node* _subtree_maximum(Node* u);            // Наибольший элемент
    Node* _find(const Type &key);               // Поиск по ключу
    void  _print_inord(Node *n); 				// Инфиксный обход
	void  _print_preord(Node *n);				// Префиксный обход
    void  _print_postord(Node *n);				// Постфиксный обход
	void  _delete_bst(Node *n);  				// Рекурсивное удаление всех элементов дерева					
	void  _copy_tree(Node*);					// Итеративное копирование дерева для конструктора копирования
public:
    Splay_tree();                               // Конструктор без параметров
    Splay_tree(const Type &data);				// Конструктор с параметрами
	Splay_tree(const Splay_tree<Type> &tree);	// Конструктор копирования
    ~Splay_tree();                              // Деструктор
    void insert(const Type &key);               // Добавление по ключу
    void erase(const Type &key);                // Удаление по ключу
    void print_inord();							// Инфиксный обход (упорядоченный)  <-- Рекурсивный вариант
	void print_preord();						// Префиксный обход					<-- Рекурсивный вариант
    void print_postord();						// Постфиксный обход	            <-- Рекурсивный вариант
    Type successor(const Type &key);
    Type predecessor(const Type& key);
    const Type& min_key()      { return _subtree_minimum(root)->data; }     // Наименьший элемент
    const Type& max_key()      { return _subtree_maximum(root)->data; }     // Наибольший
    bool empty() const         { return root == nullptr; }                  // Есть элементы или нет
    bool find(const Type &key) { return _find(key) != nullptr; }            // Поиск по значению
    size_t size() const        { return count; }                            // Кол-во элементов
};


template <typename Type>
Splay_tree<Type>::Splay_tree() : root(nullptr), count(0) {};

template <typename Type>
Splay_tree<Type>::Splay_tree(const Type& data) {
    Node *node = new Node(data);
    root = node;
    count = 1;
}

template <typename Type>
Splay_tree<Type>::Splay_tree(const Splay_tree<Type>& tree) {
    _copy_tree(tree.root);
}

template <typename Type>
void Splay_tree<Type>:: _copy_tree(Node* from) {
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

template <typename Type>
void Splay_tree<Type>::_delete_bst(Node* n) {
    if (n) {
        _delete_bst(n->left);
        _delete_bst(n->right);
        delete n;
    }
}

template <typename Type>
Splay_tree<Type>::~Splay_tree() {
    _delete_bst(root);
}

template <typename Type>
void Splay_tree<Type>::_left_rotate(Node *x) {
    Node* y = x->right;
    if (y) {
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
    }
    if (!x->parent) 
        root = y;
    else if (x == x->parent->left) 
        x->parent->left = y;
    else 
        x->parent->right = y;
    if (y) 
        y->left = x;
    x->parent = y;
}

template <typename Type>
void Splay_tree<Type>::_right_rotate(Node *x) {
    Node* y = x->left;
    if (y) {
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
    }
    if (!x->parent) 
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else 
        x->parent->right = y;
    if (y) 
        y->right = x;
    x->parent = y;
}

template <typename Type>
void Splay_tree<Type>::_splay(Node *x) {
    while (x->parent) {
        if (!x->parent->parent) {
            if (x->parent->left == x) _right_rotate(x->parent);
            else _left_rotate(x->parent);
        }
        else if (x->parent->left == x && x->parent->parent->left == x->parent) {
            _right_rotate(x->parent->parent);
            _right_rotate(x->parent);
        }
        else if (x->parent->right == x && x->parent->parent->right == x->parent) {
            _left_rotate(x->parent->parent);
            _left_rotate(x->parent);
        }
        else if (x->parent->left == x && x->parent->parent->right == x->parent) {
            _right_rotate(x->parent);
            _left_rotate(x->parent);
        }
        else {
            _left_rotate(x->parent);
            _right_rotate(x->parent);
        }
    }
}

template <typename Type>
void Splay_tree<Type>::_replace(Node* u, Node* v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v) v->parent = u->parent;
}

template <typename Type>
typename Splay_tree<Type>::Node* Splay_tree<Type>::_subtree_minimum(Node* n) {
    while (n->left) n = n->left;
    return n;
}

template <typename Type>
typename Splay_tree<Type>::Node* Splay_tree<Type>::_subtree_maximum(Node* n) {
    while (n->right) n = n->right;
    return n;
}

template <typename Type>
typename Splay_tree<Type>::Node* Splay_tree<Type>::_find(const Type &key) {
    Node* z = root;
    while (z) {
        if (z->data < key) z = z->right;
        else if (key < z->data) z = z->left;
        else return z;
    }
    return nullptr;
}

template <typename Type>
void Splay_tree<Type>::insert(const Type& key) {
    Node* z = root;
    Node* p = nullptr;
    while (z) {
        p = z;
        if (z->data < key) z = z->right;
        else z = z->left;
    }
    z = new Node(key);
    z->parent = p;

    if (!p)
        root = z;
    else if (p->data < z->data)
        p->right = z;
    else 
        p->left = z;
    _splay(z);
    count++;
}

template <typename Type>
void Splay_tree<Type>::erase(const Type &key) {
    Node* z = _find(key);
    if (!z) return;

    _splay(z);

    if (!z->left) _replace(z, z->right);
    else if (!z->right) _replace(z, z->left);
    else {
        Node *y = _subtree_minimum(z->right);
        if (y->parent != z) {
            _replace(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        _replace(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    delete z;
    count--;
}

template <typename Type>
void Splay_tree<Type>::_print_inord(Node *n) {
	if (n) {
		_print_inord(n->left);
		std::cout << n->data << " ";
		_print_inord(n->right);
	}
}

template <typename Type>
void Splay_tree<Type>::print_inord() {
	_print_inord(root);
	std::cout << "\n";
}

template <typename Type>
void Splay_tree<Type>::_print_preord(Node *current) {
	if (current) {
		std::cout << current->data << " ";
		_print_preord(current->left);
		_print_preord(current->right);
	}
}

template <typename Type>
void Splay_tree<Type>::print_preord() {
	_print_preord(root);
	std::cout << "\n";
}

template <typename Type>
void Splay_tree<Type>::_print_postord(Node* current) {
	if (current) {
		_print_preord(current->left);
		_print_preord(current->right);
		std::cout << current->data << " ";
	}
}

template <typename Type>
void Splay_tree<Type>::print_postord() {
	_print_postord(root);
	std::cout << "\n";
}

template <typename Type>
Type Splay_tree<Type>::successor(const Type &key) {
	Node *curr = root;
	Node *succ = nullptr;
	while (curr) {
		if (curr->data > key) {
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
Type Splay_tree<Type>::predecessor(const Type& key) {
    Node* curr = root;
    Node* succ = nullptr;
    while (curr) {
        if (curr->data < key) {
            succ = curr;
            curr = curr->right;
        }
        else {
            curr = curr->left;
        }
    }
    return (succ) ? succ->data : Type(0);

}


int main() {
    setlocale(0, "ru");
    Splay_tree<int> stree;
    for (int i = 0; i < 20; ++i)
        stree.insert(i);
    Splay_tree<int> st2(stree);
    cout << "Copy tree:\t";  st2.print_inord();
    cout << "In order:\t";   stree.print_inord();
    cout << "Pre order:\t";  stree.print_preord();
    cout << "Post order:\t"; stree.print_postord();
    cout << "Min elem = " << stree.min_key() << "\n";
    cout << "Max elem = " << stree.max_key() << "\n";
    cout << "Size = "     << stree.size()    << "\n";
    cout << "Find 5 = "   << stree.find(5)   << "\n";
    cout << "Find 100 = " << stree.find(100) << "\n";
    cout << "Empty = "    << stree.empty()   << "\n";
    stree.erase(5);
    stree.erase(15);
    stree.erase(454);
    cout << "delete 5, 15, 454, res == "; stree.print_inord();
    cout << "Succ 10 = "  << stree.successor(10)  << "\n";
    cout << "Succ 100 = " << stree.successor(100) << "\n";
    cout << "Pred 10 = "  << stree.predecessor(10) << "\n";

    auto x = nullptr;
    if (x == nullptr)
        cout << "\nn!!!!\n";
    if (!x)
        cout << "!x И x == NULL - ОДНО И ТОЖЕ\n";

}