/*-АА-Дерево - сбалансированное двоичное дерево поиска, 
разновидность красно-черного дерева с доп.ограничениями - AA_Tree-*/
/*Реализация большинства схожих методов есть в Red-Black Tree (RB_tree)*/

#include <iostream>

using std::cout;
using std::endl;

template <typename Type>
class AATree {
private:
	class Node {
	public:
		Type data;				    // Данные (ключ)
		int  level;				    // Высота вершины
		Node *left;				    // Указатель на левого потомка
		Node *right;			    // Указатель на правого потомка
		Node *parent;			    // Указатель на родителя
		Node(Type d, int lv, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) :
			data(d), level(lv), left(l), right(r), parent(p) {};
	};
	Node *root;					    // Корень дерева
    Node* _skew(Node *n);           // Устранение левого горизонтального ребра. Правое вращение
    Node* _split(Node *n);          // Устранение двух последовательных правых горизонтальных ребер. Левое вращение
    Node* _search(const Type &v);   // Поиск элемента
    void _balance(Node *n);         // Балансировка
    void _swap(Node* x, Node* y);   // Обмен значений
    void _increase_level(Node *n);  // Повышение уровня элемента
    void _delete(Node *n);          // Удаление элемента
    void _inorder(Node* n);			// Инфиксный обход
public:
	AATree();
	void insert(const Type &value); // Добавление элемента
    bool search(const Type &value); // Поиск
	void erase (const Type &value); // Удаление элемента (специфика есть с балансировкой)
    void show();                    // Прямой обход
};

template <typename Type>
AATree<Type>::AATree() : root(nullptr) {};

template<typename Type>
typename AATree<Type>::Node* AATree<Type>::_skew(Node* node) {
    if (node->left != nullptr)
        if (node->left->level == node->level) {
            Node* curr = node->left;
            node->left = curr->right;
            if (curr->right != nullptr) {
                node->left->parent = node;
            }
            curr->right = node;
            curr->parent = node->parent;
            node->parent = curr;
            if (curr->parent != nullptr) {
                if (curr->parent->left == node) {
                    curr->parent->left = curr;
                }
                else {
                    curr->parent->right = curr;
                }
            }
            return curr;
        }
    return node;
}

template<typename Type>
typename AATree<Type>::Node* AATree<Type>::_split(Node* node) {
    if (node->right != nullptr && node->right->right != nullptr)
        if (node->level == node->right->right->level) {
            Node* curr = node->right;
            node->right = curr->left;
            if (node->right != nullptr) {
                node->right->parent = node;
            }
            curr->left = node;
            curr->parent = node->parent;
            node->parent = curr;
            if (curr->parent != nullptr) {
                if (curr->parent->left == node) {
                    curr->parent->left = curr;
                }
                else {
                    curr->parent->right = curr;
                }
            }
            curr->level++;
            return curr;
        }
    return node;
}

template<typename Type>
typename AATree<Type>::Node* AATree<Type>::_search(const Type& value) {
    Node* curr = root;
    while (true) {
        if (value == curr->data) {
            return curr;
        }
        else if (value > curr->data) {
            if (curr->right == nullptr)
                return nullptr;
            else
                curr = curr->right;
        }
        else if (value < curr->data) {
            if (curr->left == nullptr)
                return nullptr;
            else
                curr = curr->left;
        }
    }
}

template <typename Type>
void AATree<Type>::_balance(Node* temp) {
    while (temp->parent != nullptr) {
        temp = temp->parent;
        if (temp == root) {
            temp = _skew(temp);
            temp = _split(temp);
            root = temp;
        }
        else {
            temp = _skew(temp);
            temp = _split(temp);
        }
    }
}

template<typename Type>
void AATree<Type>::_swap(Node* x, Node* y) {
    Type tmp = x->data;
    x->data  = y->data;
    y->data  = tmp;
}

template<typename Type>
void AATree<Type>::_increase_level(Node* current) {
    if (current != nullptr) {
        _increase_level(current->left);
        _increase_level(current->right);
        current->level++;
        _balance(current);
    }
}

template<typename Type>
void AATree<Type>::_delete(Node* curr) {
    if (curr->left == nullptr && curr->right == nullptr) {
        //cout << "DELETE\n";
        Node* tmp = curr->parent;
        if (tmp->left == curr) {
            tmp->left = nullptr;
        }
        else 
            tmp->right = nullptr;
        delete curr;
        //cout << "DELETE\n";
    }
    else if (curr->left == nullptr && curr->right != nullptr) {
        //cout << "DELETE\n";
        if (root != curr) {
            Node* tmp = curr->parent;
            if (tmp->left == curr) {
                tmp->left = curr->right;
            }
            else tmp->right = curr->right;
            curr->right->parent = tmp;
            _increase_level(curr->parent->left);
            _increase_level(curr->parent->right);
            _balance(curr->parent);
        }
        else {
            root = curr->right;
            curr->right->parent = nullptr;
        }
        delete curr;
    }
}

template<typename Type>
void AATree<Type>::erase(const Type &value) {
    Node* curr = _search(value);
    //cout << "CURR == " << curr->data << "\n";
    if (curr->left == nullptr && curr->right == nullptr) {
        if (root != curr) {
            Node* tmp = curr->parent;
            if (tmp->left == curr) {
                tmp->left = nullptr;
            }
            else {
                tmp->right = nullptr;
            }
        }
        else {
            root = nullptr;
        }
        delete curr;
    }
    else if (curr->left == nullptr && curr->right != nullptr) {
        if (root != curr) {
            Node* tmp = curr->parent;
            if (tmp->left == curr) {
                tmp->left = curr->right;
            }
            else {
                tmp->right = curr->right;
            }

            curr->right->parent = tmp;
            _increase_level(curr->parent->left);
            _increase_level(curr->parent->right);
            _balance(curr->parent);
        }
        else {
            root = curr->right;
            curr->right->parent = nullptr;
        }
        delete curr;
    }
    else if (curr->left != nullptr && curr->right == nullptr) {
        if (root != curr) {
            Node* tmp = curr->parent;
            if (tmp->left == curr) {
                tmp->left = curr->left;
            }
            else {
                tmp->right = curr->left;
            }
            curr->left->parent = tmp;
            _increase_level(curr->parent->left);
            _increase_level(curr->parent->right);
            _balance(curr->parent);
        }
        else {
            root = curr->left;
            curr->right->parent = nullptr;
        }
        delete curr;
    }
    else {
        Node* node = curr->right;
        while (node->left != nullptr) {
            node = node->left;
        }
        _swap(node, curr);
        _delete(curr);
    }
}

template<typename Type>
void AATree<Type>::insert(const Type& value) {
	Node *node = new Node(value, 1);		    // Создаётся узел, со значением высоты 1
	if (root == nullptr) {						// Если это первый добавляемый элемент в дереве
		root = node;					    	// То сделать его корнем
		return;									// Вернуться
	}											// Если элементы есть, тогда -->
    Node* current = root;
    bool is_set = false;                        // Флаг для определения втавки узла
    while (!is_set) {
        if (value >= current->data) {           // Если значение больше или равно значению текущего, то идем в правую ветку
            if (current->right == nullptr) {    // Если там пусто, то устанавливаем значение
                current->right = node;
                node->parent = current;
                _balance(current->right);
                is_set = true;                  // Установили, и цикл после этого прекратится
            }
            else current = current->right;      // Иначе текущий элемент меняется на правого ребенка
        }
        if (value < current->data) {		    // Если значение меньше значения текущего, то идем в левую ветку
            if (current->left == nullptr) {		// Если там пусто, то устанавливаем значение
                current->left = node;
                node->parent = current;
                _balance(current->left);
                is_set = true;					// Установили, и цикл после этого прекратится
            }
            else current = current->left;		// Иначе текущий элемент меняется на левого ребенка
        }
    }	
}

template<typename Type>
bool AATree<Type>::search(const Type& key) {
    return _search(key) != nullptr;
}

template <typename Type>
void AATree<Type> ::_inorder(Node* n) {
	if (n != nullptr) {
		_inorder(n->left);
		cout << n->data << " ";
		_inorder(n->right);
	}
}

template <typename Type>
void AATree<Type>::show() {
	_inorder(root);
	cout << "\n";
}


int main() {
	setlocale(0, "");
    AATree<int> atr;
    for (int i = 0; i < 10; ++i)
        atr.insert(rand() % 100);
    atr.show();
}