#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	int n, c, k;
	std::cin >> n >> c >> k;
	
	double ans = 0;
	for(int i = 1, x; i <= n + 1; i++) {
		std::cin >> x;
		ans += x;
	}
	int angel, hided;
	std::cin >> hided >> angel;
	
	int item = (n + 1) / k;
	//std::cerr << item   << "ok\n";
	//total = n + 3
	//simple = n + 1
	
	ans += hided * 1.0 * (1 - std::pow(1.0 * (n + 2) / (n + 3), item));
	ans += c / 100.0 * (angel);
	ans += (1 - c / 100.0) * angel * 1.0 * (1 - std::pow(1.0 * (n + 2) / (n + 3), item)) ;
	
	std::cout << std::fixed << std::setprecision(2) <<  ans << '\n';
	
//	std::cerr << std::pow(1.0 * (n + 2) / (n + 3), item);
	
}
//3 50 2
//2 3 4
//10 11 12
