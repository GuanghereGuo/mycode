#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    long long x, y;
};

long long polygon_area(const vector<Point>& vertices) {
    int n = vertices.size();
    long long area = 0;
    for (int i = 0; i < n; ++i) {
        long long x1 = vertices[i].x, y1 = vertices[i].y;
        long long x2 = vertices[(i + 1) % n].x, y2 = vertices[(i + 1) % n].y;
        area += x1 * y2 - x2 * y1;
    }
    return abs(area);
}

double point_to_line_distance(const Point& a, const Point& b, const Point& c) {
    long long A = b.y - a.y;
    long long B = a.x - b.x;
    long long C = A * a.x + B * a.y;
    return abs(A * c.x + B * c.y - C) / sqrt(A * A + B * B);
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        Point center;
        long long radius;
        cin >> center.x >> center.y >> radius;

        vector<Point> vertices(n);
        for (int i = 0; i < n; ++i) {
            cin >> vertices[i].x >> vertices[i].y;
        }
        long long max_area = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double distance = point_to_line_distance(vertices[i], vertices[j], center);
                if (distance >= radius) {
                    vector<Point> part;
                    for (int k = i; k <= j; ++k) {
                        part.push_back(vertices[k % n]);
                    }
                    long long area = polygon_area(part);
                    max_area = max(max_area, area);
                }
            }
        }
        cout << max_area * 2 << endl;
    }
}
