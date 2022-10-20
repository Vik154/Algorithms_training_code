import random
import time

"""*********Сортировка перемешиванием - shaker_sort*********"""
def shaker_sort(array):
    left = 0
    right = len(array) - 1
    while left <= right:
        for i in range(right, left, -1):
            if array[i-1] > array[i]:
                array[i], array[i - 1] = array[i - 1], array[i]
        left += 1
        for i in range(left, right + 1):
            if array[i-1] > array[i]:
                array[i], array[i - 1] = array[i - 1], array[i]
        right -= 1
"""*********************************************************"""

def create_array(size_element):
    arr = []
    for i in range(size_element):
        arr.append(round(random.random()*10000))
    return arr

def time_test(size):
    timer = time.time()
    my_array = create_array(size)
    timer = time.time() - timer
    print(f"Заполнение массива: {round(timer, 2)} сек")
    timer = time.time()
    shaker_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")
    #print(my_array)


if __name__ == "__main__":

    time_test(1000)
