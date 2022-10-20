import random
import time

"""*************Битонная сортировка - bitonic_sort************"""
def compare_swap(a, i, j, d):
    if (d == 1 and a[i] > a[j]) or (d == 0 and a[i] < a[j]):
        a[i], a[j] = a[j], a[i]

def merge(a, l, cnt, d):
    if cnt > 1:
        k = int(cnt / 2)
        for i in range(l, l + k):
            compare_swap(a, i, i + k, d)
        merge(a, l, k, d)
        merge(a, l + k, k, d)

def bitonic_sort(a, l, cnt, d):
    if cnt > 1:
        k = int(cnt / 2)
        bitonic_sort(a, l, k, 1)
        bitonic_sort(a, l + k, k, 0)
        merge(a, l, cnt, d)

def sort(a, N, u):
    bitonic_sort(a, 0, N, u)
"""***********************************************************"""

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
    sort(my_array, len(my_array), 1)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")
    #print(my_array)

if __name__ == "__main__":

    time_test(10_000)