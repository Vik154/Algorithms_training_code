# Фибоначчиева куча - Fibonacci heap — структура данных, отвечающая интерфейсу приоритетная очередь.
# Эта структура имеет меньшую амортизированную сложность, чем биномиальная куча и двоичная куча.
import math

class FHeap:                                        # Класс описывающий Фибоначчиеву кучу
    class Node:                                     # Класс описывающий 1 узел биномиального дерева
        def __init__(self, key, value): pass        # Конструктор
        def _traversal_children(self): pass         # Обход кольцевого списка детей (child)-->(next)-->(next)-->(child)->
        def _print_tree(self): pass                 # Функция обхода одного биномиального дерева, и вывода его на экран
    def __init__(self): pass                        # Конструктор кучи
    def insert(self, key, value): pass              # Добавление узла в кучу
    def _merge_roots(self, node): pass              # Объединяет (добавляет) в один список корней переданный узел
    def _add_child(self, parent, child): pass       # Объединяет в одно дерево parent и child
    def _linking_links(self, child, parent): pass   # Функция связывания ссылок при объединении деревьев
    def _cut(self, x, y): pass                      # Функция вырезания узла, при условии когда узел стал меньше родителя
    def _cascading_cut(self, y): pass               # Каскадное вырезание узлов
    def _consolidate(self): pass                    # Функция объединения деревьев одинаковой степени вложенности
    def _remove_child_node(self, y, x): pass        # Функция удаления узла из списка детей
    def _iterate_list(self, head): pass             # Обход списка корней - служебная функция
    def extract_min(self): pass                     # Удаление минимального ключа
    def _search_node(self, find_key): pass          # Поиск узла по ключу
    def decrease_key(self, old_key, new_key): pass  # Понижение приоритета у ключа
    def merge(self, heap2):  pass                   # Объединение 2-х куч в одну
    def _traversal_roots(self): pass                # Служебная функция обхода корней
    def print_heap(self): pass                      # Печать
"""----------------------------------------------------------------------------------------"""


class FHeap:                                     # Класс описывающий Фибоначчиеву кучу
    class Node:                                  # Класс описывающий 1 узел биномиального дерева
        def __init__(self, key, value):          # Конструктор
            self._left = self._right = None      # Указатели на левый и правый узлы того же предка
            self._parent = self._child = None    # Указатели на родителя и на одного из детей
            self._key = key                      # Ключ
            self._value = value                  # Значение
            self._degree = 0                     # Количество дочерних узлов в дереве (степень вложенности)
            self._mark = False                   # Был ли перемещен (вырезан) дочерний узел

        def _traversal_children(self):           # Обход кольцевого списка детей (child)-->(next)-->(next)-->(child)->
            if self._child is None:              # Если пуст - вернуться
                return
            cur_child = self._child              # Иначе запомнить первый узел и обойти по кругу список детей
            while cur_child._right is not self._child:
                yield cur_child                  # Создать генератор на указатель текущего узла в списке child
                cur_child = cur_child._right     # Продвинуть вправо указатель
            yield cur_child                      # Запоминаем в генераторе первый элемент, с которого потом начнется старт

        def _print_tree(self):                  # Функция обхода одного биномиального дерева, и вывода его на экран
            print(f"({self._key}:{self._value})", end=' -> ')
            for child in self._traversal_children():    # Начать генерировать значения по одному в диапазоне заданным
                child._print_tree()                     # yield-ом и рекурсивно вызывать себя пока yield возвращает что-то

    def __init__(self):                          # Конструктор кучи
        self._min_root = None                    # Указатель на минимальный корень
        self._root_list = None                   # Список корней биномиальных деревьев
        self._count_nodes = 0                    # Счетчик узлов

    def insert(self, key, value):                # Добавление узла в кучу
        n = self.Node(key, value)                # Создать новый узел со значением value и ключом key
        n._left = n._right = n                   # Указатели на левого и правого соседей изначально зациклены
        self._merge_roots(n)                     # Объединение (Добавление нового узла в список корней)
        if self._min_root is None or n._key < self._min_root._key:
            self._min_root = n                   # Сразу при добавлении контролировать указатель на минимальный корень
        self._count_nodes += 1                   # Увеличить счетчик и
        return n                                 # Вернуть указатель на добавленный узел, для функции decrease_key

    def _merge_roots(self, node):                # Объединяет (добавляет) в один список корней переданный узел
        if self._root_list is None:              # Если список корней был пуст, тогда
            self._root_list = node               # Переданный корень будет в списке корней единственным
        else:                                     # Если в списке были корни, тогда
            node._right = self._root_list._right  # Указатель на правого соседа у добавляемого узла указывает на правого
            node._left = self._root_list          # соседа старого корня, т.е. вставка происходит справа -->(old)-->
            self._root_list._right._left = node   # -->(old)-->(new)-->(old)-->  список ведь кольцевой!
            self._root_list._right = node

    def _add_child(self, parent, child):        # Объединяет в одно дерево parent и child
        if parent._child is None:               # Если у parent-а нет дочерних узлов
            parent._child = child               # Тогда просто подвешивается к нему дерево child
        else:                                   # Если есть поддеревья, тогда
            child._right = parent._child._right # Тогда указатели на правых и левых соседей у передаваемого поддерева
            child._left = parent._child         # нужно правильно разместить -->(old)-->(new)-->(old)-->
            parent._child._right._left = child  # Теперь указатели подвешиваемого дерева указывают на соседей, которые
            parent._child._right = child        # уже существовали в дереве

    def _linking_links(self, child, parent):    # Функция связывания ссылок при объединении деревьев
        if child == self._root_list:            # Если узел добавляемого поддерева это корень в списке корней
            self._root_list = child._right      # Тогда сдвинуть указатель на правый узел
        child._left._right = child._right       # Указатель предыдущего корня перекинуть на следующий за child корень
        child._right._left = child._left        # А у следующего за child-ом перекинуть на предыдущий за child-ом
        child._left = child._right = child      # Указатели на соседей у child зациклить на себе
        self._add_child(parent, child)          # Объединить деревья в одно
        parent._degree += 1                     # Увеличить вложенность узлов
        child._parent = parent                  # В указатель на родителя поместить передаваемый узел к которому будет
        child._mark = False                     # Подвешен child, и обновить флаг, т.к. от него ещё не отрезали узлы

    def _cut(self, x, y):                       # Функция вырезания узла, при условии когда узел стал меньше родителя
        if y._child == y._child._right:         # Если у узла 'y' дочерний узел один и у него нет соседних элементов
            y._child = None                     # Обрезать его дочерний узел
        elif y._child == x:                     # Если дочерний узел у узла 'y' это 'x', тогда перекинуть указатели
            y._child = x._right                 # Дочерний узел 'y' станет указывать на соседа
            x._right._parent = y                # А сосед станет дочерним узлом 'y'
        x._left._right = x._right               # -->(old)--X()X-->(old)
        x._right._left = x._left                # -->(old)<--------(old)
        y._degree -= 1                          # Уменьшить кол-во вложенных узлов
        self._merge_roots(x)                    # Добавить в список корней вырезанный узел
        x._parent = None                        # Т.к. это теперь корень в списке корней, родителей нет
        x._mark = False                         # и флаг обновлен, т.е. от этого нового дерева x еще ничего не отрезали

    def _cascading_cut(self, y):                # Каскадное вырезание узлов
        z = y._parent                           # Запомнить указатель на родителя переданного узла
        if z is not None:                       # Если есть родитель, тогда проверить были ли вырезаны поддеревья
            if y._mark is False:                # Если узлы не вырезались, тогда
                y._mark = True                  # Пометить как вырезанные
            else:                               # Иначе, если уже были вырезания у узла 'y'
                self._cut(y, z)                 # Тогда вырезать из узла 'z' одиночно
                self._cascading_cut(z)          # И каскадно

    def _consolidate(self):                      # Функция объединения деревьев одинаковой степени вложенности
        # Создать 2 списка, 1 - список вложенности, 2 - список корней
        degree = [None] * int(math.log(self._count_nodes) * 2)
        nodes = [w for w in self._iterate_list(self._root_list)]
        for rt in range(0, len(nodes)):         # В диапазоне от 0 до количества корней в списке
            x = nodes[rt]                       # Запомнить узел из списка корней
            d = x._degree                       # Запомнить кол-во вложенных узлов у текущего корня
            while degree[d] != None:            # Пройти по массиву вложенности
                y = degree[d]                   # Запомнить узел по индексу 'd'
                if x._key > y._key:             # Если ключ у узла 'x' из списка корней > ключа узла 'y'
                    x, y = y, x                 # Поменять местами ноды
                self._linking_links(y, x)       # Перекинуть указатели для объединения в одно дерево этих узлов
                degree[d] = None
                d += 1
            degree[d] = x
        for i in range(0, len(degree)):
            if degree[i] is not None:
                if degree[i]._key < self._min_root._key:
                    self._min_root = degree[i]

    def _remove_child_node(self, y, x):         # Функция удаления узла из списка детей
        if y._child == y._child._right:
            y._child = None
        elif y._child == x:
            y._child = x._right
            x._right._parent = y
        x._left._right = x._right
        x._right._left = x._left

    def _iterate_list(self, head):              # Обход списка корней - служебная функция
        node = stop = head
        flag = False
        while True:
            if node == stop and flag is True:
                break
            elif node == stop:
                flag = True
            yield node
            node = node._right

    def extract_min(self):                      # Удаление минимального ключа
        z = self._min_root
        if z is not None:
            if z._child is not None:
                children = [x for x in self._iterate_list(z._child)]
                for i in range(0, len(children)):
                    self._merge_roots(children[i])
                    children[i]._parent = None
            if z == self._root_list:
                self._root_list = z._right
            z._left._right = z._right
            z._right._left = z._left
            if z == z._right:
                self._min_root = self._root_list = None
            else:
                self._min_root = z._right
                self._consolidate()
            self._count_nodes -= 1
        return z

    def _search_node(self, find_key):                   # Поиск узла по ключу
        stack = []
        stack.append(self._min_root)
        while (stack):
            curr = stack.pop()
            if (curr._key == find_key):
                return curr
            else:
                if (curr._child != None):
                    stack.append(curr._child)
                start = curr
                curr = curr._right
                while (curr != start):
                    if (curr._child != None):
                        stack.append(curr._child)
                    if (curr._key == find_key):
                        return curr
                    curr = curr._right
        return None

    def decrease_key(self, old_key, new_key):               # Понижение приоритета у ключа
        res = self._search_node(old_key)
        if (res):
            if (new_key > res._key):
                return None
            res._key = new_key
            y = res._parent
            if (y != None and res._key < y._key):
                self._cut(res, y)
                self._cascading_cut(y)
            if (res._key < self._min_root._key):
                self._min_root = res
            return 1
        else:
            return 0

    def merge(self, heap2):                                # Объединение 2-х куч в одну
        new_heap = FHeap()
        new_heap._root_list, new_heap._min_root = self._root_list, self._min_root
        last = heap2._root_list._left
        heap2._root_list._left = new_heap._root_list._left
        new_heap._root_list._left._right = heap2._root_list
        new_heap._root_list._left = last
        new_heap._root_list._left._right = new_heap._root_list
        if heap2._min_root._key < new_heap._min_root._key:
            new_heap._min_root = heap2._min_root
        new_heap._count_nodes = self._count_nodes + heap2._count_nodes
        return new_heap

    def _traversal_roots(self):                 # Служебная функция обхода корней
        if self._root_list is None:
            return
        cur_node = self._root_list._right
        while cur_node is not self._root_list:
            yield cur_node._left
            cur_node = cur_node._right
        yield cur_node._left

    def print_heap(self):
        if self._root_list is None:
            print("Heap is empty")
            return
        print(f"Min_root == {self._min_root._key}")
        for root in self._traversal_roots():
            root._print_tree()
        print('')

def main():
    heap = FHeap()
    for i in range(11):
        heap.insert(i, chr(i+65))
    heap.print_heap()
    for i in range(6):
        heap.extract_min()
    heap.print_heap()
    heap.decrease_key(8, -999)
    heap.decrease_key(20, -999)
    heap.print_heap()


if __name__ == "__main__":
    main()