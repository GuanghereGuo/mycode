//
// Created by guanghere on 25-7-14.
//
#include <bits/stdc++.h>
using namespace std;

const int B = 350;                 // 理想块大小（≈sqrt(1e5)）

struct Block {
    vector<int> v;                 // 元素
    long long sum[2] {0, 0};       // sum[0]：块内偶下标之和；sum[1]：奇下标之和

    void recalc() {
        sum[0] = sum[1] = 0;
        for (int i = 0; i < (int)v.size(); ++i)
            sum[i & 1] += v[i];
    }
};

list<Block> blks;                  // 分块链表

// ---------- 工具：定位全局第 pos(1-based) 个元素 ----------
struct Loc { list<Block>::iterator it; int idx; };      // idx 为块内 0-based
Loc locate(int pos) {
    for (auto it = blks.begin(); ; ++it) {
        if (pos <= (int)it->v.size())
            return {it, pos - 1};
        pos -= it->v.size();
    }
}

// ---------- 删除并返回值 ----------
int erasePos(int pos) {
    auto [it, idx] = locate(pos);
    int val = it->v[idx];
    it->v.erase(it->v.begin() + idx);
    it->recalc();

    // 若块过小，与邻块合并 / 直接删空块
    if (it->v.empty()) {
        blks.erase(it);
    } else if (it->v.size() < B / 2) {
        auto nxt = next(it);
        if (nxt != blks.end() && (int)(it->v.size() + nxt->v.size()) <= B) {
            it->v.insert(it->v.end(), nxt->v.begin(), nxt->v.end());
            it->recalc();
            blks.erase(nxt);
        } else if (it != blks.begin()) {
            auto pre = prev(it);
            if ((int)(pre->v.size() + it->v.size()) <= B) {
                pre->v.insert(pre->v.end(), it->v.begin(), it->v.end());
                pre->recalc();
                blks.erase(it);
            }
        }
    }
    return val;
}

// ---------- 在位置 pos(1-based) 前插入 val ----------
void insertPos(int pos, int val) {
    if (blks.empty()) {                     // 首次插入（理论上不会发生）
        Block bk; bk.v = {val}; bk.recalc();
        blks.push_back(std::move(bk));
        return;
    }
    if (pos == 1) {                         // 插到序列最前
        if ((int)blks.front().v.size() >= 2 * B) {
            Block nb;                       // 先拆块再插，避免过大
            nb.v.assign(blks.front().v.begin() + B, blks.front().v.end());
            blks.front().v.resize(B);
            blks.front().recalc();
            nb.recalc();
            blks.insert(next(blks.begin()), std::move(nb));
        }
        blks.front().v.insert(blks.front().v.begin(), val);
        blks.front().recalc();
        return;
    }

    auto [it, idx] = locate(pos - 1);       // pos-1 一定存在
    it->v.insert(it->v.begin() + idx + 1, val);
    it->recalc();

    // 块过大则拆成两块
    if ((int)it->v.size() > 2 * B) {
        Block nb;
        nb.v.assign(it->v.begin() + B, it->v.end());
        it->v.erase(it->v.begin() + B, it->v.end());
        it->recalc();
        nb.recalc();
        blks.insert(next(it), std::move(nb));
    }
}

// ---------- O(√n) 计算双方得分 ----------
string winner() {
    long long fish = 0, man = 0;
    int parity = 0;                          // 0→当前轮到鱼，1→轮到渔夫
    for (auto &bk : blks) {
        fish += bk.sum[parity ^ 0];
        man  += bk.sum[parity ^ 1];
        parity ^= (bk.v.size() & 1);
    }
    if (fish > man) return "FISH";
    if (fish < man) return "MAN";
    return "TIE";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    // 建初始块
    for (int i = 0; i < n; i += B) {
        Block bk;
        bk.v.assign(a.begin() + i, a.begin() + min(n, i + B));
        bk.recalc();
        blks.push_back(std::move(bk));
    }

    while (q--) {
        int l, r; cin >> l >> r;
        int x = erasePos(l);   // 1. 取出 a_l
        insertPos(r, x);       // 2. 插到原 r 位置
        cout << winner() << '\n';
    }
    return 0;
}
