"""/*--Реализация двусвязного списка - doubly_linked_list--*/"""
import time; import random
"""************************************************************************************"""
class Node:                                     # Класс добавляемых элементов в список
    def __init__(self, data, nxt): pass         # Конструктор узла

class List:                                     # Двусвязный список
    def __init__(self): pass                    # Конструктор класса
    def empty(self): pass                       # Возвращает true если список пуст, иначе false
    def push_front(self, data): pass            # Вставка элемента в начало списка
    def push_back(self, data): pass             # Вставка элемента в конец списка
    def insert(self, data, index): pass         # Вставка элемента по индексу
    def pop_front(self): pass                   # Удаление из начала списка
    def pop_back(self): pass                    # Удаление с конца списка
    def clear(self): pass                       # Удаление всех элементов списка
    def remove(self, value): pass               # Удаление всех найденных элементов соответствующих значению value
    def show(self): pass                        # Отображение списка (печать)
    def size(self): pass                        # Возвращает количество элементов в списке
    def front(self): pass                       # Возвращает первый элемент в списке
    def back(self): pass                        # Возвращает последний элемент в списке
    def find(self, value): pass                 # Поиск элемента по значению
    def reverse(self): pass                     # Разворот списка
    def sort_bubble(self): pass                 # Сортировка пузырьком
    def sort_insertion(self): pass              # Сортировка вставками
    def sort_selection(self): pass              # Сортировка выбором
    def sort_merge(self): pass                  # Сортировка слиянием
    def __get_middle(self, node): pass          # Внутренний метод поиска середины списка для сортировки
    def __merge(self, left, right): pass        # Функция для внутреннего использования
    def __merge_sort(self): pass                # Типа инкапсулированная функция для сортировки слиянием
    def __getitem__(self, index): pass          # Обращение к элементам списка через []
    def __setitem__(self, key, value): pass     # Изменение значения через []
    def __add__(self, other): pass              # Сложение списков [] + [] и возвращение нового списка
"""************************************************************************************"""


class Node:
    def __init__(self, data=None, nxt=None, prev=None):      # Конструктор узла
        self._data = data                                    # Поле с данными
        self._next = nxt                                     # Указатель на следующий узел
        self._prev = prev                                    # Указатель на предыдущий узел


class List:
    def __init__(self, head=None, tail=None):    # Конструктор списка
        self._head = None                        # Начало списка (1-ый элемент)
        self._tail = None                        # Конец списка (последний элемент)
        self._count = None                       # Счётчик элементов в списке

    def empty(self):                             # Проверка, есть ли элементы в списке
        return self._head is None                # Если элементов нет вернет 1 иначе 0

    def push_front(self, data):                 # Добавление элемента в начало списка
        node = Node(data)                       # Создать элемент списка
        if self.empty():                        # Если список пуст, тогда это первый элемент
            node._next = None                   # Следующего узла нет, т.к. он пока один
            node._prev = None                   # Предыдущего узла нет, т.к. он пока один
            self._head = node                   # Голова указывает на добавленный элемент
            self._tail = node                   # Хвост тоже указывает на добавленный элемент
            self._count = 1                     # Обновить счётчик, теперь в списке есть элемент
        else:                                   # Если в списке есть элементы, тогда
            node._next = self._head             # Добавленный указывает на голову списка
            self._head._prev = node             # Head-->(insert)()--[]--[]--[]<--Tail
            self._head = node                   # Указатель головы перемещается на новый добавленный элемент
            self._count += 1                    # Счётчик увеличился на один добавленный элемент

    def push_back(self, data):                  # Добавляет элемент в конец списка
        node = Node(data)                       # Создается новый элемент списка
        if self.empty():                        # Если список пуст, тогда
            node._next = None                   # Следующего узла нет, т.к. он пока один
            node._prev = None                   # Следующего узла нет, т.к. он пока один
            self._head = node                   # Голова указывает на добавленный элемент
            self._tail = node                   # Хвост тоже указывает на добавленный элемент
            self._count = 1                     # Обновить счётчик, теперь в списке есть элемент
        else:                                   # Если есть элементы в списке, тогда
            self._tail._next = node             # в поле next последнего элемента добавиться новый элемент
            node._prev = self._tail             # Head-->[]--[]--[]--()(insert)<--Tail
            self._tail = node                   # Теперь хвост указывает на добавленный элемент
            self._count += 1                    # Увеличить счетчик на один добавленный элемент

    def insert(self, data, index):        # Добавляет элемент в список после указанного индекса (вправо)
        if self.empty():                        # Если список пуст неважно какой будет передан индекс, добавит в начало
            self.push_front(data)
        else:                                   # Если элементы есть в списке, тогда
            if index >= self._count:            # Пограничный случай, если индекс равен последнему или больше
                self.push_back(data)            # Тогда вставка в конец случается
                return
            elif index <= 0:                    # Если кривой индекс или 0, вставка вперед произойдёт
                self.push_front(data)           # Вставить в начало
                return                          # Вернуться
            elif index < self._count:           # Если индекс корректный, тогда
                node = Node(data)               # Создается новый узел
                temp = self._head               # Создать временный указатель на начало списка
                for i in range(index - 1):      # Пройти по списку до заданного индекса
                    temp = temp._next           # Запомнить адрес текущего узла, т.к вставка за него будет
                node._next = temp._next         # Новый узел указывает на след за temp
                node._prev = temp
                temp._next._prev = node
                temp._next = node
                self._count += 1                # Увеличить счетчик на добавленный элемент

    def pop_front(self):                        # Удаление элемента из начала списка
        if self.empty():                        # Если список пуст, ничего не делать
            return                              # Вернуться
        elif self._count == 1:                   # Если один элемент в списке, тогда
            self._head = None                   # Обнулить указатель на голову
            self._tail = None                   # Обнулить указатель на хвост
            self._count = 0                     # Счётчик скинуть в нуль
            return                              # вернуться
        else:                                   # Если в списке больше 1-го элемента, тогда
            temp = self._head._next             # Запомнить указатель на голову, явно
            self._head = None                   # Явно удалить ссылку на элемент
            self._head = temp                   # Продвинуться вперед на один элемент
            self._head._prev = None             # Следующий за первым элементом теперь первый в списке
            self._count -= 1                     # Обновить счётчик

    def pop_back(self):                         # Удаление элементов с конца
        if self.empty():                        # Если список пуст, ничего не делать
            return                              # Вернуться
        elif self._count == 1:                  # Если один элемент в списке, тогда
            self._head = None                   # Обнулить указатель на голову
            self._tail = None                   # Обнулить указатель на хвост
            self._count = 0                     # Счётчик скинуть в нуль
            return                              # вернуться
        else:                                   # Если элементов в списке больше одного, тогда
            temp = self._tail._prev             # Временный указатель который сохранит адрес предпоследнего элемента
            self._tail = None                   # Явно удалить ссылку на последний элемент
            self._tail = temp                   # Теперь хвост указывает на предпоследний элемент
            temp._next = None                    # Удалить ссылку на следующий за предпоследним элементом
            self._count -= 1                     # Зафиксировать удаление

    def clear(self):                            # Очистка списка полностью
        while self._head:                        # Пока список не пуст
            self.pop_front()                    # Удалять поэлементно начиная с головы

    def remove(self, value):                    # Удаление всех найденных элементов соответствующих значению value
        if self.empty():                        # Если список пуст
            return                              # Вернуться
        if self._count == 1:                    # Если в списке один элемент, проверить его
            if self._head._data == value:       # Если элемент подходит под условие удаления
                self.pop_back()                 # Удалить его
                return                          # Вернуться
            else:                               # Если один элемент и он не подходит, тогда
                return                          # Вернуться
        tmp = self._head._next                  # Указатель для итерации по списку
        while tmp:                              # Пока есть элементы продвигаться по списку
            if tmp._data == value:              # Если элемент совпадает, тогда проверить
                if tmp == self._tail:           # Если это последний элемент в списке
                    tmp._prev._next = None      # Тогда предыдущий никуда не указывает теперь
                    self._tail = None           # удалить значение в хвосте
                    self._tail = tmp._prev      # Хвост передвинуть на предыдущий
                    self._count -= 1            # Обновить счетчик
                    break                       # Закончить цикл
                else:                           # Если элемент не последний и надо удалять, тогда
                    tmp._next._prev = tmp._prev # У следующего элемента заменить указатель
                    tmp._prev._next = tmp._next # У предыдущего заменить указатель
                    self._count -= 1            # Текущий автоматически удалиться, т.к нет на него ссылок больше
            tmp = tmp._next                     # Продвинуть вперед

        if self._head._data == value:           # Проверить первый элемент, не подходит ли он под условие удаления
            self.pop_front()                    # Если подходит - удалить

    def show(self):  # Печать списка
        if self.empty():
            return
        temp = self._head
        print("Head -->", end=' ')
        while temp:
            if temp._next:
                print(f"{temp._data} -->", end=' ')
                temp = temp._next
            else:
                print(f"{temp._data} <-- Tail")
                temp = temp._next

    def size(self):  # Вернуть количество элементов
        return self._count

    def front(self):
        return self._head._data

    def back(self):
        return self._tail._data

    def find(self, value):
        if self.empty():
            return None
        tmp = self._head
        id = 0
        while tmp:
            if tmp._data == value:
                return id
            tmp = tmp._next
            id += 1
        return None

    def reverse(self):
        if not self._head or self._head == self._tail:
            return
        curr = self._head
        temp = None
        while curr:
            temp = curr._prev
            curr._prev = curr._next
            curr._next = temp
            curr = curr._prev
        if temp:
            self._head = temp._prev

    def sort_bubble(self):
        end = None
        while end != self._head:
            p = self._head
            while p._next != end:
                q = p._next
                if p._data > q._data:
                    p._data, q._data = q._data, p._data
                p = p._next
            end = p

    def sort_insertion(self):
        if self._count < 2:
            return
        n = self._count
        curr = self._head._next
        prev = self._head
        for i in range(n-1):
            tmp = curr._data
            prev = curr._prev
            while prev and tmp <= prev._data:
                prev._next._data = prev._data
                prev._data = tmp
                prev = prev._prev
            curr = curr._next

    def sort_selection(self):
        if self._count < 2:
            return
        curr = self._head
        it = self._head
        for _ in range(self._count - 1):
            min_id = curr
            search = it
            while search:
                if search._data < min_id._data:
                    min_id = search
                search = search._next
            if curr._data != min_id._data:
                curr._data, min_id._data = min_id._data, curr._data
            curr = curr._next
            it = it._next

    def __get_middle(self, node):
        if not node:
            return node
        slow = fast = node
        while fast._next and fast._next._next:
            slow = slow._next
            fast = fast._next._next
        return slow

    def __merge(self, left, right):
        imitation_head = Node()
        current = imitation_head
        while left and right:
            if left._data < right._data:
                current._next = left
                left = left._next
            else:
                current._next = right
                right = right._next
            current = current._next
        if not left:
            current._next = right
        else:
            current._next = left
        return imitation_head._next

    def __merge_sort(self, node):
        if not node or not node._next:
            return node
        middle = self.__get_middle(node)
        left_head = node
        right_head = middle._next
        middle._next = None
        return self.__merge(self.__merge_sort(left_head), self.__merge_sort(right_head))

    def sort_merge(self):
        self._head = self.__merge_sort(self._head)

    def __getitem__(self, index):
        if not self._head or index < 0 or index >= self._count:
            return None
        tmp = self._head
        for i in range(index):
            tmp = tmp.next
        return tmp.data

    def __setitem__(self, key, value):
        if not self._head or key < 0 or key >= self._count:
            return None
        tmp = self._head
        for i in range(key):
            tmp = tmp.next
        tmp.data = value

    def __add__(self, other):
        new_list = List()
        tmp = self._head
        while tmp:
            new_list.push_back(tmp._data)
            tmp = tmp._next
        tmp = other._head
        while tmp:
            new_list.push_back(tmp._data)
            tmp = tmp._next
        return new_list

# Функция тестирования
def time_test(length):
    my_list = List()
    py_list = []
    if length < 2100:
        print(f"Идёт заполнение \"my_list\" списка на {length} элементов:\t ", end='')
        timer = time.perf_counter()
        for i in range(length):
            my_list.push_front(random.randint(-10_000, 10_000))
        print(f"{time.perf_counter() - timer:0.3f} сек.")
        print(f"Идет сортировка \"sort_bubble\" списка:\t\t\t\t ", end='')
        timer = time.perf_counter()
        my_list.sort_bubble()
        print(f"{time.perf_counter() - timer:0.3f} сек.")
        timer = time.perf_counter()
        print(f"Идёт удаление \"my_list\" списка на {length} элементов:\t ", end='')
        my_list.clear()
        print(f"{time.perf_counter() - timer:0.3f} сек.")
    if length < 8010:
        print("=======================================================================")
        print(f"Идёт заполнение \"my_list\" списка на {length} элементов:\t ", end='')
        timer = time.perf_counter()
        for i in range(length):
            my_list.push_front(random.randint(-10_000, 10_000))
        print(f"{time.perf_counter() - timer:0.3f} сек.")
        print(f"Идет сортировка \"sort_insertion\" списка:\t\t\t ", end='')
        timer = time.perf_counter()
        my_list.sort_insertion()
        print(f"{time.perf_counter() - timer:0.3f} сек.")
        timer = time.perf_counter()
        print(f"Идёт удаление \"my_list\" списка на {length} элементов:\t ", end='')
        my_list.clear()
        print(f"{time.perf_counter() - timer:0.3f} сек.")
    if length < 5010:
        print("=======================================================================")
        print(f"Идёт заполнение \"my_list\" списка на {length} элементов:\t ", end='')
        timer = time.perf_counter()
        for i in range(length):
            my_list.push_front(random.randint(-10_000, 10_000))
        print(f"{time.perf_counter() - timer:0.3f} сек.")
        print(f"Идет сортировка \"sort_selection\" списка:\t\t\t ", end='')
        timer = time.perf_counter()
        my_list.sort_selection()
        print(f"{time.perf_counter() - timer:0.3f} сек.")
        timer = time.perf_counter()
        print(f"Идёт удаление \"my_list\" списка на {length} элементов:\t ", end='')
        my_list.clear()
        print(f"{time.perf_counter() - timer:0.3f} сек.")
    if length < 100_000:
        print("=======================================================================")
        print(f"Идёт заполнение \"my_list\" списка на {length} элементов:\t ", end='')
        timer = time.perf_counter()
        for i in range(length):
            my_list.push_front(random.randint(-10_000, 10_000))
        print(f"{time.perf_counter() - timer:0.3f} сек.")
        print(f"Идет сортировка \"sort_merge\" списка:\t\t\t\t ", end='')
        timer = time.perf_counter()
        my_list.sort_merge()
        print(f"{time.perf_counter() - timer:0.3f} сек.")
        timer = time.perf_counter()
        print(f"Идёт удаление \"my_list\" списка на {length} элементов:\t ", end='')
        my_list.clear()
        print(f"{time.perf_counter() - timer:0.3f} сек.")
    print("=======================================================================")
    print(f"Идёт заполнение \"py_list\" списка на {length} элементов:\t ", end='')
    timer = time.perf_counter()
    for i in range(length):
        py_list.append(random.randint(-10_000, 10_000))
    print(f"{time.perf_counter() - timer:0.3f} сек.")
    print(f"Идет сортировка \"py_sort\" списка:\t\t\t\t\t ", end='')
    timer = time.perf_counter()
    py_list.sort()
    print(f"{time.perf_counter() - timer:0.3f} сек.")
    timer = time.perf_counter()
    print(f"Идёт удаление \"py_list\" списка на {length} элементов:\t ", end='')
    py_list.clear()
    print(f"{time.perf_counter() - timer:0.3f} сек.\n")


if __name__ == "__main__":
    time_test(2_000)
    time_test(5_000)
    time_test(50_000)