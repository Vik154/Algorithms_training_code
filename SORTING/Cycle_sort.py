import random
import time

"""************Цикличная сортировка - cycle_sort************"""
def cycle_sort(array):
    for cycleStart in range(0, len(array) - 1):
        value = array[cycleStart]
        pos = cycleStart
        for i in range(cycleStart + 1, len(array)):
            if array[i] < value:
                pos += 1
        if pos == cycleStart:
            continue
        while value == array[pos]:
            pos += 1
        array[pos], value = value, array[pos]
        while pos != cycleStart:
            pos = cycleStart
            for i in range(cycleStart + 1, len(array)):
                if array[i] < value:
                    pos += 1
            while value == array[pos]:
                pos += 1
            array[pos], value = value, array[pos]
    return array
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
    cycle_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")
    #print(my_array)

if __name__ == "__main__":

    time_test(1_000)
