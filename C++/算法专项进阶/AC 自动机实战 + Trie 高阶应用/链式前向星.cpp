#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;

const int MAXN = 200000 + 5;   // 点数上限
const int MAXM = 400000 + 5;   // 边数上限（无向图×2）
int head[MAXN], to_[MAXM], nxt[MAXM];
ll  w_[MAXM];
int ecnt;

inline void init_graph(int n){
    // 仅 head 需要重置为 -1；其余在 addEdge 时写入即可
    fill(head, head + n + 1, -1);
    ecnt = 0;
}

inline void addEdge(int u, int v, ll w=1){
    to_[ecnt] = v;
    w_[ecnt]  = w;
    nxt[ecnt] = head[u];
    head[u]   = ecnt++;
}
// 无向图：addEdge(u,v,w); addEdge(v,u,w);

inline void traverse_from(int u){
    for(int e = head[u]; e != -1; e = nxt[e]){
        int v = to_[e];
        ll  w = w_[e];
        // ... 处理 (u -> v, w)
    }
}
