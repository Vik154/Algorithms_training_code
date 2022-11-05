"""Stack - реализация стека на основе списка"""
import random
"""**********************************************************************************"""
class Node: pass                        # Структура односвязного списка
class Stack:
    def __init__(self): pass            # Конструктор
    def push(self): pass                # Добавляет элемент в конец (вершину)
    def empty(self): pass               # Возвращает true если элементы есть, иначе false
    def size(self): pass                # Возвращает размер стека
    def top(self): pass                 # Возвращает значение в вершине стека
    def pop(self): pass                 # Удаляет элемент из вершины
    def __str__(self): pass             # Строковое представление стека
    def __lt__(self, other): pass       # Меньше чем        p1 < p2    p1.__lt__(p2)
    def __le__(self, other): pass       # Меньше или равно  p1 <= p2   p1.__le__(p2)
    def __eq__(self, other): pass       # Равно             p1 == p2   p1.__eq__(p2)
    def __ne__(self, other): pass       # Не равно          p1 != p2   p1.__ne__(p2)
    def __gt__(self, other): pass       # Больше чем        p1 > p2    p1.__gt__(p2)
    def __ge__(self, other): pass       # Больше или равно  p1 >= p2   p1.__ge__(p2)
"""**********************************************************************************"""


class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class Stack:
    def __init__(self):
        self.head = Node("head")
        self.size = 0

    def push(self, value):
        node = Node(value)
        node.next = self.head.next
        self.head.next = node
        self.size += 1

    def empty(self):
        return self.size == 0

    def size(self):
        return self.size

    def top(self):
        if self.empty():
            return None
        return self.head.next.value

    def pop(self):
        if self.empty():
            return None
        remove = self.head.next
        self.head.next = self.head.next.next
        self.size -= 1
        return remove.value

    def __str__(self):
        cur = self.head.next
        out = ""
        while cur:
            out += str(cur.value) + "->"
            cur = cur.next
        return out[:-3]

    def __lt__(self, other):           # Меньше чем        p1 < p2    p1.__lt__(p2)
        return self.size < other.size

    def __le__(self, other):           # Меньше или равно  p1 <= p2   p1.__le__(p2)
        return self.size <= other.size

    def __eq__(self, other):           # Равно             p1 == p2   p1.__eq__(p2)
        return self.size == other.size

    def __ne__(self, other):           # Не равно          p1 != p2   p1.__ne__(p2)
        return self.size != other.size

    def __gt__(self, other):          # Больше чем        p1 > p2    p1.__gt__(p2)
        return self.size > other.size

    def __ge__(self, other):          # Больше или равно  p1 >= p2   p1.__ge__(p2)
        return self.size >= other.size

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