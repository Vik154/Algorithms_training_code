"""Алгоритм поиска подстроки - Бойера-Мура-Хорспула"""
# Этап 1: формирование таблицы смещений
def table_shift(pattern):
    unique_symbol = set()           # уникальные символы в образе
    count_symbol = len(pattern)     # число символов в образе
    dict_shift = dict()             # словарь смещений

    for i in range(count_symbol-2, -1, -1):         # итерации с предпоследнего символа
        if pattern[i] not in unique_symbol:         # если символ еще не добавлен в таблицу
            dict_shift[pattern[i]] = count_symbol - i - 1
            unique_symbol.add(pattern[i])
    # отдельно формируем последний символ
    if pattern[count_symbol - 1] not in unique_symbol:
        dict_shift[pattern[count_symbol - 1]] = count_symbol
    # смещения для прочих символов
    dict_shift['*'] = count_symbol
    return dict_shift

# Этап 2: поиск образа в строке
def bmh_search(string, pattern):
    size_txt = len(string)
    size_pat = len(pattern)
    shift_tb = table_shift(pattern)     # {'e': 1, 's': 2, '*': 2} - таблица сдвигов

    if size_txt >= size_pat:
        i = size_pat-1                  # счетчик проверяемого символа в строке
        while(i < size_txt):
            k = 0
            j = 0
            fl_break = False
            for j in range(size_pat-1, -1, -1):
                if string[i - k] != pattern[j]:
                    print(f"i == {i}")
                    print(f"j == {j}")
                    print(f"k == {k}")

                    if j == size_pat-1:
                        #print(string[i - k])
                        # смещение, если не равен последний символ образа
                        off = shift_tb[string[i]] if shift_tb.get(string[i], False) else shift_tb['*']
                        print(f"shift_tb.get(string[i], False) == {shift_tb.get(string[i], False)}")
                    else:
                        off = shift_tb[pattern[j]]          # смещение, если не равен не последний символ образа

                    i += off                                # смещение счетчика строки
                    fl_break = True                         # если несовпадение символа, то fl_break = True
                    break
                k += 1                                      # смещение для сравниваемого символа в строке
            if not fl_break:                                # если дошли до начала образа, значит, все его символы совпали
                return i - k + 1
    return -1

def main():
    #string_1  = "The Boyer–Moore–Horspool is an algorithm for finding substrings in strings"
    string_1  = "strings"
    string_2  = "Алгоритм Бойера–Мура–Хорспула - это алгоритм для поиска подстрок в строках"
    pattern_1 = "in"
    pattern_2 = "поиска"
    print(bmh_search(string_1, pattern_1))
    #print(bmh_search(string_2, pattern_2))

if __name__ == "__main__":
    main()