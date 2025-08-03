#include <iostream>
using namespace std;
const int mod=1000000007;//要同余的质数
const int maxn=1000;//n的maximun

long long fa[maxn+1],ifa[maxn+1];//预处理阶乘和逆元 
// fa[i]储存i！mod，避免重复计算。
//ifa[i]预处理逆元：
//invFact[i] = (fact[i])?? % MOD，用于高效计算组合数。
long long power(long long x,long long y,long long p){
    long long res=1;//快速幂运算（x^y)%p
    while(y>0){
        if(y&1) res=res*x%p;//是奇数，多乘一个x，后面y指数>>后会向下取整
        x=x*x%p;//底数平方扩大，缩减运算
        y>>=1;//指数右移一位
    }
    return res;
}
// 预计算阶乘及其逆元
void pre(){
    fa[0]=1;//计算1000的阶乘的余数
    for(int i=1;i<=maxn;i++){
        fa[i]=fa[i-1]*i%mod;//每次计算取余防止数据溢出
    }
    // 计算 invFact[MAX_N]，即 fact[MAX_N] 在模 MOD 下的逆元
    ifa[maxn]=power(fa[maxn],mod-2,mod);//求逆元&费马小定理
    for(int i=maxn-1;i>=0;i--){//刚好1000个数
        ifa[i]=ifa[i+1]*(i+1)%mod;//其实计算到500即可，这里逆元算到了1000，但是为索引
    }
}

long long comb(int n,int m){//计算组合数
    if(m>n) return 0;//n为底，m为取出的数，n>=m
    return fa[n]*ifa[m]%mod*ifa[n-m]%mod;//！1000*500的逆元*itself 余数
}//计算顺序((fa[n] * ifa[m]) % mod * ifa[n-m]) % mod  默认从左往右依次运算
// 先计算 fa[n] * ifa[m]，可能会超出 mod，所以立刻 % mod 限制范围

int main(){
    pre();
        cout<<comb(1000,500)<<endl;
        return 0;
    
}