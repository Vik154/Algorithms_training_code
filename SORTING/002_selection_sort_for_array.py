from random import random
import time

""""*************Сортировка выбором*********************"""
def selection_sort(array):
    n = len(array)
    for i in range(n - 1):
        min_index = i
        for j in range(i + 1, n):
            if array[j] < array[min_index]:
                min_index = j
        if min_index != i:
            temp = array[i]
            array[i] = array[min_index]
            array[min_index] = temp
"""*********************--******************************"""

# Создание массива заданного количества
def create_array(size_element):
    arr = []
    for i in range(size_element):
        arr.append(round(random()*10000))
    return arr

def time_test(size):
    timer = time.time()
    my_array = create_array(size)
    timer = time.time() - timer
    print(f"Заполнение массива: {round(timer, 2)} сек")
    timer = time.time()
    selection_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")

if __name__ == "__main__":
    time_test(5_000)
