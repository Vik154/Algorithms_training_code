#include <iostream>
#include <string> 
#include <vector>
using namespace std;

/********Поиск методом Кнута–Морриса–Пратта - kmp_search*******/
size_t kpm_search(const string &str, const string &pattern) {
    
    size_t i, j, str_len, sub_len;
    str_len = str.size();
    sub_len = pattern.size();

    vector<size_t> prefix(sub_len);
    // Вычисление префикс-функции
    prefix[0] = 0;
    for (i = 1, j = 0; i < sub_len; i++) {
        while (j > 0 && pattern[j] != pattern[i])
            j = prefix[j - 1];
        if (pattern[j] == pattern[i])
            j++;
        prefix[i] = j;
    }
    // Поиск
    for (i = 0, j = 0; i < str_len; i++) {
        while (j > 0 && pattern[j] != str[i])
            j = prefix[j - 1];
        if (pattern[j] == str[i])
            j++;
        if (j == sub_len) {
            prefix.clear();
            return i - j + 1;
        }
    }
    prefix.clear();
    return -1;
}
/**************************************************************/

int main() {
    setlocale(LC_ALL, "ru");

    string pattern = "ru";
    string ss = "abcdjfidklfklmvckmruдвдлОТГОТллыruждыфы";
    std::cout << kpm_search(ss, pattern);

    std::cout << "\n--------------------\n";

    char str[] = "абвгдНрлттвWnjcxnjsdsiРРгодвдвYYTgdbya-ho-ho,dlfddfdf;w''dd,c";
    char pat[] = "ya-ho";
    std::cout << kpm_search(str, pat) << "\n";

    return 0;
}