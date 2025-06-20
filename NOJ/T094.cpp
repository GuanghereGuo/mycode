//
// Created by 24087 on 24-10-8.
//
#include <cctype>
#include <iostream>

int cnt(char src, char dest) {
    if (src == dest) return 0;
    if (isupper(src))
        return (src < dest) ? (dest - src) : ('Z' - src + dest - 'A' + 1);
    if ('0' <= src && src <= '9') {
        return (src < dest) ? (dest - src) : ('9' - src + dest - '0' + 1);
    }
    return -1;
}

int main() {
    std::string id1, id2;
    std::cin >> id1 >> id2;
    int num = 0;
    for (int i = 0; i < id1.size(); ++i)
        num += cnt(id1[i], id2[i]);
    std::cout << num << std::endl;
}