"""/*****Алгоритм Манакера - поиск самого большого палиндрома*****/"""

def manacher_odd(s):
    s = '$' + s + '^'
    n = len(s)
    res = [0] * n
    l = 0
    r = 0
    for i in range(1, n - 1):
        res[i] = max(0, min(r - i, res[l + (r - i)]))
        while s[i - res[i]] == s[i + res[i]]:
            res[i] += 1
        if i + res[i] > r:
            l = i - res[i]
            r = i + res[i]
    return res[1:-1]

def manacher(s):
    res = manacher_odd('#' + '#'.join(s) + '#')[1:-1]
    return ([x // 2 for x in res[::2]], [x // 2 for x in res[1::2]])
"""****************************************************************"""

"""*****Алгоритм Манакера - search_manacher_palindrome*****"""
def find_max_palindrome(string):
    if not string or not len(string):
        return
    st = '#' + '#'.join(f'{string}') + '#'      # Заполненная разделителями строка #a#b#c#
    size = len(st)
    pal = [0] * size
    r = c = index = id_mir = 0
    max_len = 1

    for i in range(1, size - 1):
        id_mir = 2 * c - i
        pal[i] = min(pal[id_mir], r - i) if r > i else 0

        while i > pal[i] and (i + pal[i] + 1) < size and st[i - pal[i] - 1] == st[i + pal[i] + 1]:
            pal[i] += 1
        if pal[i] + i > r:
            c = i
            r = i + pal[i]
        if max_len < pal[i]:
            max_len = pal[i]
            index = i

    return string[(index - max_len) // 2 : (max_len + index) // 2]
"""********************************************************"""

s = "Palindrome level 1000"
print(find_max_palindrome(s))