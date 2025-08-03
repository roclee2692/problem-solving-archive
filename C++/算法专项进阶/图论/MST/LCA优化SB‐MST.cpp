#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = LLONG_MAX;

// 并查集（Union-Find）——按秩合并 + 路径压缩
struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1,0) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x]==x ? x : p[x]=find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

// 原图边
struct Edge {
    int u, v;
    ll w;
};

int n, m;
vector<Edge> E;                // 所有边，1…m
vector<bool> inMST;            // 标记哪些边在 MST 中

// MST 树的邻接表：存 (目标节点, 边权)
vector<vector<pair<int,ll>>> T;

// LCA 预处理
const int LOG = 20;            // 2^20 > 1e6, n≤1e5 可调
vector<int> depth;
vector<array<int,LOG>> up;     // up[v][k] = 2^k 祖先
vector<array<ll,LOG>> maxE;    // maxE[v][k] = v→up[v][k] 路径上的最大边权

// DFS 建树并初始化 depth, up[][0], maxE[][0]
void dfs(int u, int p){
    for(auto &ed : T[u]){
        int v = ed.first; ll w = ed.second;
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;
        maxE[v][0] = w;
        dfs(v, u);
    }
}

// 在树上查询 u→v 路径上的最大边权
ll getMaxEdgeOnPath(int u, int v){
    if (depth[u] < depth[v]) swap(u,v);
    ll mx = 0;
    // 把 u 抬到和 v 同深度
    int diff = depth[u] - depth[v];
    for(int k = 0; k < LOG; ++k){
        if (diff & (1<<k)) {
            mx = max(mx, maxE[u][k]);
            u = up[u][k];
        }
    }
    if (u == v) return mx;
    // 一起往上跳，直到它们的祖先相同
    for(int k = LOG-1; k >= 0; --k){
        if (up[u][k] != up[v][k]){
            mx = max(mx, maxE[u][k]);
            mx = max(mx, maxE[v][k]);
            u = up[u][k];
            v = up[v][k];
        }
    }
    // 最后再考虑一步跳到 LCA
    mx = max(mx, maxE[u][0]);
    mx = max(mx, maxE[v][0]);
    return mx;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1. 读入
    cin >> n >> m;
    E.resize(m+1);
    for(int i = 1; i <= m; ++i){
        cin >> E[i].u >> E[i].v >> E[i].w;
    }
    // 2. Kruskal 求 MST
    vector<int> idx(m);
    iota(idx.begin(), idx.end(), 1);
    sort(idx.begin(), idx.end(), [&](int a, int b){
        return E[a].w < E[b].w;
    });
    DSU dsu(n);
    inMST.assign(m+1, false);
    ll sumMST = 0;
    T.assign(n+1, {});
    int cnt = 0;
    for(int i : idx){
        auto &e = E[i];
        if (dsu.unite(e.u, e.v)){
            inMST[i] = true;
            sumMST += e.w;
            cnt++;
            T[e.u].push_back({e.v, e.w});
            T[e.v].push_back({e.u, e.w});
            if (cnt == n-1) break;
        }
    }
    if (cnt != n-1){
        // 图不连通，MST 不存在
        cout << "-1\n";
        return 0;
    }

    // 3. LCA 预处理
    depth.assign(n+1, 0);
    up.assign(n+1, array<int,LOG>{});
    maxE.assign(n+1, array<ll,LOG>{});
    // 初始化根节点（1）祖先为 1，本身 maxE=0
    depth[1] = 0;
    for(int k = 0; k < LOG; ++k){
        up[1][k] = 1;
        maxE[1][k] = 0;
    }
    dfs(1, 0);
    // 二进制提升
    for(int k = 1; k < LOG; ++k){
        for(int v = 1; v <= n; ++v){
            int m = up[v][k-1];
            up[v][k] = up[m][k-1];
            maxE[v][k] = max(maxE[v][k-1], maxE[m][k-1]);
        }
    }

    // 4. 枚举所有非 MST 边，寻找次小生成树
    ll second = LLONG_MAX;
    for(int i = 1; i <= m; ++i){
        if (inMST[i]) continue;   // 跳过在 MST 中的边
        auto &e = E[i];
        ll mx = getMaxEdgeOnPath(e.u, e.v);
        if (e.w > mx){
            second = min(second, sumMST + e.w - mx);
        }
    }

    if (second == LLONG_MAX) cout << "-1\n";
    else                    cout << second << "\n";
    return 0;
}
