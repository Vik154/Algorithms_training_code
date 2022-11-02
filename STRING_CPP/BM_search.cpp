#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

/*Алгоритм поиска подстроки в строке Бойера — Мура - bm_search*/
vector<int64_t> prefix_func(const string& str);

int64_t bm_search(const string &str, const string &pat) {
    if (str.length() < pat.length())
        return -1;
    if (!pat.length())
        return str.length();

    unordered_map<uint8_t, int64_t> stop_table;     // Таблица стоп-символов
    unordered_map<int64_t, int64_t> suffics_table;  // Таблица суффиксов
    
    for (int64_t i = 0; i < pat.length(); ++i)
        stop_table[pat[i]] = i;

    string rt(pat.rbegin(), pat.rend());
    vector<int64_t> p = prefix_func(pat), pr = prefix_func(rt);
    for (int64_t i = 0; i < pat.length() + 1; ++i) {
        suffics_table[i] = pat.length() - p.back();
    }

    for (int64_t i = 1; i < pat.length(); ++i) {
        int64_t j = pr[i];
        suffics_table[j] = min(suffics_table[j], i - pr[i] + 1);
    }

    for (int64_t shift = 0; shift <= str.length() - pat.length();) {
        int64_t pos = pat.length() - 1;

        while (pat[pos] == str[pos + shift]) {
            if (pos == 0) return shift;
            --pos;
        }

        if (pos == pat.length() - 1) {
            unordered_map<uint8_t, int64_t>::const_iterator stop_symbol = stop_table.find(str[pos + shift]);
            int64_t stop_symbol_additional = pos - (stop_symbol != stop_table.end() ? stop_symbol->second : -1);
            shift += stop_symbol_additional;
        }
        else {
            shift += suffics_table[pat.length() - pos - 1];
        }
    }
    return -1;
}

/*Префикс функция - строит массив индексов совпадений*/
vector<int64_t> prefix_func(const string& str) {
    vector<int64_t> prefix(str.length());

    int64_t n = static_cast<int64_t>(str.length());
    int64_t k = 0;
    prefix[0] = 0;
    for (int64_t i = 1; i < n; ++i) {
        while (k > 0 && str[k] != str[i])
            k = prefix[k - 1];
        if (str[k] == str[i])
            ++k;
        prefix[i] = k;
    }
    return prefix;
}
/*************************************************************************/


int main() {
    string str = "abcdfgeyehujgfdz";
    string str2 = "Oldshulodlsdcxmjssasaxaewr";
    string pat = "eye";
    string pat2 = "od";
    std::cout << "Pattern found at position: " << bm_search(str, pat)   << "\n";
    std::cout << "Pattern found at position: " << bm_search(str2, pat2) << "\n";
    return 0;
}