#include <bits/stdc++.h>
typedef long long ll;

using std::cin;
using std::cout;
using std::max;
using std::vector;
using std::stack;
using std::tuple;
using std::get;


const ll INF = 1e18;

struct Tuple {
    ll mp, ms, ts, ma;
    Tuple(ll p = -INF, ll s = -INF, ll t = 0, ll a = -INF) : mp(p), ms(s), ts(t), ma(a) {}
};

vector<ll> A;

inline Tuple combine(const Tuple& left, const Tuple& right) {
    if (left.ma == -INF) return right;
    if (right.ma == -INF) return left;
    return Tuple(
        max(left.mp, left.ts + right.mp),
        max(right.ms, right.ts + left.ms),
        left.ts + right.ts,
        max({left.ma, right.ma, left.ms + right.mp})
    );
}

ll query(int L, int R, ll S, int N) {
    stack<tuple<int, int, Tuple>> stk;
    stk.emplace(1, N, Tuple());
    Tuple result;

    while (!stk.empty()) {
        auto [a, b, curr] = stk.top();
        stk.pop();
        if (L > b || R < a) continue;
        if (L <= a && b <= R) {
            if (a == b) {
                ll val = A[a] + S;
                result = combine(result, Tuple(val, val, val, val));
            } else {
                int mid = (a + b) / 2;
                stk.emplace(mid + 1, b, Tuple());
                stk.emplace(a, mid, Tuple());
            }
        } else {
            int mid = (a + b) / 2;
            if (R > mid) stk.emplace(mid + 1, b, Tuple());
            if (L <= mid) stk.emplace(a, mid, Tuple());
        }
    }
    return result.ma == -INF ? -INF : result.ma;
}

char buf[1 << 20], *p = buf, *end = buf;
inline char getc() {
    if (p == end) {
        end = buf + fread(buf, 1, 1 << 20, stdin);
        p = buf;
    }
    return *p++;
}

inline ll read_int() {
    ll x = 0; char c = getc(); bool neg = false;
    while (c < '0' || c > '9') { if (c == '-') neg = true; c = getc(); }
    while (c >= '0' && c <= '9') x = x * 10 + (c - '0'), c = getc();
    return neg ? -x : x;
}

char out_buf[1 << 20]; int out_pos = 0;
inline void write_int(ll x) {
    if (x < 0) out_buf[out_pos++] = '-', x = -x;
    char temp[20]; int len = 0;
    do { temp[len++] = x % 10 + '0'; x /= 10; } while (x);
    while (len--) out_buf[out_pos++] = temp[len];
    out_buf[out_pos++] = '\n';
    if (out_pos >= (1 << 19)) fwrite(out_buf, 1, out_pos, stdout), out_pos = 0;
}

int main() {
    int N = read_int(), Q = read_int();
    A.resize(N + 1);
    for (int i = 1; i <= N; i++) A[i] = read_int();
    ll S = 0;
    char event[9];
    for (int q = 0; q < Q; q++) {
        int pos = 0;
        char c = getc();
        while (c != ' ') event[pos++] = c, c = getc();
        event[pos] = '\0';
        if (event[0] == 'S') { // "STRENGTH"
            ll X = read_int();
            S += X;
        } else { // "ASSESS"
            int L = read_int(), R = read_int();
            ll M = query(L, R, S, N);
            ll V = max(M, 0LL);
            write_int(V);
        }
    }
    if (out_pos) fwrite(out_buf, 1, out_pos, stdout);
    return 0;
}