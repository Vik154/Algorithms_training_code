import random
import time


"""************Блочная сортировка - bucket_sort*************"""
def bucket_sort(array):
    largest = max(array)
    length = len(array)
    size = largest / length
    # Create Buckets
    buckets = [[] for i in range(length)]
    # Bucket Sorting
    for i in range(length):
        index = int(array[i] / size)
        if index != length:
            buckets[index].append(array[i])
        else:
            buckets[length - 1].append(array[i])

    # Sorting Individual Buckets
    for i in range(len(array)):
        buckets[i] = sorted(buckets[i])

    # Flattening the Array
    result = []
    for i in range(length):
        result = result + buckets[i]

    return result
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
    #my_array = bucket_sort(my_array)
    bucket_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")
    #print(my_array)


if __name__ == "__main__":

    time_test(10_000)
