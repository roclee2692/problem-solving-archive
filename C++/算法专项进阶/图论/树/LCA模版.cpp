#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
using de=double;
using ld=long double;
const ll INF=LLONG_MAX;
const int MAXN=1e6;
const int LOGN=20;// 2^20 > 10^5，够用
ll n,m,s;
vector<pll> el[MAXN+5];
int up[MAXN+5][LOGN+5]; // up[u][j]：从 u 向上跳 2^j 步的祖先
int depth[MAXN+5]; // 节点深度
// dist[u]：记录节点 u 到根节点的距离
long long dist[MAXN + 5];
//预处理 O(n log n)，查询 O(log n)。
// -------------------- DFS 构建 LCA 所需信息 --------------------
void dfs(int u,int fa){
    depth[u]=depth[fa]+1;//dfs是递归 边递归边存储每层的节点信息
    up[u][0]=fa;//建立深度信息，以及第一层祖先 up[u][0]（即直接父亲）。
    //开始倍增跃迁
    for(int i=1;i<=LOGN;i++){
        up[u][i]=up[up[u][i-1]][i-1];//从 u 向上跳 2^i 步 到哪里
        //递归是自上而下地构建整棵树；
        //每个节点在进入 DFS 时，其祖先信息已经准备好了；
        //构造 up[u][i] 所需的信息都已在上一层计算完，不依赖子树；
        //所以你先处理 up[u][i] 再处理子节点是正确且必须的。
    }
    for(auto &e:el[u]){
        ll v=e.first,w=e.second;
        if(v==fa) continue;
        dist[v]=dist[u]+w;
        dfs(v,u);
    }
}
// -------------------- 求 LCA(u, v) --------------------
int LCA(int x,int y){
    if(depth[x]<depth[y]) swap(x,y);
    int diff=depth[x]-depth[y];
    for(int i=0;i<=LOGN;i++){
        if(diff&(1<<i) ) x=up[x][i]; // 如果第 i 位是 1，就跳 2^i 步
    }
    if(x==y) return x;
    for(int i=LOGN;i>=0;i--){
         if(up[x][i]!=up[y][i]){
            x=up[x][i];
            y=up[y][i];
         }
    }
    return up[x][0];
}
// -------------------- 求两点距离 getDist(u, v) --------------------
long long getDist(int u, int v) {
    // 若有需要处理边界情况，可额外判断
    if(u == 0 || v == 0) return 0; // 根据第一份代码的特殊写法，可自行选择
    int lca = LCA(u, v);
    // dist[u] + dist[v] - 2 * dist[LCA(u, v)]
    return dist[u] + dist[v] - 2 * dist[lca];
    //若是无权树，设所有边权 w = 1，即退化为“边数版本”；
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>s;
    for(int i=1;i<n;i++){
        int x,y;
        ll w;
        cin>>x>>y;
        el[x].push_back({y,w});
        el[y].push_back({x,w});
    }
    dfs(s,0);// 只需要调用一次DFS，以根节点s为起点，0作为虚拟父节点
    while(m--){
        int a,b;
        cin>>a>>b;
        int ans=LCA(a,b);
        cout<<ans<<'\n';
    }
   // 查询任意两点之间的距离
//long long d = getDist(u, v);
  return 0;
}
