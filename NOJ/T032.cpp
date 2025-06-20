//
// Created by 24087 on 24-10-7.
//
#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> primes(1, 0);

//liner
void get_primes(const int n) {
    std::vector<bool> vis(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) {
            primes.push_back(i);
        }
        for(int j = 1; j <= primes.size() && i * primes[j] <= n; j++) {
            vis[i * primes[j]] = true;
            if(i % primes[j] == 0) {
                break;
            }
        }
    }
}

int main() {
    int a, b;
    std::cin >> a >> b;
    get_primes(b);

    std::cout << std::lower_bound(primes.begin(), primes.end(), b) - std::lower_bound(primes.begin(), primes.end(), a);
}