#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*****Алгоритм Манакера - поиск самого большого палиндрома*****/
vector<int> manacher_odd(string s) {
    int n = static_cast<int>(s.size());
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for (auto c : s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}
/**************************************************************/

/**Поиск наибольшего палиндрома на основе алгоритма Манакера***/
string find_max_palindrome(const string &text) {
    if (text.size() == 0) {
        return "";
    }
    int64_t size = text.size() * 2 + 1;      // Размер массива для хранения значений 
    int64_t *longest = new int64_t[size+1];  // Массив 
    longest[0] = 0;                          // Начальная четная позиция это 0
    longest[1] = 1;                          // Начальная нечетная - это 1
    int64_t center_id = 1;
    int64_t right_id  = 2;
    int64_t right = 0, left = 0;
    int64_t max_len_palindrome = 0;
    int64_t max_center_index = 0;
    int64_t start = -1, end = -1, diff = -1;

    for (right = 2; right < size; ++right) {
        left = 2 * center_id - right;
        longest[right] = 0;
        diff = right_id - right;

        if (diff > 0) {
            longest[right] = std::min(longest[left], diff);
        }
        while (((right + longest[right]) < size && (right - longest[right]) > 0) &&
              (((right + longest[right] + 1) % 2 == 0) || 
              (text[(right + longest[right] + 1) / 2] == text[(right - longest[right] - 1) / 2])))
        {
            longest[right]++;
        }
        if (longest[right] > max_len_palindrome) {
            max_len_palindrome = longest[right];
            max_center_index = right;
        }
        if (right + longest[right] > right_id) {
            center_id = right;
            right_id = right + longest[right];
        }
    }
    start = (max_center_index - max_len_palindrome) / 2;
    end   = start + max_len_palindrome - 1;
    string palindrome;

    for (int64_t i = start; i <= end; i++)
        palindrome += text[i];
    return palindrome;
}

/*****Алгоритм Манакера******/
string longest_palindrome(const string &txt) {
    vector<char> str(txt.size() * 2 + 1, '#');     // Массив вида a#a#b#w#
    
    for (int i = 0; i != txt.size(); ++i) {       // Создаем псевдостроку с границами в виде символа '#'
        str[i * 2 + 1] = txt[i];
    }

    int *pal = new int[str.size() + 2];
    int r, c, index, i_mir;
    int maxLen = 1;
    i_mir = index = r = c = 0;

    for (int i = 1; i != str.size() - 1; ++i) {
        i_mir = 2 * c - i;
        pal[i] = r > i ? min(pal[i_mir], r - i) : 0;

        while (i > pal[i] && (i + pal[i] + 1) < str.size() && str[i - pal[i] - 1] == str[i + pal[i] + 1])
            ++pal[i];

        if (pal[i] + i > r) {
            c = i;
            r = i + pal[i];
        }
        if (maxLen < pal[i]) {
            maxLen = pal[i];
            index = i;
        }
    }
    return txt.substr((index - maxLen) / 2, maxLen);
}


int main() {
    // Test function find_max_palindrome();
    string text = "abcwawdeyejglyyfu";
    string palindrome = find_max_palindrome(text);
    cout << "Longest palindrome is: " << palindrome << endl;
    cout << "Test algorithm manacher 2:\n";
    cout << "Longest palindrome is: " << longest_palindrome(text);
    return 0;
}