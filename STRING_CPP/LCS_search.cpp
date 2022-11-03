#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::max;
using std::cout;

/****Нахождение наибольшей общей подпоследовательности 
*****longest common subsequence search, LCS************/
string lcs_search(const string &str1, const string&str2) {
    int64_t len_str1 = str1.size();
    int64_t len_str2 = str2.size();
    int64_t i, j;
    string res;
    vector<vector<int64_t>> max_len(len_str1 + 1);

    for (i = 0; i <= len_str1; ++i) {
        max_len[i].resize(len_str2 + 1);
    }
    for (i = len_str1 - 1; i >= 0; i--) {
        for (j = len_str2 - 1; j >= 0; j--) {
            if (str1[i] == str2[j]) {
                max_len[i][j] = 1 + max_len[i + 1][j + 1];
            }
            else {
                max_len[i][j] = max(max_len[i + 1][j], max_len[i][j + 1]);
            }
        }
    }
    for (i = 0, j = 0; max_len[i][j] != 0 && i < len_str1 && j < len_str2;) {
        if (str1[i] == str2[j]) {
            res.push_back(str1[i]);
            i++;
            j++;
        }
        else {
            if (max_len[i][j] == max_len[i + 1][j])
                i++;
            else
                j++;
        }
    }
    return res;
}
/******************************************************/

int main() {
    setlocale(0, "ru");
    string str = "Алгоритм нахождения самой длинной общей подпоследовательности подстроки";
    string sub = "самой длинной общей подстроки";
    cout << lcs_search(str, sub);
}