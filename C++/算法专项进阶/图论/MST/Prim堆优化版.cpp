#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=(1LL<<60);
using pll=pair<ll,ll>;
// Prim（堆优化版）最小生成树模板 —— 全局变量 + 详细注释 + 健壮性检查
// 说明：
//  1. 点编号默认 1~n，图为无向加权连通图（若不连通会返回 -1）。
//  2. 采用邻接表 + 小根堆，时间复杂度 O(m log n)。
//  3. 全局保存生成树边 mst，权值和为 prim() 的返回值。
ll n,m;
vector<vector<pll>> adj;
struct edge {
  ll u, v, w;
  edge() {}
  edge(ll _u, ll _v, ll _w): u(_u), v(_v), w(_w) {}
};
// emplace_back(pre[u], u, d) 即可正常工作
vector<edge> mst;  
// Prim 相关全局辅助数组

vector<ll> dist,pre; // 每个点到当前生成树的最小边权   pre[v] = 把 v 加入 MST 时连接的父节点
// Prim：返回 MST 权值，不连通返回 -1
ll prim(ll src=1){//加点法
  dist.assign(n+1,INF);
  pre.assign(n+1,-1);
  mst.clear();
  priority_queue<pll,vector<pll>,greater<pll> > pq;
  dist[src]=0;
  pq.emplace(0,src);
  ll total=0,cnt=0;
  while(!pq.empty()){
    auto p=pq.top();pq.pop();
    ll d=p.first,u=p.second;
    if(d>dist[u]) continue;
    total+=d;
     // 只有当 pre[u]!=-1（即真正加入一条边）时才自增 cnt
        if(pre[u] != -1){
            // 保持 struct edge 不变
            mst.push_back({ pre[u], u, d });
  // 注意：使用 emplace_back 时需 struct 提供匹配的构造函数，
  //否则可改用 push_back({…}) 进行列表初始化，避免编译错误。
            cnt++;    // 现在 cnt 记录的是边数
        }
    //cnt++;// 注意：cnt 记录的是加入 MST 的节点数，
    //连通性应检查 cnt==n（节点数），而非 cnt==n-1（边数）
    for(auto &e:adj[u]){
      ll v=e.first,w=e.second;
      if(w<dist[v]){
        dist[v]=w;
        pre[v]=u;
        pq.emplace(dist[v],v);
      }
    }
  }
  return cnt==n-1 ?total:-1;
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    adj.assign(n+1,{});
    for(int i=0;i<m;i++){
      ll u,v,w;
      cin>>u>>v>>w;
      adj[u].emplace_back(v,w);
      adj[v].emplace_back(u,w);
    }
    ll ans=prim();
    if(ans == -1){
        cout << "Graph is not connected\n";
    }else{
        cout << ans << "\n";
        for(auto &e : mst) cout << e.u << " " << e.v << " " << e.w << "\n";
    }
  return 0;
}
