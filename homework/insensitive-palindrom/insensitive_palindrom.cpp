#include "insensitive_palindrom.h"
#include <algorithm>

bool is_palindrome(std::string text) {
    std::string text_cleared = text;
    auto it = std::remove_if(
        text_cleared.begin(), text_cleared.end(),
        [](unsigned char c) {
            return !(
                (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9'));
        });
    text_cleared.erase(it, text_cleared.end());
    std::transform(text_cleared.begin(), text_cleared.end(), text_cleared.begin(),
                   [](unsigned char c) { return tolower(c); });
    return std::equal(
        text_cleared.begin(),
        text_cleared.end(),
        text_cleared.rbegin());
}