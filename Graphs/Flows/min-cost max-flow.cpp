using int64 = long long;
 
class MCMF{
private:
    struct edge{
        int64 u, v, capacity, cost, old_capacity;
     
        edge(int64 from, int64 to, int64 Cost, int64 Capacity){
            cost = Cost;
            u = from;
            v = to;
            capacity = Capacity;
            old_capacity = capacity;
        }
    };
    
public:

    vector<edge> e;
    vector<vector<int> > adj;
    int64 n, source, sink, flow;
 
    MCMF(int64 N, int64 S, int64 T, int64 Flow){
        n = N;
        sink = T;
        source = S;
        flow = Flow;
 
        adj = vector<vector<int> > (n + 1);
    }
 
    void add_edge(int u, int v, int64 cost, int64 capacity){
        adj[u].push_back(e.size());
        e.push_back(edge(u, v, cost, capacity));
 
        adj[v].push_back(e.size());
        e.push_back(edge(v, u, -cost, 0));
    }
 
    bool spfa(vector<int64> &dis, vector<int64> &par){
        dis = vector<int64> (n + 1, int64(1e15));
 
        queue<int64> q;
        vector<bool> p(n + 1);
 
        q.push(source);
        dis[source] = 0;
 
        while (!q.empty()){
            int x = q.front();
            q.pop();
            p[x] = false;
 
            for (auto i : adj[x]){
                int64 Cost = e[i].cost;
                int64 Capacity = e[i].capacity;
 
                if (Capacity > 0 && dis[x] + Cost < dis[e[i].v]){
                    dis[e[i].v] = dis[x] + Cost;
                    par[e[i].v] = i;
 
                    if (p[e[i].v] == false) {
                        p[e[i].v] = true;
                        q.push(e[i].v);
                    }
                }
            }
        }
 
        return dis[sink] != int64(1e15);
    }
 
    pair<int64, int64> get_mcmf(){
        int64 mc = 0, mf = 0;
        vector<int64> dis(n + 1), par(n + 1);
 
        while (flow > mf && spfa(dis, par)){
            int now = sink;
            int64 dif = flow - mf;
 
            while (now != source) {
                dif = min(dif, e[par[now]].capacity);
                now = e[par[now]].u;
            }
 
            mf += dif;
            mc += dif * dis[sink];
 
            now = sink;
 
            while (now != source) {
                int i = par[now];
                e[i].capacity -= dif;
                e[i ^ 1].capacity += dif;
                now = e[i].u;
            }
        }
 
        return {mc, mf};
    }
};
