import random
import time

"""*********Чётно-нечётная сортировка - odd_even_sort*********"""
def odd_even_sort(data):
    n = len(data)
    isSorted = 0
    while isSorted == 0:
        isSorted = 1
        for i in range(1, n - 1, 2):
            if data[i] > data[i + 1]:
                data[i], data[i + 1] = data[i + 1], data[i]
                isSorted = 0
        for i in range(0, n - 1, 2):
            if data[i] > data[i + 1]:
                data[i], data[i + 1] = data[i + 1], data[i]
                isSorted = 0
    return data
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
    odd_even_sort(my_array)
    #my_array = odd_even_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer, 2)} сек")
    #print(my_array)

if __name__ == "__main__":
    time_test(2_000)
