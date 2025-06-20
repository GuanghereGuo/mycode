#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

const long long INF = std::numeric_limits<long long>::max();

class Dinic {
	struct Edge {
		int to;
		long long capacity, flow;
		Edge(int to, long long capacity):to(to), capacity(capacity), flow(0){
		}
	};
	int n, source, sink;
	std::vector<std::vector<int>> adj;
	std::vector<Edge> edges;
	std::vector<int> level;
	std::vector<int> ptr;
	
	bool bfs() {
		std::queue<int> q;
		level.assign(n + 1, -1);
		level[source] = 0;
		q.push(source);
		
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int idx : adj[u]){
				const Edge &e = edges[idx];
				if(e.flow < e.capacity && level[e.to] == -1) {
					level[e.to] = level[u] + 1;
					q.push(e.to);
				}
			}
		}
		
		return level[sink] != -1;
	}
	long long dfs(int u, long long pushed)  {
		if(u == sink) {
			return pushed;
		}
		for(int  &i = ptr[u]; i < adj[u].size(); ++i) {
			int idx = adj[u][i];
			Edge &e = edges[idx];
			if(level[u] + 1 != level[e.to] || e.flow == e.capacity) {
				continue;
			}
			long long flow = dfs(e.to, std::min(pushed, e.capacity - e.flow));
			if(flow > 0) {
				e.flow += flow;
				edges[idx ^ 1].flow -= flow;
				return flow;
			}
		}
		return 0;
	}
public:
	Dinic(int n, int source, int sink) :n(n), source(source), sink(sink) {
		adj.resize(n + 1);
		level.resize(n + 1);
		ptr.resize(n + 1);
	}
	
	void add_edge(int u, int v, long long capacity) {
		edges.emplace_back(v, capacity);
		edges.emplace_back(u, 0);
		adj[u].push_back(edges.size() - 2);
		adj[v].push_back(edges.size() - 1);
	}
	
	long long max_flow() {
		long long total_flow = 0;
		while(bfs()) {
			ptr.assign(n + 1, 0);
			while(long long flow = dfs(source, INF)) {
				total_flow += flow;
			}
		}
		return total_flow;
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	int n, m, s, t;
	std::cin >> n >> m >> s >> t;
	
	Dinic dinic(n + m * 2, s, t);
	
	for(int i = 1, u, v, w, x; i <= m; ++i) {
		std::cin >> u >> v >> w >> x;
		dinic.add_edge(u, n + 2 * i - 1, INF);
		dinic.add_edge(v, n + 2 * i - 1, INF);
		dinic.add_edge(w, n + 2 * i - 1, INF);
		dinic.add_edge(x, n + 2 * i - 1, INF);
		
		dinic.add_edge(n + 2 * i - 1, n + 2 * i, 1);
		dinic.add_edge(n + 2 * i, n + 2 * i - 1, 1);
		
		dinic.add_edge(n + 2 * i, u, INF);
		dinic.add_edge(n + 2 * i, v, INF);
		dinic.add_edge(n + 2 * i, w, INF);
		dinic.add_edge(n + 2 * i, x, INF);
	}
	
	std::cout << dinic.max_flow();
}

//4 1 1 2
//1 2 3 4


