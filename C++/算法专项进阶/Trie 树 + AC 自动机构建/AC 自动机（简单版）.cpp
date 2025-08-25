#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;
// === 常量（简洁版） ===
const int L = 26;                 // a..z
const int N = 1000000 + 5;        // 节点上限：∑|si| ≤ 1e6 => 节点 ≤ 1e6+1
ll nxt[N][L];
ll fail[N];
ll outcnt[N];
ll occ[N];//文本扫描时“恰好到达 u 的次数”（逐模式计数用）
ll tot=1,root=1;
vector<ll> bfsorder;
ll n;
string t;

inline ll idx(char ch){ return ch-'a'; }

inline void insertStr(const string& s){
    ll u=1;
    for(char ch:s){
        ll id=idx(ch);
        if(!nxt[u][id]) nxt[u][id]=++tot;
        u=nxt[u][id];
        //所以在建 Trie 阶段，u 一定是严格递增的，因为你永远不会遇到环。
    }
    outcnt[u]++; // 题意：编号不同即算不同模式 => 重复串也要分别计数  
}

inline void buildfail(){
    queue<ll> q;
    for(ll c=0;c<L;c++){
        ll v=nxt[1][c];
        if(v) { fail[v]=1; q.push(v); }
        else nxt[1][c]=1;
    }
    while(!q.empty()){
        ll u=q.front(); q.pop();
        bfsorder.push_back(u);
        for(ll c=0;c<L;c++){
            ll v = nxt[u][c];
            if(v){ fail[v]=nxt[fail[u]][c]; q.push(v); }
            else nxt[u][c]=nxt[fail[u]][c];//「如果从 u 没有 c 出边，那就直接接成 fail[u] 的 c 出边」。可能发生 自环：
           //这样做的好处是 匹配时不用 while 回退，一句话就能跳
           //即使自环，含义也对：在 3 读到 'a' 时，还在 3，说明这个前缀自己已经包含自己，不需要再退回去
        }
    }
}

inline ll  matchCountDistinct(const string& text){
    ll u=1;
     for(char ch : text){  // 顺着文本一个字母一个字母读
        u = nxt[u][ idx(ch) ];//最初nxt 存储的都是节点的编号// 坐“ch 号地铁”，从当前站 u 到下一站
        occ[u] += 1;//统计对应每个节点被遍历了多少遍   // 在到达的这个站“打个卡：来过”
    }//这一步只是“到达状态计数”，还没把 fail 祖先算进去。
     // 逆 BFS 序沿 fail 汇总到父：更长后缀的出现也意味着其所有 fail 祖先出现
    for(int i = (int)bfsorder.size() - 1; i >= 0; --i){
        int x = bfsorder[i];
        occ[ fail[x] ] += occ[x];//落在更长后缀 x 的次数，要贡献给它的所有 fail 祖先。
    }
    // 统计：结点 u 若被命中（occ[u]>0），则把该结点终止的“编号个数”计入答案
    long long ans = 0;
    for(int u2 = 1; u2 <= tot; ++u2){
        if(occ[u2] > 0 && outcnt[u2] > 0) ans += outcnt[u2];
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    string s;
    for(int i = 1; i <= n; ++i){
        cin >> s;
        insertStr(s);
    }
     cin >> t;
     buildfail();
    cout << matchCountDistinct(t) << "\n";
    return 0;
}