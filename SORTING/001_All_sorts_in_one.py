import random
import time


"""********Сортировка двоичным деревом - tree_sort********"""
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

    def insert(self, val):
        if self.val:
            if val < self.val:
                if self.left is None:
                    self.left = Node(val)
                else:
                    self.left.insert(val)
            elif val > self.val:
                if self.right is None:
                    self.right = Node(val)
                else:
                    self.right.insert(val)
        else:
            self.val = val

def inorder(root, res):
    if root:
        inorder(root.left, res)
        res.append(root.val)
        inorder(root.right, res)

def tree_sort(array):
    if len(array) == 0:
        return array
    root = Node(array[0])
    for i in range(1, len(array)):
        root.insert(array[i])
    # Traverse BST in order.
    res = []
    inorder(root, res)
    return res
"""*******************************************************"""

"""***********Интроспективная сортировка - intro_sort********"""
def insert_isort(array, begin=0, end=None):
    if end == None:
        end = len(array) - 1
    for i in range(begin, end):
        j = i
        to_change = array[i]
        while (j != begin and array[j - 1] > to_change):
            array[j] = array[j - 1]
            j -= 1
        array[j] = to_change
    return array

def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2

    if l < n and arr[i] < arr[l]:
        largest = l
    if r < n and arr[largest] < arr[r]:
        largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_isort(arr):
    n = len(arr)

    for i in range(n // 2, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)
    return arr

def median_elem(array, low_id, mid_id, high_id):
    if ((array[low_id] > array[mid_id]) != (array[low_id] > array[high_id])):
        return array[low_id]
    elif ((array[mid_id] > array[low_id]) != (array[mid_id] > array[high_id])):
        return array[mid_id]
    else:
        return array[high_id]

def partition_isort(array, low, high, pivot):
    i = low
    j = high
    while True:
        while (array[i] < pivot):
            i += 1
        j -= 1
        while (pivot < array[j]):
            j -= 1
        if i >= j:
            return i
        array[i], array[j] = array[j], array[i]
        i += 1

def intro_sort(array):
    max_depth = 2 * (len(array).bit_length() - 1)
    size_hold = 16
    return intro_util(array, 0, len(array), size_hold, max_depth)

def intro_util(array, start, end, size_hold, depth_limit):
    while (end - start > size_hold):
        if (depth_limit == 0):
            return heap_isort(array)
        depth_limit -= 1

        median = median_elem(array, start, start +
                             ((end - start) // 2) + 1, end - 1)
        p = partition_isort(array, start, end, median)
        intro_util(array, p, end, size_hold, depth_limit)
        end = p
    return insert_isort(array, start, end)
"""**********************************************************"""

"""***************Гибридная сортировка - tim_sort*********"""
def tinsertion_sort(array, left, right):
    for i in range(left + 1, right + 1):
        temp = array[i]
        j = i - 1
        while temp < array[j] and j >= left:
            array[j + 1] = array[j]
            j -= 1
        array[j + 1] = temp
    return array

def merge(array, l, m, r):
    array_length1 = m - l + 1
    array_length2 = r - m
    left = []
    right = []
    for i in range(0, array_length1):
        left.append(array[l + i])
    for i in range(0, array_length2):
        right.append(array[m + 1 + i])

    i = 0
    j = 0
    k = l

    while j < array_length2 and i < array_length1:
        if left[i] <= right[j]:
            array[k] = left[i]
            i += 1
        else:
            array[k] = right[j]
            j += 1
        k += 1

    while i < array_length1:
        array[k] = left[i]
        k += 1
        i += 1

    while j < array_length2:
        array[k] = right[j]
        k += 1
        j += 1

def tim_sort(array):
    size = len(array)
    RUN = len(array)
    for i in range(0, size, RUN):
        end = min(i + RUN - 1, size - 1)
        tinsertion_sort(array, i, end)

    step = RUN
    for i in range(step, size, 2 * step):
        for j in range(0, size, 2 * step):
            mid = j + size - 1
            right = min((j + 2 * step -1), (size - 1))
            if mid < right:
                merge(array, j, mid, right)
"""/*****************************************************/"""

"""/*********Нитевидная сортировка - strand_sort*********"""
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

"""*************Голубинная сортировка - pigeonhole_sort*************"""
def pigeonhole_sort(array):
    minimum = min(array)
    maximum = max(array)
    s = maximum - minimum + 1
    h = [0] * s  # holes
    for x in array:
        assert type(x) is int, "integers only please"
        h[x - minimum] += 1
    i = 0
    for c in range(s):
        while h[c] > 0:
            h[c] -= 1
            array[i] = c + minimum
            i += 1
"""*****************************************************************"""

"""*************Блинная сортировка - pancake_sort*************"""
def flip(arr, i):
    start = 0
    while start < i:
        temp = arr[start]
        arr[start] = arr[i]
        arr[i] = temp
        start += 1
        i -= 1

def findMax(arr, n):
    mi = 0
    for i in range(0,n):
        if arr[i] > arr[mi]:
            mi = i
    return mi

def pancake_sort(arr):
    curr_size = len(arr)
    while curr_size > 1:
        mi = findMax(arr, curr_size)
        if mi != curr_size-1:
            flip(arr, mi)
            flip(arr, curr_size-1)
        curr_size -= 1
"""***********************************************************"""

"""*********Чётно-нечётная сортировка - odd_even_sort*********"""
def odd_even_sort(data):
    n = len(data)
    isSorted = 0
    while isSorted == 0:
        isSorted = 1
        for i in range(1, n - 1, 2):
            if data[i] > data[i + 1]:
                data[i], data[i + 1] = data[i + 1], data[i]
                isSorted = 0
        for i in range(0, n - 1, 2):
            if data[i] > data[i + 1]:
                data[i], data[i + 1] = data[i + 1], data[i]
                isSorted = 0
    return data
"""***********************************************************"""

"""*************Битонная сортировка - bitonic_sort************"""
def compare_swap(a, i, j, d):
    if (d == 1 and a[i] > a[j]) or (d == 0 and a[i] < a[j]):
        a[i], a[j] = a[j], a[i]

def merge(a, l, cnt, d):
    if cnt > 1:
        k = int(cnt / 2)
        for i in range(l, l + k):
            compare_swap(a, i, i + k, d)
        merge(a, l, k, d)
        merge(a, l + k, k, d)

def bitonic_sort(a, l, cnt, d):
    if cnt > 1:
        k = int(cnt / 2)
        bitonic_sort(a, l, k, 1)
        bitonic_sort(a, l + k, k, 0)
        merge(a, l, cnt, d)

def sort(array, size, flag = 1):
    bitonic_sort(array, 0, size, flag)
"""***********************************************************"""

"""**************Вялая сортировка - slow_sort**************"""
def slow_rec(data, i, j):
    if i >= j:
        return data
    m = (i + j) // 2
    slow_rec(data, i, m)
    slow_rec(data, m + 1, j)
    if data[m] > data[j]:
        data[m], data[j] = data[j], data[m]
    slow_rec(data, i, j - 1)

def slow_sort(data):
    return slow_rec(data, 0, len(data) - 1)
"""*********************************************************"""

"""**Бинарная сортировка вставками - binary_insertion_sort**"""
def binary_search(arr, val, start, end):
    if start == end:
        if arr[start] > val:
            return start
        else:
            return start + 1

    if start > end:
        return start

    mid = (start + end) // 2
    if arr[mid] < val:
        return binary_search(arr, val, mid + 1, end)
    elif arr[mid] > val:
        return binary_search(arr, val, start, mid - 1)
    else:
        return mid

def binary_insertion_sort(arr):
    for i in range(1, len(arr)):
        val = arr[i]
        j = binary_search(arr, val, 0, i - 1)
        arr = arr[:j] + [val] + arr[j:i] + arr[i + 1:]
    return arr
"""*********************************************************"""

"""*****Бисерная (гравитационная) сортировка - bead_sort****"""
def bead_sort(input_list):
    return_list = []
    # Создание списка из нулей, максимальная длина которого равна максимуму списка.
    transposed_list = [0] * max(input_list)  # Это список с упавшими бусинами.
    for num in input_list:
        transposed_list[:num] = [n + 1 for n in transposed_list[:num]]

    for i in range(len(input_list)):
        return_list.append(sum(n > i for n in transposed_list))

    return_list.reverse()
    return return_list
"""*********************************************************"""

"""************Цикличная сортировка - cycle_sort************"""
def cycle_sort(array):
    for cycleStart in range(0, len(array) - 1):
        value = array[cycleStart]
        pos = cycleStart
        for i in range(cycleStart + 1, len(array)):
            if array[i] < value:
                pos += 1
        if pos == cycleStart:
            continue
        while value == array[pos]:
            pos += 1
        array[pos], value = value, array[pos]
        while pos != cycleStart:
            pos = cycleStart
            for i in range(cycleStart + 1, len(array)):
                if array[i] < value:
                    pos += 1
            while value == array[pos]:
                pos += 1
            array[pos], value = value, array[pos]
    return array
"""*********************************************************"""

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

"""************Сортировка подсчетом - count_sort*************"""
def count_sort(array):
    max_element = max(array)
    count_array_length = max_element + 1
    count_array = [0] * count_array_length

    for elm in array:
        count_array[elm] += 1

    for i in range(1, count_array_length):
        count_array[i] += count_array[i - 1]

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

"""***********Поразрядная сортировка - radix_sort***********"""
def counting_sort(array, place):
    size = len(array)
    output = [0] * size
    count = [0] * 10

    # Calculate count of elements
    for i in range(0, size):
        index = array[i] // place
        count[index % 10] += 1

    # Calculate cumulative count
    for i in range(1, 10):
        count[i] += count[i - 1]

    # Place the elements in sorted order
    i = size - 1
    while i >= 0:
        index = array[i] // place
        output[count[index % 10] - 1] = array[i]
        count[index % 10] -= 1
        i -= 1

    for i in range(0, size):
        array[i] = output[i]

# Main function to implement radix sort
def radix_sort(array):
    # Get maximum element
    max_element = max(array)
    # Apply counting sort to sort elements based on place value.
    place = 1
    while max_element // place > 0:
        counting_sort(array, place)
        place *= 10
"""*********************************************************"""

"""*********Сортировка Шелла - shell_sort_V_1.0*********"""
def shell_sort(array):
    inc = len(array) // 2
    while inc:
        for i, el in enumerate(array):
            while i >= inc and array[i - inc] > el:
                array[i] = array[i - inc]
                i -= inc
            array[i] = el
        inc = 1 if inc == 2 else int(inc * 5.0 / 11)
"""*****************************************************"""

"""*********Сортировка Шелла - shell_sort_V_2.0*********"""
def shell_sort2(array):
    size = len(array)
    interval = size // 2
    while interval > 0:
        for i in range(interval, size):
            temp = array[i]
            j = i
            while j >= interval and array[j - interval] > temp:
                array[j] = array[j - interval]
                j -= interval
            array[j] = temp
        interval //= 2
"""*****************************************************"""

"""*********Сортировка перемешиванием - shaker_sort*********"""
def shaker_sort(array):
    left = 0
    right = len(array) - 1
    while left <= right:
        for i in range(right, left, -1):
            if array[i - 1] > array[i]:
                array[i], array[i - 1] = array[i - 1], array[i]
        left += 1
        for i in range(left, right + 1):
            if array[i - 1] > array[i]:
                array[i], array[i - 1] = array[i - 1], array[i]
        right -= 1
"""*********************************************************"""

"""*******************Быстрая сортировка - quick_sort version 1.0*******************"""
def quick_sort(array):
    if array: return quick_sort([x for x in array[1:] if x < array[0]]) + array[0:1] + \
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

"""************Сортировка расческой - comb_sort*************"""
def comb_sort(array):
    gap = len(array)
    swaps = True
    while gap > 1 or swaps:
        gap = max(1, int(gap / 1.25))
        swaps = False
        for i in range(len(array) - gap):
            j = i + gap
            if array[i] > array[j]:
                array[i], array[j] = array[j], array[i]
                swaps = True
"""*********************************************************"""

"""*********Сортировка кучей (пирамидальная) - heap_sort***********"""
def heap_create(array, heap_size, root_index):
    largest = root_index  # Индекс наибольшего элемента - это корень дерева
    left_child = (2 * root_index) + 1  # Левый наследник
    right_child = (2 * root_index) + 2  # Правый наследник

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
"""****************************************************************"""

"""****************Сортировка слиянием - merge_sort****************"""
def merge_sort(array):
    if len(array) > 1:
        middle = len(array) // 2
        left = array[:middle]
        right = array[middle:]
        merge_sort(left)
        merge_sort(right)
        i = j = k = 0
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                array[k] = left[i]
                i+=1
            else:
                array[k] = right[j]
                j+=1
            k+=1
        while i < len(left):
            array[k] = left[i]
            i+=1
            k+=1
        while j < len(right):
            array[k] = right[j]
            j+=1
            k+=1
"""****************************************************************"""

"""*****************Гномья сортировка - gnome_sort*****************"""
def gnome_sort(data):
    i, size = 1, len(data)
    while i < size:
        if data[i - 1] <= data[i]:
            i += 1
        else:
            data[i - 1], data[i] = data[i], data[i - 1]
            if i > 1:
                i -= 1
"""****************************************************************"""

"""****************Сортировка пузырьком - bubble_sort****************"""
def bubble_sort(array):
    n = len(array)
    for i in range(n):
        for j in range(n - 1 - i):
            if array[j] > array[j + 1]:
                tmp = array[j]
                array[i] = array[j + 1]
                array[j + 1] = tmp
"""******************************************************************"""

"""****************Сортировка выбором - selection_sort***************"""
def selection_sort(array):
    n = len(array)
    for i in range(n - 1):
        min_index = i
        for j in range(i + 1, n):
            if array[j] < array[min_index]:
                min_index = j
        if min_index != i:
            temp = array[i]
            array[i] = array[min_index]
            array[min_index] = temp
"""******************************************************************"""

"""***************Сортировка вставками - insertion_sort**************"""
def insertion_sort(array):
    n = len(array)
    for i in range(1, n):
        current_value = array[i]
        j = i - 1
        while j >= 0:
            if current_value < array[j]:
                array[j+1] = array[j]
                array[j] = current_value
                j = j - 1
            else:
                break
"""******************************************************************"""

# Функция для тестов
def time_test(size, flag):
    my_array = [round(random.random() * 10000) for i in range(size)]
    timer = time.time()
    if flag == 1:
        intro_sort(my_array)
    elif flag == 2:
        tree_sort(my_array)
    else:
        sorted(my_array)

    timer = time.time() - timer
    #print(my_array)
    return round(timer, 2)


# Запись в логи
def file_write(info):
    path = "C:\\Users\\user\\Desktop\\Sorting_test_Python.txt"
    try:
        with open(path, 'a+') as file:
            file.write(info + "\n")
            file.close()
    except:
        print("Что-то пошло не так")


if __name__ == "__main__":
    """Для тестов 100, 1_000, 10_000, 100_000, 1_000_000"""
    log = "\nSize: \t\t Intro_sort \t Tree_sort \t Standart_python_sorted"
    print(log)
    file_write(log)
    j = 100
    for _ in range(1):
        t1 = time_test(j, 1)
        #t1 = 0
        t2 = time_test(j, 2)
        #t2 = 0
        t3 = time_test(j, 3)
        #t3 = 0
        file_write(f"{j} \t\t {t1} \t\t {t2} \t\t {t3}")
        print(f"{j} \t\t {t1} \t\t {t2} \t\t\t {t3}")
        j *= 10
        #print(t2)


"""*******************ТЕСТЫ СОРТИРОВОК**************************
Size: 		 Bubble_sort 	 Selection_sort 	 Insertion_sort
100 		 0.0 		     0.0 	        	 0.0
1'000 		 0.0 		     0.0 		         0.0
10'000 		 0.12 		     0.12 		         0.15
100'000 	 11.14 		     8.96    		     13.09

Size: 		 Quick_sort 	 Quick_sort_2    	 Comb_sort
100 		 0.0 		     0.0 	    	     0.0
1'000 		 0.01 		     0.01 	    	     0.01
10'000 		 0.08 		     0.07   	    	 0.2
100'000 	 1.02 		     0.47       		 1.84
1'000'000	 27.82 		     6.91   	    	 31.08
10'000'000	 RecursionError	 95.49  		     n * n

Size: 		 Merge_sort 	 Heap_sort 	         Gnome_sort
100 		 0.0     		 0.0        		 0.0
1'000 		 0.01 	    	 0.01 	        	 0.31
10'000 		 0.14 	    	 0.18 	        	 31.05
100'000 	 1.6 	    	 2.39 	        	 n * n
1'000'000 	 17.89 	    	 31.11 	        	 n * n * n
10'000'000 	 209.78 		 404.65 	    	 n * n * n * n

Size: 		 Shell_sort 	 Shell_sort_V2   	 Shaker_sort
100 		 0.0    		 0.0        		 0.0
1'000 		 0.01 	    	 0.01       		 0.24
10'000 		 0.11 	    	 0.13       		 25.21
100'000 	 1.56 	    	 2.04       		 n * n
1'000'000	 18.9 	    	 34.47 		         n * n * n

Size: 		 Radix_sort 	 Count_sort 	    Bucket_sort
100 		 0.0 		     0.0                0.0
1'000 		 0.0    		 0.0        		0.01
10'000 		 0.07 	    	 0.05 		        0.47
100'000 	 0.76 	    	 0.09 		        71.09
1'000'000	 9.72 	    	 0.88 		        n * n
10'000'000 	 99.42 	    	 12.69 		        n * n * n

Size: 		 Bead_sort 	     Cycle_sort      	Binary_insertion_sort
100 		 0.24 		     0.0     		    0.0
1'000 		 2.53 		     0.22 		        0.03
10'000 		 23.55 		     23.14 		        1.77
100'000      n * n 		     n * n 		        453.6

Size: 		 Bitonic_sort 	 Odd_even_sort 	    Pancake_sort
100 		 0.0 		     0.0 		        0.0
1000 		 0.02 		     0.54 		        0.36
10000 		 0.45 		     24.46 		        30.1
100000 		 7.38 		     n * n 		        n * n
1000000 	 102.23          n * n * n  		n * n * n

Size: 		 Pigeonhole_sort Tim_sort 	        Strand_sort
100 		 0.0 		    0.0 		        0.0
1'000 		 0.0 		    0.12 		        0.02
10'000 		 0.01 		    10.72 		        1.78
100'000      0.08    		1256.2 		        444.77
1'000'000	 0.58		    n * n		        n * n
10'000'000 	 10.99 		    n * n * n 		    n * n * n

Size: 		 Intro_sort 	 Tree_sort 	        Standart_python_sorted
100 		 0.0     		 0.0 		        0.0
1'000 		 0.0 	    	 0.01 		        0.0
10'000 		 0.06    		 0.56 		        0.02
100'000 	 0.61 	    	 0.69 		        0.04
1'000'000	 7.98 	    	 9.23 		        0.63
10'000'000 	 101.98 		 95.58 		        6.35
***************************************************************"""
