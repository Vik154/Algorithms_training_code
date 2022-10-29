import random

"""************Тернарный поиск - ternary_search************"""
def ternary_search(array, elem):
    left_id = 0
    right_id = len(array) - 1

    while right_id >= left_id:
        mid_1 = left_id + (right_id - left_id) // 3
        mid_2 = right_id - (right_id - left_id) // 3

        if array[mid_1] == elem:
            return mid_1
        if array[mid_2] == elem:
            return mid_2
        if array[mid_1] > elem:
            right_id = mid_1 - 1;
        elif array[mid_2] < elem:
            left_id = mid_2 + 1
        else:
            left_id  = mid_1 + 1
            right_id = mid_2 - 1

    return -1
"""********************************************************"""

"""**********Рекурсивная версия - ternary_search***********"""
def ternary_search_rec(array, elem, begin=0, end=0):
    if end >= begin:
        mid_1 = begin + (end - begin) // 3
        mid_2 = end - (end - begin) // 3

        if array[mid_1] == elem:
            return mid_1
        if array[mid_2] == elem:
            return mid_2
        if array[mid_1] > elem:
            return ternary_search_rec(array, elem, begin, mid_1 - 1)
        elif array[mid_2] < elem:
            return ternary_search_rec(array, elem, mid_2 + 2, end)
        else:
            return ternary_search_rec(array, elem, mid_1 + 1, mid_2 - 1)

    return -1
"""********************************************************"""


def main():
    arr = [random.randint(-100, 100) for i in range(200)]
    arr.sort()
    id = ternary_search(arr, 10)
    id2 = ternary_search_rec(arr, 20, 0, len(arr)-1)
    print(f"id = {id}\nid2 = {id2}")
    if id != -1:
        print(arr[id])
    if id2 != -1:
        print(arr[id2])

if __name__ == "__main__":
    main()