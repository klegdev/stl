#include "advancedCalculator.hpp"

#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <map>
#include <string>

namespace {

using Operation = std::function<double(double, double)>;

const std::map<char, Operation>& operations() {
    static const std::map<char, Operation> commands = {
        {'+', [](double a, double b) { return a + b; }},
        {'-', [](double a, double b) { return a - b; }},
        {'*', [](double a, double b) { return a * b; }},
        {'/', [](double a, double b) { return a / b; }},
        {'%', [](double a, double b) { return std::fmod(a, b); }},
        {'^', [](double a, double b) { return std::pow(a, b); }},
        {'$', [](double a, double b) { return std::pow(a, 1.0 / b); }},
        {'!', [](double a, double) {
             return std::copysign(
                 std::tgamma(std::abs(a) + 1.0), a);
         }}};

    return commands;
}

void skipWhitespace(const std::string& s, std::size_t& pos) {
    while (pos < s.size() &&
           std::isspace(static_cast<unsigned char>(s[pos]))) {
        ++pos;
    }
}

ErrorCode validateCharacters(const std::string& s) {
    bool containsComma = false;

    for (unsigned char c : s) {
        if (std::isdigit(c) || std::isspace(c) ||
            c == '.' || c == '+' || c == '-' || c == '*' ||
            c == '/' || c == '%' || c == '^' || c == '$' ||
            c == '!' || c == 'e' || c == 'E') {
            continue;
        }

        if (c == ',') {
            containsComma = true;
            continue;
        }

        return ErrorCode::BadCharacter;
    }

    return containsComma ? ErrorCode::BadFormat : ErrorCode::OK;
}

ErrorCode readNumber(
    const std::string& s,
    std::size_t& pos,
    double& number) {
    skipWhitespace(s, pos);

    if (pos == s.size() || s[pos] == '+') {
        return ErrorCode::BadFormat;
    }

    const char* start = s.c_str() + pos;
    char* end = nullptr;

    errno = 0;
    const double value = std::strtod(start, &end);

    if (end == start || errno == ERANGE || !std::isfinite(value)) {
        return ErrorCode::BadFormat;
    }

    pos += static_cast<std::size_t>(end - start);
    number = value;

    return ErrorCode::OK;
}

}  // namespace

ErrorCode process(std::string input, double* out) {
    if (out == nullptr) {
        return ErrorCode::BadFormat;
    }

    const ErrorCode charsStatus = validateCharacters(input);

    if (charsStatus != ErrorCode::OK) {
        return charsStatus;
    }

    std::size_t pos = 0;
    double left = 0.0;
    double right = 0.0;

    ErrorCode status = readNumber(input, pos, left);

    if (status != ErrorCode::OK) {
        return status;
    }

    skipWhitespace(input, pos);

    if (pos == input.size()) {
        return ErrorCode::BadFormat;
    }

    const char symbol = input[pos++];
    const auto operation = operations().find(symbol);

    if (operation == operations().end()) {
        return ErrorCode::BadFormat;
    }

    if (symbol != '!') {
        status = readNumber(input, pos, right);

        if (status != ErrorCode::OK) {
            return status;
        }
    }

    skipWhitespace(input, pos);

    if (pos != input.size()) {
        return ErrorCode::BadFormat;
    }

    if (symbol == '%' &&
        (std::trunc(left) != left ||
         std::trunc(right) != right)) {
        return ErrorCode::ModuleOfNonIntegerValue;
    }

    if ((symbol == '/' || symbol == '%') && right == 0.0) {
        return ErrorCode::DivideBy0;
    }

    if (symbol == '$' && left < 0.0) {
        return ErrorCode::SqrtOfNegativeNumber;
    }

    if ((symbol == '$' &&
         (right == 0.0 || (left == 0.0 && right < 0.0))) ||
        (symbol == '^' && left == 0.0 && right < 0.0)) {
        return ErrorCode::DivideBy0;
    }

    const double result = operation->second(left, right);

    if (!std::isfinite(result)) {
        return ErrorCode::BadFormat;
    }

    *out = result;
    return ErrorCode::OK;
}
