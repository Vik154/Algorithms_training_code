from random import random
import time

def bubble_sort(array):
    n = len(array)
    for i in range(n):
        for j in range(n - 1 - i):
            if array[j] > array[j + 1]:
                tmp = array[j]
                array[i] = array[j + 1]
                array[j + 1] = tmp

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
    bubble_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")

if __name__ == "__main__":
    time_test(5_000)
