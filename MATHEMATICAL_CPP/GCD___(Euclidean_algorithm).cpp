/*Алгоритм Евклида - наибольший общий делитель НОД*/
/*Наибольший общий делитель(greatest common divisor)*/
#include <iostream>
using std::cout;

// Хвостовая рекурсия
int gcd_rec(const int &a,const int &b) {
    if (b == 0)
        return a;
    return gcd_rec(b, a % b);
}

// Итерационный вариант
int gcd_iter(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Бинарный вариант - рекурсивная версия
int gcd_brec(int a, int b) {
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (a == b)
        return a;
    if (a == 1 || b == 1)
        return 1;
    if (a % 2 == 0 && b % 2 == 0)
        return 2 * gcd_brec(a / 2, b / 2);
    if (a % 2 == 0 && b % 2 != 0)
        return gcd_brec(a / 2, b);
    if (a % 2 != 0 && b % 2 == 0)
        return gcd_brec(a, b / 2);
    if (a < b)
        return gcd_brec((b - a) / 2, a);
    else
        return gcd_brec((a - b) / 2, b);
}

// Бинарный вариант - итерационная версия
int gcd_biter(int a, int b) {
    int tmp, nod = 1;
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (a == b)
        return a;
    if (a == 1 || b == 1)
        return 1;
    while (a != 0 && b != 0) {
        if (a % 2 == 0 && b % 2 == 0) {
            nod *= 2;
            a /= 2;
            b /= 2;
            continue;
        }
        if (a % 2 == 0 && b % 2 != 0) {
            a /= 2;
            continue;
        }
        if (a % 2 != 0 && b % 2 == 0) {
            b /= 2;
            continue;
        }
        if (a > b) {
            tmp = a;
            a = b;
            b = tmp;
        }
        tmp = a;
        a = (b - a) / 2;
        b = tmp;
    }
    if (a == 0)
        return nod * b;
    else
        return nod * a;
}

// Бинарный вариант - итерационная версия (используя битовые сдвиги)
int gcd_bit(int a, int b) {
    int tmp, nod = 1;
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (a == b)
        return a;
    if (a == 1 || b == 1)
        return 1;
    while (a != 0 && b != 0) {
        if (((a & 1) | (b & 1)) == 0) {
            nod <<= 1;
            a >>= 1;
            b >>= 1;
            continue;
        }
        if (((a & 1) == 0) && (b & 1)) {
            a >>= 1;
            continue;
        }
        if ((a & 1) && ((b & 1) == 0)) {
            b >>= 1;
            continue;
        }
        if (a > b) {
            tmp = a;
            a = b;
            b = tmp;
        }
        tmp = a;
        a = (b - a) >> 1;
        b = tmp;
    }
    if (a == 0)
        return nod * b;
    else
        return nod * a;
}

// НОК - наименьшее общее кратное (least common multiple)
int lcm(int a, int b) {             //используя форму a * b / gcd(a, b), можно получить переполнение на этапе a * b,
    return a / gcd_iter(a, b) * b;  //поэтому следует выполнять деление до умножения  
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int a, b;
    for (int i = 0; i < 3; ++i) {
        a = rand() % 1000;
        b = rand() % 1000;
        cout << "a = " << a << "  :  " << "b = " << b << "\n";
        cout << "NOD iter  = " << gcd_iter(a, b)  << "\n";
        cout << "NOD rec   = " << gcd_rec(a, b)   << "\n";
        cout << "NOD brec  = " << gcd_brec(a, b)  << "\n";
        cout << "NOD biter = " << gcd_biter(a, b) << "\n";
        cout << "NOD bit   = " << gcd_bit(a, b)   << "\n";
        cout << "NOK rec   = " << lcm(a, b)       << "\n";
        cout << "==============================\n";
    }
}