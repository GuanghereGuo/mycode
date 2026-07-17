#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <vector>

class DisjointSetUnion {
	std::vector<int> fa, size;
	std::vector<long long> mx;

public:
	explicit DisjointSetUnion(const int _n)
		: fa(_n + 1), size(_n + 1), mx(_n + 1) {
		std::iota(fa.begin(), fa.end(), 0);
	}

	void init(const int x) {
		fa[x] = x;
		size[x] = 1;
		mx[x] = 0;
	}

	int find(const int x) {
		if(fa[x] == x)
			return x;
		const int p = fa[x];
		fa[x] = find(p);
		mx[x] = std::max(mx[x], mx[p]);
		return fa[x];
	}

	int get_size(const int x) const {
		return size[x];
	}

	void merge(const int x, const int y, const long long val) {
		fa[x] = y;
		mx[x] = val;
		size[y] += size[x];
	}

	long long query(const int x) {
		find(x);
		return mx[x];
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m, q;
	std::cin >> n >> m >> q;

	const int tot = n * m;
	DisjointSetUnion dsu(tot);
	std::vector<char> vis(tot + 1, false);
	std::vector<long long> a(tot + 1);

	auto id = [m](const int x, const int y) {
		return (x - 1) * m + y;
	};

	constexpr int dx[] = {-1, 1, 0, 0};
	constexpr int dy[] = {0, 0, -1, 1};
	long long last = 0;

	while(q--) {
		int type;
		long long xx, yy;
		std::cin >> type >> xx >> yy;

		const int x = static_cast<int>(xx ^ last);
		const int y = static_cast<int>(yy ^ last);
		const int u = id(x, y);

		if(type == 1) {
			long long v;
			std::cin >> v;

			vis[u] = true;
			a[u] = v;
			dsu.init(u);

			std::array<int, 4> rt{};
			int cnt = 0;
			for(int d = 0; d < 4; ++d) {
				const int nx = x + dx[d];
				const int ny = y + dy[d];
				if(nx < 1 || nx > n || ny < 1 || ny > m)
					continue;

				const int to = id(nx, ny);
				if(!vis[to])
					continue;

				const int r = dsu.find(to);
				bool ok = true;
				for(int i = 0; i < cnt; ++i)
					if(rt[i] == r)
						ok = false;
				if(ok)
					rt[cnt++] = r;
			}

			for(int i = 0; i < cnt; ++i) {
				const int r = rt[i];
				const int s = dsu.get_size(r);
				dsu.merge(r, u, v - s + 1);
			}

			last = dsu.get_size(u) - 1;
		} else {
			last = std::max(0LL, dsu.query(u) - a[u]);
		}

		std::cout << last << '\n';
	}

	return 0;
}
