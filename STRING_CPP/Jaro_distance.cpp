#include <string>
#include <iostream>

using std::string;
using std::max;
using std::min;
using std::cout;

/**************Сходство Джаро — Винклера*************************/
double jaro_distance(const string &str_1, const string &str_2) {
	if (str_1 == str_2)
		return 1.0;
	int64_t len1 = str_1.length();		// Размер 1 строки
	int64_t	len2 = str_2.length();		// Размер 2 строки
	int64_t match = 0, i = 0, j = 0;    // Количество совпадений и индексы
	// Максимальное расстояние, до которого допускается совпадение
	int64_t max_dist = static_cast<int64_t>(floor(max(len1, len2) / 2) - 1);
	// Хэш для совпадений hash_s1[s1.length()] = { 0 }, hash_s2[s2.length()] = { 0 };
	int64_t *hash_s1 = new int64_t[str_1.length()] {0};
	int64_t *hash_s2 = new int64_t[str_2.length()] {0};

	// Пройти по первой строке и проверить совпадения
	for (i = 0; i < len1; i++) {
		for (j = max(int64_t(0), i - max_dist);
			j < min(len2, i + max_dist + 1); j++)
			// Еслие есть совпадения
			if (str_1[i] == str_2[j] && hash_s2[j] == 0) {
				hash_s1[i] = 1;
				hash_s2[j] = 1;
				match++;
				break;
			}
	}
	// Если совпадения не были найдены
	if (match == 0)
		return 0.0;
	// Количество транспозиций
	double t = 0;
	int64_t point = 0;
	// Подсчитать количество вхождений где два символа совпадают, но
	// есть третий совпадающий символ между индексами
	for (i = 0; i < len1; i++)
		if (hash_s1[i]) {
			// Поиск следующего совпадающего символа во второй строке
			while (hash_s2[point] == 0)
				point++;
			if (str_1[i] != str_2[point++])
				t++;
		}
	t /= 2;
	// Вернуть подобие Jaro
	return (((double)match) / ((double)len1)
		+ ((double)match) / ((double)len2)
		+ ((double)match - t) / ((double)match))
		/ 3.0;
}
/****************************************************************/

// Jaro Winkler Similarity //
double jaro_winkler(const string &str_1, const string &str_2) {
	double jaro_dist = jaro_distance(str_1, str_2);
	
	if (jaro_dist > 0.7) {			// Если сходство jaro превышает пороговое значение
		int64_t prefix = 0;			// Найдите длину общего префикса

		for (int64_t i = 0; i < int64_t(min(str_1.length(), str_2.length())); i++) {
			if (str_1[i] == str_2[i])			// Если символы совпадают
				prefix++;
			else
				break;
		}
		prefix = min(int64_t(4), prefix);				// В префиксе допускается не более 4 символов
		jaro_dist += 0.1 * prefix * (1 - jaro_dist);	// Вычислить сходство jaro winkler
	}
	return jaro_dist;
}


int main() {
	string s1 = "PATTERN";
	string s2 = "PATERN";
	cout << "jaro_distance == " << jaro_distance(s1, s2) << "\n";
	cout << "jaro_winkler == "  << jaro_winkler(s1, s2)  << "\n";
	return 0;
}