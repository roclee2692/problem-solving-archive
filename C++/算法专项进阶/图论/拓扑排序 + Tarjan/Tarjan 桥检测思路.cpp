#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const ll MN=2e5+5;
ll n,m;
vector<pll> G[MN];
ll dfn[MN],low[MN],ts;//节点 u 的 DFS 访问次序（时间戳）。
//low[u]：从 u 出发，经过若干条边（可以往回走一次），能到达的最早祖先的 dfn。
vector<ll> is_cut;     // is_cut[u] = 1 表示 u 是割点
vector<pll> bridges;    // 存 (min(u,v), max(u,v)) 方便排序去重
// 为了少传参，核心放在一个函数：dfs(u, 来的边id, 父亲, 是否根 & 根的儿子计数)
void dfs(ll u,ll in_eid,ll fa,ll is_root){
    dfn[u]=low[u]=++ts;
    ll child=0;
    for(auto &e:G[u]){
        ll v=e.first;
        ll eid=e.second;
        if(eid==in_eid) continue;
        if(dfn[v]==0){// 没来过：树边
            child++;
            dfs(v,eid,u,0);
            low[u]=min(low[v],low[u]);
            // 回来后，v 子树能摸到多早的门牌，可能帮 u 也更早

            // ——桥判定：v 子树怎么努力也摸不到 u（或更早），那 (u,v) 是唯一通道
            if(low[v]>dfn[u]){
                ll a=u,b=v;
                if(a>b) swap(a,b);//保证加入桥的顺序 由小到大有序
                bridges.emplace_back(a,b);
            }

            // ——割点判定（非根）：如果 v 子树连 u 都摸不到（>=），说明 u 是这几片子树的“必经枢纽”
            if(!is_root&&low[v]>=dfn[u]) is_cut[u]=1;

        }else{ // 来到一个“已经登记过”的 v，且不是“来的那条边”：
            // 这是“暗道”直接回到祖先 v，当场就能确定能摸到的最早门牌至少是 dfn[v]
            low[u]=min(low[u],dfn[v]);
        }
    }
    // 根节点割点规则：孩子数 ≥ 2 才是割点（根断了会分成多片）
    if(is_root&&child>=2) is_cut[u]=1;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;// 边编号从 1 开始
    for(int i=1;i<=m;i++){
        ll u,v;
        cin>>u>>v;
        G[u].push_back(pll(v,i));
        G[v].push_back(pll(u,i));
    }
    is_cut.assign(n+1,0);
      // 可能不连通：每个没访问过的点都要单独开 DFS
      for(ll u=1;u<=n;u++){
        if(!dfn[u]){
            dfs(u,-1,-1,1); // in_eid = -1 表示没有“来的边”，is_root = 1
        }
      }
       // 桥输出（如题目需要）
       sort(bridges.begin(),bridges.end());
      bridges.erase(unique(bridges.begin(),bridges.end()),bridges.end());
      // for (auto &e : bridges) cout << e.first << " " << e.second << "\n";
    // 如果要输出割点：
    // for (ll u = 1; u <= n; u++) if (is_cut[u]) cout << u << "\n";

    return 0;
     
}