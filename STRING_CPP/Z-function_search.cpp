#include <iostream>
using namespace std;

/*Алгоритм поиска с помощью Z-функции*/
void get_Z_array(string &str, int *Z);			// Формирует Z-массив 

int search(string &text, string &pattern) {		// Поиск подстроки в строке с помощью Z-алгоритма
	
	string concat = pattern + "$" + text;		// Конкатенация строки "Pattern + $ + Text" для Z-алгоритма
	int l = static_cast<int>(concat.length());	// Размер склееной строки для Z-массива индексов
	int *Z = new int[l];						// Z-массив индексов
	get_Z_array(concat, Z);						// Z-функция для формирования Z-массива

	for (int i = 0; i < l; ++i)	{				// Итерация по Z-массиву для поиска индекса вхождения подстроки в строку
		if (Z[i] == pattern.length())			// Если значение по индексу == длине искомого шаблона, значит есть вхождение 
			// Вернуть индекс первого элемента
			//cout << "Pattern found at index " << i - pattern.length() - 1 << endl;
			return i - static_cast<int>(pattern.length()) - 1;
	}
	return -1;
}

void get_Z_array(string &str, int *Z) {			// Заполнение (формирование) Z-массива для заданной строки
	int n = static_cast<int>(str.length());		// Длина (размер) строки
	int L = 0, R = 0, k;						// Индексы для манипуляций в циклах

	for (int i = 1; i < n; ++i)	{
		if (i > R) {							// Если i > R - значит будет использован наивный способ формирования Z-массива
			L = R = i;
			/*R-L = 0 при запуске, поэтому он начнет проверку с 0-го индекса.
			Например, для "ababab" и i = 1 значение R остается 0, а Z[i] становится 0.
			Для строки "aaaaaa" и i = 1, Z[i] и R становятся 5*/
			while (R < n && str[R - L] == str[R])
				R++;
			Z[i] = R - L;
			R--;
		}
		else {
			k = i - L;				// k соответствует числу, которое совпадает в интервале[L, R].
			if (Z[k] < R - i + 1)	// Если Z[k] меньше оставшегося интервала тогда Z[i] будет равно Z[k].
				Z[i] = Z[k];		// Например, str = "ababab", i = 3, R = 5 и L = 2
			else {
				L = i;
				while (R < n && str[R - L] == str[R])
					R++;
				Z[i] = R - L;
				R--;
			}
		}
	}
}

int main() {
	string text = "AbfjjHHHDHKnvkxmcTorklsUUnc";
	string pattern = "Tor";
	cout << "Find id pattern = " << search(text, pattern);
	return 0;
}