"""Stack - реализация стека на основе массива"""
import random

"""**********************************************************************************"""
class Stack:
    def __init__(self): pass            # Конструктор
    def push(self): pass                # Добавляет элемент в конец (вершину)
    def pop(self): pass                 # Удаляет элемент из вершины
    def top(self): pass                 # Возвращает значение в вершине стека
    def empty(self): pass               # Возвращает true если элементы есть, иначе false
    def size(self): pass                # Возвращает размер стека
    def __add__(self, other): pass      # Сложение стеков
    def __lt__(self, other): pass       # Меньше чем        p1 < p2    p1.__lt__(p2)
    def __le__(self, other): pass       # Меньше или равно  p1 <= p2   p1.__le__(p2)
    def __eq__(self, other): pass       # Равно             p1 == p2   p1.__eq__(p2)
    def __ne__(self, other): pass       # Не равно          p1 != p2   p1.__ne__(p2)
    def __gt__(self, other): pass       # Больше чем        p1 > p2    p1.__gt__(p2)
    def __ge__(self, other): pass       # Больше или равно  p1 >= p2   p1.__ge__(p2)
"""**********************************************************************************"""

class Stack:
    def __init__(self, size=10):
        self.array = [] * size          # Массив для хранения элементов
        self.count = 0                  # Счётчик элементов

    def push(self, value):
        self.array.append(value)        # Добавить значение в стек
        self.count += 1                 # Увеличить счётчик элементов

    def pop(self):
        if len(self.array) != 0:        # Если есть элементы в стеке
            self.array.pop()            # Удалить верхний
            self.count -= 1

    def top(self):
        if len(self.array) != 0:        # Если есть элементы в стеке, вернуть самый верхний
            return self.array[self.count - 1]
        else:
            return None

    def empty(self):
        if len(self.array) != 0:        # Если стек не пуст, вернуть true, иначе false
            return True
        else:
            return False

    def size(self):                     # Вернуть размер стека
        return len(self.array)

    def __add__(self, other):           # Прибавить правый стек к левому и левый изменить
        self.array = self.array + other.array
        self.count += len(other.array)
        return self.array

    def __lt__(self, other):           # Меньше чем        p1 < p2    p1.__lt__(p2)
        return len(self.array) < len(other.array)

    def __le__(self, other):           # Меньше или равно  p1 <= p2   p1.__le__(p2)
        return len(self.array) <= len(other.array)

    def __eq__(self, other):           # Равно             p1 == p2   p1.__eq__(p2)
        return len(self.array) == len(other.array)

    def __ne__(self, other):           # Не равно          p1 != p2   p1.__ne__(p2)
        return len(self.array) != len(other.array)

    def __gt__(self, other):           # Больше чем        p1 > p2    p1.__gt__(p2)
        return len(self.array) > len(other.array)

    def __ge__(self, other):           # Больше или равно  p1 >= p2   p1.__ge__(p2)
        return len(self.array) >= len(other.array)

def main():
    stack_1 = Stack()
    stack_2 = Stack()
    for i in range(20):
        stack_1.push(random.randint(0, 100))
        stack_2.push(random.randint(ord('A'), ord('Z')))

    print(f"Stack int --> ", end=' ')
    for i in range(20):
        print(f"{stack_1.top()} -> ", end=' ')
        stack_1.pop()

    print(f"\nStack char --> ", end=' ')
    for i in range(20):
        print(f"{chr(stack_2.top())} -> ", end=' ')
        stack_2.pop()


if __name__ == "__main__":
    main()