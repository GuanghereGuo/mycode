//
// Created by 24087 on 24-11-13.
//
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 5;

long long n, m, ans, sigma_l, now_val,srw,sr, sum_len_to_fill[N], sum_val_to_fill[N],
    left_time;
struct Crop {
    long long w = 0, l = 0, r = 0;
} crop[N];

bool operator<(const Crop &a, const Crop &b) { return a.w > b.w; }

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> crop[i].w >> crop[i].l >> crop[i].r;
        sigma_l += crop[i].l;
        now_val += crop[i].l * crop[i].w;
        srw += crop[i].r * crop[i].w;
        sr+=crop[i].r;
    }

    sort(crop + 1, crop + n + 1);
    ans = now_val + (m - sigma_l) * crop[1].w;

    //print crop
    for (int i = 1; i <= n; i++) {
        std::cerr << "crop[" << i << "].w = " << crop[i].w << " crop[" << i
                  << "].l = " << crop[i].l << " crop[" << i << "].r = "
                  << crop[i].r << '\n';
    }


    left_time = m - sigma_l;

    int first_unimplemented = 0;
    for (int i = 1; i <= n && left_time; first_unimplemented = i++) {
        const long long delta = min(left_time, crop[i].r - crop[i].l);
        //std::cerr << "i = " << i << " delta = " << delta << '\n';
        left_time -= delta;
        now_val += delta * crop[i].w;
        crop[i].l += delta;
    }

    for (int i = first_unimplemented; i <= n; i++) {
        sum_len_to_fill[i] = sum_len_to_fill[i - 1] + crop[i].r - crop[i].l;
        sum_val_to_fill[i] =
            sum_val_to_fill[i - 1] + crop[i].w * (crop[i].r - crop[i].l);
        //std::cerr << "i = " << i << " sum_len_to_fill = " << sum_len_to_fill[i] << " sum_val_to_fill = " << sum_val_to_fill[i] << '\n';
    }

    //sum_val_to_fill[]

    // std::cerr << "first_unimplemented = " << first_unimplemented << '\n';

    for (int i =2; i <= n; i++) {
        int idx =
            static_cast<int>(lower_bound(sum_len_to_fill + first_unimplemented,
                                         sum_len_to_fill + 1 + n, crop[i].l) -
                             sum_len_to_fill);
        long long tmp_ans = now_val;
        // if(idx == n + 1) {
        //     tmp_ans=srw+crop[i].w*(m-sr);
        //     ans = max(ans, tmp_ans);
        //     cerr<<tmp_ans<<endl;
        //     // continue;
        // }

        if(idx < i ) {
            tmp_ans -= crop[i].l * crop[i].w;
            tmp_ans += sum_val_to_fill[idx - 1] + crop[idx].w * (crop[i].l - sum_len_to_fill[idx - 1]);
        } else {
            tmp_ans -= sum_len_to_fill[i - 1] * crop[i].w;
            tmp_ans += sum_val_to_fill[i - 1];
        }
        ans = max(ans, tmp_ans);

        std::cerr << "i = " << i << " idx = " << idx << " tmp_ans = " << tmp_ans << '\n';
    }
    std::cout << ans << '\n';
}