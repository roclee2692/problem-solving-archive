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
           int mid = up[u][i-1];
           up[u][i] = up[mid][i-1];
           // 四个候选：前半段最大/次大 & 后半段最大/次大
        vector<ll> c = {
            max1[u][i-1], max2[u][i-1],
            max1[mid][i-1], max2[mid][i-1]
        };
         sort(c.begin(), c.end(), greater<ll>());
        max1[u][i] = c[0];
        max2[u][i] = c[1];
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
pll querymax1dge(ll u,ll v){
    if(depth[u]<depth[v]) swap(u,v);
     ll r1=0, r2=0;
    ll diff=depth[u]-depth[v];
    for(int i=0;i<=LOGN;i++){
        if(diff&(1<<i)){
            vector<ll> c = {r1,r2, max1[u][i], max2[u][i]};
            sort(c.begin(), c.end(), greater<ll>());
            r1=c[0]; r2=c[1];
            u=up[u][i];
        }
    }
    if(u==v) return {r1,r2};
    for(int i=LOGN;i>=0;i--){
        if(up[u][i]!=up[v][i]){
            vector<ll> c = {
                r1,r2,
                max1[u][i], max2[u][i],
                max1[v][i], max2[v][i]
            };
            sort(c.begin(), c.end(), greater<ll>());
            r1=c[0]; r2=c[1];
            u=up[u][i];
            v=up[v][i];
        }
    }
     // 最后合并 u→parent, v→parent 两条边
    vector<ll> c = {r1,r2, max1[u][0], max1[v][0]};
    sort(c.begin(), c.end(), greater<ll>());
    return {c[0], c[1]};
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
        pll res = querymax1dge(u, v);
        cout << res.first << " " << res.second << "\n";
    }
   // 查询任意两点之间的距离
//long long d = getDist(u, v);
  return 0;
}
