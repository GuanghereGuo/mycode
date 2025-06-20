#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

constexpr double R = 6371.0;

double haversine(const double lat1, const double lon1, const double lat2, const double lon2) {

    const double dlat = lat2 - lat1;
    const double dlon = lon2 - lon1;

    const double a = (1 - cos(dlat)) / 2 + cos(lat1) * cos(lat2) * (1 - cos(dlon)) / 2;
    const double c = acos( 1 - a * 2);

    return R * c;
}

int main() {
    double lat1, lon1, lat2, lon2;
    cin >> lat1 >> lon1;
    cin >> lat2 >> lon2;

    cout << fixed << setprecision(4) << haversine(lat1, lon1, lat2, lon2) << "km" << endl;

    return 0;
}
