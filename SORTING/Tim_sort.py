import random
import time

"""***************Гибридная сортировка - tim_sort*********"""
def insertion_sort(array, left, right):
    for i in range(left + 1, right + 1):
        temp = array[i]
        j = i - 1
        while temp < array[j] and j >= left:
            array[j + 1] = array[j]
            j -= 1
        array[j + 1] = temp
    return array

def merge(array, l, m, r):
    array_length1 = m - l + 1
    array_length2 = r - m
    left = []
    right = []
    for i in range(0, array_length1):
        left.append(array[l + i])
    for i in range(0, array_length2):
        right.append(array[m + 1 + i])

    i = 0
    j = 0
    k = l

    while j < array_length2 and i < array_length1:
        if left[i] <= right[j]:
            array[k] = left[i]
            i += 1
        else:
            array[k] = right[j]
            j += 1
        k += 1

    while i < array_length1:
        array[k] = left[i]
        k += 1
        i += 1

    while j < array_length2:
        array[k] = right[j]
        k += 1
        j += 1

def tim_sort(array):
    size = len(array)
    RUN = len(array)
    for i in range(0, size, RUN):
        end = min(i + RUN - 1, size - 1)
        insertion_sort(array, i, end)

    step = RUN
    for i in range(step, size, 2 * step):
        for j in range(0, size, 2 * step):
            mid = j + size - 1
            right = min((j + 2 * step -1), (size - 1))
            if mid < right:
                merge(array, j, mid, right)
"""/*****************************************************/"""

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
    tim_sort(my_array)
    #my_array = TimSort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer, 2)} сек")
    #print(my_array)

if __name__ == "__main__":
    time_test(5_000)
