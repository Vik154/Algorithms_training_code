#include <iostream>
#include <string>
#define MAXCHAR 256								// Количество символов во входном алфавите
using namespace std;

/*****Алгоритм поиска подстроки в строке - Rabin Karp search*****/
/***************Алгоритм с википедии (на python)*****************/
size_t rk_search(const string& text, const string& pattern) {
	size_t n = text.size();
	size_t m = pattern.size();
	size_t pat_hash = hash<string>{} (pattern);

	for (size_t i = 0; i < n - m + 1; ++i) {
		string str_hash = text.substr(i, m);
		//cout << str_hash << endl;
		size_t txt_hash = hash<string>{} (str_hash);

		if (txt_hash == pat_hash) {
			if (str_hash == pattern)
				return i;
		}
	}
	return -1;
}
/*****************************************************************/

/*****Алгоритм поиска подстроки в строке - Rabin Karp search*****/
/* pattern - искомая подстрока; textx - исходная строка; q - простое число */
int rk_search(char* pat, char* txt, int q) {
	int M = static_cast<int>(strlen(pat));		// Длина искомой строки
	int N = static_cast<int>(strlen(txt));		// Длина исходной
	int pat_hash = 0;							// Хэш искомой строки
	int txt_hash = 0;							// Хэш исходной строки
	int h = 1;									// Хэш для манипуляций при уменьшинии диапазона поиска
	int i, j;									// Индексы для циклов

	for (i = 0; i < M - 1; i++)	{				//  "pow(d, M-1) % q" 
		h = (h * MAXCHAR) % q;
	}
	for (i = 0; i < M; i++) {					// Создание шаблона хэша для исходной и искомой строки
		pat_hash = (MAXCHAR * pat_hash + pat[i]) % q;
		txt_hash = (MAXCHAR * txt_hash + txt[i]) % q;
	}
	for (i = 0; i <= N - M; i++) {				// Перемещение шаблона (хэша) по строке
		if (pat_hash == txt_hash) {				// Если хэши совпадают - тогда проверять посимвольно
			for (j = 0; j < M; j++) {
				if (txt[i + j] != pat[j]) {
					break;
				}
			}
			if (j == M)							// Значит нашел искомую подстроку
				return i;
				//cout << "Pattern found at index " << i << endl;
		}
		// Если i < количества символов в исходной строке, значит паттерн ещё может встретиться
		// Тогда нужно пересчитать хэш для следующей итерации, как бы сдвинуть указатели начало и конца на 1 шаг
		// нужно удалить начальный символ и добавить один (конечный) символ и пересчитать хэш
		if (i < N - M) {
			txt_hash = (MAXCHAR * (txt_hash - txt[i] * h) + txt[i + M]) % q;
			// Чтобы не получить отрицательного значения
			if (txt_hash < 0)
				txt_hash = (txt_hash + q);
		}
	}
	return -1;
}
/***************************************************************************/

int main() {
	char txt[] = "Back to Rabin-Karp Algorithm";
	char pat[] = "gor";
	//int q = INT_MAX; - простое число
	int q = 101;

	cout << "Found id pattern == " << rk_search(pat, txt, q) << endl;
	cout << "Found id pattern == " << rk_search(txt, pat);
	return 0;
}