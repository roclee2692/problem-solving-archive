#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=LLONG_MAX;
using pll=pair<ll,ll>;
struct Edge{
    ll u,v,w;
    Edge(ll u1,ll v1,ll w1):u(u1),v(v1),w(w1){}
};
ll n,m;
vector<Edge> edges;
vector<vector<ll>> dist;// dist[s][t]: 最终最短距离
vector<ll> h;  // 势能

// 1. Johnson 重加权：多源全对全最短路（有向图，允许负权但无负环）
// 返回 false 表示存在负环，true 表示成功并填充 dist 矩阵
bool johnson(){
     // 1) Bellman–Ford 在超源 0 上求势能 h[1..n]
     h.assign(n+1,INF);
     h[0]=0;
       // 临时边集 es 包含原边 + 超源边
    vector<Edge> es = edges;
    for(int v=1;v<=n;v++) es.emplace_back(0,v,0);//让最优解 只有0和负数 得到各点势能好转正
    // 做 n 轮松弛 第一轮全拉为0 下面是n-1轮松弛 
    for(int i=1;i<=n;i++){
        bool upd=0;
        for(auto &e:es){
          if(h[e.u]!=INF&&h[e.u]+e.w<h[e.v]){
            h[e.v]=h[e.u]+e.w;              
            upd=1;               
          }
        }
        if(!upd) break;
    }
     // 检测负环
    for(auto &e:es){
        if (h[e.u] != INF && h[e.u] + e.w < h[e.v])
            return false;
    }
    // 2) 重加权后构建邻接表
     vector<vector<pll>> adj(n+1);
     for(auto &e:edges){
      ll w1=e.w+h[e.u]-h[e.v];
      adj[e.u].emplace_back(e.v,w1);
     }
      // 3) 对每个源 s 跑 Dijkstra，恢复原距离
     dist.assign(n+1,vector<ll>(n+1,INF));
     for(int s=0;s<n;s++){//多源的我们要跑N轮Dijkstra
         // Dijkstra
        priority_queue<pll,vector<pll>,greater<pll>> pq;
        vector<ll> d(n+1,INF);
        d[s]=0;
       pq.emplace(0,s);
       while(!pq.empty()){
        auto p=pq.top();pq.pop();
        ll du=p.first,u=p.second;
        if(du>d[u]) continue;
        for(auto &e:adj[u]){
          ll v=e.first,w=e.second;
          if(d[u]+w<d[v]){
            d[v]=d[u]+w;
            pq.emplace(d[v],0);
          }
        }
       }
         // 恢复并保存
         for(int t=1;t<=n;t++){//dist[n+1][n+1] 只利用1--n
           if(d[t]<INF) dist[s][t]=d[t]+h[t]-h[s];//公式变换 s->t 原w1=e.w+h[u]-h[v]>0 求e.w=w1+h[t]-h[s]
         }
     }
     return true;
}


int main(){
ios::sync_with_stdio(0);cin.tie(0);
cin>>n>>m;
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }
     if (!johnson()) {
        cout << "Negative cycle detected\n";
        return 0;
    }
    
    // 输出 dist 矩阵：1…n 之间的最短路距离
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dist[i][j] == INF) cout << "INF ";
            else                    cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }

    
  return 0;
}
