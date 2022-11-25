# Имитация статического массива
class Array:                     # Класс описывающий обычный статический массив С
    def __init__(self): pass     # Конструктор
    def show(self): pass         # Вывод на экран
    def fill(self, elm): pass    # fill - Заменяет все элементы указанным значением.
    def data(self): pass         # data - Получает адрес первого элемента.
    def size(self): pass         # size - Подсчитывает количество элементов.
    def front(self): pass        # front - Обращается к первому элементу.
    def back(self): pass         # back - Обращается к последнему элементу.
    def at(self, index): pass    # at - Обращается к элементу в указанной позиции.
    def __getitem__(self): pass  # [id] - Обращение по индексу
    def __setitem__(self): pass  # [id] - Замена значений по валидному индексу
"""-----------------------------------------------------------------------------"""

class Array:
    def __init__(self, size, data=None):
        self._size = size
        self._arr = [data] * size

    # Вывод на экран
    def show(self):
        print(self._arr)

    # fill - Заменяет все элементы указанным значением.
    def fill(self, elm):
        if self._size < 1:
            return
        for i in range(self._size):
            self._arr[i] = elm

    # data - Получает адрес первого элемента.
    def data(self):
        return id(self._arr[0])

    # size - Подсчитывает количество элементов.
    def size(self):
        return self._size

    # front - Обращается к первому элементу.
    def front(self):
        return self._arr[0]

    # back - Обращается к последнему элементу.
    def back(self):
        return self._arr[self._size - 1]

    # at - Обращается к элементу в указанной позиции.
    def at(self, index):
        return self._arr[index]

    # [id] - Обращение по индексу
    def __getitem__(self, item):
        return self._arr[item]

    # [id] - Замена значений по валидному индексу
    def __setitem__(self, key, value):
        self._arr[key] = value


def main():
    inarray = Array(15, 5)
    flarray = Array(15, 0.35)
    charray = Array(15, 'w')
    print(f"Integer = ", end='')
    inarray.show()
    print(f"Double  = ", end='')
    flarray.show()
    print(f"Char    = ", end='')
    charray.show()
    print(f"Fill array on 99: ", end='')
    inarray.fill(99)
    inarray[14] = 33
    inarray[0] = 7
    inarray.show()
    print(f"Back  = {inarray.back()}")
    print(f"Front = {inarray.front()}")
    print(f"At[]  = {inarray.at(5)}")
    print(f"Reffr = {inarray.data()}")


if __name__ == "__main__":
    main()