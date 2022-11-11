"""--Бинарное дерево поиска - Binary search tree--"""
import random

class Node: pass                                        # Узлы вставляемые в дерево

class BST:                                              # Binary search tree
    def __init__(self): pass                            # Конструктор дерева
    def empty(self): pass                               # Проверка есть ли элементы в дереве
    def size(self): pass                                # Кол-во элементов в дереве
    def _size(self, pointer): pass                      # Рекурсивный подсчет элементов (внутреннее использование)
    def size_rec(self): pass                            # Рекурсивный подсчет элементов пользовательская функция
    def _depth(self, node): pass                        # Глубина дерева (внутреннее использование)
    def depth(self): pass                               # Глубина дерева возвращает наибольший размер поддерева
    def _print_inord(self, node): pass                  # Инфиксный	обход (упорядоченный) <-- Рекурсивный вариант
    def print_inord(self): pass                         # Обход дерева в симметричном порядке (слева направо): B, A, C
    def _print_preord(self, node): pass                 # Префиксный обход      <-- Рекурсивный вариант
    def print_preord(self): pass                        # Обход дерева сверху вниз (в прямом порядке): A, B, C
    def _print_postord(self, node): pass                # Постфиксный обход		<-- Рекурсивный вариант
    def print_postord(self): pass                       # Обход дерева в обратном порядке (снизу вверх): B, C, A
    def _max_elem(self, node): pass                     # Рекурсивный поиск максимального элемента от заданного узла
    def max_elem(self): pass                            # Вызов пользовательский
    def _min_elem(self, node): pass                     # Рекурсивный поиск минимального элемента от заданного узла
    def min_value(self): pass                           # итеративный поиск самого маленького элемента
    def max_value(self): pass                           # итеративный поиск самого большого элемента
    def show_inord(self): pass                          # Инфиксный	обход (упорядоченный) <-- Итеративный вариант
    def show_preord(self): pass                         # Префиксный обход                <-- Итеративный вариант
    def show_postord(self): pass                        # Постфиксный обход               <-- Итеративный вариант
    def successor(self, key): pass                      # Поиск преемника (больший ключ по сравнению с оригинальным ключом)
    def insert(self, data): pass                        # Рекурсивная вставка элементов
    def find(self, key): pass                           # Поиск элемента по значению
    def _delete_tree(self, pointer): pass               # Имитация удаления узлов и освобождения памяти как в C++
    def del_tree(self): pass                            # Пользовательский вызов
    def erase(self, elem): pass                         # Удаление элемента по значению (ключу)


"""================================================="""
class Node:
    def __init__(self, data=None):
        self._data = data
        self._left = None
        self._right = None


class BST:
    def __init__(self):                             # Конструктор дерева
        self._root = None                           # Указатель на корень дерева, самый первый элемент
        self._count = 0                             # Счётчик элементов в дереве

    def empty(self):                                # Проверка есть ли элементы в дереве
        return self._count is None                  # Если элементов нет 0 иначе 1

    def size(self):
        return self._count

    def _size(self, pointer):           # Рекурсивный подсчет элементов
        if pointer is None:
            return 0
        return self._size(pointer._left) + self._size(pointer._right) + 1

    def size_rec(self):
        return self._size(self._root)

    def _depth(self, node):                         # Глубина дерева
        left_num = right_num = 0
        if node is None:
            return 0
        if node._left:
            left_num += self._depth(node._left)
        if node._right:
            right_num += self._depth(node._right)
        return left_num if left_num > right_num else right_num + 1

    def depth(self):
        return self._depth(self._root)

    def _print_inord(self, node):
        if node:
            self._print_inord(node._left)
            print(node._data, end=' ')
            self._print_inord(node._right)

    def print_inord(self):
        if self._count:
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

    def _max_elem(self, node):
        if node is None:
            return None
        elif node._right is None:
            return node._data
        else:
            return self._max_elem(node._right)

    def max_elem(self):
        return self._max_elem(self._root)

    def _min_elem(self, node):
        if node is None:
            return None
        elif node._left is None:
            return node._data
        else:
            return self._min_elem(node._left)

    def min_elem(self):
        return self._min_elem(self._root)

    def min_value(self):                            # итеративный поиск самого маленького элемента
        curr = self._root
        while curr._left is not None:
            curr = curr._left
        return curr._data

    def max_value(self):                            # итеративный поиск самого большого элемента
        curr = self._root
        while curr._right is not None:
            curr = curr._right
        return curr._data

    def show_inord(self):
        stack = []
        curr = self._root
        while curr or len(stack) != 0:
            while curr:
                stack.append(curr)
                curr = curr._left
            top = stack.pop()
            print(top._data, end=' ')
            curr = top._right
        print('')

    def show_preord(self):
        stack = []
        curr = self._root
        while curr or len(stack) != 0:
            while curr:
                print(curr._data, end=' ')
                stack.append(curr)
                curr = curr._left
            top = stack.pop()
            curr = top._right
        print('')

    def show_postord(self):
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
                print(top._data, end=' ')
            else:
                curr = top._right
        print('')

    def successor(self, key):
        curr = self._root
        succ = None
        while curr:
            if curr._data > key:
                succ = curr
                curr = curr._left
            else:
                curr = curr._right
        return succ._data if succ else 0

    def insert(self, data):                         # Рекурсивная вставка элементов
        if self._root is None:                      # Если элемент первый, тогда
            self._root = Node(data)                 # Сделать его корнем
            self._count += 1                        # Увеличить счетчик
            return                                  # Вернуться
        curr = self._root                           # Временный указатель на начало дерева
        while curr and curr._data != data:          # Пока указатель существует и не равен вставляемому значению
            if curr._data > data and curr._left is None:    # Если вставляемое значение меньше текущего и нет потомков,
                curr._left = Node(data)             # Создать новый узел и положить его в левую часть
                self._count += 1                    # Увеличить счетчик
                return                              # Вернуться
            if curr._data < data and curr._right is None:   # Если вставляемый элемент больше текущего и нет потомков,
                curr._right = Node(data)            # Создать новый узел дерева в правой части
                self._count += 1                    # Увеличить счетчик
                return                              # Вернуться
            if data < curr._data:                   # Если вставляемый меньше текущего продвинуться влево
                curr = curr._left
            else:                                   # Если вставляемый элемент больше или равен текущему
                curr = curr._right                  # Тогда идём вправо

    def find(self, key):                            # Поиск элемента по значению
        curr = self._root                           # Временный указатель для обхода по дереву
        while curr and curr._data != key:           # Пока указатель не пуст и значение в нем не равно искомому
            if key < curr._data:                    # Если искомое значение меньше значения в текущем указателе
                curr = curr._left                   # Спуститься влево
            else:
                curr = curr._right                  # Иначе вправо
        return curr is not None                     # Вернуть False если не нашел, иначе true

    def _delete_tree(self, pointer):                # Имитация удаления узлов и освобождения памяти как в C++
        if pointer:                                 # Хотя тут такой необходимости нет, т.к. автоматический сборщик сам сделает это
            self._delete_tree(pointer._left)
            self._delete_tree(pointer._right)
            pointer._data = None

    def del_tree(self):
        self._delete_tree(self._root)
        self._count = 0

    def erase(self, elem):                          # Удаление элемента по значению (ключу)
        if self._root is None:
            return
        curr = self._root
        parent = None
        while curr and curr._data != elem:
            parent = curr
            if elem < curr._data:
                curr = curr._left
            else:
                curr = curr._right
        if curr is None:
            return
        if curr._left == None:
            if parent and parent._left == curr:
                parent._left = curr._right
            if parent and parent._right == curr:
                parent._right = curr._right
            self._count -= 1
            curr._data = None
            return
        if curr._right == None:
            if parent and parent._left == curr:
                parent._left = curr._left
            if parent and parent._right == curr:
                parent._right = curr._left
            self._count -= 1
            curr._data = None
            return
        replace = curr._right
        while replace._left:
            replace = replace._left
        replace_value = replace._data
        self.erase(replace_value)
        curr._data = replace_value


def main():
    tree_int = BST()
    tree_char = BST()
    for i in range(20):
        tree_int.insert(random.randint(0, 100))
        tree_char.insert(chr(random.randint(10, 100)))
    print("----------------Integer tree-------------------")
    print(f"In-order -->\t", end='')
    tree_int.print_inord()
    print(f"Pre-order -->\t", end='')
    tree_int.print_preord()
    print(f"Post-order -->\t", end='')
    tree_int.print_postord()
    print("----------------Char tree-------------------")
    print(f"In-order -->\t", end='')
    tree_char.show_inord()
    print(f"Pre-order -->\t", end='')
    tree_char.show_preord()
    print(f"Post-order -->\t", end='')
    tree_char.show_postord()


if __name__ == "__main__":
    main()