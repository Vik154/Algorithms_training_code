"""Алгоритм поиска подстроки - Бойера-Мура"""
# Boyer Moore Search -- bm_search
def bm_search(haystack, needle):
    if not needle:
        return 0;
    pre = [-1] * 1100               # В пайтоне 256 для русских символов не пойдет из-за UTF
    needle_size = len(needle)
    for i in range(needle_size):
        pre[ord(needle[i])] = i

    hay_size = len(haystack)
    shift_ind = 0

    while shift_ind <= (hay_size - needle_size):
        j = needle_size - 1
        while (j >= 0) and haystack[shift_ind + j] == needle[j]:
            j -= 1
        if j < 0:
            return shift_ind;
        else:
            shift_ind += max(1, pre[ord(needle[j])] - j)
    return -1
"""*********************************************************************"""

"""Алгоритм поиска подстроки - Бойера-Мура-Хорспула V_2.0"""
def bmh_search2(haystack, needle):
    hay_size = len(haystack)
    needle_size = len(needle)
    if needle_size > hay_size:
        return -1;

    pre = [needle_size] * 1251

    for i in range(needle_size - 1):
        pre[ord(needle[i])] = needle_size - i - 1

    shift_ind = needle_size - 1
    while shift_ind < hay_size:
        j = needle_size - 1
        i = shift_ind
        while j >= 0 and haystack[i] == needle[j]:
            j -= 1
            i -= 1
        if j < 0:
            return i + 1;
        shift_ind += max(1, pre[ord(needle[j])] - j)

    return -1;
"""******************************************************"""

def main():
    string_1  = "The Boyer–Moore–Horspool is an algorithm for finding substrings in strings"
    string_2  = "Алгоритм Бойера–Мура–Хорспула - это алгоритм для поиска подстрок в строках"
    pattern_1 = "rithm"
    pattern_2 = "поиск"
    print(bm_search(string_1, pattern_1))
    print(bm_search(string_2, pattern_2))
    print(bmh_search2(string_1, pattern_1))
    print(bmh_search2(string_2, pattern_2))

if __name__ == "__main__":
    main()