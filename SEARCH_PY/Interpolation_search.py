import random

"""*******Интерполяционный поиск - interpolation_search********"""
def interpolation_search(array, elem):
    high = len(array) - 1
    low = 0

    while low <= high and elem >= array[low] and elem <= array[high]:
        if low == high:
            if array[low] == elem:
                return low
            return -1
        pos = low + ((high - low) // (array[high] - array[low]) * (elem - array[low]))

        if array[pos] == elem:
            return pos
        if array[pos] < elem:
            low = pos + 1
        else:
            high = pos - 1
    return -1
"""************************************************************"""

#*********--Рекурсивный вариант--*******
def interpolation_search_rec(array, value, begin=0, end=0):
    if begin <= end and value >= array[begin] and value <= array[end]:
        pos = begin + ((end - begin) // (array[end] - array[begin])) * (value - array[begin])

        if array[pos] == value:
            return pos
        if array[pos] < value:
            return interpolation_search_rec(array, value, pos + 1, end)
        if array[pos] > value:
            return interpolation_search_rec(array, value, begin, pos - 1)
    return -1


def main():
    arr = [random.randint(-100, 100) for i in range(200)]
    arr.sort()
    id = interpolation_search(arr, 10)
    id2 = interpolation_search_rec(arr, 10, 0, len(arr) - 1)
    print(f"id = {id}\nid2 = {id2}")
    if id != -1:
        print(arr[id])
    if id2 != -1:
        print(arr[id2])


if __name__ == "__main__":
    main()