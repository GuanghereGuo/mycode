#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	long long ans = 0;
	int n, m;
	std::cin >> n >> m;
	std::vector<long long> pre(n + 1);
	std::vector<int> yu(m);
	for(int i = 1; i <= n; i++) {
		std::cin >> pre[i];
		pre[i] += pre[i - 1];
		ans += yu[pre[i] % m];
		if(pre[i] % m == 0) {
			ans++;
		}
		yu[pre[i] % m]++;
	}
	std::cout << ans;
}
