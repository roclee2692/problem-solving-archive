#include <bits/stdc++.h>
using namespace std;
using ll  = long long;
using pll = pair<ll,ll>;
// ---- 配置 ----
const int N = 2000005; // 够用就行，Luogu常规 N<=1e5，用4*N空间
static ll a[N];
static ll n, m, mod;
struct Node{
    ll sum;
    ll mul;
    ll add;
} tr[N<<2];
inline void pull(int u){
    tr[u].sum=(tr[u<<1].sum+tr[u<<1|1].sum)%mod;
}
inline void apply(ll u,ll l,ll r,ll mulv,ll addv){
    //apply 函数里面确实“什么都有”，它同时处理乘法和加法。
    //那么，为什么一个单纯的“区间加”或者“区间乘”，也要调用这个看起来更复杂的“全功能”函数呢？
    //为了统一处理懒标记的叠加和下推，避免逻辑混乱。
    //把“浓缩倍率 mulv”旋钮拧到 1（1倍浓缩=保持原样）。
    //把“加糖量 addv”旋钮拧到 0（0克糖=不加糖）。
     tr[u].sum = (tr[u].sum * mulv + addv * (r - l + 1)) % mod;
    tr[u].mul = (tr[u].mul * mulv) % mod;
    tr[u].add = (tr[u].add * mulv + addv) % mod;
    /*apply 是一个通用的“操作处理器”。任何区间修改任务，无论是单纯的加法、单纯的乘法，
    还是未来可能更复杂的组合，都可以被包装成“乘以mulv，加上addv”的形式，
    然后交给 apply 这一个函数来处理。*/
    /*简化设计：通过提供“中性值”（乘法是1，加法是0），简单的操作可以无缝使用这个通用接口。
    这样做的好处是，处理懒标记叠加和下推的核心逻辑只需要写一次，就在 apply 和 push 函数里。
    这让代码更健壮，更易于维护。*/
}
// 把父节点的懒标记下推到孩子
inline void push(int u, int l, int r){
    ll mulv = tr[u].mul;
    ll addv = tr[u].add;
    if(mulv == 1 && addv == 0) return; // 无懒标记，省事
    int mid = (l + r) >> 1;
    apply(u<<1,     l,   mid, mulv, addv);
    apply(u<<1|1, mid+1,   r, mulv, addv);
    tr[u].mul = 1; tr[u].add = 0; // 清空本节点懒标记
}
void build(int u, int l, int r){
    tr[u].mul = 1;     // 重要：乘法懒标记初始为 1
    tr[u].add = 0;
    if(l == r){
        tr[u].sum = a[l] % mod;
        return;
    }
    int mid = (l + r) >> 1;
    build(u<<1, l,   mid);
    build(u<<1|1, mid+1, r);
    pull(u);
}
// 区间乘：对 [L,R] 乘以 v
void range_mul(int u, int l, int r, int L, int R, ll v){
    //通过分治 将所有在RL范围内的选出来 l r是广泛的区间 要二分选择合适的
    if(L <= l && r <= R){
        apply(u, l, r, v % mod, 0);
        return;
    }
    push(u, l, r);
    int mid = (l + r) >> 1;
    if(L <= mid) range_mul(u<<1, l, mid, L, R, v);
    if(R >  mid) range_mul(u<<1|1, mid+1, r, L, R, v);
    pull(u);
}
// 区间加：对 [L,R] 加上 v
void range_add(int u, int l, int r, int L, int R, ll v){
    if(L <= l && r <= R){
        apply(u, l, r, 1, v % mod);
        // 区间[L,R]乘v：若当前节点区间被完全覆盖则应用懒标记，否则先下推、再递归，最后回溯更新。
        return;
    }
    push(u, l, r);
    int mid = (l + r) >> 1;
    if(L <= mid) range_add(u<<1, l, mid, L, R, v);
    if(R >  mid) range_add(u<<1|1, mid+1, r, L, R, v);
    pull(u);
}
// 区间和查询
ll range_sum(int u, int l, int r, int L, int R){
    if(L <= l && r <= R) return tr[u].sum;
    push(u, l, r);
    int mid = (l + r) >> 1;
    ll ans = 0;
    if(L <= mid) ans = (ans + range_sum(u<<1, l, mid, L, R)) % mod;
    if(R >  mid) ans = (ans + range_sum(u<<1|1, mid+1, r, L, R)) % mod;
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> mod;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);

    while(m--){
        int op; cin >> op;
        if(op == 1){
            int x, y; ll k; cin >> x >> y >> k;
            if(x > y) swap(x, y);
            range_mul(1, 1, n, x, y, k % mod);
        }else if(op == 2){
            int x, y; ll k; cin >> x >> y >> k;
            if(x > y) swap(x, y);
            range_add(1, 1, n, x, y, k % mod);
        }else{ // op == 3
            int x, y; cin >> x >> y;
            if(x > y) swap(x, y);
            cout << range_sum(1, 1, n, x, y) % mod << '\n';
        }
    }
    return 0;
}