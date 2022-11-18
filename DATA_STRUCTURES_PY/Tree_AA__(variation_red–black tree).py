"""/*-АА-Дерево - сбалансированное двоичное дерево поиска,
разновидность красно-черного дерева с доп.ограничениями - AA_Tree-*/
/*Реализация большинства схожих методов есть в Red-Black Tree (RB_tree)*/"""
import random

class Node: pass                            # Класс описывающий узел дерева
class AATree:                               # Класс описывающий дерево
    def __init__(self): pass                # Конструктор
    def _skew(self, node): pass             # Устранение левого горизонтального ребра. Правое вращение
    def _split(self, node): pass            # Устранение двух последовательных правых горизонтальных ребер. Левое вращение
    def _search(self, key): pass            # Поиск элемента
    def _balance(self, node): pass          # Балансировка
    def _swap(self, a, b): pass             # Обмен значений
    def _increase_level(self, node): pass   # Повышение уровня элемента
    def _delete(self, node): pass           # Удаление элемента служебная функция
    def erase(self, value): pass            # Удаление элемента
    def insert(self, value): pass           # Добавление элемента
    def search(self, key): pass             # Поиск
    def _print_inord(self, node): pass      # Прямой обход
    def show(self): pass                    # Вывод на экран
"""------------------------------------------------------------"""

class Node:
    def __init__(self, data, level):
        self._left = None
        self._right = None
        self._parent = None
        self._data = data
        self._level = level


class AATree:
    def __init__(self):
        self._root = None

    def _skew(self, node):
        if node._left != None:
            if node._left._level == node._level:
                curr = node._left
                node._left = curr._right
                if curr._right != None:
                    node._left._parent = node
                curr._right = node
                curr._parent = node._parent
                node._parent = curr
                if curr._parent != None:
                    if curr._parent._left == node:
                        curr._parent._left = curr
                    else:
                        curr._parent._right = curr
                return curr
        return node

    def _split(self, node):
        if node._right != None and node._right._right != None:
            if node._level == node._right._right._level:
                curr = node._right
                node._right = curr._left
                if node._right != None:
                    node._right._parent = node
                curr._left = node
                curr._parent = node._parent
                node._parent = curr
                if curr._parent != None:
                    if curr._parent._left == node:
                        curr._parent._left = curr
                    else:
                        curr._parent._right = curr
                curr._level += 1
                return curr
        return node

    def _search(self, key):
        curr = self._root
        while True:
            if key == curr._data:
                return curr
            elif key > curr._data:
                if curr._right == None:
                    return None
                else:
                    curr = curr._right
            elif key < curr._data:
                if curr._left == None:
                    return None
                else:
                    curr = curr._left

    def _balance(self, node):
        while node._parent != None:
            node = node._parent
            if node == self._root:
                node = self._skew(node)
                node = self._split(node)
                self._root = node
            else:
                node = self._skew(node)
                node = self._split(node)

    def _swap(self, a, b):
        tmp = a._data
        a._data = b._data
        b._data = tmp

    def _increase_level(self, node):
        if node != None:
            self._increase_level(node._left)
            self._increase_level(node._right)
            node._level += 1
            self._balance(node)

    def _delete(self, node):
        if node._left == None and node._right == None:
            tmp = node._parent
            if tmp._left == node:
                tmp._left = None
            else:
                tmp._right = None
            node._left = None
            node._right = None
            node._data = None

        elif node._left == None and node._right != None:
            if self._root != node:
                tmp = node._parent
                if tmp._left == node:
                    tmp._left = node._right
                else:
                    tmp._right = node._right
                node._right._parent = tmp
                self._increase_level(node._parent._left)
                self._increase_level(node._parent._right)
                self._balance(node._parent)
            else:
                self._root = node._right
                node._right._parent = None
            node._left = None
            node._right = None
            node._data = None

    def erase(self, value):
        curr = self._search(value)
        if curr._left == None and curr._right == None:
            if self._root != curr:
                tmp = curr._parent
                if tmp._left == curr:
                    tmp._left = None
                else:
                    tmp._right = None
            else:
                self._root = None
            curr._data = None
            curr._left = None
            curr._right = None

        elif curr._left == None and curr._right != None:
            if self._root != curr:
                tmp = curr._parent
                if tmp._left == curr:
                    tmp._left = curr._right
                else:
                    tmp._right = curr._right
                curr._right._parent = tmp
                self._increase_level(curr._parent._left)
                self._increase_level(curr._parent._right)
                self._balance(curr._parent)
            else:
                self._root = curr._right
                curr._right._parent = None
            curr._data = None
            curr._left = None
            curr._right = None

        elif curr._left != None and curr._right == None:
            if self._root != curr:
                tmp = curr._parent
                if tmp._left == curr:
                    tmp._left = curr._left
                else:
                    tmp._right = curr._left
                curr._left._parent = tmp
                self._increase_level(curr._parent._left)
                self._increase_level(curr._parent._right)
                self._balance(curr._parent)
            else:
                self._root = curr._left
                curr._right._parent = None
            curr._data = None
            curr._left = None
            curr._right = None

        else:
            node = curr._right
            while node._left != None:
                node = node._left
            self._swap(node, curr)
            self._delete(curr)

    def insert(self, value):
        node = Node(value, 1)
        if self._root == None:
            self._root = node
            return
        curr = self._root
        is_set = False
        while is_set is False:
            if value >= curr._data:
                if curr._right == None:
                    curr._right = node
                    node._parent = curr
                    self._balance(curr._right)
                    is_set = True
                else:
                    curr = curr._right
            if value < curr._data:
                if curr._left == None:
                    curr._left = node
                    node._parent = curr
                    self._balance(curr._left)
                    is_set = True
                else:
                    curr = curr._left

    def search(self, key):
        return self._search(key) != None

    def _print_inord(self, node):
        if node != None:
            self._print_inord(node._left)
            print(node._data, end=' ')
            self._print_inord(node._right)

    def show(self):
        if self._root:
            self._print_inord(self._root)
            print(end='\n')
        else:
            print("BST is empty")


def main(size):
    tree = AATree()
    for i in range(size):
        tree.insert(random.randint(0, 100))
    tree.show()


if __name__ == "__main__":
    main(20)