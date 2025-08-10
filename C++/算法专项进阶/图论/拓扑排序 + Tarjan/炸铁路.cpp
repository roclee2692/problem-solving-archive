#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const int N=4e5+5;
ll n,m;
ll dfn[N],low[N],ts;
vector<pll> G[N],bridges;
void dfs(ll u,ll in_eid,ll fa,ll is_root){
    dfn[u]=low[u]=++ts;
    for(auto &e:G[u]){
        ll v=e.first;
        ll eid=e.second;
        if(eid==in_eid) continue;
        if(dfn[v]==0){//在判断“是否是树边”时写成了 dfn[u] == 0 应该判断邻居 v 是否未访问
            dfs(v,eid,u,0);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){//v的最短门牌无法到比u的id更小 说明无论如何也回不来了 即u v是桥
                ll a=u;
                ll b=v;
                if(a>b) swap(a,b);
                bridges.emplace_back(a,b);
            }
        }else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}
int main(){
    cin>>n>>m;
    for(ll i=1;i<=m;i++) {
        ll a,b;
        cin>>a>>b;
        G[a].push_back(pll(b,i));
        G[b].push_back(pll(a,i));
    }
    for(ll i=1;i<=n;i++){
        if(dfn[i]==0)
        dfs(i,-1,-1,1);
    }
    sort(bridges.begin(),bridges.end());
    bridges.erase(unique(bridges.begin(),bridges.end()),bridges.end());
    for (auto &e : bridges) cout << e.first << " " << e.second << "\n";
    return 0;
}