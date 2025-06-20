#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct Node {
	int t1, t2;
};

int n, sum1, sum2, ans = INT_MAX, time0;
std::vector<Node> vec;

void dfs(int dep) {
	if(dep > n) {
		ans = std::min(std::max(sum1, sum2), ans);
		return;
	}
	sum1 += vec[dep].t1;
	dfs(dep + 1);
	sum1 -= vec[dep].t1;
	
	sum2 +=  vec[dep].t2;
	dfs(dep + 1);
	sum2 -=  vec[dep].t2;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	std::cin >> n;
	vec.resize(n + 1);
	
	for(int i = 1; i <= n; i++) {
		std::cin >> vec[i].t1 >> vec[i].t2;
	}
	
	dfs(1);
	
	std::cout << ans;
}


//4
//100 1
//1 90
//1 20
//1 20

//2
//114514 3
//666 4

//5
//1 1
//2 2
//3 3
//4 4
//5 5

