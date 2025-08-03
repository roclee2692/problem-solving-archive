#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pii = pair<int,int>;
 const int INF = INT_MAX;//int 类型的最大值

 
/* ———— 模板 1：动态邻接表 ———— */
struct Graph1{
    int V;
    vector<vector<pii>> adj;
    Graph1(int n):V(n),adj(n){}// 大小 n+1，索引 1…n 
    // 注意「输入是 1…n 编号，却按 0…n-1 来处理」 这里数组大小改成n+1
    void addEdge(int u,int v,int w,bool directed=0){
        adj[u].emplace_back(v,w);//正向邻接表 存出度
        if(directed==1) adj[v].emplace_back(u,w);
    }
    vector<int> dijkstra(int src){
        vector<int> dist(V,INF); 
        dist[src]=0;
        priority_queue<pii,vector<pii>,greater<pii>> pq; // 元素类型  底层容器  比较器：greater 使得 top() 是最小值
        pq.emplace(0,src);

        while(!pq.empty()){
            auto p=pq.top(); pq.pop();
            int d = p.first, u = p.second;
//松弛操作 给到 v 的距离“放松”一下，看看能不能再缩短一点，能就更新。
//d 就是你当初 emplace(dist[u], u) 时，把当时 dist[u] 的值装到队列里的那个“快照”。
            if(d>dist[u]) continue;// u之前也压入过不是最终最短路径的值 只有d==dist[u] 该值才是可用的
            for(auto q:adj[u]){
                int v=q.first,w=q.second;
                if (dist[u] + w < dist[v]) {//先判断再 emplace，避免冗余，
                    dist[v] = dist[u] + w;//min()会将每条边都往堆里压一次，即便它并没有“松弛”到更短的距离
                    pq.emplace(dist[v], v);
                }
            }
        }
        return dist;
    }
};

/* ———— 模板 2：静态数组邻接表 ———— */
const int MAXN = 100000;
struct Graph2 {
    int N;
    vector<pii> adj[MAXN];
    Graph2(int n): N(n) {
        for (int i = 0; i < N; i++) adj[i].clear();
    }
    void addEdge(int u, int v, int w, bool directed=false) {
        adj[u].emplace_back(v, w);
        if (!directed) adj[v].emplace_back(u, w);
    }
    vector<int> dijkstra(int src) {
        const int INF = INT_MAX;
        vector<int> dist(N, INF);
        dist[src] = 0;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.emplace(0, src);
        while (!pq.empty()) {
            auto p = pq.top(); pq.pop();
            int d = p.first, u = p.second;
            if (d > dist[u]) continue;
            for (auto &e : adj[u]) {
                int v = e.first, w = e.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        return dist;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 任选其一：
    // Graph1 G1(n);
    Graph2 G2(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // G1.addEdge(u, v, w);
        G2.addEdge(u, v, w);
    }

    // auto dist = G1.dijkstra(0);
    auto dist = G2.dijkstra(0);

    for (int i = 0; i < n; i++)
        cout << i << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << "\n";//最好排除INF 索引为1时 防止将0 索引错误输出

    return 0;
}
