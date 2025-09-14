#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
const int N = 2000005;

ll n,m,a[N];
/*任何一个区间 [L, R] 都可以被拆分成树上的少数几个（数量级为 O(logN)）节点所代表的子区间的组合。
这样，我们对区间的操作就可以转化为对这几个节点的操作，从而大大提高了效率。*/
struct Node{ 
    ll mysum,lazy;//这活儿先不干，打个条子记下来，等真需要的时候再说。
} tr[N<<2];
//(u<<1) | 1 先算 u<<1，结果是 u*2。 再跟 1 做按位或 |。
//由于最低位或上 1，就是在原来偶数的基础上 +1。所以 (u<<1)|1 = u*2+1。
inline void push_up(ll u){
    tr[u].mysum=tr[u<<1].mysum+tr[u<<1|1].mysum;
}
inline void apply(ll u,ll l,ll r,ll v){
    tr[u].mysum+=v*(r-l+1);
    tr[u].lazy+=v;//给节点 u 打上懒标记，并更新它的 sum 值。
}
inline void push_down(ll u,ll l,ll r){
    ll &lz=tr[u].lazy;//懒标记下推。把父节点的修改任务传递给直接子节点。
    if(!lz) return;
    ll mid=(l+r)>>1;
    apply(u<<1,l,mid,lz);
    apply(u<<1|1,mid+1,r,lz);
    lz=0;//清空懒标记，因为已经下推到子节点了
}

// —— 建树 O(N) ——
void build(ll u,ll l,ll r){
    tr[u].lazy=0;
    if(l==r){ tr[u].mysum=a[l];return; }
    ll mid=(l+r)>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    push_up(u);
}
// —— 区间加：在 [L, R] 上加 v ——  O(logN)
void update(int u, int l, int r, int L, int R, ll v){
    // 情况1：当前节点区间被修改区间[L, R]完全覆盖
    if(L <= l && r <= R){ apply(u, l, r, v); return; }
    
    push_down(u, l, r); // 先下推懒标记，确保子节点信息正确
    
    int mid = (l + r) >> 1;
    // 情况2：递归修改有交集的子节点
    if(L <= mid) update(u<<1, l, mid, L, R, v);
    if(R >  mid) update(u<<1|1, mid+1, r, L, R, v);
    
    push_up(u); // 修改完子节点后，更新自己的信息
}
// —— 区间和查询：S(L..R) —— O(logN)
ll query(int u, int l, int r, int L, int R){
    if(L <= l && r <= R) return tr[u].mysum;
    push_down(u, l, r);
    ll mid = (l + r) >> 1;
    ll ans = 0;
    if(L <= mid) ans += query(u<<1, l, mid, L, R);
    if(R >  mid) ans += query(u<<1|1, mid+1, r, L, R);
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);
    while(m--){
        int op; cin >> op;
        if(op == 1){
            int x, y; ll k; cin >> x >> y >> k;
            if(x > y) swap(x, y);
            update(1, 1, n, x, y, k);
        }else{ // op == 2
            int x, y; cin >> x >> y;
            if(x > y) swap(x, y);
            cout << query(1, 1, n, x, y) << '\n';
        }
    }
    return 0;
}