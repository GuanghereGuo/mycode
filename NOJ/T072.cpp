//
// Created by 24087 on 24-10-16.
//
#include <iostream>
#include <vector>

class Point {
   public:
    double x, y;
    explicit Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class LineSegment {
    Point A, B;
   public:
    LineSegment(const Point& a, const Point& b) : A(a), B(b) {}

    [[nodiscard]] double cross(const Point& p) const {
        return (B.x - A.x) * (p.y - A.y) - (B.y - A.y) * (p.x - A.x);
    }

    [[nodiscard]] bool on_segment(const Point& p) const {
        return (p.x <= std::max(A.x, B.x) && p.x >= std::min(A.x, B.x) &&
                p.y <= std::max(A.y, B.y) && p.y >= std::min(A.y, B.y));
    }

    [[nodiscard]] bool intersect(const LineSegment& other) const {
        double d1 = cross(other.A);
        double d2 = cross(other.B);
        double d3 = other.cross(A);
        double d4 = other.cross(B);

        if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
            ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
            return true;
        }

        if (d1 == 0 && on_segment(other.A)) return true;
        if (d2 == 0 && on_segment(other.B)) return true;
        if (d3 == 0 && other.on_segment(A)) return true;
        if (d4 == 0 && other.on_segment(B)) return true;

        return false;
    }
};

int main() {
    std::vector<LineSegment> vec;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        double x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        vec.emplace_back(Point(x1, y1), Point(x2, y2));
    }
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(vec[i].intersect(vec[j])) {
                std::cout << "X: #" << i + 1 << " #" << j + 1 << std::endl;
                ++cnt;
            }
        }
    }
    std::cout << "n=" << cnt << std::endl;
}
