#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int MAXN = 500000 + 5; // 题目数据范围：n,m≤5×10^5
int n, m;                    // n个数，m次操作
ll bit[MAXN];                // 树状数组
ll a[MAXN];                  // 原数组（可选）

inline int lowbit(int x){ return x& -x; }
// 单点加：a[pos] += delta
inline void add(int pos,ll delta){
    for(int i=pos;i<=n;i+=lowbit(i)) { bit[i]+=delta; }
}
// 前缀和：sum(1..pos)
inline ll sum(int pos){
    ll res=0;
    for(int i=pos;i>0;i-=lowbit(i)) res+=bit[i];
    return res;
}
// 区间和：sum(l..r)
inline ll range_sum(int l,int r){
    return sum(r)-sum(l-1);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        add(i,a[i]);
    }
    while(m--){
        int op; cin>>op;
        if(op==1){
            int x; ll k;
            cin>>x>>k;
            add(x,k);
        }else if(op==2){
            int x,y;
            cin>>x>>y;
            cout<<range_sum(x,y)<<'\n';
        }
    }
    return 0;
}