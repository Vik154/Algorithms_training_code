import random
import time

"""**********Итеративный бинарный поиск - binary_search**********"""
def binary_search(array, item):
    low = 0                                 # Начало поиска (указатель на 0-ой индекс массива)
    high = len(array) - 1                   # Конец поиска (указатель на последний элемент)

    while low <= high:                      # Пока указатели не встретились, выполнять следующую логику
        mid = low + (high - low) // 2       # Индекс середины массива
        if item == array[mid]:              # Если искомый элемент найден, вернуть индекс этого элемента
            return mid
        elif item > array[mid]:             # Если искомый больше среднего, значит искать справа
            low = mid + 1                   # Левый указатель теперь указывает на середину массива - 1
        else:                               # Если искомый элемент меньше среднего
            high = mid - 1                  # Сдвинуть правый указатель на середину - 1
    return None                             # Если элемент не нашёлся - вернуть ничего
"""**************************************************************"""

"""**********Рекурсивный бинарный поиск - binary_search**********"""
def binary_search_recursive(array, elem, start=0, end=None):
    if end is None:
        end = len(array) - 1
    if start > end:
        return None
    mid = (start + end) // 2
    if elem == array[mid]:
        return mid
    if elem < array[mid]:
        return binary_search_recursive(array, elem, start, mid - 1)
    # elem > arr[mid]
    return binary_search_recursive(array, elem, mid + 1, end)
"""**************************************************************"""

# Функция тестирования
def time_test(length):
    array_int = [round(random.random()*100) for i in range(length)]
    array_float = [round(random.random()*100, 2) for i in range(length)]
    array_char = [chr(random.randint(ord('a'), ord('z'))) for i in range(length)]

    array_int.sort()
    array_float.sort()
    array_char.sort()

    timer = time.perf_counter()
    id_int = binary_search(array_int, round(random.random()*100))
    t_int = time.perf_counter() - timer

    timer = time.perf_counter()
    id_float = binary_search(array_float, round(random.random()*100, 2))
    t_float = time.perf_counter() - timer

    tr = time.perf_counter()
    id_char = binary_search(array_char, chr(random.randint(ord('a'), ord('z'))))
    t_char = time.perf_counter() - tr

    print(f"Integer_id = {id_int} --> time: {t_int:0.5f}\nFloat_id = {id_float} --> time: {t_float:0.5f}")
    print(f"Char_id = {id_char} --> time: {t_char:0.5f}")


if __name__ == "__main__":
    #main()
    time_test(100_000)