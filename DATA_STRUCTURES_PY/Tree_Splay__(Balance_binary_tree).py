"""Splay tree - Расширяющееся (косое) самобалансирующиеся двоичное дерево поиска"""

class Node: pass                                # Класс описывающий узлы вставляемые в дерево
class Splay_tree:                               # Расширяющееся самобалансирующееся дерево
    def __init__(self, data=None): pass         # Конструктор с параметром и без
    def _left_rotate(self, x): pass             # Разворот поддерева с корнем x влево
    def _right_rotate(self, x): pass            # Разворот поддерева с корнем x вправо
    def _splay(self, x): pass                   # Поднимет ключ в корень, если он присутствует в дереве, иначе поднимет
    # в корень самый последний элемент к которому был осуществлен доступ и возвращает новый корень.
    def _replace(self, u, v): pass              # Замена вершин для функции erase, для удаления по ключу
    def _subtree_min(self, node): pass          # Наименьший элемент дерева
    def _subtree_max(self, node): pass          # Наибольший элемент
    def _find(self, key): pass                  # Поиск элемента по ключу (Служебная функция)
    def insert(self, key): pass                 # Вставка элемента в дерево
    def erase(self, key): pass                  # Удаление по значению
    def _print_inord(self, node): pass          # Инфиксный обход
    def print_inord(self): pass                 # Печать
    def _print_preord(self, node): pass         # Префиксный обход
    def print_preord(self): pass                # Печать
    def _print_postord(self, node):pass         # Постфиксный обход
    def print_postord(self): pass               # Печать
    def successor(self, key): pass              # Потомок
    def predecessor(self, key): pass            # Предок
    def min_key(self): pass                     # Наименьшее значение в дереве
    def max_key(self): pass                     # Наибольшее
    def find(self, key): pass                   # Поиск по ключу
    def size(self): pass                        # Кол-во элементов
"""-----------------------------------------------------------------------------"""

class Node(object):
    def __init__(self, data):
        self._data = data
        self._left = None
        self._right = None
        self._parent = None


class Splay_tree:
    def __init__(self, data=None):
        if data is None:
            self._root = None
            self._count = 0
        else:
            node = Node(data)
            self._root = node
            self._count = 1

    def _left_rotate(self, x):                # Разворот поддерева с корнем n влево
        y = x._right
        if y:
            x._right = y._left
            if y._left:
                y._left._parent = x
            y._parent = x._parent
        if x._parent is None:
            self._root = y
        elif x == x._parent._left:
            x._parent._left = y
        else:
            x._parent._right = y
        if y:
            y._left = x
        x._parent = y

    def _right_rotate(self, x):
        y = x._left
        if y:
            x._left = y._right
            if y._right:
                y._right._parent = x
            y._parent = x._parent
        if x._parent is None:
            self._root = y
        elif x == x._parent._left:
            x._parent._left = y
        else:
            x._parent._right = y
        if y:
            y._right = x
        x._parent = y

    def _splay(self, x):
        while x._parent:
            if x._parent._parent is None:
                if x._parent._left == x:
                    self._right_rotate(x._parent)
                else:
                    self._left_rotate(x._parent)
            elif x._parent._left == x and x._parent._parent._left == x._parent:
                self._right_rotate(x._parent._parent)
                self._right_rotate(x._parent)
            elif x._parent._right == x and x._parent._parent._right == x._parent:
                self._left_rotate(x._parent._parent)
                self._left_rotate(x._parent)
            elif x._parent._left == x and x._parent._parent._right == x._parent:
                self._right_rotate(x._parent)
                self._left_rotate(x._parent)
            else:
                self._left_rotate(x._parent)
                self._right_rotate(x._parent)

    def _replace(self, u, v):
        if u._parent is None:
            self._root = v
        elif u == u._parent._left:
            u._parent._left = v
        else:
            u._parent._right = v
        if v:
            v._parent = u._parent

    @staticmethod
    def _subtree_min(node):
        while node._left:
            node = node._left
        return node

    @staticmethod
    def _subtree_max(node):
        while node._right:
            node = node._right
        return node

    def _find(self, key):
        curr = self._root
        while curr:
            if curr._data < key:
                curr = curr._right
            elif curr._data > key:
                curr = curr._left
            else:
                return curr
        return None

    def insert(self, key):
        z = self._root
        p = None
        while z:
            p = z
            if key > z._data:
                z = z._right
            else:
                z = z._left
        z = Node(key)
        z._parent = p

        if p is None:
            self._root = z
        elif p._data < z._data:
            p._right = z
        else:
            p._left = z
        self._splay(z)
        self._count += 1

    def erase(self, key):
        z = self._find(key)
        if z is None:
            return
        self._splay(z)
        if z._left is None:
            self._replace(z, z._right)
        elif z._right is None:
            self._replace(z, z._right)
        else:
            y = self._subtree_min(z._right)
            if y._parent != z:
                self._replace(y, y._right)
                y._right = z._right
                y._right._parent = y
            self._replace(z, y)
            y._left = z._left
            y._left._parent = y
        z = None
        self._count -= 1

    def _print_inord(self, node):
        if node:
            self._print_inord(node._left)
            print(node._data, end=' ')
            self._print_inord(node._right)

    def print_inord(self):
        if self._root:
            self._print_inord(self._root)
            print(end='\n')
        else:
            print("BST is empty")

    def _print_preord(self, node):
        if node:
            print(node._data, end=' ')
            self._print_inord(node._left)
            self._print_inord(node._right)

    def print_preord(self):
        if self._count:
            self._print_preord(self._root)
            print(end='\n')
        else:
            print("BST is empty")

    def _print_postord(self, node):
        if node:
            self._print_inord(node._left)
            self._print_inord(node._right)
            print(node._data, end=' ')

    def print_postord(self):
        if self._count:
            self._print_postord(self._root)
            print(end='\n')
        else:
            print("BST is empty")

    def successor(self, key):
        curr = self._root
        succ = None
        while curr:
            if curr._data > key:
                succ = curr
                curr = curr._left
            else:
                curr = curr._right
        return succ._data if succ else None

    def predecessor(self, key):
        curr = self._root
        succ = None
        while curr:
            if curr._data < key:
                succ = curr
                curr = curr._right
            else:
                curr = curr._left
        return succ._data if succ else None

    def min_key(self):
        return self._subtree_min(self._root)._data

    def max_key(self):
        return self._subtree_max(self._root)._data

    def find(self, key):
        return self._find(key) != None

    def size(self):
        return self._count


def main():
    stree = Splay_tree(10)
    for i in range(20):
        stree.insert(i)
    print("In order\t", end='')
    stree.print_inord()
    print("Pre order\t", end='')
    stree.print_preord()
    print("Post order\t", end='')
    stree.print_postord()
    print(f"Max key == {stree.max_key()}")
    print(f"Min key == {stree.min_key()}")
    print(f"Succ 10 == {stree.successor(10)}")
    print(f"Pred 10 == {stree.predecessor(10)}")
    print(f"Size tree: {stree.size()}")


if __name__ == "__main__":
    main()