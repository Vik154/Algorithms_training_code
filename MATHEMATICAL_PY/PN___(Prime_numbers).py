# Алгоритмы простых чисел - Поиск,
# Факторизация, решето Эратосфена, Аткина, Сундарама
import math

# Проверка на простоту O(N) - Простым называется натуральное число,
# которое делится только на единицу и на себя.
def is_prime(n):
    if n == 1:
        return False
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

# Проверка на простоту O(sqrt(N))
def is_prime2(n):
    if n == 1:
        return False
    i = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += 1
    return True

# Факторизация - разложение на простые множители
def factorize(n):
    factors = []
    i = 2
    while i * i <= n:
        while n % i == 0:
            n //= i
            factors.append(i)
        i += 1
    if n > 1:
        factors.append(n)
    return factors


# Решето Эратосфена O(N * sqrt(N)) - поиск всех простых числа в диапазоне до N
def eratosfen(n):
    prime = [1] * (n + 1)
    prime[0], prime[1] = 0, 0
    for i in range(2, n + 1):  # можно и до sqrt(N)
        if prime[i]:
            for j in range(2 * i, n + 1, i):  # идем с шагом i, можно начиная с i * i
                prime[j] = 0
    return prime

# Решето Эратосфена O(N) - для каждого числа до N его минимальный простой делитель
def eratosfen2(n):
    primes = []
    min_d = [0] * (n + 1)
    for i in range(2, n + 1):
        if min_d[i] == 0:
            min_d[i] = i
            primes.append(i)
        for p in primes:
            if p > min_d[i] or i * p > n:
                break
            min_d[i * p] = p
    return primes

# Решето Аткина - нахождение всех простых чисел, не превышающих заданное натуральное limit
def atkin_sieve(limit):
    results = [2, 3, 5]
    sieve = [False] * (limit + 1)
    factor = int(math.sqrt(limit)) + 1
    for i in range(1, factor):
        for j in range(1, factor):
            n = 4 * i ** 2 + j ** 2
            if (n <= limit) and (n % 12 == 1 or n % 12 == 5):
                sieve[n] = not sieve[n]
            n = 3 * i ** 2 + j ** 2
            if (n <= limit) and (n % 12 == 7):
                sieve[n] = not sieve[n]
            if i > j:
                n = 3 * i ** 2 - j ** 2
                if (n <= limit) and (n % 12 == 11):
                    sieve[n] = not sieve[n]
    for index in range(5, factor):
        if sieve[index]:
            for jndex in range(index ** 2, limit, index ** 2):
                sieve[jndex] = False
    for index in range(7, limit):
        if sieve[index]:
            results.append(index)
    return results

# Решето Сундарама — детерминированный алгоритм нахождения всех простых чисел до N
def sundaram(limit):
    res_arr  = (limit - 1) // 2
    bool_arr = [True] * res_arr
    j = i = 1
    while (i + j + 2 * i * j) <= res_arr:
        while (i + j + 2 * i * j) <= res_arr:
            bool_arr[2 * i * j + i + j - 1] = False
            j += 1
        i += 1
        j = i
    primes = [2]
    for i in range(0, res_arr):
        if bool_arr[i]:
            primes.append(i * 2 + 3)
    return primes


def main():
    print(f"Проверка чисел на простое или составное")
    for i in [1, 2, 3, 10, 11, 12, 105, 1007]:
        print(f"{i} ->", is_prime2(i), end='; ')
    print(f"\nФакторизация - разложение на простые множители")
    for i in [2, 3, 10, 11, 12, 105, 1007]:
        print(i, '=', ' x '.join(str(x) for x in factorize(i)), end='; ')
    print(f"\nРешето Эратосфена bool в дипазоне 50:")
    res = eratosfen(50)
    print(res, end=' ')
    print(f"\nРешето Эратосфена в дипазоне 50:")
    res = eratosfen2(50)
    print(res, end=' ')
    print(f"\nРешето Аткина в дипазоне 50:")
    res = atkin_sieve(50)
    print(res, end=' ')
    print(f"\nРешето Синдарама в дипазоне 50:")
    res = sundaram(50)
    print(res, end=' ')

if __name__ == "__main__":
    main()