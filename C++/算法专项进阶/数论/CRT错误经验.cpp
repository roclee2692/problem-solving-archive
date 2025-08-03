#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using i128 = __int128_t;
ll n;
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll x1,y1;
    ll gcd=exgcd(b,a%b,x1,y1);
    x=y1;
    y=x1-(a/b)*y1;
    return gcd;
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
        if (m == 1) continue;// x ≡ r (mod 1) 没信息，直接跳过
        ll mi=M/m;
        ll ti,y;//求逆幂指数写错
        exgcd(mi,m,ti,y);
        ti=(ti%m+m)%m;//exgcd求出的ti有可能是负的
         ti = (ti % m + m) % m;
        i128 t = (i128)r[i] * mi % M;
        t = t * ti % M;
        ll temp = (ll)t;
        sum=(sum+temp)%(ll)M;//累加和取模应对 M 取模
    }//利用了大模与各小模互素时的环同构，形成从小同余到大同余的唯一“拼装”过程。
    if(sum<=0)sum=M;  // 必须输出正整数
    cout<<sum<<'\n';
  return 0;
}