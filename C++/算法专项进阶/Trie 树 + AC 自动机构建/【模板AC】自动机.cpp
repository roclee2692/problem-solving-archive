#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+7;
const int L=26;
ll fail[N];
ll nxt[N][L];
ll cnt[N];
ll tot=1,r=1;
ll passcnt[N],endpos[N];
ll n;
// 为逐模式的“自底向上汇总”准备的 BFS 序（从浅到深）
vector<ll> bfsOrder;
inline ll idx(char ch){ return ch-'a'; }
inline void ac_clear(){
    for(int i=1;i<N;i++){
        for(int c=0;c<L;c++) nxt[i][c]=0;
        fail[i]=endpos[i]=cnt[i]=0;
    }
    tot=1,r=1;
    bfsOrder.clear();
}
inline void ac_insert(const string &s,ll pid){
    ll u=1;
    for(char ch:s){
        ll id=idx(ch);
        if(!nxt[u][id]) nxt[u][id]=++tot;
        u=nxt[u][id];
    }
    endpos[pid]=u;// 允许重复模式：每个编号单独指向它的末结点
}
inline void ac_build(){
    queue<ll> q;
    for(int c=0;c<L;c++){
        ll v=nxt[r][c];
        if(v) { fail[v]=r;q.push(v); }
        else nxt[r][c]=r;
    }
    while(!q.empty()){
        ll u=q.front(); q.pop();
        bfsOrder.push_back(u);
        for(int c=0;c<L;c++){
            ll v=nxt[u][c];
            if(v) { fail[v]=nxt[fail[u]][c];q.push(v); }
            else nxt[u][c]=nxt[fail[u]][c];//return back
        }
    }
}
inline void ac_match(const string &s){
    ll u=1;
    for(char ch:s){
        ll id=idx(ch);
        u=nxt[u][id];
        cnt[u]++;
    }
    for(int i=bfsOrder.size()-1;i>=0;i--){
        ll x=bfsOrder[i];// get a node
        cnt[fail[x]]+=cnt[x]; 
/*cnt[fail[x]] += cnt[x] 是在 fail 树上做子→父汇总：凡是文本位置能落在结点 x，
        它的所有 fail 祖先（更短的后缀模式）也应该算一次，所以把次数加到父亲 fail[x]。
        若 fail[x]==root(=1)，说明 L(x) 没有任何非空后缀在 Trie 中，汇总到根就到此为止；
        根不代表任何模式，所以根的计数不参与答案，安全。
        cnt[u]：文本扫描时恰好到达状态 u 的次数。
fail[x]：L(x) 的最长真后缀所在结点（在 Trie 中存在）。*/
    }
}
int main(){
    string s;
  //  cin>>n;
    if(!(cin>>n)) return 0;
    vector<string> pat(n+1);
    ac_clear();
    for(int i=1;i<=n;i++) {//模式编号从 0 开始插入，输出却按 1..n 取值，索引错位。
        cin>>pat[i];
        ac_insert(pat[i],i);
    }
    cin>>s;
    ac_build();
    ac_match(s);
      // 输出每个模式的出现次数
    for(int i=1;i<=n;i++){
        cout<<cnt[endpos[i]]<<'\n';
    }
    return 0;
}