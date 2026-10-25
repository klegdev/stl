#include "transform_containers.h"
#include <algorithm>
std::map<int, std::string> removeDuplicateAndTranformToMap(std::list<std::string> list,
                                                           std::deque<int> deq) {
    list.sort();
    auto list_it = std::unique(list.begin(), list.end());
    list.erase(list_it, list.end());
    std::sort(deq.begin(), deq.end());
    auto deq_it = std::unique(deq.begin(), deq.end());
    deq.erase(deq_it, deq.end());

    std::map<int, std::string> result;

    auto n = std::min(list.size(), deq.size());
    std::transform(deq.begin(), std::next(deq.begin(), n),
                   list.begin(), std::inserter(result, result.end()),
                   [](int key, const std::string& value) {
                       return std::make_pair(key, value);
                   });
    return result;
}