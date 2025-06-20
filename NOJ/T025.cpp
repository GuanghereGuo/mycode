//
// Created by 24087 on 24-10-5.
//
#include <iostream>
#include <cmath>
#include <string>

unsigned count_digits(unsigned number) {
    if (number == 0) {
        return 1;
    }
    unsigned digits = 0;
    while (number > 0) {
        number /= 10;
        ++digits;
    }
    return digits;
}

unsigned get_digit_at_position(unsigned number, unsigned position) {
    return (number / static_cast<unsigned>(pow(10, position - 1))) % 10;
}

void print_separator(unsigned length) {
    for (unsigned i = 0; i < length; ++i) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

void print_formatted_multiplication(unsigned multiplicand, unsigned multiplier) {
    const unsigned product = multiplicand * multiplier;
    const unsigned product_length = count_digits(product) + 1;
    const unsigned multiplicand_length = count_digits(multiplicand);
    const unsigned multiplier_length = count_digits(multiplier);

    for (unsigned i = 0; i < product_length - multiplicand_length; ++i) {
        std::cout << " ";
    }
    std::cout << multiplicand << std::endl;

    std::cout << "x";
    for (unsigned i = 0; i < product_length - multiplier_length - 1; ++i) {
        std::cout << " ";
    }
    std::cout << multiplier << std::endl;

    print_separator(product_length);

    for (unsigned i = 1; i <= multiplier_length; ++i) {
        unsigned partial_product = get_digit_at_position(multiplier, i) * multiplicand;
        if (i == multiplier_length) {
            std::cout << "+";
        } else {
            for (unsigned j = 0; j < product_length - count_digits(partial_product) - i + 1; ++j) {
                std::cout << " ";
            }
        }
        std::cout << partial_product << std::endl;
    }

    print_separator(product_length);

    std::cout << " " << product << std::endl;
}

int main() {
    unsigned multiplicand, multiplier;

    std::cin >> multiplicand >> multiplier;

    print_formatted_multiplication(multiplicand, multiplier);
}
