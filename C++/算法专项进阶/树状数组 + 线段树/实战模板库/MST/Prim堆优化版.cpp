/*
 * 【Prim 算法】- 最小生成树（堆优化版）
 * 
 * 时间复杂度：O((V + E) log V)
 * 空间复杂度：O(V + E)
 * 
 * 适用场景：
 *   - 求最小生成树（权值最小）
 *   - 稠密图更优
 *   - 需要逐步构建生成树
 * 
 * 模板题：洛谷 P3366 - 【模板】最小生成树
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=(1LL<<60);
using pll=pair<ll,ll>;
const int XN=1e6+7;

ll n,m;
struct Edge{
  ll u,v,w;
};
vector<Edge> mst;
vector<pll> adj[XN];
vector<ll> dist;
vector<ll> pre;
ll prim(ll src=1){
  ll total=0,cnt=0;
  dist.assign(n+1,INF);
  pre.assign(n+1,-1);
  mst.clear();
  priority_queue< pll,vector<pll>,greater<pll> > pq;
  dist[src]=0;
  pq.emplace(0,src);
  while(!pq.empty()){
    auto [d,u]=pq.top(); pq.pop();
    if(d>dist[u]) continue;
    total+=d;
    if(pre[u]!=-1){
      mst.push_back({pre[u],u,d});
      cnt++;
    }
    for(auto &e:adj[u]){
     auto [v,w]=e;
     if(w<dist[v]){
      dist[v]=w;
      pq.emplace(dist[v],v);
      pre[v]=u;
     }
    }
  }
  return cnt==n-1 ?total:-1;
}

int main(){
  ios_base::sync_with_stdio(0);  cin.tie(0);
  cin>>n>>m;
  for(int i=0;i<m;i++){
    ll u,v,w;
    cin>>u>>v>>w;
    // 无向图：两端都要加边
    adj[u].push_back({v,w});
    adj[v].push_back({u,w});
  }
  ll ans=prim();
  if(ans==-1){
    cout<<"orz\n";
  }else{
    cout<<ans<<'\n';
        // 可选：输出每条边
        // for(auto &e:mst) cout<<e.u<<" "<<e.v<<" "<<e.w<<"\n";
  }
  return 0;
}
/*
 * 【Prim 算法步骤】
 * 1. 从起点开始，初始化dist[src]=0
 * 2. 每次选择dist最小且未加入MST的节点u
 * 3. 将u加入MST，更新u的邻居到MST的最短边
 * 4. 重复直到所有节点加入（n-1条边）
 * 
 * 【为什么贪心有效？】
 * - 切分定理（Cut Property）：
 *   "连接两个连通分量的最小边一定在MST中"
 * - Prim每次选择最小的连接边，保证全局最优
 * 
 * 【与 Kruskal 的对比】
 * Prim:
 *   - 时间：O((V + E) log V)（堆优化）
 *   - 空间：O(V + E)
 *   - 适合：稠密图
 *   - 特点：逐点扩展
 * Kruskal:
 *   - 时间：O(E log E)
 *   - 空间：O(V + E)
 *   - 适合：稀疏图
 *   - 特点：逐边添加
 * 
 * 【常见优化】
 * - 斐波那契堆：降至O(E + V log V)，但常数大
 * - 邻接矩阵版本：适合V²级别边数的稠密图
 * - 起点选择：从度数大的点开始可能更快
 * 
 * 【提交前检查】
 * - [ ] 邻接表是否正确构建？
 * - [ ] 堆中是否有过时状态检查？
 * - [ ] 是否检查了连通性（cnt==n-1）？
 * - [ ] dist初始化是否为INF？
 * - [ ] 边权是否可能溢出？
 */
