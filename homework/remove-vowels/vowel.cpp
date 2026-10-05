#include "vowel.hpp"
#include <algorithm>
#include <string>
#include <vector>

void removeVowels(std::vector<std::string>& vec) {
    std::vector<char> vowels = {'a', 'e', 'i', 'o', 'u', 'y'};

    for (auto& str : vec) {
        str.erase(
            std::remove_if(str.begin(), str.end(), [&vowels](char letter) {
                return std::find(vowels.begin(), vowels.end(), std::tolower(letter)) != vowels.end();
            }),
            str.end());
    }
}