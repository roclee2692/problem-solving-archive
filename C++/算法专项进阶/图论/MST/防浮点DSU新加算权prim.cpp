#include <bits/stdc++.h>
using namespace std;
using ld=double;//用 double 替代 long double：与题目期望格式一致，误差可控。
using ll=long long;
const ll INF=1e18;
using pll=pair<ll,ll>;
using pld=pair<ll,ld>;
using pdl=pair<ld,ll>;
vector<pll> V;
vector<ld> dist;
vector<vector<pld>> adj;
vector<ll> pre;
struct edge{ll u,v;ld w;};
vector<edge> mst;
ll n,m;
struct DSU{
    vector<ll> p,r;
    DSU(int n=0):p(n+1),r(n+1){iota(p.begin(),p.end(),0);}
    ll find(ll x){if(p[x]!=x) p[x]=find(p[x]);return p[x];}
    bool unite(ll a,ll b){
        a=find(a);b=find(b);
        if(a==b) return 0;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        if(r[a]==r[b]) r[a]++;
        return 1;
    }
};
ld add(ll a,ll b){
    ld x1=V[a].first,y1=V[a].second;
    ld x2=V[b].first,y2=V[b].second;
    ld x=(x1-x2);
    ld y=(y1-y2);
    ld w=sqrt(x*x+y*y);
    return w;
}
ld prim(ll src=1){
    mst.clear();
    dist.assign(n+1,INF);
    pre.assign(n+1,-1);
    priority_queue<pdl,vector<pdl>,greater<pdl>> pq;
    pq.emplace(0,src);
    dist[src]=0;
    // Prim：用 vis 数组取代浮点比较
     vector<char> vis(n+1, 0);
    ld ans=0;ll cnt=0;
    while(!pq.empty()){
        auto p=pq.top();pq.pop();
        ld d=p.first; ll u=p.second;
        //if(d>dist[u]) continue;
        //if (d - dist[u] > 1e-12) continue;//必要时加 eps 容忍 
        //微小误差可能让本该“最小”的边因 d > dist[u] 被当成“过期”丢弃，改变选边顺序
         if(vis[u]) continue;      // 直接用 vis 跳过重复
          vis[u] = 1;
// 用浮点时请保留 “d > dist[u]” 判断，而不要写 “d != dist[u]”，否则误差会把新元素当作过期元素丢掉，Prim 可能返回 -1。
        ans+=d;
        if(pre[u]!=-1)  mst.push_back({pre[u],u,d});
        cnt++;
        for(auto &x:adj[u]){
            ll v=x.first;ld  w=x.second;
            if(w<dist[v]){
                dist[v]=w;
                pre[v]=u;
                pq.emplace(w,v);
            }
        }
    }
    return (cnt==n)?ans:-1;
}
int main(){
//ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    DSU dsu(n);
    adj.assign(n+1,{});
    V.assign(n+1,{});
    for(ll i=1;i<=n;i++) {
        ld x,y;
        cin>>x>>y;
        V[i]= make_pair(x, y);
    }
    while(m--){
        ll u,v;
        cin>>u>>v;
        dsu.unite(u,v);
         // 已有边：费用 0
        adj[u].emplace_back(v,0);
        adj[v].emplace_back(u,0);
    }
   // 不同连通块之间补全距离边
   for(int i=1;i<=n;i++){
    for(int j=i+1;j<=n;j++){
        //if(!dsu.unite(i,j)){  会进行合并 无论在不在一个集合都会合并在一个集合
        if(dsu.find(i)!=dsu.find(j)){// 只给不同连通块加距离边 只判断不进行合并操作
            ld w=add(i,j);
            adj[i].emplace_back(j,w);
            adj[j].emplace_back(i,w);
        }
    }
   }
    ld ans=prim(1);
    if(ans<0) cout<<-1<<"\n";
    //cout.setf(ios::fixed);
    else cout<<fixed <<setprecision(2)<<ans<<"\n";//使用 setprecision(2) 时，
    //默认是对有效数字总数生效，而不是小数位数。要 固定显示两位小数，还需要加上 fixed 操作符
  return 0;
}