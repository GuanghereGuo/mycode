//
// Created by 24087 on 24-10-16.
//
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>

class Student {
public:
    long long id;
    std::string name;
    int score;
    Student(long long id, std::string name, int score)
        : id(id), name(std::move(name)), score(score) {}
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Student> grade;
    for (int i = 0; i < n; ++i) {
        long long id;
        std::string name;
        int score;
        std::cin >> id >> name >> score;
        grade.emplace_back(id, std::move(name), score);
    }

    std::sort(grade.begin(), grade.end(), [](const Student& a, const Student& b) {
        return (a.score > b.score) || (a.score == b.score && a.id < b.id);
    });

    for (const auto& item : grade) {
        std::cout << item.id << " " << item.name << " " << item.score << std::endl;
    }
}
