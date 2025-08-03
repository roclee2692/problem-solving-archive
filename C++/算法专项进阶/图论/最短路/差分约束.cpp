#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = (ll)1e18;
struct Edge { ll u, v; ll w; };
ll n, m;
vector<Edge> edges;
vector<ll> distDif;
// 解差分约束：判断是否可行，并求最小 x[i]
bool SDC(){
     // 节点编号假设为 1..n，加入超源 0
    distDif.assign(n+1, INF);
    distDif[0] = 0;
    // 构造超源边 0->i (权 0)
    vector<Edge> es = edges;
    for (int i = 1; i <= n; ++i)
        es.push_back({0, i, 0});
          // Bellman–Ford 松弛 n 轮
    for (int i = 0; i < n; ++i) {
        bool updated = false;
        for (auto &e : es) {
            if (distDif[e.u] != INF && distDif[e.u] + e.w < distDif[e.v]) {
                distDif[e.v] = distDif[e.u] + e.w;
                updated = true;
            }
        }
        if (!updated) break;
    }
    // 第 n 轮检测负环
    for (auto &e : es) {
        if (distDif[e.u] != INF && distDif[e.u] + e.w < distDif[e.v])
            return false;
    }
    return true;
}

int main(){
ios::sync_with_stdio(0);cin.tie(0);
    
    // 输入：变量个数 n，不等式条数 m
    cin >> n >> m;
    edges.clear();
    edges.reserve(m);
    // 每条约束 u,v,w 表示 x[v] - x[u] <= w
    for (int i = 0; i < m; ++i) {
        int u, v; ll w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
     bool ok = SDC();
      if (!ok) {
        cout << "NO\n";  // 存在冲突（负环）
    } else {
        cout << "YES\n";
        // 若需输出最小解 x[1..n]：
        // for (int i = 1; i <= n; ++i) cout << distDif[i] << ' ';
        // cout << "\n";
    }
  return 0;
}
