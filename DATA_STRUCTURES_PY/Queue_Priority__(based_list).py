# Priority Queue FIFO -- Очередь с приоритетом на основе связного списка
import random

class Node: pass                                # Класс описывающий узел очереди
class Pqueue:                                   # Класс описывающий очередь
    def __init__(self, data, prior): pass       # Конструктор с параметром и без
    def push(self, elem, prior): pass           # Добавление элементов по приоритету
    def front(self): pass                       # Возвращает первый элемент в очереди, если он есть
    def back(self): pass                        # Возвращает последний элемент
    def pop(self): pass                         # Удаление из начала очереди FIFO
    def clear(self): pass                       # Очистка очереди
    def show(self): pass                        # Печать
    def empty(self): pass                       # true Если пуста, иначе false
    def size(self): pass                        # Возвращает кол-во элементов
"""----------------------------------------------------------------"""

class Node:
    def __init__(self, data, prior):
        self._data = data
        self._prior = prior
        self._next = None

class Pqueue:
    def __init__(self, data=None, prior=None):  # Конструктор с параметром и без
        if data is None and prior is None:      # Если не переданный ни элемент ни приоритет
            self._head = None                   # Инициализация полей null-ами
            self._tail = None
            self._count = 0
        else:                                   # Если элемент и приоритет переданы
            self._count = 1                     # Увеличить счетчик на 1
            node = Node(data, prior)            # Создать новый узел
            self._head = self._tail = node      # И начало и конец очереди указывают на него

    def push(self, elem, prior):                # Добавление элементов по приоритету
        new_node = Node(elem, prior)            # Создать элемент с заданным приоритетом
        if self._head is None:                  # Если это первый добавляемый элемент, то
            self._head = self._tail = new_node  # Тогда и начало и конец указывают на него
            self._count += 1
            return
        temp = self._head                       # Указатель временный на начало очереди
        prev = None                             # Запоминатель адреса
        # Пока есть элементы в очереди и приоритет выше чем у заданного, продвигаться к концу
        while (temp != None) and (temp._prior > prior):
            prev = temp                         # Запомнить адрес предыдущего элемента
            temp = temp._next                   # Продвинуться по очереди вперед
        if temp == None:                        # Если дошли до конца очереди и заданный приоритет был самым низким
            prev._next = new_node               # Добавить это элемент в конец очереди
            self._tail = new_node               # Хвост указывает на него
        else:                                   # Если встретил низший приоритет, значит дальше приоритеты ниже
            if prev == None:                    # Если предыдущий указвает на 0, значит итераций не было т.к приоритет выше
                new_node._next = self._head     # Новый элемент встает вперед очереди
                self._head = new_node           # Голова указывает на новый элемент
            else:                               # Если итерации были, тогда настроить указатели
                new_node._next = temp           # Новый элемент будет указывать на найденное значение
                prev._next = new_node           # А предыдущий будет указывать на новый
        self._count += 1                        # Увеличить счетчик

    def front(self):
        return self._head._data if self._count > 0 else None

    def back(self):
        return self._tail._data if self._count > 0 else None

    def pop(self):                              # Удаление из начала очереди FIFO
        if self._head is None:
            return
        tmp = self._head
        self._head = self._head._next
        del tmp
        self._count -= 1

    def clear(self):
        while self._count:
            self.pop()

    def show(self):
        if self._count == 0:
            print("Queue is empty!")
            return
        tmp = self._head
        while tmp:
            print(f"({tmp._data}:{tmp._prior})", end='<-')
            tmp = tmp._next
        print('')

    def empty(self):
        return self._count == 0

    def size(self):
        return self._count


def main():
    pqu = Pqueue(4, 1)
    for i in range(15):
        pqu.push(i, random.randint(0, 10))
    pqu.show()
    for i in range(5):
        pqu.pop()
    pqu.show()
    print(f"front = {pqu.front()}")
    print(f"front = {pqu.back()}")
    pqu.clear()
    pqu.show()


if __name__ == "__main__":
    main()