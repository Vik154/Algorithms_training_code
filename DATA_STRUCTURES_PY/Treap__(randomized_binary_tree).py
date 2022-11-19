"""Декартово дерево - Treap"""
import random

class Node: pass                            # Класс описывающий узел дерева
class Treap:                                # Класс описывающий дерево
    def __init__(self): pass                # Конструктор
    def _left_rotate(self, x): pass         # Вращение влево
    def _right_rotate(self, x): pass        # Вращение вправо
    def _travel_up(self, x): pass           # Обход приоритетов по родителям
    def _travel_down(self, x): pass         # Обход приоритетов по потомкам
    def _delete_key(self, node, elm): pass  # Удаление элемента
    def _min_key(self, node): pass          # Наименьший элемент в дереве
    def _max_key(self, node): pass          # Наибольший элемент в дереве
    def _print_inord(self, node): pass      # Инфиксный обход
    def _pretty_print(self, node, st, last): pass   # Печать (представление дерева)
    def insert(self, key, prior): pass              # Вставка элемента
    def split(self, dummy, tree1, tree2): pass      # Разделение дерева по заданному ключу
    def merge(self, tree1, tree2): pass             # Слияние двух деревьев в одно
    def erase(self, elm): pass              # Удаление элемента
    def min_key(self): pass                 # Минимальный элемент в дереве
    def max_key(self): pass                 # Максимальный элемент в дереве
    def inorder_rec(self): pass             # Инфиксный обход
    def pretty_print(self): pass            # Представление дерева
"""-----------------------------------------------------------------------------------------"""

class Node:
    def __init__(self, data, prior):
        self._data = data
        self._priority = prior
        self._parent = None
        self._right = None
        self._left = None


class Treap:
    def __init__(self):
        self._root = None

    def _left_rotate(self, x):
        y = x._right
        x._right = y._left
        if y._left != None:
            y._left._parent = x
        y._parent = x._parent
        if x._parent == None:
            self._root = y
        elif x == x._parent._left:
            x._parent._left = y
        else:
            x._parent._right = y
        y._left = x
        x._parent = y

    def _right_rotate(self, x):
        y = x._left
        x._left = y._right
        if y._right != None:
            y._right._parent = x
        y._parent = x._parent
        if x._parent == None:
            self._root = y
        elif x == x._parent._right:
            x._parent._right = y
        else:
            x._parent._left = y
        y._right = x
        x._parent = y

    def _travel_up(self, x):
        if x._parent == None:
            return
        if x._parent != None and x._priority >= x._parent._priority:
            return
        if x == x._parent._left:
            self._right_rotate(x._parent)
        else:
            self._left_rotate(x._parent)
        self._travel_up(x)

    def _travel_down(self, x):
        if x._left == None and x._right == None:
            return
        if x._left != None and x._right != None:
            if x._left._priority < x._right._priority:
                self._right_rotate(x)
            else:
                self._left_rotate(x)
        elif x._left != None:
            self._right_rotate(x)
        else:
            self._left_rotate(x)
        self._travel_down(x)

    def _delete_key(self, node, elm):
        x = None
        while node != None:
            if node._data == elm:
                x = node
                break
            if node._data <= elm:
                node = node._right
            else:
                node = node._left
        if x == None:
            #print("Такого элемента нет в дереве")
            return
        self._travel_down(x)
        if x == x._parent._left:
            x._parent._left = None
        else:
            x._parent._right = None
        x._data = None
        x._priority = None
        x._left = None
        x._right = None
        x._parent = None

    def _min_key(self, node):
        while node._left != None:
            node = node._left
        return node

    def _max_key(self, node):
        while node._right != None:
            node = node._right
        return node

    def _print_inord(self, node):
        if node != None:
            self._print_inord(node._left)
            print(f"{node._data}(p{node._priority})", end=' ')
            self._print_inord(node._right)

    def _pretty_print(self, node, st, last):
        if node != None:
            print(st, end='')
            if last:
                print("R----", end='')
                st += "     "
            else:
                print("L----", end='')
                st += "|    "
            print(str(node._data) + "(" + str(node._priority) + ")")
            self._pretty_print(node._left, st, False)
            self._pretty_print(node._right, st, True)

    def insert(self, key, prior):
        node = Node(key, prior)
        y = None
        x = self._root
        while x != None:
            y = x
            if node._data < x._data:
                x = x._left
            else:
                x = x._right
        node._parent = y
        if y == None:
            self._root = node
        elif node._data < y._data:
            y._left = node
        else:
            y._right = node
        if node._parent != None:
            self._travel_up(node)

    def split(self, dummy, tree1, tree2):
        self.insert(dummy, -99)
        tree1._root = self._root._left
        tree2._root = self._root._right

        self._root._left = None
        self._root._right = None
        self._root = None

    def merge(self, tree1, tree2):
        largest = tree1._max_key(tree1._root)
        smallest = tree2._max_key(tree2._root)

        data = largest._data if largest._data >= smallest._data else smallest._data
        new_root = Node(data, 99)
        new_root._left = tree1._root
        new_root._right = tree2._root

        self._travel_down(new_root)
        curr = new_root
        while curr._parent != None:
            curr = curr._parent
        self._root = curr

        if new_root == new_root._parent._left:
            new_root._parent._left = None
        else:
            new_root._parent._right = None
        new_root = None

    def min_key(self):
        return self._min_key(self._root)._data

    def max_key(self):
        return self._max_key(self._root)._data

    def show(self):
        if self._root:
            self._print_inord(self._root)
            print(end='\n')
        else:
            print("BST is empty")

    def pretty_print(self):
        if self._root:
            self._pretty_print(self._root, "", True)

    def erase(self, elm):
        self._delete_key(self._root, elm)


def main(size):
    tree = Treap()
    for _ in range(size):
        tree.insert(random.randint(0, 100), random.randint(0, 10))
    tree.show()
    print("======================================================")
    tr1 = Treap()
    tr2 = Treap()
    tree.split(50, tr1, tr2)
    tr1.pretty_print()
    tr2.pretty_print()
    print("======================================================")
    tree.merge(tr1, tr2)
    tree.pretty_print()
    print("======================================================")
    tree.show()
    for _ in range(size * 3):
        tree.erase(random.randint(0, 100))
    tree.show()


if __name__ == "__main__":
    main(20)