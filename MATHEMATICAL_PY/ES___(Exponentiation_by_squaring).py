# Алгоритмы возведение в степень
import random

# Для положительных целочисленных степеней и чисел
def pow_iter(base, power):
    res = 1
    while power > 1:
        if power % 2 == 1:
            res *= base
        base *= base
        power //= 2
    if power > 0:
        res *= base
    return res

# Рекурсивное возведение в степень для положительных целых степеней
def pow_rec(num, power):
    return 1 if power == 0 else num * pow_rec(num, power - 1)

# Индийский алгоритм возведения в степень за логарифмическое время.
def pow_ind(num, power):
    return 1 if power == 0 else (num if (power & 1) else 1) * pow_ind(num * num, power // 2)

# Возведение двойки в степень (для 64-х разрядной '1 i64', для 32-х - просто 1)
def pow_two(power):
    return 1 << power

# Алгоритм: Бинарное возведение в степень
def bin_power(b, e):
    v = 1.0
    while e != 0:
        if (e & 1) != 0:
            v *= b
        b *= b
        e >>= 1
    return v


for _ in range(3):
    a = random.randint(1, 100)
    b = random.randint(1, 10)
    print(f"Num = {a}  :  Pow = {b}")
    print(f"Pow_iter = {pow_iter(a, b)}")
    print(f"Pow_rec  = {pow_rec(a, b)}")
    print(f"Pow_ind  = {pow_ind(a, b)}")
    print(f"Bin_pow  = {bin_power(a, b)}")

print(f"Pow two  = {pow_two(50)}")
print(f"Pow two  = {pow_two(5)}")
print(f"Pow two  = {pow_two(10)}")