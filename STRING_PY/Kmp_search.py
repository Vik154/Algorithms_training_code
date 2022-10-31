"""********Поиск методом Кнута–Морриса–Пратта - kmp_search*******"""
def kmp(string, pattern):
    str_len = len(string)
    pat_len = len(pattern)
    prefix = [0]*pat_len
    j = 0
    for i in range(1, pat_len):
        while j > 0 and pattern[j] != pattern[i]:
            j = prefix[j-1]
        if pattern[j] == pattern[i]:
            j += 1
        prefix[i] = j

    j = 0
    for i in range(str_len):
        while j > 0 and pattern[j] != string[i]:
            j = prefix[j - 1]
        if pattern[j] == string[i]:
            j += 1
        if j == pat_len:
            prefix.clear()
            return i - j + 1

    prefix.clear()
    return -1
"""**************************************************************"""

def main():
    text = "wqdsdssYYncxhjsUUJDm, cbsskООлвдrootсыдсДДДыы"
    patt = "root"
    res = kmp(text, patt)
    print(res)

if __name__ == "__main__":
    main()