"""Алгоритм грубой силы - подробный перебор"""
def brute_force(string, pattern):
    pat_len = len(pattern)
    txt_len = len(string)
    index = -1
    if (pat_len <= txt_len):
        for i in range(txt_len - pat_len + 1):
            sub = string[i:pat_len]
            if (sub == pattern):
                index = i
                break

    return index

# Список для теста, для поиска элемента
test_str = [
    ["a", "ab", "aa"], ["b", "bb", "bc"], ["d", "dd", "de"],
    ["ac", "e", "db"], ["da", "w", "aa"], ["ba", "b", "db"],
    ["a", "ab", "aa"], ["b", "bb", "bc"], ["d", "dd", "aa"] ]

for i in range(len(test_str)):
    for j in range(len(test_str[i])):
        id = brute_force(test_str[i][j], "aa")
        if id != -1:
            print(f"id = test_str[{i}][{j}]")