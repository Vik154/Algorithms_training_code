import random
import time

"""*************Сортировка кучей (пирамидальная) - heap_sort****************"""
def heap_create(array, heap_size, root_index):
    largest = root_index                    # Индекс наибольшего элемента - это корень дерева
    left_child = (2 * root_index) + 1       # Левый наследник
    right_child = (2 * root_index) + 2      # Правый наследник

    # Если левый потомок больше корня - запомнить его индекс
    if left_child < heap_size and array[left_child] > array[largest]:
        largest = left_child
    # То же для правого потомка
    if right_child < heap_size and array[right_child] > array[largest]:
        largest = right_child
    # Если наибольший элемент уже не корневой, они меняются местами
    if largest != root_index:
        array[root_index], array[largest] = array[largest], array[root_index]
        heap_create(array, heap_size, largest)

def heap_sort(array):
    size = len(array)
    for i in range(size, -1, -1):
        heap_create(array, size, i)
    # Перемещаем корень в самый конец списка
    for i in range(size - 1, 0, -1):
        array[i], array[0] = array[0], array[i]
        heap_create(array, i, 0)
"""*****************************************************************************"""


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
    heap_sort(my_array)
    timer = time.time() - timer
    print(f"Сортировка массива на {size} элементов: {round(timer,2)} сек")
    #print(my_array)


if __name__ == "__main__":

    time_test(100_000)