#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	int n, m, q;
	std::cin >> n >> m >> q;
	
	std::vector<std::vector<bool>> stone(n + 1, std::vector<bool>(m + 1, true));
	std::vector<std::vector<int>> jump[4];// up down left right
	
	for(int i = 0; i < 4; i++) {
		jump[i].resize(n + 2, std::vector<int>(m + 2));
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			jump[0][i][j] = i;
			jump[1][i][j] = i;
			jump[2][i][j] = j;
			jump[3][i][j] = j;
		}
	}
	
	int ans = n * m;
	
	auto break_stone = [&](int x, int y) {
		stone[x][y] = false;
		jump[0][x][y] = jump[0][x - 1][y];
		jump[1][x][y] = jump[1][x + 1][y];
		jump[2][x][y] = jump[2][x][y - 1];
		jump[3][x][y] = jump[3][x][y + 1];
		ans--;
	};
	
	for(int i = 1, x, y; i <= q; i++) {
		std::cin >> x >> y;
		if(stone[x][y]) {
			break_stone(x, y);
			continue;
		}
		
		//up
		int x_up = x;
		while(x_up >= 1 && !stone[x_up][y] && jump[0][x_up][y] != 0) {
			x_up = jump[0][x_up][y];
		}
		if(x_up != 0 && stone[x_up][y]) {
			int x_upf = x;
			while(x_upf >= 1 && !stone[x_upf][y] && jump[0][x_upf][y] != 0) {
				int tmp = x_upf;
				x_upf = jump[0][x_upf][y];
				jump[0][tmp][y] = x_up;
			}
			break_stone(x_up, y);
		}
		//down
		int x_down = x;
		while(x_down <= n && !stone[x_down][y] && jump[1][x_down][y] != 0) {
			x_down = jump[1][x_down][y];
		}
		if(x_down <= n && stone[x_down][y]) {
			int x_downf = x;
			while(x_downf <= n && !stone[x_downf][y] && jump[1][x_downf][y] != 0) {
				int tmp = x_downf;
				x_downf = jump[1][x_downf][y];
				jump[1][tmp][y] = x_down;
			}
			break_stone(x_down, y);
		}
		//left
		int y_left = y;
		while(y_left >= 1 && !stone[x][y_left] && jump[2][x][y_left] != 0) {
			y_left = jump[2][x][y_left];
		}
		if(y_left != 0 && stone[x][y_left]) {
			int y_leftf = y;
			while(y_leftf >= 1 && !stone[x][y_leftf] && jump[2][x][y_leftf] != 0) {
				int tmp = y_leftf;
				y_leftf = jump[2][x][y_leftf];
				jump[2][x][y_leftf] = y_left;
			}
			break_stone(x, y_left);
		}
		//right
		int y_right = y;
		while(y_right <= m && !stone[x][y_right] && jump[3][x][y_right] != 0) {
			y_right = jump[3][x][y_right];
		}
		if(y_right <= m && stone[x][y_right]) {
			int y_rightf = y;
			while(y_rightf <= m && !stone[x][y_rightf] && jump[3][x][y_rightf] != 0) {
				int tmp = y_rightf;
				y_rightf = jump[3][x][y_rightf];
				jump[3][x][y_rightf] = y_right;
			}
			break_stone(x, y_right);
		}
	}

	std::cout << ans;
}
//2 4 3
//1 2
//1 2
//1 3


//4 3 10
//2 2
//4 1
//1 1
//4 2
//2 1
//3 1
//1 3
//1 2
//4 3
//4 2

//		if(stone[x][y]) {
//			stone[x][y] = false;
//			ans--;
//			continue;
//		}
//			//up
//			int x_up = x;
//			while(x_up >= 1 && !stone[x_up][y]) {
//				x_up--;
//			}
//			if(x_up != 0) {
//				stone[x_up][y] = false;
//				ans--;
//			}
//			//down
//			int x_down = x;
//			while(x_down <= n && !stone[x_down][y]) {
//				x_down++;
//			}
//			if(x_down <= n) {
//				stone[x_down][y] = false;
//				ans--;
//			}
//			//left
//			int y_left = y;
//			while(y_left >= 1 && !stone[x][y_left]) {
//				y_left--;
//			}
//			if(y_left != 0) {
//				stone[x][y_left] = false;
//				ans--;
//			}
//			//up
//			int y_right = y;
//			while(y_right <= m && !stone[x][y_right]) {
//				y_right++;
//			}
//			if(y_right <= m) {
//				stone[x][y_right] = false;
//				ans--;
//			}
//		}

