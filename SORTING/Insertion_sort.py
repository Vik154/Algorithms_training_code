from random import random
import time

"""***************Сортировка вставками**************"""
def insertion_sort(array):
    n = len(array)
    for i in range(1, n):
        current_value = array[i]
        j = i - 1
        while j >= 0:
            if current_value < array[j]:
                array[j+1] = array[j]
                array[j] = current_value
                j = j - 1
            else:
                break
"""**************************************************"""

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
    insertion_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")


if __name__ == "__main__":
    time_test(5_000)
