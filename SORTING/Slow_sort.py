import random
import time

"""**************Вялая сортировка - slow_sort**************"""
def slow_rec(data, i, j):
    if i >= j:
        return data
    m = (i + j) // 2
    slow_rec(data, i, m)
    slow_rec(data, m + 1, j)
    if data[m] > data[j]:
        data[m], data[j] = data[j], data[m]
    slow_rec(data, i, j - 1)

def slow_sort(data):
    return slow_rec(data, 0, len(data) - 1)
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
    slow_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")
    #print(my_array)

if __name__ == "__main__":

    time_test(100)
