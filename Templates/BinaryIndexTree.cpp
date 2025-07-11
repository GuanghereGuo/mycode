class BIT {
	using ll = long long;
	int n;
	std::vector<ll> tr;
	constexpr static int low_bit(const int x) {
		return x & -x;
	}

public:
	BIT(int n): n(n), tr(n + 1) {}
	void add(int idx, ll val) {
		for(int i = idx; i <= n; i += low_bit(i)) {
			tr[i] += val;
		}
	}
	ll query(int idx) {
		ll res = 0;
		for(int i = idx; i; i -= low_bit(i)) {
			res += tr[i];
		}
		return res;
	}
	ll query(int l, int r) {
		return query(r) - query(l - 1);
	}
};

class EBIT {
	class BIT {
		using ll = long long;
		int n;
		std::vector<ll> tr;
		constexpr static int low_bit(const int x) {
			return x & -x;
		}

	public:
		explicit BIT(int n): n(n), tr(n + 1) {}
		void add(int idx, ll val) {
			for(int i = idx; i <= n; i += low_bit(i)) {
				tr[i] += val;
			}
		}
		ll query(int idx) {
			ll res = 0;
			for(int i = idx; i; i -= low_bit(i)) {
				res += tr[i];
			}
			return res;
		}
		ll query(int l, int r) {
			return query(r) - query(l - 1);
		}
	};

	int n;
	BIT d, di;
public:
	explicit EBIT(int n): n(n), d(n), di(n) {}
	//sum(r) = d_sum * (r + 1) - di_sum
	using ll = long long;

	ll query(int idx) {
		return d.query(idx) * (idx + 1) - di.query(idx);
	}
	ll query(int l, int r) {
		return query(r) - query(l - 1);
	}

	void add(int l, int r, int val) {
		d.add(l, val);
		d.add(r + 1, -val);

		di.add(l, val * l);
		di.add(r + 1, -val * (r + 1));
	}
	void add(int idx, int val) {
		add(idx, idx, val);
	}
};