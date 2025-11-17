#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
ll bit[N];
ll a[N];
ll n,m;
inline ll lowbit(ll x){ return x&-x; }
//树状数组擅长：快速单点修改 和 快速查询前缀和。
//用一个树状数组来维护这个差分数组 D。
inline void add(ll pos,ll delta){
    for(ll i=pos;i<=n;i+=lowbit(i)){ bit[i]+=delta; }
}
inline ll mysum(ll x){
    ll res=0;
    for(ll i=x;i>0;i-=lowbit(i)){ res+=bit[i]; }
    return res;
}
// 区间加 [l, r] += v  —— 差分两次 add
/*对原始数组 A 的区间 [l, r] 进行加 v 操作，等价于只对差分数组 D 进行两个单点修改：
D[l] 加上 v
D[r+1] 减去 v*/
inline void range_add(ll l,ll r,ll v){
    add(l, v);
     // add(idx, val) 是树状数组的单点修改函数，
    // 它会给树状数组中 idx 位置及其所有父节点加上 val。
    // 这里树状数组维护的是差分数组 D。
    // 对应操作：D[l] += v
    // 对应操作：D[r+1] -= v
    // 需要判断 r+1 是否越界
    if(r + 1 <= n) add(r + 1, -v);
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin>>n>>m;
    a[0] = 0; // 初始化a[0]，用于计算差分
    for(int i=1;i<=n;i++){
        cin>>a[i];
        // 建差分：d[i]=a[i]-a[i-1]，落到 BIT 上
        add(i, a[i] - a[i-1]); // 直接用add即可，不需要range_add
    }
    while(m--){
        ll op; cin>>op;
        if(op==1){
            ll x,y,k;
            cin>>x>>y>>k;
              range_add(x,y,k);
        }else if(op==2){
            ll x; cin>>x;
            cout << mysum(x) << "\n";
        }
    }
    return 0;
}