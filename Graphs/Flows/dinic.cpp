class dinic{
	private:
	struct edge{
		int64 u, v, i, c;
		edge(int U, int V, int I, int64 C): u(U), v(V), i(I), c(C) {}
	};
 
	public:
	vector<edge> edges;
	int n, source, sink;
	vector<vector<int> > adj;
 
	dinic(int size, int s, int t): n(size), source(s), sink(t), adj(vector<vector<int> > (n + 1)) {}
 
	void add_edge(int u, int v, int64 c){
		adj[u].push_back(int(edges.size()));
		edges.push_back(edge(u, v, edges.size(), c));
		adj[v].push_back(int(edges.size()));
		edges.push_back(edge(v, u, edges.size(), 0));
	}
 
	int64 get_max_flow(){
		int64 ans = 0;
		vector<int> par(n + 1, 0);
		auto level = par, dead_end = par;
 
		auto bfs = [&](){
			for (int i = 0; i <= n; i ++){
				level[i] = n + 1;
				dead_end[i] = 0;
				par[i] = - 1;
			}
			
			queue<int> q;
			q.push(source);
			level[source] = 0;
 
			while (!q.empty()){
				int t = q.front();
				q.pop();
 
				if (t == sink)
					return true;
 
				for (auto i : adj[t]){
					edge e = edges[i];
					if (e.c == 0 || level[e.v] != n + 1)
						continue;
					level[e.v] = level[t] + 1;
					q.push(e.v);
				}
			}
 
			return false;
		};
 
		auto dfs = [&](auto &&dfs, int cur, int last) -> bool{
			par[cur] = last;
			if (cur == sink)
				return true;
			if (dead_end[cur])
				return false;
 
			for (auto i : adj[cur]){
				auto e = edges[i];
 
				if (e.c == 0 || level[e.v] <= level[cur])
					continue;
				if (dfs(dfs, e.v, i) == true)
					return true;
			}
 
			dead_end[cur] = 1;
			return false;
		};
 
		while (bfs()){
			while(dfs(dfs, source, 0)){
				int64 x = sink, mn = 1e15;
				while (x != source){
					int i = par[x];
					mn = min(mn, edges[i].c);
					x = edges[i].u;
				}
 
				x = sink;
				ans += mn;
 
				while (x != source){
					int i = par[x];
					int j = i ^ 1;
 
					edges[i].c -= mn;
					edges[j].c += mn;
					x = edges[i].u;
				}
			}
		}
 
		return ans;
	}
};
