#include "compression.hpp"
#include <stdexcept>

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(std::array<std::array<uint8_t, width>, height> data) {
    std::vector<std::pair<uint8_t, uint8_t>> compressed_data = {};

    for (auto data_line : data) {
        uint8_t last_data{};
        uint8_t count = 1;
        for (int i = 0; i < width; i++) {
            if (i == 0) {
                last_data = data_line[i];
                continue;
            }
            if (last_data == data_line[i]) {
                count++;
            } else {
                compressed_data.push_back(std::make_pair(last_data, count));
                last_data = data_line[i];
                count = 1;
            }
        }
        compressed_data.push_back(std::make_pair(last_data, count));
    }
    return compressed_data;
}

std::array<std::array<uint8_t, width>, height> decompressGrayscale(std::vector<std::pair<uint8_t, uint8_t>> compressed_data) {
    std::array<std::array<uint8_t, width>, height> decompressed_data = {};
    int count = 0;
    int current_height = 0;
    std::array<uint8_t, width> decompressed_line = {};
    for (auto data_pair : compressed_data) {
        for (int i = 0; i < data_pair.second; i++) {
            if (count == width) {
                count = 0;
                current_height++;
            }

            if (current_height >= height) {
                throw std::runtime_error("Too much compressed data");
            }

            decompressed_data[current_height][count] = data_pair.first;
            count++;
        }
    }
    return decompressed_data;
}
