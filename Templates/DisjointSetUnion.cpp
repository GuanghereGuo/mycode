class DisjointSetUnion {
	int n;
	std::vector<int> fa, size;

public:
	explicit DisjointSetUnion(const int _n): n(_n), fa(_n + 1), size(_n + 1, 1) {
		std::iota(fa.begin(), fa.end(), 0);
	}
	int find(const int x) {
		if(fa[x] == x)
			return x;
		return fa[x] = find(fa[x]);
	}
	void unite(int x, int y) {
		x = find(x);
		y = find(y);
		if(x == y)
			return;
		if(size[x] < size[y])
			std::swap(x, y);
		fa[y] = x;
		size[x] += size[y];
	}
};