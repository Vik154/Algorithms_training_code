import random
import time

"""***********Интроспективная сортировка - intro_sort********"""
def insert_isort(array, begin=0, end=None):
    if end == None:
        end = len(array) - 1
    for i in range(begin, end):
        j = i
        to_change = array[i]
        while (j != begin and array[j - 1] > to_change):
            array[j] = array[j - 1]
            j -= 1
        array[j] = to_change
    return array

def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2

    if l < n and arr[i] < arr[l]:
        largest = l
    if r < n and arr[largest] < arr[r]:
        largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_isort(arr):
    n = len(arr)

    for i in range(n // 2, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)
    return arr

def median_elem(array, low_id, mid_id, high_id):
    if ((array[low_id] > array[mid_id]) != (array[low_id] > array[high_id])):
        return array[low_id]
    elif ((array[mid_id] > array[low_id]) != (array[mid_id] > array[high_id])):
        return array[mid_id]
    else:
        return array[high_id]

def partition_isort(array, low, high, pivot):
    i = low
    j = high
    while True:
        while (array[i] < pivot):
            i += 1
        j -= 1
        while (pivot < array[j]):
            j -= 1
        if i >= j:
            return i
        array[i], array[j] = array[j], array[i]
        i += 1

def intro_sort(array):
    max_depth = 2 * (len(array).bit_length() - 1)
    size_hold = 16
    return intro_util(array, 0, len(array), size_hold, max_depth)

def intro_util(array, start, end, size_hold, depth_limit):
    while (end - start > size_hold):
        if (depth_limit == 0):
            return heap_isort(array)
        depth_limit -= 1

        median = median_elem(array, start, start +
                             ((end - start) // 2) + 1, end - 1)
        p = partition_isort(array, start, end, median)
        intro_util(array, p, end, size_hold, depth_limit)
        end = p
    return insert_isort(array, start, end)
"""**********************************************************"""

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
    intro_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer, 2)} сек")
    print(my_array)


if __name__ == "__main__":
    time_test(100)
