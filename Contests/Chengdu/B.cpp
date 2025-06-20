//
// Created by 24087 on 24-11-11.
//
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1'000'000'007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, Q;
    cin >> n >> Q;
    string s;
    cin >> s;

    // 计算总的 '?' 数量
    int total_q = 0;
    for(char ch : s){
        if(ch == '?') total_q++;
    }

    // dp[last][a][b]: 当前最后一个服饰类型为 last，分配了 a 个 'a'，b 个 'b'
    // last: 0=a, 1=b, 2=c, 3=undefined (初始状态)
    // 由于 n <=300 和 total_q <=300，使用二维数组压缩 a 和 b
    // dp_prev 和 dp_new 使用 vector<vector<ll>>，其中索引为 a*(total_q+1) + b
    // last =0,1,2,3
    const int MAX_A = total_q;
    const int MAX_B = total_q;
    vector<vector<ll>> dp_prev(4, vector<ll>((MAX_A+1)*(MAX_B+1), 0LL));
    // 初始状态: last=3 (undefined), a=0, b=0
    dp_prev[3][0*(MAX_B+1) + 0] = 1;

    // Temporary DP for new states
    vector<vector<ll>> dp_new(4, vector<ll>((MAX_A+1)*(MAX_B+1), 0LL));

    for(int i=0;i<n;i++){
        // Reset dp_new
        for(int l=0;l<4;l++) fill(dp_new[l].begin(), dp_new[l].end(), 0LL);
        // 当前字符
        char c_i = s[i];
        // 遍历所有可能的前一个状态
        for(int last_prev=0; last_prev<4; last_prev++){
            for(int a_prev=0; a_prev <= total_q; a_prev++){
                for(int b_prev=0; b_prev <= total_q - a_prev; b_prev++){
                    int index = a_prev*(MAX_B+1) + b_prev;
                    ll val = dp_prev[last_prev][index];
                    if(val ==0) continue;

                    if(c_i == 'a' || c_i == 'b' || c_i == 'c'){
                        // 固定服饰
                        int t_val;
                        if(c_i == 'a') t_val =0;
                        else if(c_i == 'b') t_val =1;
                        else t_val =2;
                        if(last_prev ==3 || t_val != last_prev){
                            // 不同于前一个
                            // 不增加 a 或 b
                            if(a_prev <= total_q && b_prev <= total_q - a_prev){
                                int new_last = t_val;
                                int new_a = a_prev;
                                int new_b = b_prev;
                                int new_index = new_a*(MAX_B+1) + new_b;
                                dp_new[new_last][new_index] = (dp_new[new_last][new_index] + val) % MOD;
                            }
                        }
                    }
                    else if(c_i == '?'){
                        // 需要分配
                        for(int t_val=0;t_val<3;t_val++){
                            if(last_prev ==3 || t_val != last_prev){
                                int new_a = a_prev;
                                int new_b = b_prev;
                                if(t_val ==0) new_a +=1;
                                if(t_val ==1) new_b +=1;
                                if(new_a > total_q || new_b > total_q - new_a) continue;
                                int new_last = t_val;
                                int new_index = new_a*(MAX_B+1) + new_b;
                                dp_new[new_last][new_index] = (dp_new[new_last][new_index] + val) % MOD;
                            }
                        }
                    }
                }
            }
        }
        // 交换 dp_prev 和 dp_new
        dp_prev = dp_new;
    }

    // 计算 dp_total[a][b} = sum over last=0,1,2 of dp_prev[last][a][b}
    // 初始化 dp_total 为二维数组
    vector<vector<ll>> dp_total(total_q+1, vector<ll>(total_q+1, 0LL));
    for(int last=0; last<3; last++){
        for(int a=0; a<=total_q; a++){
            for(int b=0; b<=total_q - a; b++){
                int index = a*(MAX_B+1) + b;
                dp_total[a][b] = (dp_total[a][b] + dp_prev[last][index]) % MOD;
            }
        }
    }

    // 预处理前缀和 pre_sum[a][b} = sum_{b'=0 to b} dp_total[a][b'}
    vector<vector<ll>> pre_sum(total_q+1, vector<ll>(total_q+1, 0LL));
    for(int a=0; a<=total_q; a++){
        pre_sum[a][0] = dp_total[a][0];
        for(int b=1; b<=total_q; b++){
            pre_sum[a][b] = (pre_sum[a][b-1] + dp_total[a][b]) % MOD;
        }
    }

    // 处理查询
    while(Q--){
        int x, y, z;
        cin >> x >> y >> z;
        // m = 总的 '?' 数量
        int m_total = total_q;
        // k = m - z
        int k = m_total - z;
        // 需要满足 a <=x, b <= y, a + b >=k
        // 也就是 c = m - a - b <= z
        // 即 a + b >= m - z
        // 并且 a <=x, b <= y
        ll answer =0;
        // a 从 max(0, k - y) 到 min(x, m_total)
        // b 从 max(k - a,0) 到 min(y, m_total - a)
        for(int a=0; a<=min(x, m_total); a++){
            int b_start = max(k - a, 0);
            int b_end = min(y, m_total - a);
            if(b_start > b_end) continue;
            // 使用 pre_sum 计算 [b_start, b_end] 的和
            if(b_start ==0){
                answer = (answer + pre_sum[a][b_end]) % MOD;
            }
            else{
                answer = (answer + pre_sum[a][b_end] - pre_sum[a][b_start -1] + MOD) % MOD;
            }
        }
        cout << answer << "\n";
    }
}
