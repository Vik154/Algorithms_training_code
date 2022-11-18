"""Красно-черное дерево - Red-Black tree"""
import random

class Node: pass                                    # Класс описывающий узел дерева
class RB_tree:                                      # Класс описывающий красно-черное дерево
    def __init__(self, data=None): pass             # Конструктор с параметром и без
    def _left_rotate(self, x): pass                 # Вращение влево
    def _right_rotate(self, x): pass                # Вращение вправо
    def _fix_insert(self, x): pass                  # Корректировка цветов при добавлении ключей, поддержание сбалансированности
    def _fix_delete(self, x): pass                  # Корректировка цветов при удалении элемента, поддержание сбалансированности
    def _swap(self, x, y): pass                     # Служебная функция для замены элемента
    def _delete_key(self, node, key): pass          # Служебная функция для удаления элемента
    def _min_iter(self, node): pass                 # Наименьший элемент в дереве  <-- Итеративный поиск
    def _max_iter(self, node): pass                 # Наибольший элемент в дереве  <-- Итеративный поиск
    def _min_rec(self, node): pass                  # Наименьший элемент в дереве  <-- Рекурсивный поиск
    def _max_rec(self, node): pass                  # Наибольший элемент в дереве  <-- Рекурсивный поиск
    def _search_rec(self, node, key): pass          # Рекурсивный поиск элемента по значению
    def _search_iter(self, node, key): pass         # Итеративный поиск элемента по значению
    def _successor(self, node): pass                # Приемник переданного ключа, т.е следующий больший ключ
    def _predecessor(self, node): pass              # Предшественник переданного ключа, т.е. ближайший наименьший по отношению к переданному
    def _print_inord(self, node): pass              # Инфиксный обход		<-- Рекурсивный вариант
    def _print_preord(self, node): pass             # Префиксный обход		<-- Рекурсивный вариант
    def _print_postord(self, node): pass            # Постфиксный обход	<-- Рекурсивный вариант
    def _destroy(self, node): pass                  # Удаление дерева
    def _depth(self, node): pass                    # Глубина дерева, возвращает размер самой длинной ветки
    def _size(self, node): pass                     # Рекурсивный подсчёт кол-ва элементов в дереве
    def _pretty_print(self, node, st, last): pass   # Аккуратная печать (представление дерева)
    def clear(self): pass                           # Очистка дерева
    def empty(self): pass                           # Есть ли элементы в дереве
    def search(self, key): pass                     # Поиск по ключу
    def insert(self, key): pass                     # Добавление элемента (ключа)
    def erase(self, key): pass                      # Удаление по значению
    def get_root(self): pass                        # Значение в корне
    def min_key(self): pass                         # Минимальный элемент в дереве
    def max_key(self): pass                         # Максимальный элемент в дереве
    def successor(self, key): pass                  # Приемник (самый ближний наибольший элемент относительно переданного)
    def predecessor(self, key): pass                # Предшественник (самый ближний наименьший элемент от переданного)
    def depth(self): pass                           # Глубина дерева с учетом фиктивных nil листов (черная высота)
    def size(self): pass                            # Кол-во элементов в дереве, рекурсивное вычисление
    def inorder_iter(self): pass                    # Инфиксный обход		<-- Итеративный вариант
    def preorder_iter(self): pass                   # Префиксный обход		<-- Итеративный вариант
    def postorder_iter(self): pass                  # Постфиксный обход	    <-- Итеративный вариант
    def inorder_rec(self): pass                     # Инфиксный обход		<-- Рекурсивный вариант
    def preorder_rec(self): pass                    # Префиксный обход		<-- Рекурсивный вариант
    def postorder_rec(self): pass                   # Постфиксный обход	    <-- Рекурсивный вариант
    def pretty_print(self): pass                    # Представление дерева
"""---------------------------------------------------------------------------"""


class Node:                                     # Класс описывающий узел дерева
    def __init__(self, data, color='red'):      # Конструктор узла
        self._left = None                       # Левый потомок
        self._right = None                      # Правый потомок
        self._parent = None                     # Родитель
        self._data = data                       # Данные (ключ)
        self._color = color                     # Цвет листа, по правилу всегда добавляется красный


class RB_tree:                                  # Класс описывающий красно-черное дерево
    def __init__(self, data=None):              # Конструктор с параметром и без
        self._nil = Node(None, 'black')         # При создании экземпляра создается фиктивная вершина - черная
        if data == None:                        # Если создается дерево без параметра
            self._root = self._nil              # Указатель на корень дерева
        else:
            self._root = Node(data, 'black')    # Создается вершина черная - которая будет пока что корнем

    def _left_rotate(self, x):
        y = x._right
        x._right = y._left
        if y._left != self._nil:
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
        if y._right != self._nil:
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

    def _fix_insert(self, x):
        while x._parent._color == 'red':
            if x._parent == x._parent._parent._right:
                tmp = x._parent._parent._left
                if tmp._color == 'red':
                    tmp._color = 'black'
                    x._parent._color = 'black'
                    x._parent._parent._color = 'red'
                    x = x._parent._parent
                else:
                    if x == x._parent._left:
                        x = x._parent
                        self._right_rotate(x)
                    x._parent._color = 'black'
                    x._parent._parent._color = 'red'
                    self._left_rotate(x._parent._parent)
            else:
                tmp = x._parent._parent._right
                if tmp._color == 'red':
                    tmp._color = 'black'
                    x._parent._color = 'black'
                    x._parent._parent._color = 'red'
                    x = x._parent._parent
                else:
                    if x == x._parent._right:
                        x = x._parent
                        self._left_rotate(x)
                    x._parent._color = 'black'
                    x._parent._parent._color = 'red'
                    self._right_rotate(x._parent._parent)
            if x == self._root:
                break
        self._root._color = 'black'

    def _fix_delete(self, x):
        while x != self._root and x._color == 'black':
            if x == x._parent._left:
                s = x._parent._right
                if s._color == 'red':
                    s._color = 'black'
                    x._parent._color = 'red'
                    self._left_rotate(x._parent)
                    s = x._parent._right

                if s._left._color == 'black' and s._right._color == 'black':
                    s._color = 'red'
                    x = x._parent
                else:
                    if s._right._color == 'black':
                        s._left._color = 'black'
                        s._color = 'red'
                        self._right_rotate(s)
                        s = x._parent._right

                    s._color = x._parent._color
                    x._parent._color = 'black'
                    s._right._color = 'black'
                    self._left_rotate(x._parent)
                    x = self._root
            else:
                s = x._parent._left
                if s._color == 'red':
                    s._color = 'black'
                    x._parent._color = 'red'
                    self._right_rotate(x._parent)
                    s = x._parent._left

                if s._left._color == 'black' and s._right._color == 'black':
                    s._color = 'red'
                    x = x._parent
                else:
                    if s._left._color == 'black':
                        s._right._color = 'black'
                        s._color = 'red'
                        self._left_rotate(s)
                        s = x._parent._left

                    s._color = x._parent._color
                    x._parent._color = 'black'
                    s._left._color = 'black'
                    self._right_rotate(x._parent)
                    x = self._root
        x._color = 'black'

    def _swap(self, x, y):
        if x._parent == None:
            self._root = y
        elif x == x._parent._left:
            x._parent._left = y
        else:
            x._parent._right = y
        y._parent = x._parent

    def _delete_key(self, node, key):
        z = self._nil
        while node != self._nil:
            if node._data == key:
                z = node
            if node._data <= key:
                node = node._right
            else:
                node = node._left

        if z == self._nil:
            return

        y = z
        original_color = y._color
        if z._left == self._nil:
            x = z._right
            self._swap(z, z._right)
        elif z._right == self._nil:
            x = z._left
            self._swap(z, z._left)
        else:
            y = self._min_iter(z._right)
            original_color = y._color
            x = y._right
            if y._parent == z:
                x._parent = y
            else:
                self._swap(y, y._right)
                y._right = z._right
                y._right._parent = y

            self._swap(z, y)
            y._left = z._left
            y._left._parent = y
            y._color = z._color
        if original_color == 'black':
            self._fix_delete(x)

    def _min_iter(self, node):
        while node._left != self._nil:
            node = node._left
        return node

    def _max_iter(self, node):
        while node._right != self._nil:
            node = node._right
        return node

    def _min_rec(self, node):
        if node == self._nil or node == None:
            return None
        if node._left == self._nil or node._left == None:
            return node
        else:
            return self._min_rec(node._left)

    def _max_rec(self, node):
        if node == self._nil or node == None:
            return None
        if node._right == self._nil or node._right == None:
            return node
        else:
            return self._max_rec(node._right)

    def _search_rec(self, node, key):
        if key == node._data:
            return node
        if node == self._nil or node == None:
            return None
        if key < node._data:
            return self._search_rec(node._left, key)
        if key > node._data:
            return self._search_rec(node._right, key)

    def _search_iter(self, node, key):
        tmp = node
        while tmp._data is not None:
            if key > tmp._data:
                tmp = tmp._right
            elif key < tmp._data:
                tmp = tmp._left
                #print(tmp._data)
            else:
                #print(tmp)
                return tmp
        return None

    def _successor(self, node):
        if node._right != self._nil:
            return self._min_iter(node._right)
        if node._data == self.max_key():
            print("Данный ключ наибольший в дереве у него нет приемника")
            return None

        tmp = node._parent
        while tmp._data and node == tmp._right:
            node = tmp
            tmp = tmp._parent
        return tmp

    def _predecessor(self, node):
        if node._left != self._nil:
            return self._max_iter(node._left)
        if node._data == self.min_key():
            print("Данный ключ наименьший элемент в дереве, у него нет предшественника")
            return None

        tmp = node._parent
        while tmp and node == tmp._left:
            node = tmp
            tmp = tmp._parent
        return tmp

    def _print_inord(self, node):
        if node != self._nil:
            self._print_inord(node._left)
            print(node._data, end=' ')
            self._print_inord(node._right)

    def _print_preord(self, node):
        if node != self._nil:
            print(node._data, end=' ')
            self._print_inord(node._left)
            self._print_inord(node._right)

    def _print_postord(self, node):
        if node != self._nil:
            self._print_inord(node._left)
            self._print_inord(node._right)
            print(node._data, end=' ')

    def _destroy(self, node):
        if node != None and node != self._nil:
            self._destroy(node._left)
            self._destroy(node._right)
            node._data = None

    def _depth(self, node):
        left_num = 0
        right_num = 0
        if node is None:
            return 0
        if node._left:
            left_num += self._depth(node._left)
        if node._right:
            right_num += self._depth(node._right)
        return (left_num + 1) if left_num > right_num else (right_num + 1)

    def _size(self, node):
        if node is None or node == self._nil:
            return 0
        return self._size(node._left) + self._size(node._right) + 1

    def _pretty_print(self, node, st, last):
        if node != self._nil:
            print(st, end='')
            if last:
                print("R----", end='')
                st += "     "
            else:
                print("L----", end='')
                st += "|    "

            color = "RED" if node._color == 'red' else "BLACK"
            print(str(node._data) + "(" + color + ")")
            self._pretty_print(node._left, st, False)
            self._pretty_print(node._right, st, True)

    def clear(self):
        self._destroy(self._root)
        self._root = None

    def empty(self):
        return self._root is None

    def search(self, key):
        return self._search_iter(self._root, key) is not None

    def insert(self, key):
        node = Node(key, 'red')
        node._parent = None
        node._left = self._nil
        node._right = self._nil

        y = None
        x = self._root

        while x != self._nil:
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

        if node._parent == None:
            node._color = 'black'
            return
        if node._parent._parent == None:
            return
        self._fix_insert(node)

    def erase(self, key):
        self._delete_key(self._root, key)

    def get_root(self):
        return self._root._data

    def min_key(self):
        return self._min_iter(self._root)._data

    def max_key(self):
        return self._max_iter(self._root)._data

    def successor(self, key):
        tmp = self._search_iter(self._root, key)
        if tmp != None and tmp != self._nil:
            tm = self._successor(tmp)
            #print(tm._data)
            return tm._data if tm else None
        else:
            print("Нет такого ключа!")
            return None

    def predecessor(self, key):
        tmp = self._search_iter(self._root, key)
        if tmp != None and tmp != self._nil:
            tm = self._predecessor(tmp)
            return tm._data if tm else None
        else:
            print("Нет такого ключа!")
            return None

    def depth(self):
        return self._depth(self._root)

    def size(self):
        return self._size(self._root)

    def inorder_iter(self):
        stack = []
        curr = self._root
        while curr or len(stack) != 0:
            while curr:
                stack.append(curr)
                curr = curr._left
            top = stack.pop()
            if top != self._nil:
                print(top._data, end=' ')
            curr = top._right
        print('')

    def preorder_iter(self):
        stack = []
        curr = self._root
        while curr or len(stack) != 0:
            while curr:
                if curr != self._nil:
                    print(curr._data, end=' ')
                stack.append(curr)
                curr = curr._left
            top = stack.pop()
            curr = top._right
        print('')

    def postorder_iter(self):
        stack = []
        curr = self._root
        prev = None
        while curr or len(stack) != 0:
            while curr:
                stack.append(curr)
                curr = curr._left
            top = stack[len(stack)-1]
            if top._right is None or prev == top._right:
                stack.pop()
                prev = top
                if top != self._nil:
                    print(top._data, end=' ')
            else:
                curr = top._right
        print('')

    def inorder_rec(self):
        if self._root:
            self._print_inord(self._root)
            print(end='\n')
        else:
            print("BST is empty")

    def preorder_rec(self):
        if self._root:
            self._print_preord(self._root)
            print(end='\n')
        else:
            print("BST is empty")

    def postorder_rec(self):
        if self._root:
            self._print_postord(self._root)
            print(end='\n')
        else:
            print("BST is empty")

    def pretty_print(self):
        if self._root:
            self._pretty_print(self._root, "", True)


def main(size):
    tree = RB_tree()
    for _ in range(size):
        tree.insert(random.randint(0, 20))
    print("IN-order recursive: \t", end='')
    tree.inorder_rec()
    print("PRE-order recursive:\t", end='')
    tree.preorder_rec()
    print("POST-order recursive:\t", end='')
    tree.postorder_rec()
    print(f"Succes random key:\t\t{tree.successor(random.randint(0, 20))}")
    print(f"Predeces random key:\t{tree.predecessor(random.randint(0, 20))}")
    print(f"MINIMUM == {tree.min_key()}")
    print(f"MAXIMUM == {tree.max_key()}")
    print(f"DEPTH   == {tree.depth()}")
    print(f"SIZE    == {tree.size()}")
    print(f"SEARCH  == {tree.search(random.randint(0, 20))}")
    print("============Pretty print===================")
    tree.pretty_print()
    print("============Delete random key===================")
    for _ in range(size * 2):
        tree.erase(random.randint(0, 20))
    print("IN-order iterative: \t", end='')
    tree.inorder_iter()
    print("PRE-order iterative:\t", end='')
    tree.preorder_iter()
    print("POST-order iterative:\t", end='')
    tree.postorder_iter()
    print("============Pretty print===================")
    tree.pretty_print()


if __name__ == "__main__":
    main(20)