/* Биномиальная куча - binomial heap
  Множество биномиальных деревьев, которые удовлетворяют следующим свойствам:
  1). Каждое биномиальное дерево в куче подчиняется свойству неубывающей кучи:
  ключ узла не меньше ключа его родительского узла (упорядоченное в соответствии со свойством неубывающей кучи дерево).
  2). Для любого неотрицательного целого k найдется не более одного биномиального дерева, чей корень имеет степень k. */
#include <iostream>
#include <list>

using std::list;
using std::swap;
using std::cout;


template <typename Type>
class BHeap {                   // Класс описывающий кучу (в данном случае со свойствами MAX Heap)
    class Node {                // Класс описывающий 1 узел биномиального дерева
    public:
        int64_t data;           // Ключ узла
        Type value;             // Значение узла (данные)
        int64_t degree;         //   (6)                    // Степень вложенности, кол-во дочерних ухлов
        Node* parent;           //    |                     // Указатель на родителя
        Node* sibling;          //   (4)-->(3)-->(key)      // Указатель на правый соседний узел     
        Node* child;            //   /     /                // Указатель на крайнего левого потомка
                                // (1)   (key)
        Node(const int64_t& key, const Type& val) : data(key), value(val), 
            degree(0), parent(nullptr), sibling(nullptr), child(nullptr) {};
    };
    // Список упорядоченных по возрастанию (degree) корней биномиальных деревьев
    list<Node*> heap;                                   // такого вида: head-->(0)-->(2)-->(5)-->(n+1)
    list<Node*> union_heap(list<Node*>&, list<Node*>&); // Объединяет в один список корни биномиальных деревьев
    list<Node*> remove_min(Node* tree);                 // Удаление минимального ключа и возврат нового списка корней
    Node* find_node(Node* it, const int64_t& val);      // Поиск по ключа (возвращает указатель на узел)
    Node* linking_links(Node *child, Node *parent);     // Cвязывание ссылок деревьев 
    Node* _get_min();                                   // Получить минимальный ключ в куче
    void  regulate_heap_properties();                   // Регулирование свойств кучи (поддержание упорядоченности)
    void  _show(Node* h);                               // Служебная функция обхода кучи, для печати
public:
    void insert(const int64_t &key, const Type &val);   // Добавление элемента (ключ - значение)
    // Уменьшает ключ, присваивая ему новое значение, Вершина, ключ которой был уменьшен, «всплывает» как в обычной куче.
    void decrease_key(const int64_t& old, const int64_t& nevv);
    void extract_min();                                 // Извлекает (удаляет) узел с минимальным ключом из биномиальной кучи
    void print_heap();                                  // Печать кучи (key - value)
    bool find_key(const int64_t& key) {                 // true если ключ есть, иначе false
        return find_node(heap.front(), key) != nullptr;
    }
    int64_t get_min() {
        return _get_min()->data;
    }
    void delete_key(const int64_t &key) {   // Удалить ключ из кучи
        decrease_key(key, INT_MIN);         // Понизить приоритет удаляемого узла до минимума
        extract_min();                      // Удалить узел
    }
};


template <typename Type>
list<typename BHeap<Type>::Node*> BHeap<Type>::union_heap(list<Node*>& h1, list<Node*>& h2) {
    list<Node*> new_list_roots;
    typename list<Node*>::iterator it = h1.begin();
    typename list<Node*>::iterator ot = h2.begin();
    while (it != h1.end() && ot != h2.end()) {
        if ((*it)->degree <= (*ot)->degree) {
            new_list_roots.push_back(*it);
            it++;
        }
        else {
            new_list_roots.push_back(*ot);
            ot++;
        }
    }
    while (it != h1.end()) {
        new_list_roots.push_back(*it);
        it++;
    }
    while (ot != h2.end()) {
        new_list_roots.push_back(*ot);
        ot++;
    }
    return new_list_roots;
}

template <typename Type>
typename BHeap<Type>::Node* BHeap<Type>::linking_links(Node* child, Node* parent) {
    if (child->data > parent->data)
        swap(child, parent);
    parent->parent = child;
    parent->sibling = child->child;
    child->child = parent;
    child->degree++;
    return child;
}

template <typename Type>
void BHeap<Type>::regulate_heap_properties() {
    if (heap.size() <= 1)
        return;
    typename list<Node*>::iterator it1, it2, it3;
    it1 = it2 = it3 = heap.begin();
    // 1-ая ситуация: получились в куче два дерева одинаковой степени (после слияния 'merge_heap')
    // heap.node.degree == heap.node.next.degree вот такая ситуация --> (2)-->(2)-->(4)-->(8)
    // и при этом h.node.key <= h.node.next.key  т.е ключ текущего дерева меньше ключа следующего дерева
    // 2-я ситуация: тоже что и в первом случае (2)-->(2)-->(4)-->(8), но только key > next.key
    // 3-я ситуация: получилось 3 подряд одинаковых степеней вложенности (2)-->(2)-->(2)-->(4)-->(8)
    // 4-я ситуация: heap.degree != heap.next.degree и heap.key < heap.next.key
    if (heap.size() == 2) {
        it2 = it1;
        it2++;
        it3 = heap.end();
    }
    else {
        it2++;
        it3 = it2;
        it3++;
    }
    while (it1 != heap.end()) {
        if (it2 == heap.end())
            it1++;
        else if ((*it1)->degree < (*it2)->degree) {
            it1++;
            it2++;
            if (it3 != heap.end())
                it3++;
        }
        else if (it3 != heap.end() &&
            (*it1)->degree == (*it2)->degree &&
            (*it1)->degree == (*it3)->degree) {
            it1++;
            it2++;
            it3++;
        }
        else if ((*it1)->degree == (*it2)->degree) {
            *it1 = linking_links(*it1, *it2);
            it2 = heap.erase(it2);
            if (it3 != heap.end())
                it3++;
        }
    }
}

template <typename Type>
void BHeap<Type>::insert(const int64_t& key, const Type& val) {
    Node* new_node = new Node(key, val);
    list<Node*> temp;
    temp.push_back(new_node);
    heap = union_heap(heap, temp);
    regulate_heap_properties();
}

template <typename Type>
list<typename BHeap<Type>::Node*> BHeap<Type>::remove_min(Node *tree) {
    list<Node*> hp;
    Node* temp = tree->child;
    Node* subl;
    while (temp) {
        subl = temp;
        temp = temp->sibling;
        subl->sibling = nullptr;
        hp.push_front(subl);
    }
    return hp;
}

template <typename Type>
typename BHeap<Type>::Node* BHeap<Type>::_get_min() {
    typename list<Node*>::iterator it = heap.begin();
    Node* temp = *it;
    while (it != heap.end()) {
        if ((*it)->data < temp->data)
            temp = *it;
        it++;
    }
    return temp;
}

template <typename Type>
typename BHeap<Type>::Node* BHeap<Type>::find_node(Node* it, const int64_t& val) {
    if (it == nullptr)
        return nullptr;
    if (it->data == val)
        return it;
    Node* res = find_node(it->child, val);
    if (res != nullptr)
        return res;
    return find_node(it->sibling, val);
}

template <typename Type>
void BHeap<Type>::_show(Node *h) {
    while (h) {
        cout << '(' << h->data << ":" << h->value << ") ";
        _show(h->child);
        h = h->sibling;
    }
}

template <typename Type>
void BHeap<Type>::print_heap() {
    typename list<Node*>::iterator it;
    it = heap.begin();
    cout << "Key : Val --> ";
    while (it != heap.end()) {
        _show(*it);
        it++;
    }
    cout << "\n";
}
  
template <typename Type>
void BHeap<Type>::decrease_key(const int64_t& old, const int64_t& nevv) {
    typename list<Node*>::iterator it = heap.begin();
    Node* node = nullptr;
    while (it != heap.end() && node == nullptr) {
        node = find_node(*it, old);
        it++;
    }
    if (node == nullptr)
        return;
    node->data = nevv;
    Node* parent = node->parent;
    while (parent != NULL && node->data < parent->data) {
        swap(node->data, parent->data);
        node = parent;
        parent = parent->parent;
    }
}

template <typename Type>
void BHeap<Type>::extract_min() {
    list<Node*> new_hp, res;
    Node* temp;
    temp = _get_min();
    typename  list<Node*>::iterator it;
    it = heap.begin();
    while (it != heap.end()) {
        if (*it != temp) {
            new_hp.push_back(*it);
        }
        it++;
    }
    res = remove_min(temp);
    heap = union_heap(new_hp, res);
    regulate_heap_properties();
}



int main() {
    BHeap<char> heap;
    for (int64_t i = 0; i < 10; ++i) 
        heap.insert(i, char(i + 65));
    heap.print_heap();
    cout << "Extract min:\n";
    heap.extract_min();
    heap.extract_min();
    heap.extract_min();
    heap.print_heap();
    cout << "Min key: " << heap.get_min() << '\n';
    cout << "Function decrase_key:\n";
    heap.decrease_key(8, 100);
    heap.decrease_key(5, 25);
    heap.print_heap();
    return 0;
}