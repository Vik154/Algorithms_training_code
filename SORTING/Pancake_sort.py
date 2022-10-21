import random
import time

"""*************Блинная сортировка - pancake_sort*************"""
def flip(arr, i):
    start = 0
    while start < i:
        temp = arr[start]
        arr[start] = arr[i]
        arr[i] = temp
        start += 1
        i -= 1

def findMax(arr, n):
    mi = 0
    for i in range(0,n):
        if arr[i] > arr[mi]:
            mi = i
    return mi

def pancake_sort(arr):
    curr_size = len(arr)
    while curr_size > 1:
        mi = findMax(arr, curr_size)
        if mi != curr_size-1:
            flip(arr, mi)
            flip(arr, curr_size-1)
        curr_size -= 1
"""***********************************************************"""

def create_array(size_element):
    arr = []
    for i in range(size_element):
        arr.append(round(random.random() * 10000))
    return arr


def time_test(size):
    timer = time.time()
    my_array = create_array(size)
    timer = time.time() - timer
    print(f"Заполнение массива: {round(timer, 2)} сек")
    timer = time.time()
    pancake_sort(my_array)
    #my_array = odd_even_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer, 2)} сек")
    #print(my_array)


if __name__ == "__main__":
    time_test(3000)
