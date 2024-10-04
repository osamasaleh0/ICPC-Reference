class hopcroft_karp{
	public:
	
	int n;
	vector<vector<int> > adj;
	vector<int> match, dist;
 
	hopecroft_carp(int size){
		n = size;
		adj.resize(n + 1);
		match = dist = vector<int> (n + 1);
	}
 
	int operator[](int x){
		return match[x];
	}
 
	void add_edge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
 
	bool bfs(){
		queue<int> q;
		dist = vector<int> (n + 1, 1e9);
 
		for (int i = 1; i <= n; i ++){
			if (match[i] == 0){
				q.push(i);
				dist[i] = 0;
			}
		}
 
		dist[0] = 1e9;
		while (!q.empty()){
			int x = q.front();
			q.pop();
			if (dist[x] >= dist[0])
				continue;;
			for (auto i : adj[x]){
				if (dist[match[i]] == 1e9){
					dist[match[i]] = dist[x] + 1;
					q.push(match[i]);
				}
			}
		}
 
		return dist[0] != 1e9;
	}
 
	bool dfs(int cur){
		if (cur == 0)
			return true;
		for (auto i : adj[cur]){
			if (dist[match[i]] == dist[cur] + 1 && dfs(match[i])){
				match[cur] = i;
				match[i] = cur;
				return true;
			}
		}
 
		dist[cur] = 1e9;
		return false;
	}
 
	int get_maximum_matching(){
		int ans = 0;
 
		while (bfs()){
			for (int i = 1; i <= n; i ++)
				if (match[i] == 0 && dfs(i))
					ans ++;
		}
 
		return ans;
	}
};
