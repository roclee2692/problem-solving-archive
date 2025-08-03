#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n;
ll qpow1(ll a,ll b){
    if(b==0) return 1;
    ll half=qpow1(a,b/2);
    ll res=half*half;
    if(b&1) res*=a;
    return res;
}
ll qpow2(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1) res*=a;
        a*=a;//虽然计算了 a = a₃ = a⁸，但此时 b 已移位成 0，循环退出，不会再把𝑎^8乘入 res。
        b>>=1;//这里 a 不能写成 res！！！
    }
    return res;
}
ll modpow1(ll a,ll b,ll mod){
    if(b==0) return 1;
    ll half=modpow1(a,b/2,mod);
    ll res=half*half%mod;
    if(b&1) res=res*(a%mod) %mod;
    return res;
}
ll modpow2(ll a,ll b,ll m){
    if (m == 0) return 0; 
   ll res=1;
   a%=m;
   while(b){
    if(b&1) res=(res*a)%m;
    a=(a*a)%m;
    b>>=1;
   } 
   return res;
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    ll a=10,b=10;
    cout<<qpow1(a,b)<<'\n';
    cout<<qpow2(a,b)<<'\n';
    ll c=10,d=100,m=1e9+7;
    cout<<modpow1(c,d,m)<<'\n';
    cout<<modpow2(c,d,m);
  return 0;
}
