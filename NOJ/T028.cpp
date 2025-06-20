//
// Created by 24087 on 24-10-5.
//
#include <iostream>

bool is_non_decreasing(unsigned number) {
    unsigned current_digit, previous_digit = 10;
    while (number > 0) {
        current_digit = number % 10;
        if (current_digit > previous_digit) {
            return false;
        }
        previous_digit = current_digit;
        number /= 10;
    }
    return true;
}

unsigned find_largest_non_decreasing(unsigned int number) {
    while (!is_non_decreasing(number)) {
        --number;
    }
    return number;
}

int main() {
    unsigned input_number;

    std::cin >> input_number;

    unsigned result = find_largest_non_decreasing(input_number);
    std::cout << result << std::endl;
}
