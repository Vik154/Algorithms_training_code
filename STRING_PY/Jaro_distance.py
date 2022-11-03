from math import floor

"""********Сходство Джаро — Винклера***********"""
def jaro_distance(str1, str2):
    if str1 == str2:
        return 1.0
    len1 = len(str1)
    len2 = len(str2)
    max_dist = floor(max(len1, len2) / 2) - 1
    match = 0
    hash_s1 = [0] * len(str1)
    hash_s2 = [0] * len(str2)

    for i in range(len1):
        for j in range(max(0, i - max_dist), min(len2, i + max_dist + 1)):
            if (str1[i] == str2[j] and hash_s2[j] == 0):
                hash_s1[i] = 1
                hash_s2[j] = 1
                match += 1
                break

    if (match == 0):
        return 0.0
    t = 0
    point = 0
    for i in range(len1):
        if (hash_s1[i]):
            while (hash_s2[point] == 0):
                point += 1
            if (str1[i] != str2[point]):
                t += 1
            point += 1
    t = t // 2

    return (match / len1 + match / len2 + (match - t) / match) / 3.0
"""********************************************"""

# Jaro Winkler Similarity
def jaro_winkler(str_1, str_2):
    jaro_dist = jaro_distance(str_1, str_2)

    if jaro_dist > 0.7:
        prefix = 0
        for i in range(min(len(str_1), len(str_2))):
            if str_1[i] == str_2[i]:
                prefix += 1;
            else:
                break
        prefix = min(4, prefix)
        jaro_dist += 0.1 * prefix * (1 - jaro_dist)

    return jaro_dist


s1 = "PRINT"
s2 = "PRINTS"
print(round(jaro_distance(s1, s2), 6))
print(round(jaro_winkler(s1, s2), 6))