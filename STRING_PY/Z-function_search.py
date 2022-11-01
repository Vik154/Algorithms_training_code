"""Алгоритм поиска подстроки с помощью Z-функции"""

# Функция формирования Z-массива по переданной строке
def get_Z_array(string, z):
    n = len(string)

    # Формирование Z-массива в промежжутке [L:R]
    l, r, k = 0, 0, 0
    for i in range(1, n):

        # если i > R - значит нет совпадений и поэтому для вычисления Z[i] используется наивный способ.
        if i > r:
            l, r = i, i
            # R-L = 0 при запуске, поэтому он начнет проверку с 0-го индекса.
            # Например, для "ababab" и i = 1 значение R остается 0, а Z[i] становится 0.
            # Для строки "aaaaaa" и i = 1, Z[i] и R становятся 5
            while r < n and string[r - l] == string[r]:
                r += 1
            z[i] = r - l
            r -= 1
        else:
            # k соответствует числу, которое совпадает в интервале [L, R].
            k = i - l
            # Если Z[k] меньше оставшегося интервала, то Z[i] будет равно Z[k].
            # Например, str = "ababab", i = 3, R = 5 и L = 2
            if z[k] < r - i + 1:
                z[i] = z[k]
            else:
                l = i
                while r < n and string[r - l] == string[r]:
                    r += 1
                z[i] = r - l
                r -= 1

# Функция поиска подстроки с использованием Z-функции
def search(text, pattern):
    concat = pattern + "$" + text       # Создание шаблона поиска "Pattern + $ + Text"
    l = len(concat)
    z = [0] * l                         # Создание Z-массива
    get_Z_array(concat, z)              # Заполнение Z-массива

    # Перебираем Z массив для поиска индекса вхождения
    for i in range(l):

        # Если значение по индексу == длине искомого шаблона, значит есть вхождение
        if z[i] == len(pattern):
            return i - len(pattern) - 1
    return -1


if __name__ == "__main__":
    text = "kdfsdkfnvjoensdovndRootkmlskvslvnjkfd"
    pattern = "Root"
    print(f"Find id pattern = {search(text, pattern)}")
