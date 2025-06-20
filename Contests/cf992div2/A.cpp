//
// Created by 24087 on 24-12-8.
//
//
// Created by 24087 on 24-12-8.
//
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int test_cases, array_size, divisor, result_index;
    std::cin >> test_cases;

    std::cerr << "who! are! we!\n";
    while (test_cases--) {
        std::cin >> array_size >> divisor;
        std::vector<int> array(array_size);

        for (int i = 0; i < array_size; i++) {
            std::cin >> array[i];
        }

        bool found_result = false;

        for (int i = 0; i < array_size; i++) {
            bool is_valid = true;

            for (int j = 0; j < array_size; j++) {
                if (i != j && std::abs(array[i] - array[j]) % divisor == 0) {
                    is_valid = false;
                    break;
                }
            }

            if (is_valid) {
                found_result = true;
                result_index = i + 1;
                break;
            }
        }

        if (found_result) {
            std::cout << "YES" << std::endl << result_index;
        } else {
            std::cout << "NO";
        }

        std::cout << std::endl;
    }

    return 0;
}
