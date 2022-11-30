# Биномиальная куча - binomial heap #
# Множество биномиальных деревьев, которые удовлетворяют следующим свойствам:
# 1). Каждое биномиальное дерево в куче подчиняется свойству неубывающей кучи:
# ключ узла не меньше ключа его родительского узла (упорядоченное в соответствии со свойством неубывающей кучи дерево).
# 2). Для любого неотрицательного целого k найдется не более одного биномиального дерева, чей корень имеет степень k.

class Node: pass                                # Класс описывающий 1 узел биномиального дерева
class BHeap:                                    # Класс описывающий биномиальную кучу
    def __init__(self): pass                    # Конструктор
    def _union_heap(self, heap1, heap2): pass   # Объединяет в один список корни биномиальных деревьев
    def _linking_links(self, child, par): pass  # Связывание ссылок деревьев
    def _regulate_heap_properties(self):pass    # Регулирование свойств кучи (поддержание упорядоченности)
    def _find_node(self, node, val): pass       # Поиск по ключу (возвращает указатель на узел)
    def _show(self, node): pass                 # Служебная функция обхода кучи, для печати
    def _get_min(self): pass                    # Служебная функция - получить минимальный ключ в куче
    def _remove_min(self, tree): pass           # Удаление минимального ключа и возврат нового списка корней
    def get_min(self): pass                     # Получить минимальный ключ в куче
    def insert(self, key, value): pass          # Вставить key - value в кучу
    def decrease_key(self, old, new): pass      # Уменьшает ключ, присваивая ему новое значение
    def extract_min(self): pass                 # Извлекает (удаляет) узел с минимальным ключом из биномиальной кучи
    def print_heap(self): pass                  # Печать кучи
    def delete_key(self, key): pass             # Удалить ключ
"""-----------------------------------------------------------------------------------------------------------"""

class Node:
    def __init__(self, key, value):
        self._key = key                 # Ключи
        self._value = value             # Значения
        self._degree = 0                #   (6)                   // Степень вложенности, кол-во дочерних ухлов
        self._parent = None             #    |                    // Указатель на родителя
        self._sibling = None            #   (4)-->(3)-->(key)     // Указатель на правый соседний узел
        self._child = None              #   /     /               // Указатель на крайнего левого потомка
                                        # (1)   (key)

class BHeap:
    def __init__(self):
        self._heap = []             # Упорядоченные по degree корни биномиальных деревьев вида head-->(1)-->(4)-->(9)

    def _union_heap(self, heap1, heap2):
        new_list_root = []                              # Список новых корней биномиальных деревьев
        it1 = 0                                         # Итератор на 1ую кучу (список биномиальных корней)
        it2 = 0                                         # Итератор на 2-ую
        while it1 < len(heap1) and it2 < len(heap2):    #
            if heap1[it1]._degree <= heap2[it2]._degree:
                new_list_root.append(heap1[it1])
                it1 += 1
            else:
                new_list_root.append(heap2[it2])
                it2 += 1
        while it1 < len(heap1):
            new_list_root.append(heap1[it1])
            it1 += 1
        while it2 < len(heap2):
            new_list_root.append(heap2[it2])
            it2 += 1
        return new_list_root

    def _linking_links(self, child, parent):
        if child._key > parent._key:
            child, parent = parent, child
        parent._parent = child
        parent._sibling = child._child
        child._child = parent
        child._degree += 1
        return child

    def _regulate_heap_properties(self):
        if len(self._heap) <= 1:
            return
        id1 = 0
        id2 = 0
        id3 = 0
        if len(self._heap) == 2:
            id2 += 1
            id3 = len(self._heap)
        else:
            id2 += 1
            id3 += 2
        while id1 < len(self._heap):
            if id2 == len(self._heap):
                id1 += 1
            elif self._heap[id1]._degree <= self._heap[id2]._degree:
                id1 += 1
                id2 += 1
                if id3 < len(self._heap):
                    id3 += 1
            elif (id3 < len(self._heap)) and \
                (self._heap[id1]._degree == self._heap[id2]._degree) and \
                (self._heap[id1]._degree == self._heap[id3]._degree):
                id1 += 1
                id2 += 1
                id3 += 1
            elif self._heap[id1]._degree == self._heap[id2]._degree:
                self._heap[id1] = self._linking_links(self._heap[id1], self._heap[id2])
                self._heap.remove(self._heap[id2])
                if id3 != len(self._heap):
                    id3 += 1

    def _find_node(self, node, val):
        if node is None:
            return None
        if node._key == val:
            return node
        res = self._find_node(node._child, val)
        if res is not None:
            return res
        return self._find_node(node._sibling, val)

    def _remove_min(self, tree):
        hp = []
        tmp = tree._child
        while tmp:
            sub = tmp
            tmp = tmp._sibling
            sub._sibling = None
            hp.append(sub)
        return hp

    def _show(self, node):
        while node:
            print(f"({node._key}:{node._value})", end=' ')
            self._show(node._child)
            node = node._sibling

    def _get_min(self):
        it = 0
        tmp = self._heap[0]
        while it != len(self._heap):
            if self._heap[it]._key < tmp._key:
                tmp = self._heap[it]
            it += 1
        return tmp

    def get_min(self):
        res = self._get_min()
        return res._key if res is not None else None

    def insert(self, key, value):
        new_node = Node(key, value)
        temp = []
        temp.append(new_node)
        self._heap = self._union_heap(self._heap, temp)
        self._regulate_heap_properties()

    def decrease_key(self, old, new):
        it = 0
        node = None
        while it < len(self._heap) and node is None:
            node = self._find_node(self._heap[it], old)
            #print(f"node == {node}")
            it += 1
        if node is None:
            return
        node._key = new
        parent = node._parent
        while parent != None and node._key < parent._key:
            node._key, parent._key = parent._key, node._key
            node = parent
            parent = parent._parent

    def extract_min(self):
        new_heap = []
        tmp = self._get_min()
        it = 0
        while it != len(self._heap):
            if self._heap[it] != tmp:
                new_heap.append(self._heap[it])
            it += 1
        res = self._remove_min(tmp)
        self._heap = self._union_heap(new_heap, res)
        self._regulate_heap_properties()

    def print_heap(self):
        it = 0
        while it != len(self._heap):
            self._show(self._heap[it])
            it += 1

    def delete_key(self, key):
        INT_MIN = -2147483648
        self.decrease_key(key, INT_MIN)    # Понизить приоритет удаляемого узла до минимума
        self.extract_min()                 # Удалить минимум, т.е узел


def main():
    hp = BHeap()
    for i in range(10):
        hp.insert(i, chr(i+65))
    hp.print_heap()
    print("\nRes job function extract_min():")
    hp.extract_min()
    hp.extract_min()
    hp.extract_min()
    hp.print_heap()
    print(f"\nMin key = {hp.get_min()}")
    print("Function decrease key:")
    hp.decrease_key(3, 999)
    hp.decrease_key(7, 666)
    hp.print_heap()
    print("\nDelete key 999 and 4:")
    hp.delete_key(999)
    hp.delete_key(4)
    hp.print_heap()


if __name__ == "__main__":
    main()