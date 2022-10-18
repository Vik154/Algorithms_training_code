from random import random
import time

"""*********************Сортировка слиянием********************"""
def merge_sort(array):
    if len(array) > 1:
        middle = len(array) // 2
        left = array[:middle]
        right = array[middle:]
        merge_sort(left)
        merge_sort(right)
        i = j = k = 0
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                array[k] = left[i]
                i+=1
            else:
                array[k] = right[j]
                j+=1
            k+=1
        while i < len(left):
            array[k] = left[i]
            i+=1
            k+=1
        while j < len(right):
            array[k] = right[j]
            j+=1
            k+=1
"""***********************************************************"""

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
    merge_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")

if __name__ == "__main__":
    time_test(100_000)
