//
// Created by guanghere on 25-7-10.
//
#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_ITER = 100;
constexpr double INF = 1e6;
constexpr double EPS = 1e-7;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator*(double t) const { return Point(x * t, y * t); }
};

double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double computeMaxDistance(double t, const Point& P0, const Point& d,
                          const vector<Point>& devices) {
    Point P = P0 + d * t;
    double maxDist = 0;
    for (const auto& dev : devices) {
        double dist = distance(P, dev);
        maxDist = max(maxDist, dist);
    }
    return maxDist;
}

double ternarySearch(const vector<Point>& devices, const Point& P0,
                     const Point& d) {
    double left = -INF, right = INF;
    while (std::abs(left - right) > EPS) {
        double mid = (left + right) / 2;
        double t1 = mid - EPS;
        double t2 = mid + EPS;
    //for (int i = 0; i < MAX_ITER; ++i) {
        // double t1 = left + (right - left) / 3;
        // double t2 = right - (right - left) / 3;
        double dist1 = computeMaxDistance(t1, P0, d, devices);
        double dist2 = computeMaxDistance(t2, P0, d, devices);
        if (dist1 < dist2) {
            //right = t2;
            right = mid;
        } else {
            //left = t1;
            left = mid;
        }
    }
    double t_opt = (left + right) / 2;
    return computeMaxDistance(t_opt, P0, d, devices);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T;
    cin >> T;
    for (int test = 0; test < T; ++test) {
        int n;
        cin >> n;
        vector<Point> devices(n);
        for (int i = 0; i < n; ++i) {
            cin >> devices[i].x >> devices[i].y;
        }
        double a, b, c;
        cin >> a >> b >> c;

        Point P0;
        if (fabs(b) > EPS) {
            P0 = Point(0, -c / b);
        } else {
            P0 = Point(-c / a, 0);
        }
        Point d(-b, a);

        double minMaxDist = ternarySearch(devices, P0, d);
        cout << minMaxDist << endl;
    }

    return 0;
}