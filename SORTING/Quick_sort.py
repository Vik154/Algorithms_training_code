import random
import time

"""*******************Быстрая сортировка - quick_sort version 1.0*******************"""
def quick_sort(array):
    if array: return quick_sort([x for x in array[1:] if x < array[0]]) + array[0:1] +\
                     quick_sort([x for x in array[1:] if x >= array[0]])
    return []
"""*********************************************************************************"""

"""*******************Быстрая сортировка - quick_sort version 2.0*******************"""
def quick_sort2(array):
    if len(array) <= 1:
        return array
    else:
        q = random.choice(array)
    l_nums = [n for n in array if n < q]

    e_nums = [q] * array.count(q)
    b_nums = [n for n in array if n > q]
    return quick_sort2(l_nums) + e_nums + quick_sort2(b_nums)
"""*********************************************************************************"""

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
    quick_sort2(my_array)
    #my_array = quick_sort2(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")
    #print(my_array)


if __name__ == "__main__":

    time_test(500_000)