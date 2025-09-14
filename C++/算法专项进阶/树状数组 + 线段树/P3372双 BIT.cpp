#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
// —— 全局参数与数组（按需放大上限） ——
const ll MAXN = 2000005;
// B1 维护差分数组 d[i]
// B2 维护 d[i] * (i-1)
ll n, m, a[MAXN], B1[MAXN], B2[MAXN];
// —— BIT 基础 —— 
inline ll lowbit(ll x){ return x & -x; }
inline void add(ll *B, ll pos, ll delta){
    for(ll i = pos; i <= n; i += lowbit(i)) B[i] += delta;
}
inline ll sum(ll *B, ll pos){
    ll res = 0;
    for(ll i = pos; i > 0; i -= lowbit(i)) res += B[i];
    return res;
}
// —— 双 BIT：区间加 + 区间和 ——
// 在 [l, r] 上 +k
inline void range_add(ll l, ll r, ll k){
    if(l > r) swap(l, r);
    // 维护 B1，即维护 d[i]
    add(B1, l, k); 
    if(r + 1 <= n) add(B1, r + 1, -k);
    
    // 维护 B2，即维护 d[i] * (i-1)
    add(B2, l, k * (l - 1)); 
    if(r + 1 <= n) add(B2, r + 1, -k * r);
}
// 前缀和 S(1..x)
inline ll prefix_sum(ll x){ return x * sum(B1, x) - sum(B2, x); }
//这行代码就是我们上面推导出的魔法公式的直接实现。
//它可以在 O(logN) 时间内计算出原数组 A 的前 x 项和。
// 区间和 S(l..r)
inline ll range_sum(ll l, ll r){
    if(l > r) swap(l, r);
    return prefix_sum(r) - prefix_sum(l - 1);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(ll i = 1; i <= n; ++i){
        cin >> a[i];
        // 把初始数组并入结构：对每个 i 做一次区间加 [i,i] +a[i]
        range_add(i, i, a[i]);
        //把初始数组 a 的每个元素 a[i] 看作是一次对 [i, i] 区间增加 a[i] 的操作，
        //直接调用 range_add 函数，优雅地完成了初始化。
    }

    while(m--){
        ll op; cin >> op;
        if(op == 1){
            ll x, y, k; cin >> x >> y >> k;
            range_add(x, y, k);
        }else{ // op == 2
            ll x, y; cin >> x >> y;
            cout << range_sum(x, y) << '\n';
        }
    }
    return 0;
}