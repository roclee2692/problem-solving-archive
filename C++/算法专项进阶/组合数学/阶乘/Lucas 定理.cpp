#include<bits/stdc++.h>
using namespace std;
using ll=long long;
// 快速幂算法：计算 (base^exp) % mod
ll fastpow(ll base,ll exp,ll mod){
    ll res=1;
    base %= mod; // 预先取模，防止 base 过大
    while(exp>0){
        // 1. 如果 exp 是奇数 (二进制最低位是1)，说明需要乘上当前的 base
        if(exp&1) res=(res*base)%mod;
         // 2. base 自我平方，为下一位做准备 (a -> a^2 -> a^4 -> ...)
        base=(base*base)%mod;
        // 3. exp 右移一位，处理下一个二进制位
        exp/=2;
    }
    return res;
}
ll power(ll base,ll exp,ll mod){
    base %= mod; // 预先取模，防止 base 过大
    if(exp==0) return 1;//边界先行 任何数的0次方都是1
    ll res=power(base,exp/2,mod)%mod;//无论奇偶先求个half
    res=(res*res)%mod;
    if(exp%2==1) res=(res*base)%mod;//奇数另外加上base
    return res;
}
vector<ll> fact;// 阶乘数组
void precompute_factorials(ll p){
    fact.assign(p+1,0);
    fact[0]=1;
    for(ll i=1;i<=p;i++){
        fact[i]=(fact[i-1]*i)%p;
    }
}
// 组合数函数 C(n, k) % p，要求 n, k < p
ll combination(ll n,ll k,ll p){
    if(k>n||k<0) return 0;
    if(k==0||k==n) return 1;
    if(fact[k]==0||fact[n-k]==0) return 0;
    // C(n,k) = n! / (k! * (n-k)!)
    // C(n,k) ≡ n! * (k!)^(p-2) * ((n-k)!)^(p-2) (mod p) 
    //==n! *( (k!)*((n-k)!) )^(p-2)
    ll nfact=fact[n];
    ll de=(fact[k]*fact[n-k])%p;
    return (nfact*power(de,p-2,p))%p;
}
// 卢卡斯定理
ll lucas(ll n,ll k,ll p){
    if(k>n||k<0) return 0;
    if(k==0) return 1;
    return (lucas(n/p,k/p,p)*combination(n%p,k%p,p))%p;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    ll T;
    cin>>T;
    while (T--) {
        ll n, m, p;
        cin >> n >> m >> p;
        
        // 每次 p 可能不同，所以每次都预处理
        precompute_factorials(p);
        
        cout << lucas(n + m, n, p) << "\n";
    }

    return 0;
}