import random
import time

"""/*********Нитевидная сортировка - strand_sort*********/"""
def merge_list(a, b):
    out = []
    while len(a) and len(b):
        if a[0] < b[0]:
            out.append(a.pop(0))
        else:
            out.append(b.pop(0))
    out += a
    out += b
    return out

def strand(a):
    i, s = 0, [a.pop(0)]
    while i < len(a):
        if a[i] > s[-1]:
            s.append(a.pop(i))
        else:
            i += 1
    return s

def strand_sort(a):
    out = strand(a)
    while len(a):
        out = merge_list(out, strand(a))
    return out
"""/*****************************************************/"""

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
    strand_sort(my_array)
    #my_array = strand_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer, 2)} сек")
    #print(my_array)

if __name__ == "__main__":
    time_test(10_000)
