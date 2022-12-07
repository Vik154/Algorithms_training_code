/*-Би-Дерево - BTree Сбалансированное дерево поиска*/
#include <iostream>

using std::cout;


class BTree {
private:
    class Node {
    public:
        Node(const int&, const bool &);     // Конструктор
        Node **ch;                          // Массив дочерних указателей
        int count_keys;                     // Текущее количество ключей
        int *array_keys;                    // Массив ключей
        bool leaf;                          // Верно, когда узел является листом, иначе ложь
        int t;                              // Минимальная степень
        Node* _search(const int&);          // Поиск по ключу, возвращает nullptr, если нет ключа.
        int  _find_key(const int&);         // Функция, которая возвращает индекс первого ключа, который больше или равен k
        int  _predecessor(const int&);      // Предшественник ключа, где ключ находится в переданной позиции в узле
        int  _successor(const int&);        // Преемник ключа, где ключ находится в переданной позиции в узле
        void _traverse();                   // Функция для обхода всех узлов
        void _insert_helper(const int&);    // Вспомогательная функция для вставки нового ключа в поддерево
        void _split(const int&, Node*);     // Служебная функция для разделения узла.
        void _remove(const int&);           // Удаление ключа в поддереве, служебная функция
        void _remove_is_leaf(const int&);   // Функция для удаления ключа, который является листом
        void _remove_not_leaf(const int&);  // Функция для удаления ключа, который не является конечным узлом
        void _fill(const int&);             // Заполнение дочернего узла, если этот дочерний узел имеет менее t-1 ключей
        void _borrow_prev(const int&);      // Заимствование ключа из узла C [id-1] и помещение его в массив child[id]
        void _borrow_next(const int&);      // Заимствование ключа из узла C [id+1] и помещение его в массив child[id]
        void _merge(const int&);            // Объединение id-го потомка узла с (id+1)-ым потомком узла
    };
private:
    Node* root;                 // Указатель на корень
    int deg;                      // Минимальная степень
public:
    BTree(const int&);          // Конструктор, принимает степень
    void traverse();            // Обход (печать)
    void insert(const int&);    // Вставка
    void remove(const int&);    // Удаление
    bool search(const int&);    // Поиск
};


BTree::BTree(const int& deg) : root(nullptr), deg(deg) {};

void BTree::traverse() {
    if (root) root->_traverse();
}

void BTree::insert(const int &key) {
    if (root == nullptr) {
        root = new Node(deg, true);
        root->array_keys[0] = key;  
        root->count_keys = 1;
    }
    else {
        if (root->count_keys == 2 * deg - 1) {
            Node* s = new Node(deg, false);
            s->ch[0] = root;
            s->_split(0, root);
            int i = 0;
            if (s->array_keys[0] < key)
                i++;
            s->ch[i]->_insert_helper(key);
            root = s;
        }
        else
            root->_insert_helper(key);
    }
}

void BTree::remove(const int &key) {
    if (!root) {
        return;
    }
    root->_remove(key);
    if (root->count_keys == 0) {
        Node* tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->ch[0];
        delete tmp;
    }
    return;
}

bool BTree::search(const int &key) {
    return root->_search(key) != nullptr;
}

BTree::Node::Node(const int &deg, const bool &lf) {
    t = deg;                            // Копируем заданную минимальную степень
    leaf = lf;                          // Копируем свойство листа, 'true' - когда узел является листом
    array_keys = new int[2 * t - 1];    // Выделение памяти для максимального количества ключей
    ch = new Node * [2 * t];            // Выделение памяти для массива указателей на потомков
    count_keys = 0;                     // Количество ключей, при создании узла == 0
}

typename BTree::Node::Node* BTree::Node::_search(const int& key) {
    int i = 0;
    while (i < count_keys && key > array_keys[i])   // Находим первый ключ больше или равный k
        i++;
    if (array_keys[i] == key)                       // Если найденный ключ равен k, вернуть этот узел
        return this;
    if (leaf == true)                               // Если ключ здесь не найден и это листовой узел
        return nullptr;
    return ch[i]->_search(key);                  // Переходим к соответствующему потомку
}

int BTree::Node::_find_key(const int& key) {
    int idx = 0;
    while (idx < count_keys && array_keys[idx] < key)
        ++idx;
    return idx;
}

int BTree::Node::_predecessor(const int& id) {     // Функция для получения предшественника ключа id
    Node* cur = ch[id];
    while (!cur->leaf)                              // Продолжаем двигаться в крайний правый узел, пока не дойдем до листа
        cur = cur->ch[cur->count_keys];
    return cur->array_keys[cur->count_keys - 1];    // Возвращаем последний ключ листа
}

int BTree::Node::_successor(const int& id) {
    Node* cur = ch[id + 1];
    while (!cur->leaf)          // Продолжаем перемещать крайний левый узел, начиная с C [id + 1], пока не дойдем до листа
        cur = cur->ch[0];
    return cur->array_keys[0];  // Возвращаем первый ключ листа
}

void BTree::Node::_traverse() {             // Функция для обхода всех узлов в поддереве, основанном на этом узле
    int i;
    for (i = 0; i < count_keys; i++) {      // Есть n ключей и n + 1 потомков, проходит через n ключей и первые n потомков
        if (leaf == false)                  // Если это не лист, то перед печатью ключа [i] 
            ch[i]->_traverse();          // пройти по поддереву с корнем дочернего элемента C [i].
        std::cout << " " << array_keys[i];
    }
    if (leaf == false)                      // Распечатываем поддерево с последним потомком
        ch[i]->_traverse();
}

void BTree::Node::_insert_helper(const int &key) {  // Вставка нового ключа в узел, узел должен быть неполным
    int i = count_keys - 1;                         // Инициализируем индекс как индекс самого правого элемента
    if (leaf == true) {                             // Если это листовой узел
        while (i >= 0 && array_keys[i] > key) {     // Находит расположение нового ключа, который нужно вставить
            array_keys[i + 1] = array_keys[i];      // Перемещает все большие клавиши на одну позицию вперед
            i--;
        }
        array_keys[i + 1] = key;                    // Вставляем новый ключ в найденное место
        count_keys = count_keys + 1;
    }
    else {                                          // Если этот узел не лист
        while (i >= 0 && array_keys[i] > key)       // Найдите ребенка, у которого будет новый ключ
            i--;
        if (ch[i + 1]->count_keys == 2 * t - 1) {   // Проверка на заполненность узла, если он полон - нужно разделить его
            _split(i + 1, ch[i + 1]);               // После разделения средний ключ child[i] поднимается вверх
            if (array_keys[i + 1] < key)
                i++;
        }
        ch[i + 1]->_insert_helper(key);
    }
}

void BTree::Node::_split(const int &id, Node *cur) {// Разделение дочернего узла, cur должен быть заполнен
    Node* z = new Node(cur->t, cur->leaf);          // Новый узел, который будет хранить (t-1) ключи cur
    z->count_keys = t - 1;

    for (int j = 0; j < t - 1; j++)                 // Копируем последние (t-1) ключи cur в z
        z->array_keys[j] = cur->array_keys[j + t];

    if (cur->leaf == false) {
        for (int j = 0; j < t; j++)                 // Копируем последние t дочерних элементов cur в z
            z->ch[j] = cur->ch[j + t];
    }
    cur->count_keys = t - 1;                        // Уменьшаем количество ключей в cur
    for (int j = count_keys; j >= id + 1; j--)      // Создание пространства для нового дочернего элемента
        ch[j + 1] = ch[j];
    ch[id + 1] = z;                                 // Связываем нового потомка с этим узлом, ключ cur переместится в этот узел

    for (int j = count_keys - 1; j >= id; j--)      // Перемещение всех больших ключей на одну позицию вперед.
        array_keys[j + 1] = array_keys[j];
    array_keys[id] = cur->array_keys[t - 1];        // Копируем средний ключ cur в этот узел
    count_keys = count_keys + 1;                    // Увеличиваем количество ключей в этом узле
}

void BTree::Node::_remove(const int &key) {         // Удаление ключа key из поддерева
    int id = _find_key(key);
    if (id < count_keys && array_keys[id] == key) { // Удаляемый ключ есть в этом узле
        if (leaf)
            _remove_is_leaf(id);                     // Если узел является листом, вызывается removeFromLeaf
        else
            _remove_not_leaf(id);                  // Иначе вызывается removeFromNonLeaf
    }
    else {                                          
        if (leaf)                                   // Если этот узел является листом, значит, ключа нет в дереве
            return;
        bool flag = ((id == count_keys) ? true : false);    // Флаг указывает, есть ли ключ в поддереве
        // Если у дочернего элемента, в котором должен существовать ключ, меньше t ключей, заполняем этот дочерний элемент
        if (ch[id]->count_keys < t)
            _fill(id);
        if (flag && id > count_keys)
            ch[id - 1]->_remove(key);
        else
            ch[id]->_remove(key);
    }
    return;
}

void BTree:: Node::_remove_is_leaf(const int &id) { // Удаление ключа, который является листовым узлом
    for (int i = id + 1; i < count_keys; ++i)
        array_keys[i - 1] = array_keys[i];      // Перемещение всех ключей на одну позицию назад
    count_keys--;                               // Уменьшаем количество ключей
    return;
}

void BTree:: Node::_remove_not_leaf(const int &id) { // Удаление ключа, который не является конечным узлом
    int k = array_keys[id];
    if (ch[id]->count_keys >= t) {
        int pred = _predecessor(id);
        array_keys[id] = pred;
        ch[id]->_remove(pred);
    }
    else if (ch[id + 1]->count_keys >= t) {
        int succ = _successor(id);
        array_keys[id] = succ;
        ch[id + 1]->_remove(succ);
    }
    else {
        _merge(id);
        ch[id]->_remove(k);
    }
    return;
}

void BTree:: Node::_fill(const int &id) {
    if (id != 0 && ch[id - 1]->count_keys >= t)
        _borrow_prev(id);
    else if (id != count_keys && ch[id + 1]->count_keys >= t)
        _borrow_next(id);
    else {
        if (id != count_keys)
            _merge(id);
        else
            _merge(id - 1);
    }
    return;
}

void BTree:: Node::_borrow_prev(const int &id) {
    Node* child = ch[id];
    Node* sibling = ch[id - 1];

    for (int i = child->count_keys - 1; i >= 0; --i)
        child->array_keys[i + 1] = child->array_keys[i];

    if (!child->leaf) {
        for (int i = child->count_keys; i >= 0; --i)
            child->ch[i + 1] = child->ch[i];
    }
    child->array_keys[0] = array_keys[id - 1];
    if (!child->leaf)
        child->ch[0] = sibling->ch[sibling->count_keys];
    array_keys[id - 1] = sibling->array_keys[sibling->count_keys - 1];

    child->count_keys += 1;
    sibling->count_keys -= 1;
    return;
}

void BTree:: Node::_borrow_next(const int &id) {
    Node* child = ch[id];
    Node* sibling = ch[id + 1];

    child->array_keys[(child->count_keys)] = array_keys[id];

    if (!(child->leaf))
        child->ch[(child->count_keys) + 1] = sibling->ch[0];

    array_keys[id] = sibling->array_keys[0];

    for (int i = 1; i < sibling->count_keys; ++i)
        sibling->array_keys[i - 1] = sibling->array_keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->count_keys; ++i)
            sibling->ch[i - 1] = sibling->ch[i];
    }
    child->count_keys += 1;
    sibling->count_keys -= 1;
    return;
}

void BTree:: Node::_merge(const int &id) {
    Node* child = ch[id];
    Node* sibling = ch[id + 1];

    child->array_keys[t - 1] = array_keys[id];

    for (int i = 0; i < sibling->count_keys; ++i)
        child->array_keys[i + t] = sibling->array_keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->count_keys; ++i)
            child->ch[i + t] = sibling->ch[i];
    }
    for (int i = id + 1; i < count_keys; ++i)
        array_keys[i - 1] = array_keys[i];

    for (int i = id + 2; i <= count_keys; ++i)
        child[i - 1] = child[i];

    child->count_keys += sibling->count_keys + 1;
    count_keys--;
    delete(sibling);
    return;
}


int main() {
    BTree tree(20);     // В-дерево со степенью t = 20
    for (int i = 0; i < 20; i++)
        tree.insert(rand() % 20);
    tree.traverse();
    cout << "\n";
    for (int i = 0; i < 20; i++)
        tree.remove(rand() % 20);
    tree.traverse();
    cout << "\nBOOL == " << tree.search(rand() % 20);
}