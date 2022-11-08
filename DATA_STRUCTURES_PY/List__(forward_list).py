"""/*--Реализация односвязного списка - forward_list--*/"""
import time; import random
"""************************************************************************************"""
class Node:                                     # Класс добавляемых элементов в список
    def __init__(self, data, next): pass        # Конструктор узла

class Forward_list:                             # Односвязный список
    def __init__(self): pass                    # Конструктор класса
    def empty(self): pass                       # Возвращает true если список пуст, иначе false
    def push_front(self, data): pass            # Вставка элемента в начало списка
    def push_back(self, data): pass             # Вставка элемента в конец списка
    def insert_after(self, data, index): pass   # Вставка элемента по индексу
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
    def __init__(self, data=None, next=None):   # Конструктор узла
        self.data = data                        # Поле с данными
        self.next = next                        # Указатель на следующий узел


class Forward_list:
    def __init__(self, head=None, tail=None):   # Конструктор списка
        self.head = None                        # Начало списка (1-ый элемент)
        self.tail = None                        # Конец списка (последний элемент)
        self.count = None                       # Счётчик элементов в списке

    def empty(self):                            # Проверка, есть ли элементы в списке
        return self.head is None                # Если элементов нет вернет 1 иначе 0

    def push_front(self, data):                 # Добавление элемента в начало списка
        node = Node(data)                       # Создать элемент списка
        if self.empty():                        # Если список пуст, тогда это первый элемент
            node.next = None                    # Следующего узла нет, т.к. он пока один
            self.head = node                    # Голова указывает на добавленный элемент
            self.tail = node                    # Хвост тоже указывает на добавленный элемент
            self.count = 1                      # Обновить счётчик, теперь в списке есть элемент
        else:                                   # Если в списке есть элементы, тогда
            node.next = self.head               # Добавленный указывает на голову списка
            self.head = node                    # Указатель головы перемещается на новый добавленный элемент
            self.count += 1                     # Счётчик увеличился на один добавленный элемент

    def push_back(self, data):                  # Добавляет элемент в конец списка
        node = Node(data)                       # Создается новый элемент списка
        if self.empty():                        # Если список пуст, тогда
            node.next = None                    # Следующего узла нет, т.к. он пока один
            self.head = node                    # Голова указывает на добавленный элемент
            self.tail = node                    # Хвост тоже указывает на добавленный элемент
            self.count = 1                      # Обновить счётчик, теперь в списке есть элемент
        else:                                   # Если есть элементы в списке, тогда
            self.tail.next = node               # в поле next последнего элемента добавиться новый элемент
            self.tail = node                    # Теперь хвост указывает на добавленный элемент
            self.count += 1                     # Увеличить счетчик на один добавленный элемент

    def insert_after(self, data, index):        # Добавляет элемент в список после указанного индекса (вправо)
        if self.empty():                        # Если список пуст неважно какой будет передан индекс, добавит в начало
            node = Node(data)                   # Создается новый узел
            node.next = None                    # Следующего узла нет, т.к. он пока один
            self.head = node                    # Голова указывает на добавленный элемент
            self.tail = node                    # Хвост тоже указывает на добавленный элемент
            self.count = 1                      # Обновить счётчик, теперь в списке есть элемент
        else:                                   # Если элементы есть в списке, тогда
            if index >= self.count - 1:         # Пограничный случай, если индекс равен последнему или больше
                self.push_back(data)            # Тогда вставка в конец случается
            elif index < 0:                     # Если кривой индекс, вставка вперед произойдёт
                self.push_front(data)           # Вставить в начало
                return                          # Вернуться
            elif index < self.count:            # Если индекс корректный, тогда
                node = Node(data)               # Создается новый узел
                temp = self.head                # Создать временный указатель на начало списка
                for i in range(index):          # Пройти по списку до заданного индекса
                    temp = temp.next            # Запомнить адрес текущего узла, т.к вставка за него будет
                node.next = temp.next           # Добавленный узел теперь указывает куда указывал темп
                temp.next = node                # А поле next теперь указывает на добавленный узел
                self.count += 1                 # Увеличить счетчик на добавленный элемент

    def pop_front(self):                        # Удаление элемента из начала списка
        if self.empty():                        # Если список пуст, ничего не делать
            return                              # Вернуться
        elif self.count == 1:                   # Если один элемент в списке, тогда
            self.head = None                    # Обнулить указатель на голову
            self.tail = None                    # Обнулить указатель на хвост
            self.count = 0                      # Счётчик скинуть в нуль
            return                              # вернуться
        else:                                   # Если в списке больше 1-го элемента, тогда
            temp = self.head                    # Запомнить указатель на голову, явно
            self.head = None                    # Явно удалить ссылку на элемент
            self.head = temp.next               # Продвинуться вперед на один элемент
            self.count -= 1                     # Обновить счётчик

    def pop_back(self):                         # Удаление элементов с конца
        if self.empty():                        # Если список пуст, ничего не делать
            return                              # Вернуться
        elif self.count == 1:                   # Если один элемент в списке, тогда
            self.head = None                    # Обнулить указатель на голову
            self.tail = None                    # Обнулить указатель на хвост
            self.count = 0                      # Счётчик скинуть в нуль
            return                              # вернуться
        else:                                   # Если элементов в списке больше одного, тогда
            temp = self.head                    # Временный указатель который сохранит адрес предпоследнего элемента
            for _ in range(self.count-2):       # Продвинуть указатель до предпоследнего элемента
                temp = temp.next                # Продвигаться по списку вперед
            self.tail = None                    # Явно удалить ссылку на последний элемент
            self.tail = temp                    # Теперь хвост указывает на предпоследний элемент
            temp.next = None                    # Удалить ссылку на следующий за предпоследним элементом
            self.count -= 1                     # Зафиксировать удаление

    def clear(self):                            # Очистка списка полностью
        while self.head:                        # Пока список не пуст
            self.pop_front()                    # Удалять поэлементно начиная с головы

    def remove(self, value):                    # Удаление всех найденных элементов соответствующих значению value
        if self.empty():                        # Если список пуст
            return                              # Вернуться
        if self.count == 1:                     # Если в списке один элемент, проверить его
            if self.head.data == value:         # Если элемент подходит под условие удаления
                self.head = None                # Обнулить указатель на голову
                self.tail = None                # Обнулить указатель на хвост
                self.count = 0                  # Обновить счетчик
                return                          # Вернуться
            else:                               # Если один элемент и он не подходит, тогда
                return                          # Вернуться
        slow = self.head                        # Запоминатель адреса, если элемент встретиться, чтобы адрес сохранить
        fast = self.head.next                   # Быстрый указатель идет впереди медленного и проверяет элементы
        while fast:                             # Пока есть элементы продвигаться по списку
            if fast.data == value:              # Если элемент совпадает, тогда проверить
                if fast.next:                   # Если есть следующий элемент, тогда
                    slow.next = fast.next       # Предыдущий теперь указывает на следующий за текущим
                    fast = None                 # Удаляется текущий
                    fast = slow.next            # Быстрый указывает на следующий за удаленным текущим
                    self.count -= 1             # Обновить счетчик
                else:                           # Если следующего элемента нет за текущим, тогда
                    slow.next = None            # Указатель на текущий удаляется
                    fast = None                 # Удаляется сам элемент
                    self.count -= 1             # Счетчик обновляется
                    self.tail = slow            # Теперь хвост указывает на предыдущий за удаленным
            else:                               # Если ни slow ни fast не указывают на удаляемый элемент
                fast = fast.next                # Сдвинуть на шаг вперед быстрый
                slow = slow.next                # Сдвинуть на шаг вперед медленный

        if self.head.data == value:             # Проверить первый элемент после цикла
            if self.head.next:                  # Если он не один в списке
                self.head = self.head.next      # Продвинуть указатель вперед
                self.count -= 1                 # Обновить счетчик
            else:                               # Если он один
                self.head = self.tail = None    # Значит список теперь пуст
                self.count = 0

    def show(self):                             # Печать списка
        if self.empty():
            return
        temp = self.head
        print("Head -->", end=' ')
        while temp:
            if temp.next:
                print(f"{temp.data} -->", end=' ')
                temp = temp.next
            else:
                print(f"{temp.data} <-- Tail")
                temp = temp.next

    def size(self):                             # Вернуть количество элементов
        return self.count

    def front(self):
        return self.head.data

    def back(self):
        return self.tail.data

    def find(self, value):
        if self.empty():
            return None
        tmp = self.head
        id = 0
        while tmp:
            if tmp.data == value:
                return id
            tmp = tmp.next
            id += 1
        return None

    def reverse(self):
        if not self.head or self.head == self.tail:
            return
        curr = self.head
        prev = temp = None
        while curr:
            temp = curr.next
            curr.next = prev
            prev = curr
            curr = temp
        self.tail = self.head
        self.head = prev

    def sort_bubble(self):
        end = None
        while end != self.head:
            p = self.head
            while p.next != end:
                q = p.next
                if p.data > q.data:
                    p.data, q.data = q.data, p.data
                p = p.next
            end = p

    def sort_insertion(self):
        a = b = p = h = i = None
        i = self.head
        while i:
            a = i
            i = i.next
            b = h
            p = None
            while b and a.data > b.data:
                p = b
                b = b.next
            if not p:
                a.next = h
                h = a
            else:
                a.next = b
                p.next = a
        if h:
            self.head = h

    def sort_selection(self):
        # Hi from c++
        nmin = tmp = None
        p2 = r2 = None
        p1 = r1 = self.head
        while p1:
            nmin = p2 = r2 = p1
            tmp = p1.next
            while tmp:
                if tmp.data < p2.data:
                    r2 = nmin
                    p2 = tmp
                nmin = tmp
                tmp = tmp.next
            if p1 != p2:
                if p1 == self.head:
                    self.head = p2
                else:
                    r1.next = p2

                tmp = p2.next
                if p1 == r2:
                    p2.next = p1
                    p1.next = tmp
                else:
                    nmin = p1.next
                    r1.next = p2
                    r2.next = p1
                    p1.next = tmp
                    p2.next = nmin
                p1 = p2
            r1 = p1
            p1 = p1.next

    def __get_middle(self, node):
        if not node:
            return node
        slow = fast = node
        while fast.next and fast.next.next:
            slow = slow.next
            fast = fast.next.next
        return slow

    def __merge(self, left, right):
        imitation_head = Node()
        current = imitation_head
        while left and right:
            if left.data < right.data:
                current.next = left
                left = left.next
            else:
                current.next = right
                right = right.next
            current = current.next
        if not left:
            current.next = right
        else:
            current.next = left
        return imitation_head.next

    def __merge_sort(self, node):
        if not node or not node.next:
            return node
        middle = self.__get_middle(node)
        left_head = node
        right_head = middle.next
        middle.next = None
        return self.__merge(self.__merge_sort(left_head), self.__merge_sort(right_head))

    def sort_merge(self):
        self.head = self.__merge_sort(self.head)

    def __getitem__(self, index):
        if not self.head or index < 0 or index >= self.count:
            return None
        tmp = self.head
        for i in range(index):
            tmp = tmp.next
        return tmp.data

    def __setitem__(self, key, value):
        if not self.head or key < 0 or key >= self.count:
            return None
        tmp = self.head
        for i in range(key):
            tmp = tmp.next
        tmp.data = value

    def __add__(self, other):
        new_list = Forward_list()
        tmp = self.head
        while tmp:
            new_list.push_back(tmp.data)
            tmp = tmp.next
        tmp = other.head
        while tmp:
            new_list.push_back(tmp.data)
            tmp = tmp.next
        return new_list


# Функция тестирования
def time_test(length):
    my_list = Forward_list()
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