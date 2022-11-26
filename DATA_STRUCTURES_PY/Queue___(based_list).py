# /*Queue FIFO - очередь на основе списка*/
class Queue:                        # Класс описывающий очередь
    def __init__(self, data): pass  # Конструктор
    def push(self, elm): pass       # Добавить элемент в конец очереди
    def pop(self): pass             # Удалить первый элемент
    def show(self): pass            # Печать
    def empty(self): pass           # true если пуста, иначе false
    def size(self): pass            # Кол-во элементов
    def back(self): pass            # Последний элемент в очереди
    def front(self): pass           # Первый элемент
"""-------------------------------------------"""

class Queue:
    def __init__(self, data=None):
        if data is None:
            self._size = 0
            self._node = []
        else:
            self._size = 1
            self._node = [data]

    def push(self, elm):
        self._node.append(elm)
        self._size += 1

    def pop(self):
        if self._size == 0:
            return
        self._node.pop()
        self._size -= 1

    def show(self):
        if self._size == 0:
            return
        for i in range(self._size):
            print(f"({self._node[i]})", end="<-")
        print('')

    def empty(self):
        return self._size == 0

    def size(self):
        return self._size

    def back(self):
        return self._node[self._size - 1] if self._size >= 1 else None

    def front(self):
        return self._node[0] if self._size > 0 else None


def main():
    que = Queue()
    for i in range(1, 16):
        que.push(i)
    que.show()
    for i in range(5):
        que.pop()
    que.show()

if __name__ == "__main__":
    main()