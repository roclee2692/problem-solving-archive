#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
using de=double;
using ld=long double;
const ll INF=LLONG_MAX;
const ll MAXN=1e5+5;
const ll LOGN=20;
vector<char> inMST;        // 0/1 标记
ll n,m;
struct edge{
    ll v,u,w;
};
ll up[MAXN][LOGN+1], depth[MAXN];
ll mx1[MAXN][LOGN+1], mx2[MAXN][LOGN+1];
vector<pll> G[MAXN];
vector<edge> E;
vector<ll> used;

struct DSU{ 
    ll n;
    vector<ll> p,r;
    DSU(ll n1):n(n1),p(n+1),r(n+1,0){iota(p.begin(),p.end(),0);}
ll find(ll x){ if(x!=p[x]) p[x]=find(p[x]); return p[x];}
bool unite(ll a,ll b){
    a=find(a);  b=find(b);
    if(a==b) return 0;
    if(r[a]<r[b]) swap(a,b);
    p[b]=a;
    if(r[a]==r[b]) r[a]++;
    return 1;
}
};
ll kruskal(ll idx=-1){
    ll len=0;
    used.clear();// 如果你还想保留索引列表
    inMST.assign(m+1, 0);  // 每次重置
    for(int i=1;i<=n;i++) G[i].clear();//每次跑 kruskal 之前必须清空图
    DSU dsu(n);
    ll total=0;
    for(int i=1;i<=m;i++){
        if(i==idx) continue;
        auto &e=E[i];
        if(dsu.unite(e.v,e.u)){
            used.push_back(i);
            inMST[i] = 1;  // 标记
            G[e.u].push_back({e.v,e.w});
            G[e.v].push_back({e.u,e.w});
            total+=e.w;
            len=used.size();
            if(len==n-1) break;
        }
    }
    return len==n-1?total:-1;
}
void dfs(ll u,ll fa,ll w){
    depth[u]=depth[fa]+1;
    up[u][0]=fa;
    mx1[u][0]=w;//存的是「从 u 走 1 步到父节点 fa 时那条边的权重」
    mx2[u][0]=-1;//在只跳 1 步的场景下，这条路径上只有一条边，是没有第二大的用 -1（或任何比所有合法边权都小的值）来表示「无第二大」
    for(int i=1;i<=LOGN;i++){
        ll mid=up[u][i-1];
        up[u][i]=up[mid][i-1];
       // 四个候选：前段 mx1/mx2，后段 mx1/mx2
        ll a = mx1[u][i-1], b = mx2[u][i-1];
        ll c = mx1[mid][i-1], d = mx2[mid][i-1];
        // 选出前两大
        array<ll,4> t = {a,b,c,d};
        sort(t.begin(), t.end(), greater<ll>());
        mx1[u][i] = t[0];
        mx2[u][i] = t[1];
    }
    for(auto &e:G[u]){
        ll v=e.first, w=e.second;
        if(v==fa) continue;//为了避开“回头路”
        dfs(v,u,w);
    }
}
pll QLCA(ll x,ll y){
    if(depth[x]<depth[y]) swap(x,y);
     ll r1=-1, r2=-1;
    ll dx=depth[x]-depth[y];
    for(int i=0;i<=LOGN;i++){
        if(dx&(1<<i)) {
        array<ll,4> t = {r1,r2, mx1[x][i], mx2[x][i]};
        sort(t.begin(),t.end(),greater<ll>());
        r1=t[0]; r2=t[1];
        x = up[x][i];
        }
    }
    if(x==y) return {r1,r2};
    for(int i=LOGN;i>=0;i--){
        if(up[x][i]!=up[y][i]){
            array<ll,6> t={r1,r2,mx1[x][i],mx1[y][i],mx2[x][i],mx2[y][i]};
            sort(t.begin(),t.end(),greater<ll>());
            r1=t[0]; r2=t[1];
            x=up[x][i];
            y=up[y][i];
        }
    }
     // 最后跳一格到 LCA
     array<ll,6> t={r1,r2,mx1[x][0],mx2[x][0],mx1[y][0], mx2[y][0]};
     sort(t.begin(),t.end(),greater<ll>());
    return {t[0], t[1]};
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    E.resize(m+1);
    for(int i=1;i<=m;i++) {
        cin>>E[i].u>>E[i].v>>E[i].w;
    }
    sort(E.begin()+1,E.end(),[](auto &a,auto &b){return a.w<b.w;});
    ll sum=kruskal(-1);
for(int i = 0; i <= LOGN; ++i){
    up[0][i]  = 0;     // 祖先仍是 0
    mx1[0][i] = -1;    // 最大、次大都置 -1
    mx2[0][i] = -1;
}
//原图必须连通 才能有严格次小生成树。
//数据保证必定存在严格次小生成树。
//故图必定联通  一次dfs
    dfs(1,0,0);
    ll ans=INF;
for(int i=1;i<=m;i++){
        if(inMST[i]) continue;  // 只遍历非树边
    //对每一条“非树边”尝试把它插进来，看看能不能形成一个“严格次小生成树”，
    //最后取所有尝试结果里的最小值。
    if(E[i].u == E[i].v) continue;   // 跳过自环
    ll u = E[i].u;
    ll v = E[i].v;
    ll w = E[i].w;

     // C++11 取对 LCA 返回的 pair
    pair<ll,ll> p = QLCA(u, v);
    ll m1 = p.first;
    ll m2 = p.second;
     if (w > m1) {
        ans = min(ans, sum + w - m1);
    }
    else if (w == m1 && m2 >= 0 && m2 < m1 ) {
        ans = min(ans, sum + w - m2);//当一条路径上最大的两条树边权 m1, m2 恰好相等时,就“萎回”成最小生成树的权值，而题目要求“严格次小”，必须要 > sum。
        //在第二种替换分支中，多加一个 m2 < m1 的判断，确保替换后真的比原来大：
    }
    }
    
        cout<<ans;
  return 0;
}
