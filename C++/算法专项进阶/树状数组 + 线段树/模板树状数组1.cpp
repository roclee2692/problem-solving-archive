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