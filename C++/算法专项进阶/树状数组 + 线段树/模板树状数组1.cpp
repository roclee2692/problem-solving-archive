#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
ll n,m;
ll bit[N];
ll a[N];

inline ll lowbit(ll x){ return x&-x; }
inline void add(ll pos,ll delta){
    for(int i=pos;i<=n;i+=lowbit(i)) bit[i]+=delta;
}
inline ll mysum(ll pos){
    ll res=0;
    for(int i=pos;i>0;i-=lowbit(i)) res+=bit[i];
    return res;
}
inline ll range_sum(ll l,ll r){ 
    return mysum(r)-mysum(l-1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        add(i,a[i]);
    }
    while(m--){
        
        ll op; cin>>op;
        if(op==1){
            ll x,k; cin>>x>>k;
            add(x,k);
        }else if(op==2){
            ll x,y;
            cin>>x>>y;
            if(x>y) swap(x,y);
            cout<<range_sum(x,y)<<'\n';
        }

    }
    return 0;
}
/*3) 区间加 + 区间和查询（2 个 BIT：B1、B2）
ll B1[MAXN], B2[MAXN];

inline void add(ll *B, int pos, ll delta){
    for(int i = pos; i <= n; i += lowbit(i)) B[i] += delta;
}

inline ll sum(ll *B, int pos){
    ll res = 0;
    for(int i = pos; i > 0; i -= lowbit(i)) res += B[i];
    return res;
}

// 在 [l, r] 上 +k
inline void range_add(int l, int r, ll k){
    add(B1, l, k); if(r + 1 <= n) add(B1, r + 1, -k);
    add(B2, l, k * (l - 1)); if(r + 1 <= n) add(B2, r + 1, -k * r);
}

inline ll prefix_sum(int x){ // 含初始数组时需先用 add1 建好
    return x * sum(B1, x) - sum(B2, x);
}

inline ll range_sum(int l, int r){
    return prefix_sum(r) - prefix_sum(l - 1);
}


要点：公式 S(x) = x*ΣB1 - ΣB2；同时能做“区间加 + 区间求和”。

4) k-th 前缀（找最小 pos 使前缀和 ≥ k）
int kth_by_prefix(ll k){
    int pos = 0;
    int maxp = 1; while((maxp<<1) <= n) maxp <<= 1; // 最高位 2^p
    for(int p = maxp; p; p >>= 1){
        int nxt = pos + p;
        if(nxt <= n && bit_[nxt] < k){
            k -= bit_[nxt];
            pos = nxt;
        }
    }
    return pos + 1; // 若越界需自行处理
}


要点：典型“求前缀第 k 个 1/频数”的套路。*/