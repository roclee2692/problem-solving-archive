#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;
// ===== 配置（按题面） =====
const ll L = 26;                 // 字母表 a-z
const ll N = 1e6+7; 
ll nxt[N][L];
ll fail[N];
ll cnt[N];
ll endid[N];
ll tot=1;
vector<ll> bfs_order;
ll n;
string t;
vector<ll> ans;
inline ll idx(char ch){ return ch-'a'; }
inline void ac_clear(){
    for(int i=1;i<=tot;i++){
        for(int c=0;c<L;c++) nxt[i][c]=0;
        fail[i]=cnt[i]=endid[i]=0;
    }
    tot=1;
    bfs_order.clear();//把元素数量（size）置为 0，析构存放的元素。
}
inline void ac_insert(const string &s,ll pid){
    ll u=1;
    for(char ch:s){
        ll id=idx(ch);
        if(!nxt[u][id]) nxt[u][id]=++tot;
        u=nxt[u][id];
    }
    endid[u]=pid;
}
// BFS 构造 fail，同时把缺省转移补成自动机边
inline void ac_build(){
    queue<ll> q;
    for(int c=0;c<L;c++){
        ll v=nxt[1][c];
        if(v) { fail[v]=1;q.push(v); }
        else nxt[1][c]=1;
    }
    bfs_order.clear();    // 记录 BFS 顺序（不含 root）
    while(!q.empty()){
        ll u=q.front(); q.pop();
        bfs_order.push_back(u);
        for(int c=0;c<L;c++){
            ll v=nxt[u][c];
            if(v) { fail[v]=nxt[fail[u]][c];q.push(v); }
            else nxt[u][c]=nxt[fail[u]][c];// 补自动机转移
        }
    }
}
// 匹配文本并把出现次数分配到各模式
inline void ac_match(const string &t,vector<ll> &ans){
    ll u=1;
    for(char ch:t){
        ll c=idx(ch);
        u=nxt[u][c];
        cnt[u]++;
    }
    for(ll i=(ll)bfs_order.size()-1;i>=0;i--){
        ll x=bfs_order[i];
        cnt[fail[x]]+=cnt[x];//fail本质是在本条链路和符合条件链路的最长公共前后缀的回退
    }
    for(int node=1;node<=tot;node++){
        ll pid=endid[node];//节点node 对应模式串索引
        if(pid>0) ans[pid]=cnt[node];//模式串被命中过
        //（被命中只能是末尾节点 代表完整模式串的结束） 使该节点的计数赋值给 节点模式索引的答案中
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while(cin>>n && n){
        ac_clear();
        vector<string> pat(n+1);
        for(int i=1;i<=n;i++){
              cin>>pat[i];
              ac_insert(pat[i],i);
        }
        cin>>t;
        ac_build();
        ans.assign(n+1,0);
        ac_match(t,ans);
        ll mx=0;
        for(ll i=1;i<=n;i++) mx = max(mx, ans[i]);
            cout << mx << "\n";
        for(ll i=1;i<=n;i++) if(ans[i]==mx) cout << pat[i] << "\n";    
    }
    return 0;
}