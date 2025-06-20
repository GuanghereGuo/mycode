//
// Created by 24087 on 24-10-9.
//
#include <iostream>
#include <vector>

//线性筛
std::vector<int> prime;
std::vector<bool> is_prime;

void get_primes(const int n) {
    is_prime.resize(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= n; ++j) {
            is_prime[i * prime[j]] = false;
            if (i % prime[j] == 0) break;
        }
    }
}


int main() {
    int n;
    std::cin >> n;
    get_primes(n);
    std::cout << prime.size() << std::endl;
}