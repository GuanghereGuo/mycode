#include <iostream>
#include <vector>
#include <set>

int main() {
    char(*a)[3] = nullptr;
    a++;
    std::cout << a << std::endl;

}