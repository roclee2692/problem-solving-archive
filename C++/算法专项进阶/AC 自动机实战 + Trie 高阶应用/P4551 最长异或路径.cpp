
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
const int MAXB=60;
struct XORTrie{

    vector<array<ll,2>> nxt;
    ll tot;
    XORTrie(ll MN=0){ if(MN) init(MN); }
    void init(ll MN){
        nxt.assign( MN+2,{0,0});
        tot=1;
    }
    inline int bit(ll x,ll b){ return (x>>b)&1; }
    inline void insert(ll x){
        ll u=1;
        for(int b=MAXB;b>=0;b--){
            int c=bit(x,b);
            if(!nxt[u][c]) nxt[u][c]=++tot;
            u=nxt[u][c];
        }
    }
    inline ll query_max_xor(ll x){
        ll u=1,val=0;
        for(int i=MAXB;i>=0;i--){
            int c=bit(x,i),want=c^1;
            if(nxt[u][want]){ u=nxt[u][want];val|=(1LL<<i); }
            else { u=nxt[u][c]; }
        }
        return val; // 最大异或值
    }
    
};

ll n, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if(!(cin>>n)) return 0;
    vector<vector<pll>> adj(n+1);
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
     // 1) 根 1，求前缀异或
     vector<ll> pref(n+1, 0);
    vector<int> vis(n+1, 0);
    stack<int> st;
    st.push(1);vis[1]=1;pref[1]=0;
    while(!st.empty()){
        int u=st.top(); st.pop();
        for(auto x:adj[u]){
            int v=x.first;
            ll w=x.second;
            if(vis[v]) continue;
            vis[v]=1;
            pref[v]=pref[u]^w;
            st.push(v);
        }
    }
    // 2) 最大异或对
    XORTrie tr((ll)n * (MAXB + 1) );//“我要插入 n 个数，每个数最多用到 MAXB+1 层，所以最多新建这么多节点”。
        ll ans = 0;
    tr.insert(pref[1]);
    for(int i=2;i<=n;i++){
        ans = max(ans, tr.query_max_xor(pref[i]));
        tr.insert(pref[i]);
    }
    cout << ans << "\n";
    return 0;
}