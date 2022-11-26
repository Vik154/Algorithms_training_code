# /*Динамический массив - имитация вектора*/
class Darray:                                   # Класс описывающий динамический массив
    def __init__(self, size, data): pass        # Конструктор
    def push_back(self, elm): pass              # Добавление элемента в конец
    def insert(self, elm, ind): pass            # Вставка элемента по заданному индексу со смещением вправо
    def resize(self, count, elem): pass         # Определяет новый размер массива (заполнение массива элементами)
    def reserve(self, sz): pass                 # Перевыделение вместительности
    def pop_back(self): pass                    # Удаление с конца
    def erase(self, elem): pass                 # Удаление по значению
    def clear(self): pass                       # Очистка массива
    def empty(self): pass                       # True если пуст, иначе false
    def back(self): pass                        # Возвращает последний элемент массива
    def front(self): pass                       # Возвращает первый элемент массива
    def data(self): pass                        # Возвращает адрес 1-го элемента
    def at(self, ind): pass                     # Возвращает значение массива по индексу
    def __getitem__(self, ind): pass            # Получить значение по индексу через [id]
    def __setitem__(self, ind, value): pass     # Заменить значение по индексу [id] = value
    def show(self): pass                        # Печать массива
    def size(self): pass                        # Размер массива
    def capacity(self): pass                    # Вместительность массива
"""-------------------------------------------------------------------------"""

class Darray:
    def __init__(self, size=2, data=None):
        if data is None:                        # Если при создании данных нет, тогда
            self._size = 0                      # Счетчик элементов == 0, т.к элементов нет
            self._capacity = size               # А вместительность равна либо 2 либо, переданной в параметре
        if data is not None:                    # Если надо заполнить массив значениями, тогда
            self._size = size                   # Счетчик элементов актуален и равен либо дефолту, либо заданному
            self._capacity = 0                  # Равна 0, потом будет перевыделение памяти при необходимости
        self._array = [data] * size             # Заполнить массив значениями

    def push_back(self, elm):                   # Добавление элемента в конец
        if self._capacity > 0:                  # Если еще есть элемент в массиве, тогда
            self._array[self._size] = elm		# Добавить за последним существующим
            self._size += 1         			# Увеличить счетчик
            self._capacity -= 1				    # Уменьшить вместимость
        else:                                   # Если capacity == 0, нужно увеличить массив,
            # В старый массив добавить еще пространства увеличенного вдове (по типу вектора)
            self._array = self._array + ([None] * (self._size * 2))
            self._array[self._size] = elm       # Добавить элемент
            self._capacity = self._size - 1     # Уменьшить вместительность
            self._size += 1                     # Увеличить счетчик элементов

    def insert(self, elm, ind):                 # Вставка элемента по заданному индексу со смещением вправо
        if ind >= self._size:                   # Если индекс >= кол-ву элементов в массиве, тогда
            self.push_back(elm)                 # Вставить в конец
            return                              # И вернуться
        if ind < 0:                             # Если индекс кривой
            return                              # Ничего не делать
        new_arr = self._array + [None]          # Создать временный массив, для смещения всех элементов после индекса
        flag = True                             # Флаг, указывающий на найденный индекс после которого нужно смещение
        for i in range(self._size):             # Поэлементный обход всего массива
            if flag is False:                   # Если флаг опущен, значит надо делать смещение вправо на 1
                new_arr[i + 1] = self._array[i] # Сдвиг на 1 элемент вправо
            if flag and i != ind:               # Если флаг поднят и индекс ещё не найден, тогда
                new_arr[i] = self._array[i]     # Делать обычное копирование
            if flag and i == ind:               # Если встретился индекс, по которому нужно добавить элемент
                new_arr[i] = elm                # Добавить этот элемент
                new_arr[i + 1] = self._array[i] # Добавить элемент по i индексу уже со сдвигом вправо
                flag = False                    # Опустить флаг, чтобы дальше добавлять со смещением

        if self._capacity == 0:                 # Проверить, если старый массив был заполнен, тогда
            self._array = new_arr               # Скопировать новый массив со сдвигом на 1 вправо
            del new_arr                         # Удалить временный массив, он не нужен
            self._capacity = 0                  # Вместительность также 0, т.е. он по-прежнему полон
            self._size += 1                     # Увеличился счетчик на 1 добавленный элемент
            return                              # Вернуться
        # Если еще было место в массиве, тогда
        self._array = new_arr                   # Скопировать новый массив со сдвигом на 1 вправо
        del new_arr                             # Удалить его
        self._capacity -= 1                     # Уменьшить вместительность
        self._size += 1                         # Увеличить счетчик

    def resize(self, count, elem):              # Определяет новый размер массива (заполнение массива элементами)
        if count <= self._size or count < 0:    # Если кол-во перевыделяемой вместительности < 0 или размера массива
            return                              # Ничего не делать
        if self._size == 0:                     # Если элементов в массиве нет, тогда
            for i in range(count):              # Заполнить его элементами
                self.push_back(elem)
            return
        for i in range(self._size, count):      # Если все корректно, тогда начать за последним элементом
            self.push_back(elem)                # Добавлять необходимое кол-во элементов

    def reserve(self, sz):                      # Перевыделение вместительности
        if sz <= self._capacity:                # Если текущая вместительность больше или равна заданной
            return                              # Ничего не делать
        self._array = self._array + [None] * sz # Увеличить вместительность текущего массива
        self._capacity = sz                     # Вместительность стала равной заданной

    def pop_back(self):                         # Удаление с конца
        if self._size == 0:                     # Если элементов нет
            return
        self._array[self._size-1] = None       # Заполнить ячейку null и не позволять обращаться к ним
        self._size -= 1
        self._capacity += 1

    def erase(self, elem):                      # Удаление по значению
        if self._size == 0:                     # Если нет элементов, вернуться
            return
        ind = -1                                # Индекс найденного элемента
        for i in range(self._size):             # Пройти по массиву
            if elem == self._array[i]:          # Запомнить индекс элемента
                ind = i
                break
        if (ind >= 0) and (ind < self._size):   # Если индекс корректный, элемент был найден
            self._array[ind] = None             # Стереть элемент
            tmp_arr = []                        # Временный массив для сдвига элементов
            for i in range(self._size):         # Пройти па массиву
                if self._array[i] is not None:  # Скопировать поэлементно
                    tmp_arr.append(self._array[i])
            self._size -= 1                     # Уменьшить размер
            self._capacity += 1                 # Вместительность увеличить
            self._array = tmp_arr               # Новый массив без удаленного элемента
            del tmp_arr                         # Удалить ненужный

    def clear(self):
        while self._size != 0:
            self.pop_back()

    def empty(self):
        return self._size == 0

    def back(self):
        return self._array[self._size - 1] if self._size != 0 else None

    def front(self):
        return self._array[0] if self._size != 0 else None

    def data(self):
        return id(self._array[0]) if self._size != 0 else None

    def at(self, ind):
        return self._array[ind] if self._size > ind else None

    def __getitem__(self, ind):
        return self._array[ind] if self._size > ind else None

    def __setitem__(self, ind, value):
        if ind >= self._size:
            return
        self._array[ind] = value

    def show(self):
        if self._size == 0:
            print("Array is empty!")
            return
        print('[ ', end='')
        for i in range(self._size):
            print(self._array[i], end=', ')
        print(']')

    def size(self):
        return self._size

    def capacity(self):
        return self._capacity


def main():
    inarr = Darray(5, 3)
    charr = Darray(5, 'w')
    flarr = Darray()

    for i in range(15):
        inarr.push_back(i)
        charr.insert(chr(i+67), i)
        flarr.push_back(round(i * 0.28, 2))

    inarr.show()
    charr.show()
    flarr.show()

    for i in range(5):
        inarr.erase(i)
        charr.pop_back()
    inarr.show()
    charr.show()


if __name__ == "__main__":
    main()