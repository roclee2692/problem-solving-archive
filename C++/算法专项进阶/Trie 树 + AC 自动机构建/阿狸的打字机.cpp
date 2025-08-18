#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;

// ================== 参数 ==================
const ll SIG = 26;
const ll MAXN = 100000 + 5;   // 节点上限 ≈ 1 + 输入串中字母数

// ================== 全局结构（全 ll） ==================
ll ch[MAXN][SIG];        // goto：ch[u][c] = v
ll fail_[MAXN];          // fail 指针
ll fa[MAXN];             // “打字 Trie”父节点（用于 B 回退）
ll root = 1, tot = 1;    // 根=1，节点自增

vector<ll> sons[MAXN];         // “打字 Trie”的树邻接（只存真实儿子）
vector<ll> failTree[MAXN];     // 失败树

ll tin_[MAXN], tout_[MAXN], timer_ = 0;  // 失败树的 DFS 序

// 第 k 次 P 打印对应到的节点
ll id2node[MAXN];
ll nP = 0;

// 把询问挂到 y 对应的节点：pair(xNode, queryId)
vector<pll> queriesAt[MAXN];
vector<ll> ans;                // 答案 1..m

// ================== BIT（Fenwick） on Euler Tour ==================
struct BIT {
    ll n;
    vector<ll> t;
    static inline ll lowbit(ll x){ return x & -x; }
    inline void init(ll _n){ n = _n; t.assign((size_t)n + 1, 0); }
    inline void add(ll x, ll v){ for(; x <= n; x += lowbit(x)) t[(size_t)x] += v; }
    inline ll sum(ll x){ ll s=0; for(; x > 0; x -= lowbit(x)) s += t[(size_t)x]; return s; }
    inline ll range(ll l, ll r){ if(l>r) return 0; return sum(r) - sum(l-1); }
} bitFT;

// ================== 工具 ==================
inline ll idx(char c){ return (ll)(c - 'a'); }

// ================== 1) 读按键串，建“打字 Trie”并记录 P ==================
inline void buildTypingTrie(const string &ops){
    ll cur = root;
    fa[root] = root;
    for(char c : ops){
        if(c == 'B'){
            cur = fa[cur];
        }else if(c == 'P'){
            id2node[++nP] = cur;
        }else{
            ll k = idx(c);
            if(!ch[cur][k]){
                ch[cur][k] = ++tot;
                fa[tot] = cur;
                sons[cur].push_back(tot);
            }
            cur = ch[cur][k];
        }
    }
}

// ================== 2) 基于“打字 Trie”建 AC fail + 失败树 ==================
inline void buildAC(){
    queue<ll> q;
    fail_[root] = 0;
    // 根的儿子：fail=根
    for(ll c=0;c<SIG;c++){
        ll v = ch[root][c];
        if(v){ fail_[v] = root; q.push(v); }
    }
    // BFS
    while(!q.empty()){
        ll u = q.front(); q.pop();
        for(ll c=0;c<SIG;c++){
            ll v = ch[u][c];
            if(!v) continue;
            ll f = fail_[u];
            while(f && !ch[f][c]) f = fail_[f];
            fail_[v] = ch[f][c] ? ch[f][c] : root;
            q.push(v);
        }
    }
    // 失败树
    for(ll u=2; u<=tot; ++u){
        failTree[ fail_[u] ].push_back(u);
    }
}

// ================== 3) 失败树 DFS 序 ==================
inline void dfsFail(ll u){
    tin_[u] = ++timer_;
    for(ll v : failTree[u]) dfsFail(v);
    tout_[u] = timer_;
}

// ================== 4) 在“打字 Trie”上 DFS，在线回答查询 ==================
inline void dfsTyping(ll u){
    bitFT.add(tin_[u], 1); // 激活当前节点
    // 回答挂在 y=u 的所有询问
    for(const auto &pq : queriesAt[u]){
        ll xNode = pq.first;
        ll qid   = pq.second;
        ans[(size_t)qid] = bitFT.range(tin_[xNode], tout_[xNode]);
    }
    for(ll v : sons[u]) dfsTyping(v);
    bitFT.add(tin_[u], -1); // 退栈
}

// ================== 主程序 ==================
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string ops;
    if(!(cin >> ops)) return 0;

    // A. 建“打字 Trie”
    buildTypingTrie(ops);

    // B. 建 AC 的 fail + 失败树 + Euler 序
    buildAC();
    dfsFail(root);
    bitFT.init(timer_);

    // C. 读询问并离线挂到 y 节点
    ll m; cin >> m;
    ans.assign((size_t)m + 1, 0);
    for(ll i=1;i<=m;i++){
        ll x,y; cin >> x >> y;
        ll xNode = id2node[x];
        ll yNode = id2node[y];
        queriesAt[yNode].push_back({xNode, i});
    }

    // D. 在“打字 Trie”上 DFS，顺手在线回答
    dfsTyping(root);

    for(ll i=1;i<=m;i++) cout << ans[(size_t)i] << "\n";
    return 0;
}
