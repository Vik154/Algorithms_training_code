/*Алгоритмы возведение в степень*/
#include <iostream>

using std::cout;

// Для положительных целочисленных степеней и чисел
int64_t power(int64_t base, int64_t pow) {
	int64_t res = 1;
	while (pow > 1) {
		if (pow % 2 == 1)
			res *= base;
		base *= base;
		pow /= 2;
	}
	if (pow > 0)
		res *= base;
	return res;
}

// Рекурсивное возведение в степень для положительных целых степеней
int64_t pow_rec(int64_t num, int64_t pow) {
	return (!pow) ? 1 : num * pow_rec(num, pow - 1);
}

//Индийский алгоритм возведения в степень за логарифмическое время.
int64_t pow_ind(int64_t num, int64_t pow) {
	return (!pow) ? 1 : ((pow & 1) ? num : 1) * pow_ind(num * num, pow / 2);
}

// Возведение двойки в степень (для 64-х разрядной '1 i64', для 32-х - просто 1)
int64_t pow_two(int64_t pow) {
	return 1i64 << pow;
}

// Алгоритм: "Старая аппроксимация"
// Источник: https://habr.com/ru/post/584662/
double old_approxpow(double b, double e) {
	union {
		double d;
		long long i;
	} u = { b };
	u.i = (long long)(4606853616395542500L + e * (u.i - 4606853616395542500L));
	return u.d;
}

// Алгоритм: использованный в игре Quake III Arena 2005
// Он возводил число x в степень -0.5, т.е. находил значение: \frac{1}{\sqrt{x}}
// Источник: https://habr.com/ru/post/584662/
float fast_inv_sqrt(float x) {
	float xhalf = 0.5f * x;
	int i = *(int*)&x;          // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);  // what the fuck?
	x = *(float*)&i;
	x = x * (1.5f - (xhalf * x * x));
	return x;
}

// Алгоритм: Бинарное возведение в степень
double bin_power(double b, unsigned long long e) {
	double v = 1.0;
	while (e != 0) {
		if ((e & 1) != 0) {
			v *= b;
		}
		b *= b;
		e >>= 1;
	}
	return v;
}

// Алгоритм: "Делящая быстрая степень"
double fast_powdiv(double b, double e) {
	if (b == 1.0 || e == 0.0) {
		return 1.0;
	}
	double eAbs = fabs(e);
	double el = ceil(eAbs);
	double basePart = old_approxpow(b, eAbs / el);
	double result = bin_power(basePart, (unsigned long long)el);
	if (e < 0.0) {
		return 1.0 / result;
	}
	return result;
}

// Алгоритм: "Дробная быстрая степень"
double fast_power_fractional(double b, double e) {
	if (b == 1.0 || e == 0.0) {
		return 1.0;
	}
	double absExp = fabs(e);
	unsigned long long eIntPart = (long long)absExp;
	double eFractPart = absExp - eIntPart;
	double result = old_approxpow(b, eFractPart) * bin_power(b, eIntPart);
	if (e < 0.0) {
		return 1.0 / result;
	}
	return result;
}

// Алгоритм: "Другая аппроксимация"
double another_approximate_power(double a, double b) {
	union {
		double d;
		int x[2];
	} u = { a };
	u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
	u.x[0] = 0;
	return u.d;
}


int main() {
	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < 3; ++i) {
		int64_t num = static_cast<int64_t>(rand() % 100);
		int64_t pow = static_cast<int64_t>(rand() % 10);
		cout << "Num: " << num << " | Pow: " << pow << "\n";
		cout << "Power   = " << power(num, pow)     << "\n";
		cout << "Pow_rec = " << pow_rec(num, pow)   << "\n";
		cout << "Pow_ind = " << pow_ind(num, pow)   << "\n";
	}
	cout << "Two in pow:      " << pow_two(50) << "\n";
	cout << "Old approximate: " << old_approxpow(1.85, 15.37) << "\n";
	cout << "Fast_inv_sqrt:   " << fast_inv_sqrt(2) << "\n";
	cout << "bin_power:       " << bin_power(2.7, 50) << "\n";
	cout << "fast_powdiv:     " << fast_powdiv(-2.5, -2.6) << "\n";
	cout << "fast_fractional: " << fast_power_fractional(-2.5, -2.6) << "\n";
	cout << "another_approx:  " << another_approximate_power(3.2, 2.8) << "\n";
}