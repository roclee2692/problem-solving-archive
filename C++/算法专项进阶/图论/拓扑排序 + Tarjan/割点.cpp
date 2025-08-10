#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const int N=4e5+5;
ll n,m;
ll dfn[N],low[N],ts,cnt;
vector<pll> G[N];
vector<bool> is_cut;
void dfs(ll u,ll in_eid,ll fa,ll is_root){
    dfn[u]=low[u]=++ts;
    ll child=0;
    for(auto &e:G[u]){
        ll v=e.first;
        ll eid=e.second;
        
        if(eid==in_eid) continue;
        if(dfn[v]==0){//在判断“是否是树边”时写成了 dfn[u] == 0 应该判断邻居 v 是否未访问
            child++;
            dfs(v,eid,u,0);
            low[u]=min(low[u],low[v]);
            if(!is_root&&low[v]>=dfn[u]) {
                if(!is_cut[u]){               // ✅ 只在第一次标记时计数
                    is_cut[u] = 1;
                    cnt++;
                }
            }
        }else{
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(is_root&&child>=2){
        if(!is_cut[u]){                       // ✅ 同样避免重复计数
            is_cut[u] = 1;
            cnt++;
        }
    }
}
int main(){
    cin>>n>>m;
    is_cut.assign(n+1,0);
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
    cout<<cnt<<'\n';
    for (ll u = 1; u <= n; u++)//不用排序 已经是按照编号输出 排序会错位 Bool无大小
        if (is_cut[u]) cout << u <<" ";
    return 0;
}