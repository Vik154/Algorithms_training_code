#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;

/*****Алгоритм поиска подстроки - Бойера-Мура-Хорспула*****/
// Этап 1: формирование таблицы смещений
map<char, int64_t> table_shift(string pattern) {
    int64_t count_symbol = pattern.size();                      // Количество символов в искомой строке             
    set<char> unique_symbol;                                    // Уникальные символы в образе
    map<char, int64_t> dict_shift;                              // Словарь смещений вида {'a': 1, 'b': 2, 'c': 3, '$':3}

    for (int64_t i = count_symbol - 2; i > -1; --i) {           // Начиная с предпоследнего элемента в искомой строке
        if (unique_symbol.count(pattern[i]) != 1) {             // Если символ ещё не записан в словарь смещений
            dict_shift[pattern[i]] = count_symbol - i - 1;      // Добавить этот символ со значением индекса считая с конца
            unique_symbol.insert(pattern[i]);                   // Добавить уникальный символ в множество (в набор)
        }
    }
    if (!unique_symbol.count(pattern[count_symbol - 1])) {      // Проверить последний символ, если его нет в множестве
        dict_shift[pattern[count_symbol - 1]] = count_symbol;   // Тогда добавить символ в словарь зо значением последнего индекса + 1
    }
    dict_shift['%'] = count_symbol;                             // Добавить в словарь ограничительный символ
    return dict_shift;                                          // Вернуть получившийся словарь "смещений"
}

/**************Сам алгоритм поиска - bmh_search***************/
// Этап 2: поиск образа в строке
int64_t bmh_search(string txt, string pat) {               
    int64_t size_txt = static_cast<int64_t>(txt.size());        // Размер исходной строки
    int64_t size_pat = static_cast<int64_t>(pat.size());        // Размер искомой строки
    int64_t i = 0, k = 0, j = 0, off = 0;                       // Индексы для манипуляций в цикле
    map<char, int64_t> shift_tb = table_shift(pat);             // Словарь смещений сформированный по искомой строке

    if (size_txt >= size_pat) {                                 // Если исходная меньше искомой - вернуть -1
        i = size_pat - 1;                                       // Потск начинается с этого места
        while (i < size_txt) {                                  // Пока индекс меньше длины шаблона итерироваться по строке
            k = j = 0;                                          // Опять копипаста (можно опустить)
            bool fl_break = false;                              // Флаг для прерыванияцикла, если найдется подстрока или превысит размер
            for (j = size_pat - 1; j >= 0; --j) {               // Начиная с индекса == длине шаблона и в обратную сторону
                if (txt[i - k] != pat[j]) {                     // Если указатели не вышли за предел строки исходной, то
                    if (j == size_pat - 1) {                    // Проверить равен индекс длине шаблона
                        // Если равен тогда проверить посимвольно
                        off = shift_tb.count(txt[i]) != 1 ? shift_tb['%'] : shift_tb[txt[i]];
                    }
                    else {
                        off = shift_tb[pat[j]];
                    }
                    i = i + off;
                    fl_break = true;
                    break;
                }
                k++;
            }
            if (!fl_break) {
                return i - k + 1;
            }
        }
    }
    return -1;
}


int main() {
    setlocale(0, "Ru");
    string en_str = "The Boyer–Moore–Horspool is an algorithm for finding substrings in strings";
    string ru_str = "Алгоритм Бойера–Мура–Хорспула - это алгоритм для поиска подстрок в строках";
    string en_pat = "rithm";
    string ru_pat = "поиск";
    cout << "En pattern index == " << bmh_search(en_str, en_pat) << "\n";
    cout << "========================================================\n";
    cout << "Ru pattern index == " << bmh_search(ru_str, ru_pat) << "\n";
    return 0;
}