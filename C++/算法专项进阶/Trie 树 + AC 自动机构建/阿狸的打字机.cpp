#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;

const int L=26;
const int N=1e5;

ll nxt[N][L];
ll fail[N];
ll fa[N];// “打字 Trie”父节点（用于 B 回退）
ll tot=1,r=1;
vector<ll> sons[N];     // “打字 Trie”的树邻接（只存真实儿子）
vector<ll> failtree[N];//失败树
ll tin[N],tout[N],timer=0; // 失败树的 DFS 序
ll knode[N];//// 第 k 次 P 打印对应到的节点
ll np=0;
// 把询问挂到 y 对应的节点：pair(xNode, queryId)
vector<pll> query[N];
vector<ll> ans;



int main(){
     ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string ops;
    if(!(cin>>ops)) return 0;
    // buildTypingTrie();
    // buildAC();
    // dfsFail(r);
    // bitFT.init(timer_);   // BIT 的大小 = 失败树节点数（按 Euler 序大小）

    ll m; cin>>m;
    ans.assign(m+1,0);
    for(int i=1;i<=m;i++){
        ll x,y;
    cin>>x>>y;
    ll xNode=knode[x];
    ll yNode=knode[y];
    query[yNode].push_back({xNode,i});
    }
    // dfsTyping(r);
    for(ll i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}