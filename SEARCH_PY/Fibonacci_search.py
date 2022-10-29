import random

# Поиск фибоначчи в упорядоченном массиве
def fibonacci_search(array, value):
    # Инициализация чисел фибоначчи
    fibo_1 = 0                          # Первое число (m-2)
    fibo_2 = 1                          # Второе число (m-1)
    fibo_3 = fibo_1 + fibo_2            # Третье число (m)
    length = len(array)                 # Длина массива

    while fibo_3 < length:              # Пока 3 - ье число фибоначчи меньше длины массива
        fibo_1 = fibo_2                 # Искать последовательность чисел
        fibo_2 = fibo_3
        fibo_3 = fibo_1 + fibo_2

    offset = -1                                     # Смещение - это конец исключенного диапазона спереди
    while fibo_3 > 1:                               # Цикл выполняется до тех пор, пока есть элементы для проверки
        index = min(offset + fibo_1, length - 1)    # Проверка на валидность, принадлежит ли индекс заданному диапозону
        if array[index] < value:                    # Если искомое значение больше чем значение массива по этому индексу
            fibo_3 = fibo_2                         # тогда сократить массив на данный индекс
            fibo_2 = fibo_1
            fibo_1 = fibo_3 - fibo_2
            offset = index
        elif array[index] > value:                  # Если искомое значение меньше, значения по заданному индексу
            fibo_3 = fibo_1                         # тогда обрезать массив справа и сместиться левее
            fibo_2 = fibo_2 - fibo_1
            fibo_1 = fibo_3 - fibo_2
        else:                                       # Если элемент найден вернуть его индекс
            return index

    if (fibo_2 and array[offset + 1] == value):     # Сравнение последнего элемента
        return offset + 1

    return -1                                       # Если элемент не найден вернуть - 1


def search_test(size):
    arr = [random.randint(-100, 100) for _ in range(size)]
    arr.sort()
    print(arr)
    id = fibonacci_search(arr, random.randint(-100, 100))
    print(id)

if __name__ == "__main__":
    search_test(200)