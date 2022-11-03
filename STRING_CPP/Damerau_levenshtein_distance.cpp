#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::min;

/******Расстояние Дамерау — Левенштейна (дистанция редактирования)*****/
int64_t damerau_levenshtein_distance(const string &txt_1, const string &txt_2) {
    if (txt_1.size() < txt_2.size()) {
        return damerau_levenshtein_distance(txt_2, txt_1);
    }
    int64_t len_str1 = txt_1.length();
    int64_t len_str2 = txt_2.length();
    int64_t i = 0, j = 0, l_cost = 0;

    int64_t **d = new int64_t* [len_str1 + 1];
    for (i = 0; i < len_str1 + 1; ++i) {
        d[i] = new int64_t[len_str2 + 1];
    }
    for (i = 0; i <= len_str1; i++) {
        d[i][0] = i;
    }
    for (j = 0; j <= len_str2; j++) {
        d[0][j] = j;
    }
    for (i = 1; i <= len_str1; i++) {
        for (j = 1; j <= len_str2; j++) {
            if (txt_1[i - 1] == txt_2[j - 1]) {
                l_cost = 0;
            }
            else {
                l_cost = 1;
            }
            d[i][j] = min(d[i - 1][j] + 1, min(d[i][j - 1] + 1, d[i - 1][j - 1] + l_cost));
            //              delete                insert             substitution
            if ((i > 1) && (j > 1) && (txt_1[i - 1] == txt_2[j - 2]) && (txt_1[i - 2] == txt_2[j - 1])) {
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + l_cost);  // transposition
            }
        }
    }
    int64_t result = d[len_str1][len_str2];
    for (i = 0; i < len_str1 + 1; ++i)
        delete[] d[i];
    delete[] d;
    return result;
}
/***************************************************************/

int main() {
    string st1 = "собака";
    string st2 = "бабака";
    cout << "dist == " << damerau_levenshtein_distance(st1, st2);
    return 0;
}