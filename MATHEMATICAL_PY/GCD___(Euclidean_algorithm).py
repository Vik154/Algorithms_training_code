"""Алгоритм Евклида - наибольший общий делитель НОД
---Наибольший общий делитель(greatest common divisor)"""
import random

# Хвостовая рекурсия
def gcd_rec(a, b):
    if b == 0:
        return a
    return gcd_rec(b, a % b)

# Итерационный вариант
def gcd_iter(a, b):
    while b != 0:
        b, a = a % b, b
    return a

# Бинарный вариант - рекурсивная версия
def gcd_brec(a, b):
    if a == 0:
        return b
    if b == 0:
        return a
    if a == b:
        return a
    if a == 1 or b == 1:
        return 1
    if a % 2 == 0 and b % 2 == 0:
        return 2 * gcd_brec(a // 2, b // 2)
    if a % 2 == 0 and b % 2 != 0:
        return gcd_brec(a // 2, b)
    if a % 2 != 0 and b % 2 == 0:
        return gcd_brec(a, b // 2)
    if a < b:
        return gcd_brec((b - a) // 2, a)
    else:
        return gcd_brec((a - b) // 2, b)

# Бинарный вариант - итерационная версия
def gcd_biter(a, b):
    nod = 1
    if a == 0:
        return b
    if b == 0:
        return a
    if a == b:
        return a
    if a == 1 or b == 1:
        return 1
    while a != 0 and b != 0:
        if a % 2 == 0 and b % 2 == 0:
            nod *= 2
            a //= 2
            b //= 2
            continue
        if a % 2 == 0 and b % 2 != 0:
            a //= 2
            continue
        if a % 2 != 0 and b % 2 == 0:
            b //= 2
            continue
        if a > b:
            a, b = b, a
        a, b = (b - a) // 2, a
    if a == 0:
        return nod * b
    else:
        return nod * a

# Бинарный вариант - итерационная версия (используя битовые сдвиги)
def gcd_bit(a, b):
    nod = 1
    if a == 0:
        return b
    if b == 0:
        return a
    if a == b:
        return a
    if a == 1 or b == 1:
        return 1
    while a != 0 and b != 0:
        if ((a & 1) | (b & 1)) == 0:
            nod <<= 1
            a >>= 1
            b >>= 1
            continue
        if ((a & 1) == 0) and (b & 1):
            a >>= 1
            continue
        if (a & 1) and (b & 1) == 0:
            b >>= 1
            continue
        if a > b:
            a, b = b, a
        a, b = (b - a) >> 1, a
    if a == 0:
        return nod * b
    else:
        return nod * a

# НОК - наименьшее общее кратное (least common multiple)
def lcm(a, b):                      # используя форму a * b / gcd(a, b), можно получить переполнение на этапе a * b,
    return a // gcd_iter(a, b) * b  # поэтому следует выполнять деление до умножения

def main():
    for _ in range(3):
        a = random.randint(0, 1000)
        b = random.randint(0, 1000)
        if a < b:
            a, b = b, a
        print(f"a = {a}  :  b = {b}")
        print(f"NOD iter  = {gcd_iter(a, b)}")
        print(f"NOD rec   = {gcd_rec(a, b)}")
        print(f"NOD brec  = {gcd_brec(a, b)}")
        print(f"NOD biter = {gcd_biter(a, b)}")
        print(f"NOD bit   = {gcd_bit(a, b)}")
        print(f"NOK rec   = {lcm(a, b)}")


if __name__ == "__main__":
    main()