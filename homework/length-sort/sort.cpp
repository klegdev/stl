#include "sort.hpp"

std::deque<std::string> lengthSort(const std::forward_list<std::string>& fl) {
    std::deque<std::string> deq;
    auto fl_sorted = fl;
    fl_sorted.sort([](const std::string& str_first, const std::string& str_second) {
        if (str_first.size() != str_second.size())
            return str_first.size() < str_second.size();
        else {
            return str_first.compare(str_second) < 0;
        }
    });
    deq.insert(deq.begin(), fl_sorted.begin(), fl_sorted.end());
    return deq;
}