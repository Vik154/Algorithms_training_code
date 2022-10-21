import random
import time

"""*************Голубинная сортировка - pigeonhole_sort*************"""
def pigeonhole_sort(array):
    minimum = min(array)
    maximum = max(array)
    s = maximum - minimum + 1
    h = [0] * s  # holes
    for x in array:
        assert type(x) is int, "integers only please"
        h[x - minimum] += 1
    i = 0
    for c in range(s):
        while h[c] > 0:
            h[c] -= 1
            array[i] = c + minimum
            i += 1
"""*****************************************************************"""

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
    pigeonhole_sort(my_array)
    #my_array = odd_even_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer, 2)} сек")
    #print(my_array)


if __name__ == "__main__":
    time_test(1_000_000)
