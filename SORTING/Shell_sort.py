import random
import time


"""*********Сортировка Шелла - shell_sort_V_1.0*********"""
def shell_sort(array):
    inc = len(array) // 2
    while inc:
        for i, el in enumerate(array):
            while i >= inc and array[i - inc] > el:
                array[i] = array[i - inc]
                i -= inc
            array[i] = el
        inc = 1 if inc == 2 else int(inc * 5.0 / 11)
"""*****************************************************"""

"""*********Сортировка Шелла - shell_sort_V_2.0*********"""
def shell_sort2(array):
    size = len(array)
    interval = size // 2
    while interval > 0:
        for i in range(interval, size):
            temp = array[i]
            j = i
            while j >= interval and array[j - interval] > temp:
                array[j] = array[j - interval]
                j -= interval
            array[j] = temp
        interval //= 2
"""*****************************************************"""

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
    shell_sort2(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")
    #print(my_array)


if __name__ == "__main__":

    time_test(100_000)