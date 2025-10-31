#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=4e18;
using pll=pair<ll,ll>;
ll m,n;
ll u,v,w;
vector<ll> dist,ans,pre;
vector<vector<pll>> adj;
vector<ll> dijkstra(){
    dist.assign(n+1,INF);
    pre.assign(n+1, -1);            // 初始化前驱
    dist[1]=0;
    priority_queue<pll,vector<pll>,greater<pll>> pq;
    pq.emplace(0,1);
    while(!pq.empty()){
    auto p=pq.top();pq.pop();
    ll d=p.first,u=p.second;
    if(d>dist[u]) continue;
        for(auto &e:adj[u]){
        ll v=e.first,w=e.second;
        if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                pre[v] = u;             // 记录前驱
                pq.emplace(dist[v],v);
            }
        }
    }
       // 用前驱回溯路径
       ans.clear();
       if(dist[n]!=INF){
        for(int x=n;x!=-1;x=pre[x])  ans.push_back(x);
        reverse(ans.begin(),ans.end());
       }
    return ans;
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    adj.resize(n+1);
    while(m--){
        cin>>u>>v>>w;
        adj[u].emplace_back(v,w);//正确做法是向尾部插入 这里是容器就用emplace_back pq才是emplace
        adj[v].emplace_back(u, w);
    }
    dijkstra();
     if (ans.empty()) {
        cout << -1;
    } else {
        for (auto x : ans)
            cout << x << ' ';
    }
  return 0;
}
