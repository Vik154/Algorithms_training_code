#include <iostream>
#include <string>  
#include <vector>

/******Полный перебор (грубая сила) - brute_force*******/
int brute_force(const std::string& text, const std::string& pattern) {
    size_t pat_l = pattern.length();						// Получить размер искомой строки
    size_t txt_l = text.length();							// Получить размер исходной строки
    int index = -1;											// Индекс найденной подстроки, а иначе вернет -1
    if (pat_l <= txt_l) {									// Если длина искомой меньше длины исходной
        for (size_t i = 0; i < txt_l - pat_l + 1; i++) {	// С начала исходной до конца исходной минус искомой +1 символ
            std::string s = text.substr(i, pat_l);			// Вернет подстроку начиная с i и количеством симолов pat_l
            if (s == pattern) {								// Если сформированная подстрока == искомой
                index = i;									// В индекс поместить указатель на первый элемент массива чаров
                break;										// Закончить и вернуть индекс первого символа
            }
        }
    }
    return index;
}

/*******Множество для теста******/
std::vector<std::vector<std::string>> test_set = {
    // {text, pattern, expected output}
    {"a", "aa", "-1"},  {"a", "a", "0"},    {"ba", "b", "0"},
    {"bba", "bb", "0"}, {"bbca", "c", "2"}, {"ab", "b", "1"},
    {"c", "cc", "cdd"}, {"dcdc", "d", "c"}, {"aa", "b", "1"} };


int main() {
	setlocale(LC_ALL, "Ru");
	std::string str_default("abcdabcdrgfhdkjknxkanahnhuiooeprrphfgd");	// Исходная строка
	std::string str_pattern("nah");										// Искомая

	int id = brute_force(str_default, str_pattern);						// Возвращает индекс на 1ый элемент
	std::cout << str_default[id] << "\n";								// Выведет 1-ый символ искомой
	std::cout << str_default.substr(id, str_pattern.length()) << "\n";	// Выведет искомую подстроку
	
	std::cout << "=============На итераторах================\n";

	std::vector<std::vector<std::string>>::iterator iter_set = test_set.begin();
	std::vector<std::string>::iterator iter_str;

	for (iter_set; iter_set != test_set.end(); iter_set++) {
		for (iter_str = iter_set->begin(); iter_str != iter_set->end(); iter_str++) {
			std::string pattern_1 = "ab";
			std::string pattern_2 = "cd";

			int id_1 = brute_force(*iter_str, pattern_1);
			int id_2 = brute_force(*iter_str, pattern_2);

			if (id_1 != -1) std::cout << "OK\n";
			if (id_2 != -1) std::cout << "OK\n";
			else std::cout << "No found\n";	
		}
	}

	std::cout << "===========На индексах================\n";

	for (int i = 0; i < test_set.size(); ++i) {
		for (int j = 0; j < test_set[i].size(); ++j) {
			std::string pattern_1 = "ab";
			std::string pattern_2 = "cd";

			int id_1 = brute_force(test_set[i][j], pattern_1);
			int id_2 = brute_force(test_set[i][j], pattern_2);

			if (id_1 != -1) std::cout << "OK\n";
			if (id_2 != -1) std::cout << "OK\n";
			else std::cout << "No found\n";
		}
	}

	std::cout << "======Auto C++17 - C++20========\n";

	for (const auto& i : test_set) {
		for (const auto j : i) {
			std::string pattern_1 = "ab";
			std::string pattern_2 = "cd";

			int id_1 = brute_force(j, pattern_1);
			int id_2 = brute_force(j, pattern_2);
			if (id_1 != -1) { std::cout << "OK\n"; }
			if (id_2 != -1) { std::cout << "OK\n"; }
		}
	}

	return 0;
}