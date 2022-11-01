"""Алгоритм поиска подстроки в строке - Rabin Karp search"""

def rk(string, pattern):
    pat_hash = hash(pattern)
    n, m = len(string), len(pattern)
    for i in range(n-m+1):
        txt_hash = hash(string[i:i + m])
        if txt_hash == pat_hash:
            if string[i:i+m] == pattern:
                return i
    return -1
"""******************************************************"""

"""****Алгоритм поиска подстроки в строке - rk_search****"""
MAXCHAR = 256           # Кол-во символов в алфавите

def rk_search(pat, txt, q):
    M = len(pat)        # Длина искомой строки
    N = len(txt)        # Длина исходной строки
    p_hash = 0          # Хэш искомой строки
    t_hash = 0          # Хэш исходной
    m_hash = 1          # Хэш для манипуляций со строкой (шаблон сдвига)
    j = 0               # Индекс для цикла

    for i in range(M - 1):          # m_hash == "pow(d, M-1)%q"
        m_hash = (m_hash * MAXCHAR) % q

    for i in range(M):              # Создание шаблона хэша для исходной и искомой строки
        p_hash = (MAXCHAR * p_hash + ord(pat[i])) % q
        t_hash = (MAXCHAR * t_hash + ord(txt[i])) % q

    for i in range(N - M + 1):      # Перемещение шаблона (хэша) по строке
        if p_hash == t_hash:        # Если хэши совпадают - тогда проверять посимвольно
            # Check for characters one by one
            for j in range(M):
                if txt[i + j] != pat[j]:
                    break
                else:
                    j += 1
            if j == M:                          # Значит нашел искомую подстроку
                return i
        # Если i < количества символов в исходной строке, значит паттерн ещё может встретиться
        # Тогда нужно пересчитать хэш для следующей итерации, как бы сдвинуть указатели начало и конца на 1 шаг
        # нужно удалить начальный символ и добавить один (конечный) символ и пересчитать хэш
        if i < N - M:
            t_hash = (MAXCHAR * (t_hash - ord(txt[i]) * m_hash) + ord(txt[i + M])) % q
            # Чтобы не получить отрицательного значения
            if t_hash < 0:
                t_hash = t_hash + q
    return -1
"""******************************************************"""


if __name__ == '__main__':
    txt = "Back to Rabin-Karp Algorithm"
    pat = "gor"
    q = 101

    print(f"Found id pattern == {rk_search(pat, txt, q)}")
    print(f"Found id pattern == {rk(txt, pat)}")