# MAX HEAP - Максимальная куча (самый большой ключ находится в корне)
# Ключи родительских узлов всегда больше или равны ключам дочерних узлов
# MIN HEAP - Минимальная куча (самый маленький ключ находится в корне)
# Ключи родительских узлов меньше или равны ключам дочерних узлов
import random

class Heap_min: pass                        # Класс описывающий минимальную кучу (корень самый маленький элемент)
class Heap_max:                             # Класс описывающий кучу (корень самый большой элемент)
    def __init__(self): pass                # Конструктор
    def __get_parent_id(self, ind): pass    # Получить индекс родителя
    def __get_rchild_id(self, ind): pass    # Получить индекс правого потомка
    def __get_lchild_id(self, ind): pass    # Получить индекс левого потомка
    def size(self): pass                    # Получить размер кучи
    def _heapify_down(self, ind): pass      # Проталкивание элемента вниз
    def _heapify_up(self, ind): pass        # Проталкивание элемента вверх
    def push(self, key): pass               # Добавление элемента
    def pop(self): pass                     # Удаление
    def top(self): pass                     # Получить верхний элемент (корень)
"""-----------------------------------------------------------"""


class Heap_max:
    def __init__(self):
        self._heap_elem = []

    def __get_parent_id(self, ind):
        return (ind - 1) // 2

    def __get_rchild_id(self, ind):
        return 2 * ind + 2

    def __get_lchild_id(self, ind):
        return 2 * ind + 1

    def size(self):
        return len(self._heap_elem)

    def _heapify_down(self, ind):
        left = self.__get_lchild_id(ind)    # Получить левого потомка узла с индексом 'id'
        right = self.__get_rchild_id(ind)   # Получить правого потомка узла с индексом 'id'
        largest = ind                       # Запомнить 'id' наибольшего узла
        # Cравниваем Array[id] с его левым и правым дочерними элементами и находим наибольшее значение
        if (left < self.size()) and (self._heap_elem[left] > self._heap_elem[ind]):
            largest = left
        if (right < self.size()) and (self._heap_elem[right] > self._heap_elem[largest]):
            largest = right
        # Если индекс наибольшего и найденного не равны, иначе ничего не делать
        if largest != ind:
            # Поменять местами потомка и родителя
            self._heap_elem[ind], self._heap_elem[largest] = self._heap_elem[largest], self._heap_elem[ind]
            # И вызвать рекурсивно heapify-down для потомка
            self._heapify_down(largest)

    def _heapify_up(self, ind):
        # Ели узел с индексом 'id' и его родитель нарушают свойство кучи
        if ind and (self._heap_elem[self.__get_parent_id(ind)] < self._heap_elem[ind]):
            # Поменять их местами, если свойство кучи нарушено
            self._heap_elem[ind], self._heap_elem[self.__get_parent_id(ind)] = \
                self._heap_elem[self.__get_parent_id(ind)], self._heap_elem[ind]
            # Вызвать heapify-up для родителя
            self._heapify_up(self.__get_parent_id(ind))

    def push(self, key):
        self._heap_elem.append(key)  # Вставить новый элемент в конец вектора
        index = self.size() - 1      # Получить индекс элемента
        self._heapify_up(index)      # Вызов heapify-up от index

    def pop(self):
        try:
            # Если в куче нет элементов, бросить исключение
            if self.size() == 0:
                raise Exception("Heap is empty, stupid man!")
            self._heap_elem[0] = self._heap_elem.pop()        # Заменить корень кучи последним элементом и удалить замененный
            self._heapify_down(0)                             # Вызвать heapify-down для корня
        except Exception as msg:                              # Ловим и печатаем исключение
            print(msg)

    def top(self):
        try:
            # Если в куче нет элементов, бросить исключение
            if self.size() == 0:
                raise Exception("Heap is empty, stupid man!")
            return self._heap_elem[0]
        except Exception as msg:                              # Ловим и печатаем исключение
            print(msg)


class Heap_min:
    def __init__(self):
        self._heap_elem = []

    def __get_parent_id(self, ind):
        return (ind - 1) // 2

    def __get_rchild_id(self, ind):
        return 2 * ind + 2

    def __get_lchild_id(self, ind):
        return 2 * ind + 1

    def size(self):
        return len(self._heap_elem)

    def _heapify_down(self, ind):
        left = self.__get_lchild_id(ind)    # Получить левого потомка узла с индексом 'id'
        right = self.__get_rchild_id(ind)   # Получить правого потомка узла с индексом 'id'
        smallest = ind                      # Запомнить 'id' наименьшего узла
        # Cравниваем Array[id] с его левым и правым дочерними элементами и находим наибольшее значение
        if (left < self.size()) and (self._heap_elem[left] < self._heap_elem[ind]):
            smallest = left
        if (right < self.size()) and (self._heap_elem[right] < self._heap_elem[smallest]):
            smallest = right
        # Если индекс наибольшего и найденного не равны, иначе ничего не делать
        if smallest != ind:
            # Поменять местами потомка и родителя
            self._heap_elem[ind], self._heap_elem[smallest] = self._heap_elem[smallest], self._heap_elem[ind]
            # И вызвать рекурсивно heapify-down для потомка
            self._heapify_down(smallest)

    def _heapify_up(self, ind):
        # Ели узел с индексом 'id' и его родитель нарушают свойство кучи
        if ind and (self._heap_elem[self.__get_parent_id(ind)] > self._heap_elem[ind]):
            # Поменять их местами, если свойство кучи нарушено
            self._heap_elem[ind], self._heap_elem[self.__get_parent_id(ind)] = \
                self._heap_elem[self.__get_parent_id(ind)], self._heap_elem[ind]
            # Вызвать heapify-up для родителя
            self._heapify_up(self.__get_parent_id(ind))

    def push(self, key):
        self._heap_elem.append(key)  # Вставить новый элемент в конец вектора
        index = self.size() - 1      # Получить индекс элемента
        self._heapify_up(index)      # Вызов heapify-up от index

    def pop(self):
        try:
            # Если в куче нет элементов, бросить исключение
            if self.size() == 0:
                raise Exception("Heap is empty, stupid man!")
            self._heap_elem[0] = self._heap_elem.pop()        # Заменить корень кучи последним элементом и удалить замененный
            self._heapify_down(0)                             # Вызвать heapify-down для корня
        except Exception as msg:                              # Ловим и печатаем исключение
            print(msg)

    def top(self):
        try:
            # Если в куче нет элементов, бросить исключение
            if self.size() == 0:
                raise Exception("Heap is empty, stupid man!")
            return self._heap_elem[0]
        except Exception as msg:                              # Ловим и печатаем исключение
            print(msg)


def main():
    iheap = Heap_max()
    dheap = Heap_max()
    imin = Heap_min()
    dmin = Heap_min()

    for i in range(20):
        iheap.push(random.randint(0, 100))
        imin.push(random.randint(0, 100))
        dheap.push(random.randint(0, 100) * 0.28)
        dmin.push(random.randint(0, 100) * 0.28)

    print("Integer max heap: ", end='\t')
    for i in range(20):
        print(iheap.top(), end=' ')
        iheap.pop()
    print("\nInteger min heap: ", end='\t')
    for i in range(20):
        print(imin.top(), end=' ')
        imin.pop()
    print("\nDouble max heap: ", end='\t')
    for i in range(20):
        print(round(dheap.top(), 2), end=' ')
        dheap.pop()
    print("\nDouble min heap: ", end='\t')
    for i in range(20):
        print(round(dmin.top(), 2), end=' ')
        dmin.pop()
    print("\nChecking for emptiness:")
    dheap.top()
    iheap.top()


if __name__ == "__main__":
    main()