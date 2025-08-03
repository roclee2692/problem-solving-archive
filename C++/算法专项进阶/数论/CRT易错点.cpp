#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
ll qpow(ll a,ll b,ll m){
    ll res=1;
    a%=m;
    while(b){
        if(b&1) res=res*a%m;
        a=a*a%m;
        b>>=1; 
    }
    return res;
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    vector<ll> mod(n),r(n);
    for(int i=0;i<n;i++){
        cin>>mod[i]>>r[i];
    }
    ll M=1,sum=0;//M 未初始化
    for(ll i=0;i<n;i++) M*=mod[i];
    for(ll i=0;i<n;i++){
        ll m=mod[i];
        ll mi=M/m;
        ll ti=qpow(mi,m-2,m);//求逆幂指数写错
        ll temp=r[i]*mi%m*ti%m;
        sum=(sum+temp)%M;//累加和取模应对 M 取模
    }//利用了大模与各小模互素时的环同构，形成从小同余到大同余的唯一“拼装”过程。
    cout<<sum<<'\n';
  return 0;
}