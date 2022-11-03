#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::min;

/*Алгоритм метрики - Расстояние Левенштейна (дистанция редактирования)*/
template<typename Type>
size_t levenstein_distance(const Type& source, const Type& target) {
    if (source.size() > target.size()) {
        return levenstein_distance(target, source);
    }
    size_t min_size = source.size();
    size_t max_size = target.size();
    vector<size_t> lev_dist(min_size + 1);

    for (size_t i = 0; i <= min_size; ++i) {
        lev_dist[i] = i;
    }
    for (size_t j = 1; j <= max_size; ++j) {
        size_t previous_diagonal = lev_dist[0], previous_diagonal_save;
        ++lev_dist[0];

        for (size_t i = 1; i <= min_size; ++i) {
            previous_diagonal_save = lev_dist[i];
            if (source[i - 1] == target[j - 1]) {
                lev_dist[i] = previous_diagonal;
            }
            else {
                lev_dist[i] = min(min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
            }
            previous_diagonal = previous_diagonal_save;
        }
    }
    return lev_dist[min_size];
}
/**********************************************************************/

int main() {
    setlocale(0, "ru");
    string src = "котик";
    string dst = "скотина";
    std::cout << "dst == " << levenstein_distance(src, dst);
}