"""****Нахождение наибольшей общей подпоследовательности
*****longest common subsequence search, LCS**************"""

def lcs_search(txt, sub):
    len_str1 = len(txt)
    len_str2 = len(sub)
    res = ""
    max_len = [[0] * (len_str2 + 1)] * (len_str1 + 1)

    for i in range(len_str1 - 1, -1, -1):
        for j in range(len_str2 - 1, -1, -1):
            if txt[i] == sub[j]:
                max_len[i][j] = 1 + max_len[i + 1][j + 1]
            else:
                max_len[i][j] = max(max_len[i + 1][j], max_len[i][j + 1])

    i = j = 0
    while max_len[i][j] != 0 and i < len_str1 and j < len_str2:
        if txt[i] == sub[j]:
            res += txt[i]
            i += 1
            j += 1
        else:
            if max_len[i][j] == max_len[i + 1][j]:
                i += 1
            else:
                j += 1

    return res


if __name__ == "__main__":
    txt = "Алгоритм нахождения самой длинной общей подпоследовательности подстроки";
    sub = "самой длинной общей подстроки";
    print(lcs_search(txt, sub))