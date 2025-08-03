#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
using de=double;
using ld=long double;
const ll INF=LLONG_MAX;
const ll MAXN=1e5+5;
const ll LOGN=20;
ll depth[MAXN];
ll dp[MAXN][LOGN+1];
ll minE[MAXN][LOGN+1];
vector<pll> adj[MAXN];
struct edge{ll u,v,w;};
vector<edge> edges;
vector<edge> maxst;
struct DSU{
    ll n;
    vector<ll> p,r;
    DSU(ll n1):n(n1),p(n+1),r(n+1,0){iota(p.begin(),p.end(),0);}
    ll find(ll x){if(x!=p[x]) p[x]=find(p[x]); return p[x];}
    bool unite(ll a,ll b){
        a=find(a); b=find(b);
        if(a==b) return 0;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        if(r[a]==r[b]) r[a]++;
        return 1;
    }
};

void kruskal(ll n, DSU &dsu){
    
    maxst.clear();
    maxst.reserve(n-1);

    for(auto &e:edges){
        ll u=e.u,v=e.v,w=e.w;
        if(dsu.find(u)!=dsu.find(v)) {
        dsu.unite(u,v);
        maxst.push_back(e);
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
        ll ok=maxst.size();
        if(ok==n-1) break;
        }
    }
    return;
}

void dfs(ll u,ll fa,ll w){
    depth[u]=depth[fa]+1;
    dp[u][0]=fa;
    minE[u][0]=(fa==0?INF:w);
    for(int i=1;i<=LOGN;i++){
        ll mid=dp[u][i-1];
        dp[u][i]=dp[mid][i-1];
        minE[u][i]=min(minE[u][i-1],minE[mid][i-1]); // 两段跳跃的最小值合并取最小
    }
    for(auto &e:adj[u]){
        ll v=e.first,w=e.second;
        if(v==fa) continue;//为了避开“回头路”
        dfs(v,u,w);
    }
}
ll QLCA(ll a,ll b){
    ll ans=INF;
    if(depth[a]<depth[b]) swap(a,b);
    ll diff=depth[a]-depth[b];
    for(int i=0;i<=LOGN;i++){
        if(diff&(1<<i)) {
            ans=min(ans,minE[a][i]);
            a=dp[a][i];
        }
    }
    if(a==b) return ans;
    for(int i=LOGN;i>=0;i--){
        if(dp[a][i]!=dp[b][i]){
            ans=min(ans,minE[a][i]);
            ans=min(ans,minE[b][i]);
            a=dp[a][i];
            b=dp[b][i];
        }
    }
     // 最后跳一格到 LCA
    ans = min(ans, minE[a][0]);
    ans = min(ans, minE[b][0]);
    return ans;
}

int main(){
    ll n,m,q;
    cin>>n>>m;
    DSU dsu(n);
    while(m--){
        ll x,y,z;
        cin>>x>>y>>z;
        edges.push_back({x,y,z});
    }
    sort(edges.begin(),edges.end(),[](const edge &a,const edge &b) {return a.w>b.w;});
    cin>>q;
       kruskal(n,dsu);
        /* ① 先初始化虚根 0 的整行 */
        for(int i=0;i<=LOGN;i++){
        dp[0][i]   = 0;
        minE[0][i] = INF;
    }
        /* ② 对每个连通分量跑 DFS，一次性完成 */
for(int i = 1; i <= n; i++){
    // 对每个连通分量跑一次 DFS：使用 depth[]==0 判断未访问节点
    //已经访问过的只会大于0 为0即说明未访问
    if(depth[i] == 0){      // 还没访问过
        dfs(i, 0, 0);
    }
}
    while(q--){
        ll x,y;
        cin>>x>>y;
         if (dsu.find(x) != dsu.find(y)) {
        cout << -1 << '\n';
        continue;
    }
        ll ans=QLCA(x,y);
    cout<<ans<<'\n';

    }
    return 0;
}