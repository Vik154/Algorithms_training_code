from math import sqrt
import random

"""**********Поиск прыжками - jump_search**********"""
def jump_search(array, elem):
    size = len(array)
    step = int(sqrt(size))
    prev = step

    while array[min(step, size) - 1] < elem:
        prev = step
        step += int(sqrt(size))
        if prev >= size:
            return -1

    while array[prev] < elem:
        prev += 1
        if prev == min(step, size):
            return -1

    if array[prev] == elem:
        return prev

    return -1
"""************************************************"""

def main():
    arr = [random.randint(-100, 100) for i in range(200)]
    arr.sort()
    id = jump_search(arr, 10)
    print(f"id = {id}")
    if id != -1:
        print(arr[id])

if __name__ == "__main__":
    main()