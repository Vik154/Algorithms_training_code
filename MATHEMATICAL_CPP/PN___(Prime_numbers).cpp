// Алгоритмы простых чисел - Поиск,
// Факторизация, решето Эратосфена,
#include <iostream>
#include <vector>

using std::vector;
using std::cout;

// Проверка на простоту O(N) - Простым называется натуральное число,
// которое делится только на единицу и на себя.
bool is_prime(int n) {
    if (n == 1)
        return false;
    for (int i = 2; i < n; ++i)
        if (n % i == 0)
            return false;
    return true;
}

// Проверка на простоту O(sqrt(N))
bool is_prime2(int n) {
    if (n == 1)
        return false;
    int i = 2;
    while (i * i <= n) {
        if (n % i == 0)
            return false;
        i++;
    }
    return true;
}

// Факторизация - разложение на простые множители
vector<int> factorize(int n) {
    vector<int> factors;
    int i = 2;
    while (i * i <= n) {
        while (n % i == 0) {
            n /= i;
            factors.push_back(i);
        }
        i++;
    }
    if (n > 1)
        factors.push_back(n);
    return factors;
}

// Решето Эратосфена O(N) - для каждого числа до N его минимальный простой делитель
vector<bool> eratosfen(int n) {
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= n; ++i)   // valid for n < 46340^2 = 2147395600
        if (prime[i])
            for (int j = i * i; j <= n; j += i)
                prime[j] = false;
    return prime;
}

// Решето Эратосфена O(N) - для каждого числа до N его минимальный простой делитель
vector<int> eratosfen2(int n) {
    vector<int> prime;
    vector<int> min_d(n + 1, 0);
    for (int i = 2; i < n + 1; ++i) {
        if (min_d[i] == 0) {
            min_d[i] = i;
            prime.push_back(i);
        }
        for (auto const& p : prime) {
            if (p > min_d[i] || i * p > n)
                break;
            min_d[i * p] = p;
        }
    }
    return prime;
}

// Решето Аткина - нахождение всех простых чисел, не превышающих заданное натуральное limit.
vector<bool> atkin_sieve(uint64_t const &limit) {
    // Предварительное просеивание
    vector<bool> sieve(limit);
    for (uint64_t x2 = 1, dx2 = 3; x2 < limit; x2 += dx2, dx2 += 2)
        for (uint64_t y2 = 1, dy2 = 3, n; y2 < limit; y2 += dy2, dy2 += 2) {
            // n = 4x² + y²
            n = (x2 << 2) + y2;
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
                sieve[n].flip();
            // n = 3x² + y²
            n -= x2;
            if (n <= limit && n % 12 == 7)
                sieve[n].flip();
            // n = 3x² - y² (при x > y)
            if (x2 > y2) {
                n -= y2 << 1;
                if (n <= limit && n % 12 == 11)
                    sieve[n].flip();
            }
        }
    // Все числа, кратные квадратам, помечаются как составные
    uint64_t r = 5;
    for (uint64_t r2 = r * r, dr2 = (r << 1) + 1; r2 < limit; ++r, r2 += dr2, dr2 += 2)
        if (sieve[r])
            for (uint64_t mr2 = r2; mr2 < limit; mr2 += r2)
                sieve[mr2] = false;
    // Числа 2 и 3 — заведомо простые
    if (limit > 2)
        sieve[2] = true;
    if (limit > 3)
        sieve[3] = true;
    return sieve;
}

// Решето Сундарама — детерминированный алгоритм нахождения всех простых чисел до N 
void sundaram(int n) {
    if (n < 2)
        return;
    int* a = new int[n], i, j, k;
    memset(a, 0, sizeof(int) * n);
    for (i = 1; 3 * i + 1 < n; i++) {
        for (j = 1; (k = i + j + 2 * i * j) < n && j <= i; j++) {
            a[k] = 1;
        }
    }
    cout << "2 ";
    for (i = 1; i < n; i++) {
        if (a[i] == 0) cout << (2 * i + 1) << " ";
    }
    delete[] a;
}


int main() {
    setlocale(0, "");
    vector<int> vec{ 1,2,3,10,11,12,105,1007 };

    cout << "Проверка чисел на простое или составное\n";
    for (auto const& val : vec) {
        cout << val << " -> ";
        is_prime2(val) ? cout << "true; " : cout << "false; ";
    }
    cout << "\nФакторизация - разложение на простые множители\n";
    for (auto const& val : vec) {
        cout << val << " = ";
        auto res = factorize(val);
        for (auto const& i : res)
            cout << i << " + ";
        cout << "; ";
    }
    cout << "\nРешето Эратосфена в дипазоне 50:\n";
    auto res = eratosfen2(50);
    for (auto const& i : res) {
        cout << i << " ";
    }
    cout << "\nРешето Аткина в диапазоне 50:\n";
    uint64_t lim = 50;
    vector<bool> primes = atkin_sieve(lim);
    for (uint64_t number = 2u; number < lim; ++number)
        if (primes[number])
            std::cout << number << ' ';
    
    cout << "\nРешето Сундарама в дипазоне 50:\n";
    sundaram(50/2);
}