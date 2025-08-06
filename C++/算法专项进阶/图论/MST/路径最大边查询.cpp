#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
using de=double;
using ld=long double;
const ll INF=LLONG_MAX;
const int MAXN=1e6;
long long dist[MAXN];
const int LOGN=20;// 2^20 > 10^5，够用
ll n,m,s;
vector<pll> el[MAXN+5];
int up[MAXN+5][LOGN+5]; // up[u][j]：从 u 向上跳 2^j 步的祖先
int depth[MAXN+5]; // 节点深度
ll max1[MAXN+5][LOGN+1];           // max1[u][i]：u 向上跳 2^i 步过程中经过的最大边权
ll max2[MAXN+5][LOGN+1];   // 第二大边权 
// -------------------- DFS 构建 LCA 所需信息 --------------------
void dfs(int u,int parent){
    depth[u]=depth[parent]+1;//dfs是递归 边递归边存储每层的节点信息
    up[u][0]=parent;//建立深度信息，以及第一层祖先 up[u][0]（即直接父亲）。
    max1[u][0]=(parent==0)?0:max1[u][0];
    //开始倍增跃迁
    for(int i=1;i<=LOGN;i++){
        up[u][i]=up[up[u][i-1]][i-1];//从 u 向上跳 2^i 步 到哪里
        //递归是自上而下地构建整棵树；
        //每个节点在进入 DFS 时，其祖先信息已经准备好了；
        //构造 up[u][i] 所需的信息都已在上一层计算完，不依赖子树；
        //所以你先处理 up[u][i] 再处理子节点是正确且必须的。
        max1[u][i]=max(max1[u][i-1],max1[up[u][i-1]][i-1]);
    }
    for(auto e:el[u]){
        ll v=e.first,w=e.second;
        if(v==parent) continue;
        dist[v]=dist[u]+w;
        // 在这里给子节点赋第一跳的边权
        max1[v][0] = w;
        dfs(v,u);
    }
}
// -------------------- 求 LCA(u, v) 倍增 LCA - --------------------
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
// -------------------- 求树上距离 --------------------
long long getDist(int u, int v) {
    int lca = LCA(u, v);
    return dist[u] + dist[v] - 2 * dist[lca];
}

// -------------------- 查询 u->v 路径上的最大边权 --------------------
ll querymax1dge(ll u,ll v){
    if(depth[u]<depth[v]) swap(u,v);
    ll res=0;
    ll diff=depth[u]-depth[v];
    for(int i=0;i<=LOGN;i++){
        if(diff&(1<<i)){
            res=max(res,max1[u][i]);
            u=up[u][i];
        }
    }
    if(u==v) return res;
    for(int i=LOGN;i>=0;i--){
        if(up[u][i]!=up[v][i]){
            res=max(max1[u][i],res);
            res=max(max1[v][i],res);
            u=up[u][i];
            v=up[v][i];
        }
    }
    // 3. 最后再比较一次它们各自到父节点的那条边
    res = max(res, max1[u][0]);
    res = max(res, max1[v][0]); 
    return res;
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>s;
    for(int i=1;i<n;i++){
        int x,y,w=1;
        cin>>x>>y>>w;
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
    // 处理 m 次最大边查询
    while(m--){
        int u, v;
        cin >> u >> v;
        cout << querymax1dge(u, v) << "\n";
    }
   // 查询任意两点之间的距离
//long long d = getDist(u, v);
  return 0;
}
