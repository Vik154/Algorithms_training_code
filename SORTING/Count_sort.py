import random
import time

"""************Сортировка подсчетом - count_sort*************"""
def count_sort(array):
    max_element = max(array)
    count_array_length = max_element+1
    count_array = [0] * count_array_length

    for elm in array:
        count_array[elm] += 1

    for i in range(1, count_array_length):
        count_array[i] += count_array[i-1]

    output_array = [0] * len(array)
    i = len(array) - 1
    while i >= 0:
        current_elm = array[i]
        count_array[current_elm] -= 1
        new_position = count_array[current_elm]
        output_array[new_position] = current_elm
        i -= 1

    return output_array
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
    #my_array = count_sort(my_array)
    count_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")
    #print(my_array)


if __name__ == "__main__":

    time_test(1_000_000)
