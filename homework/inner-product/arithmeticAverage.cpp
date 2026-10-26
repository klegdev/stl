#include "arithmeticAverage.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>

double ArithmeticAverage(const std::vector<int>& vec_first, const std::vector<int>& vec_second) {
    if (vec_first.empty() && vec_second.empty())
        return 0;
    int sum_first = std::accumulate(vec_first.begin(), vec_first.end(), 0);
    int sum_second = std::accumulate(vec_second.begin(), vec_second.end(), 0);

    int sum = sum_first + sum_second;
    int size = vec_first.size() + vec_second.size();
    return static_cast<double>(sum) / size;
}

double Distance(const std::vector<int>& vec_first, const std::vector<int>& vec_second) {
    if (vec_first.size() != vec_second.size())
        return 0;
    if (vec_first.empty())
        return 0;
    double sum = 0;
    for (size_t i = 0; i < vec_first.size(); i++) {
        sum += std::pow(vec_second[i] - vec_first[i], 2);
    }
    return std::sqrt(sum);
}
