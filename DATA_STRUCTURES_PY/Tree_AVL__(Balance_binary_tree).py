"""/*--AVL Tree - Сбалансированное двоичное дерево--*/"""
class Node:
    def __init__(self): pass

class AVL:
    def __init__(self): pass                # Конструктор
    def _height(self, node): pass			# Спектр высоты (Возвращает высоту для текущего поддерева, для пустого = 0)
    def _bfactor(self, node): pass          # Вычисление баланса узла (Возвращает разницу высоты между левым и правым поддеревом)
    def _fixheight(self, node): pass		# Установка поля высоты узла (Обновляет поле height для текущего узла)
    def _rotate_right(self, node): pass		# Правый поворот вокруг p
    def _rotate_left(self, node): pass		# Левый поворот вокруг q
    def _balance(self, node): pass   		# Балансировка узла p
    def _insert(self, node, key): pass	    # Вставка ключа k в дерево с корнем p
    def _find_min(self, node): pass			# Служебная функция поиска минимума для функции удаления узла
    def _remove_min(self, node): pass		# Служебная функция удаления узла с минимальным ключа
    def _remove_value(self, node, key): pass  # Удаление ключа из дерева
    def _print(self, node, level): pass     # Печать структуры дерева
    def _del_tree(self, node): pass         # Рекурсивное освобождение памяти
    def insert(self, key): pass             # Вставка
    def remove(self, key): pass				# Удаление по значению
    def show(self): pass				    # Вывод на экран
"""---------------------------------------------------------------------------"""

class Node:
    def __init__(self, data):
        self._data = data                   # Данные
        self._left = None                   # Левый потомок
        self._right = None                  # Правый потомок
        self._height = 1                    # Высота поддерева


class AVL:
    def __init__(self):                     # Конструктор
        self._root = None

    def _height(self, node):      # Спектр высоты (Возвращает высоту для текущего поддерева, для пустого = 0)
        if node is not None:
            return node._height
        else:
            return 0
        # return node._height if node is not None else None

    def _bfactor(self, node):     # Вычисление баланса узла (Возвращает разницу высоты между левым и правым поддеревом)
        return self._height(node._right) - self._height(node._left)

    def _fixheight(self, node):           # Установка поля высоты узла (Обновляет поле height для текущего узла)
        hl = self._height(node._left)
        hr = self._height(node._right)
        if hl > hr:
            node._height = hl + 1
        else:
            node._height = hr + 1
        #node._height = (hl + 1) if hl > hr else (hr + 1)

    def _rotate_right(self, node):       # Правый поворот вокруг p
        q = node._left
        node._left = q._right
        q._right = node
        self._fixheight(node)
        self._fixheight(q)
        return q

    def _rotate_left(self, node):       # Левый поворот вокруг q
        p = node._right
        node._right = p._left
        p._left = node
        self._fixheight(node)
        self._fixheight(p)
        return p

    def _balance(self, node):           # Балансировка узла p
        self._fixheight(node)
        if self._bfactor(node) == 2:
            if self._bfactor(node._right) < 0:
                node._right = self._rotate_right(node._right)
            return self._rotate_left(node)
        if self._bfactor(node) == -2:
            if self._bfactor(node._left) > 0:
                node._left = self._rotate_left(node._left)
            return self._rotate_right(node)
        return node

    def _insert(self, node, key):            # Вставка ключа k в дерево с корнем p
        if node is None:
            return Node(key)
        if key < node._data:
            node._left = self._insert(node._left, key)
        else:
            node._right = self._insert(node._right, key)
        return self._balance(node)

    def _find_min(self, node):               # Служебная функция поиска минимума для функции удаления узла
        return self._find_min(node._left) if node._left else node

    def _remove_min(self, node):             # Служебная функция удаления узла с минимальным ключа
        if node._left is None:
            return node._right
        node._left = self._remove_min(node._left)
        return self._balance(node)

    def _remove_value(self, node, key):     # Удаление ключа из дерева
        if node is None:
            return None
        if key < node._data:
            node._left = self._remove_value(node._left, key)
        elif key > node._data:
            node._right = self._remove_value(node._right, key)
        else:
            q = node._left
            r = node._right
            node = None
            if r is None:
                return q
            minv = self._find_min(r)
            minv._right = self._remove_min(r)
            minv._left = q
            return self._balance(minv)
        return self._balance(node)

    def _print(self, node, level):        # Печать структуры дерева
        if node is None:
            return
        for i in range(level):
            print("---", end=' ')
        print(node._data)
        self._print(node._left, level + 1)
        self._print(node._right, level + 1)

    def _del_tree(self, node):            # Рекурсивное освобождение памяти
        if node:
            self._del_tree(node._left)
            self._del_tree(node._right)
            node._data = None

    def insert(self, key):                   # Вставка
        self._root = self._insert(self._root, key)

    def remove(self, key):                   # Удаление по значению
        self._remove_value(self._root, key)

    def show(self):                          # Вывод на экран
        self._print(self._root, 0)


def main():
    avl = AVL()
    for i in range(20):
        avl.insert(i)
    avl.show()

if __name__ == "__main__":
    main()