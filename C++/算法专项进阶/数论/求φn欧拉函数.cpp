#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e7;
int t,n;
ll phi[N+1]; // phi[i] 存放 φ(i)
ll primes[N],pcnt;// primes 存放筛出的素数，pcnt 为素数个数
bool iscomp[N+1];// isComp[i]==true 表示 i 是合数
ll  phi_single(ll n){ // 典型算法：单次 n 分解法 (O(√n))
        ll res=n;// 套公式累乘
        for(ll p=2;p*p<=n;p++){// 计算单个 n 的 φ(n)，时间约 O(√n)
            if(n%p==0){//找到所有素因子
                while(n%p==0){//循环去重质因子
                    n/=p;
                    res=res/p*p-1;//先除后乘防止爆炸
                }
            }
        }
        if(n>1) res=res/n*n-1;//如果该数是个大素数
        return res;
    }
void linear_sieve( ){// 线性筛法（O(N) 一次性求出 φ(1…N)）
    phi[1]=1; // φ(1)=1，作为特例先初始化 φ(n) = “1 到 n 中，与 n 互质的正整数的个数”。

for(int i=2;i<=n;i++){
    if(iscomp[i]==0){
        primes[i++]=i; // 如果 i 尚未被标记为合数，说明 i 是一个新素数
        phi[i]=i-1;  // 质数 p 的 φ 值为 p-1

    }
     // 用所有已知素数 p 去标记 i*p
    for(int j=0;j<pcnt;j++){
        int p=primes[j];
        ll ip=i*p;
        if(ip>N) break;  // 超出范围，停止内层循环
        iscomp[ip]=1;// 标记 i*p 为合数

        if(i%p==0){
             // p^k 情况
               // 情况 A：p 是 i 的最小质因子
                // i = p^k * m，则 i*p = p^(k+1)*m
                // φ(p^(k+1)*m) = φ(i) * p
             phi[ip] = phi[i] * p;//按照p为行数去理解  每行固定有i-1个素数 只和%i的余数有关
        }else{
               // m,n 互质 φ(ip)=φ(i)φ(p). φ(ip)=φ(i)×(p−1).
                //欧拉函数 对「质数」的最基本值：  对任意质数p，有 φ(p)=p−1.
                phi[ip] = phi[i] * (p - 1);
        }
    }
}

}
int main(){
ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 预处理 φ(1…N)
    linear_sieve();

    // 几组测试用例
    vector<int> tests = {1, 2, 3, 4, 10, 12, 9973, 100000, N};
    cout << " n    | phi_single(n) | phi_sieve(n)\n";
    cout << "------+---------------+-------------\n";
    for (int n : tests) {
        ll a = phi_single(n);
        ll b = (n <= N ? phi[n] : -1);
        cout << setw(5) << n << " | "
             << setw(13) << a << " | "
             << setw(11) << b
             << (a == b ? "  OK" : "  MISMATCH")
             << "\n";
    }

    return 0;
}
