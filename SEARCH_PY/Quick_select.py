import random

"""Функция partition - группирует список (от индексов left до right) на две части,
то есть, которые меньше определенного элемента, и те, которые больше или равны элементу.
Это известно как схема разбиения Ломуто , которая проще,
но менее эффективна, чем исходная схема разбиения Хоара """

def partition(array, left, right):
    pivot = array[right]
    id = left
    for i in range(left, right-1):
        if array[i] <= pivot:
            array[id], array[i] = array[i], array[id]
            id += 1

    array[id], array[right] = array[right], array[id]
    return id

# Возвращает k-й наименьший элемент в списке в пределах `left…right`
# (т.е. left <= k <= right). Пространство поиска в массиве
# меняется для каждого раунда, но размер списка остается прежним.
# Таким образом, `k` не нужно обновлять с каждым раундом.

def quick_select(array, left, right, k):
    # Если k - это наименьший элемент в массиве
    if k > 0 and k <= right - left + 1:
        # Разделить массив и получить индекс сводного элемента в отсортированном массиве
        index = partition(array, left, right)
        # Если позиция та же, что и у k_th, вернуть значение
        if (index - left) == (k - 1):
            return array[index]
        # Если позиция больше, то повторить рекурсивно для левого подмассива
        if index - left > k - 1:
            return quick_select(array, left, index - 1, k)
        # Иначе, повторит рекурсивно для правой части массива
        return quick_select(array, index + 1, right, k - index + left - 1)

    # Если k больше, чем количество элементов в массиве
    return -1
"""********************************************************"""

def main():
    arr = [random.randint(-100, 100) for i in range(200)]
    #arr.sort()
    k = random.randint(-100, 100)
    k_th = quick_select(arr, 0, 100, k)
    print(f"k_th = {k_th}") if k_th != -1 else print("k_th = -1")

if __name__ == "__main__":
    main()