#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
	int t1, t2;
	Node(int t1, int t2):t1(t1), t2(t2){
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	std::vector<Node> s1, s2;
	
	int n;
	std::cin >> n;
	int sum1 = 0, sum2 = 0;
	for(int i = 1, x, y; i <= n; i++) {
		std::cin >> x >> y;
		if(x <= y) {
			s1.emplace_back(x, y);
			sum1 += x;
		} else {
			s2.emplace_back(x, y);
			sum2 += y;
		}
	}
	
	for(auto i : s1) {
		std::cerr << i.t1 << '+' << i.t2 << ' ';
	}
	std::cout << std::endl;
	for(auto i : s2) {
		std::cerr << i.t1 << '+' << i.t2 << ' ';
	}
	std::cout << std::endl;
	
	if(sum1 == sum2) {
		std::cout << sum1;
		return 0;
	}
	int cnt = 0;
	int ans = std::max(sum1, sum2);
	while(sum1 != sum2 && cnt < 2000) {
		if(sum1 < sum2) {
			std::sort(s2.begin(), s2.end(), [](const Node& a, const Node &b) {
				return (a.t1) > (b.t1);	
			});
			Node tmp = s2.back();
			if (std::max(sum1 + tmp.t1, sum2 - tmp.t2) < ans) {
				sum1 += tmp.t1;
				sum2 -= tmp.t2;
				ans = std::max(sum1, sum2);
				s2.pop_back();
				s1.push_back(tmp);
				cnt = 0;
			} else {
				cnt++;
			}
		} else {
			std::sort(s1.begin(), s1.end(), [](const Node& a, const Node &b) {
				return (a.t2) > (b.t2);	
			});
			Node tmp = s1.back();
			if (std::max(sum1 - tmp.t1, sum2 + tmp.t2) < ans) {
				sum1 -= tmp.t1;
				sum2 += tmp.t2;
				ans = std::max(sum1, sum2);
				s1.pop_back();
				s2.push_back(tmp);
				cnt = 0;
			} else {
				cnt++;
			}
		}
		std::sort(s2.begin(), s2.end(), [](const Node& a, const Node &b) {
				return (a.t1) > (b.t1);	
		});
		std::sort(s1.begin(), s1.end(), [](const Node& a, const Node &b) {
			return (a.t2) > (b.t2);	
		});
		Node tmp1 = s1.back();
		Node tmp2 = s2.back();
		if (std::max(sum1 - tmp1.t1 + tmp2.t1, sum2 + tmp1.t2 - tmp2.t2) < ans) {
			sum1 = sum1 - tmp1.t1 + tmp2.t1;
			sum2 = sum2 - tmp2.t2 + tmp1.t2;
			ans = std::max(sum1, sum2);
			s1.pop_back();
			s2.pop_back();
			s1.push_back(tmp2);
			s2.push_back(tmp1);
			cnt = 0;
		} else {
			cnt++;
		}
	}
	for(auto i : s1) {
		std::cerr << i.t1 << '+' << i.t2 << ' ';
	}
	std::cout << std::endl;
	for(auto i : s2) {
		std::cerr << i.t1 << '+' << i.t2 << ' ';
	}
	std::cout << std::endl;
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

