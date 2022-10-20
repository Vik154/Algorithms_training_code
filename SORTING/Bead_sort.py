import random
import time

"""*****Бисерная (гравитационная) сортировка - bead_sort****"""
def beadsort(input_list):
    return_list = []
    # Создание списка из нулей, максимальная длина которого равна максимуму списка.
    transposed_list = [0] * max(input_list)     # Это список с упавшими бусинами.
    for num in input_list:
        transposed_list[:num] = [n + 1 for n in transposed_list[:num]]

    for i in range(len(input_list)):
        return_list.append(sum(n > i for n in transposed_list))

    return_list.reverse()
    return return_list
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
    #my_array = bead_sort(my_array)
    bead_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")
    #print(my_array)


if __name__ == "__main__":

    time_test(1000)
