#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl

namespace wxy{

typedef std::pair<int,int> PII;

const int N = 2e5 + 50;

int n,m,k,mod;

int dfn[N],low[N],idx[N],cnt_dcc,tot;

int stk[N],size[N],top;

bool vis[N];

int from[N],to[N],val[N],f[N][55];

int dist[N],topo[N],topo_cnt;

struct Graph{
int deg[N];
std::vector<int> out[N];
std::vector<int> in[N];
std::vector<int> win[N];
std::vector<int> wout[N];
inline void add(int x,int y,int we) {
out[x].push_back(y); in[y].push_back(x); deg[y]++;
win[y].push_back(we); wout[x].push_back(we);
}
inline void clear(){
rep(i,1,n) {
out[i].clear(); in[i].clear();
wout[i].clear(); win[i].clear();
deg[i] = 0;
}
}
}G0,GD,G;

inline void clear(){
G0.clear(); G.clear(); GD.clear();
memset(f,0,sizeof f); memset(topo,0,sizeof topo);
topo_cnt = top = tot = cnt_dcc = 0;
memset(vis,false,sizeof vis); memset(dist,0,sizeof dist);
memset(dfn,0,sizeof dfn); memset(low,0,sizeof low);
memset(idx,0,sizeof idx); memset(stk,0,sizeof stk);
memset(size,0,sizeof size);
}

void tarjan(int x) {
vis[x] = true; dfn[x] = low[x] = ++tot; stk[++top] = x;
for (int i = 0; i < G0.out[x].size(); i++) {
int v = G0.out[x][i];
if (!dfn[v]) {
tarjan(v); low[x] = std::min(low[x],low[v]);
} else if (vis[v]) low[x] = std::min(low[x],dfn[v]);
}
if (dfn[x] == low[x]) {
int y = -1; ++cnt_dcc;
do {
y = stk[top--]; vis[y] = false;
idx[y] = cnt_dcc; size[cnt_dcc]++;
} while (x != y);
}
}

inline void dijkstra(int s){
std::priority_queue<PII,std::vector<PII>,std::greater<PII> > q;
memset(dist,0x3f,sizeof dist); memset(vis,false,sizeof vis);
dist[s] = 0; q.push(std::make_pair(0,s)); f[s][0] = 1;
rep(i,1,cnt_dcc) if (size[i] > 1) f[i][0] = -1;
while (q.size()) {
int x = q.top().se; q.pop();
if (vis[x]) continue;
vis[x] = true;
for (int i = 0; i < G.out[x].size(); i++){
int v = G.out[x][i],w = G.wout[x][i];
if (dist[v] > dist[x] + w) {
dist[v] = dist[x] + w; q.push(std::make_pair(dist[v],v));
}
}
} rep(i,1,cnt_dcc) if (!vis[i]) f[i][0] = 0;
}

inline void BuildGraphDcc(){
rep(i,1,n)
if (!dfn[i]) tarjan(i);
rep(i,1,m) {
from[i] = idx[from[i]]; to[i] = idx[to[i]];
if (from[i] == to[i]) continue;
G.add(from[i],to[i],val[i]);
}
}

inline void BuildShortGraph(){
dijkstra(idx[1]);
rep(i,1,m) {
if (from[i] == to[i]) continue;
int u = from[i],v = to[i],w = val[i];
if (dist[u] + w == dist[v]) GD.add(u,v,w);
}
}

inline void topo_sort(){
std::queue<int> q;
rep(i,1,cnt_dcc)
if (GD.deg[i] == 0) q.push(i);
while (q.size()) {
int x = q.front(); q.pop(); topo[++topo_cnt] = x;
for (int i = 0; i < GD.out[x].size(); i++) {
int v = GD.out[x][i];
if (--GD.deg[v] == 0) q.push(v);
}
}
}

inline void solve(){
clear(); gin >> n >> m >> k >> mod;
rep(i,1,m) {
gin >> from[i] >> to[i] >> val[i];
if (val[i] == 0) G0.add(from[i],to[i],val[i]);
} BuildGraphDcc(); BuildShortGraph(); topo_sort();
rep(i,0,k)
rep(j,1,topo_cnt) {
int x = topo[j];
for (int p = 0; p < G.in[x].size(); p++) {
int v = G.in[x][p],w = G.win[x][p];
int vv = dist[x] + i - (dist[v] + w);
if (vv < 0) continue;
if (f[v][vv] == 0 || f[x][i] == -1) continue;
if (f[v][vv] == -1) f[x][i] = -1;
else f[x][i] = (f[x][i] + f[v][vv]) % mod;
}
}
bool ck = true; int now = idx[n]; int ans = 0;
rep(i,0,k){ans = (ans + f[now][i]) % mod; if (f[now][i] == -1) ck = false;}
if (ck == false) prt << -1 << edl;
else prt << ans << edl;
}

inline void main(){
#ifndef ONLINE_JUDGE
freopen("in.in","r",stdin);
freopen("out.out","w",stdout);
#endif
int t; gin >> t;
while (t--) solve();
}

}signed main(){wxy::main(); return 0;}