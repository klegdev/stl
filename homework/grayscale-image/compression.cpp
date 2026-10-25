#include "compression.hpp"
#include <algorithm>
#include <stdexcept>

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(std::array<std::array<uint8_t, width>, height> data) {
    std::vector<std::pair<uint8_t, uint8_t>> compressed_data;

    std::for_each(data.begin(), data.end(), [&](const auto& row) {
        auto first = row.begin();

        while (first != row.end()) {
            auto it = std::adjacent_find(
                first, row.end(), std::not_equal_to<>{});

            auto last = (it == row.end()) ? row.end() : std::next(it);

            auto count = std::distance(first, last);

            while (count > 0) {
                auto n = std::min<decltype(count)>(count, 255);
                compressed_data.emplace_back(*first, static_cast<uint8_t>(n));
                count -= n;
            }

            first = last;
        }
    });

    return compressed_data;
}

std::array<std::array<uint8_t, width>, height> decompressGrayscale(std::vector<std::pair<uint8_t, uint8_t>> compressed_data) {
    std::array<std::array<uint8_t, width>, height> decompressed_data = {};
    std::vector<uint8_t> pixels(width * height, 0);

    size_t count = 0;

    std::for_each(compressed_data.begin(), compressed_data.end(),
                  [&](const auto& data_pair) {
                      if (data_pair.second > pixels.size() - count)
                          throw std::runtime_error("Too much compressed data");

                      std::fill_n(
                          pixels.begin() + count,
                          data_pair.second,
                          data_pair.first);

                      count += data_pair.second;
                  });

    count = 0;

    std::for_each(decompressed_data.begin(), decompressed_data.end(),
                  [&](auto& row) {
                      std::copy_n(
                          pixels.begin() + count,
                          width,
                          row.begin());

                      count += width;
                  });

    return decompressed_data;
}