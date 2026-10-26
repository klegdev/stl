#include "advancedCalculator.hpp"

#include <iostream>
#include <string>

const char* errorName(ErrorCode code) {
    switch (code) {
    case ErrorCode::OK:
        return "Ok";
    case ErrorCode::BadCharacter:
        return "BadCharacter";
    case ErrorCode::BadFormat:
        return "BadFormat";
    case ErrorCode::DivideBy0:
        return "DivideBy0";
    case ErrorCode::SqrtOfNegativeNumber:
        return "SqrtOfNegativeNumber";
    case ErrorCode::ModuleOfNonIntegerValue:
        return "ModuleOfNonIntegerValue";
    }
    return "UnknownError";
}

int main() {
    std::cout << "Advanced calculator (wpisz 'exit', aby zakonczyc)\n";
    std::cout << "Przyklady: 5 + 5, 125 $ 3, 5 !\n";

    std::string input;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, input) || input == "exit") {
            break;
        }

        double result = 0.0;
        const ErrorCode code = process(input, &result);
        if (code == ErrorCode::OK) {
            std::cout << "Wynik: " << result << '\n';
        } else {
            std::cout << "Blad: " << errorName(code) << '\n';
        }
    }
}