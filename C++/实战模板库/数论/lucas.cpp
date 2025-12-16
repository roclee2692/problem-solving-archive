/*
 * 【Lucas 定理】- 大模数下的组合数计算
 * 
 * 时间复杂度：O(p log_p n) 预处理，O(log_p n) 单次查询
 * 空间复杂度：O(p)
 * 
 * 适用场景：
 *   - 模数 p 为质数且较小（p ≤ 1e5）
 *   - n, m 很大（≤ 1e18）
 *   - 计算 C(n, m) % p
 * 
 * 模板题：
 *   - 洛谷 P3807 - 【模板】卢卡斯定理
 *   - Codeforces 1132G - Greedy Subsequences
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int XN=1e5+5;
ll fac[XN];
ll inv[XN];
ll p;

ll qpow(ll a,ll b,ll mod){
    ll res=1;
    a%=mod;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
void init(ll mod){
    p=mod;
    fac[0]=1;
    for(int i=1;i<p;i++){
        fac[i]=fac[i-1]*i%p;
    }
    inv[p-1]=qpow(fac[p-1],p-2,p);
    for(int i=p-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%p;
    }

}
ll C(ll n,ll m){
    if(m>n||m<0) return 0;
    if(m==0||m==n) return 1;
    return fac[n]*inv[m]%p*inv[n-m]%p;
}
ll lucas(ll n,ll m){
    if(m==0) return 1;
    if(n<p && m<p) return C(n,m);
    return lucas(n/p,m/p)*C(n%p,m%p)%p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        ll n, m;
        cin >> n >> m >> p;
        
        // ===== 每次查询需要重新初始化（因为 p 可能不同）=====
        init(p);
        
        cout << lucas(n, m) << "\n";
    }
    
    return 0;
}
/*
 * ========== Lucas 定理核心原理 ==========
 * 
 * 【什么是 Lucas 定理？】
 * - 用于计算大数组合数 C(n, m) % p（p 为质数）
 * - 递归公式：C(n, m) % p = C(n/p, m/p) * C(n%p, m%p) % p
 * - 适用条件：p 是质数且较小（≤ 1e5），n, m 可以很大（≤ 1e18）
 * 
 * 【为什么需要 Lucas 定理？】
 * 普通组合数计算方法：
 * 1. 公式法：C(n, m) = n! / (m! * (n-m)!)
 *    - 问题：n 很大时，n! 会溢出
 * 2. 杨辉三角递推：C(n, m) = C(n-1, m-1) + C(n-1, m)
 *    - 问题：需要 O(n*m) 空间和时间，n 大时不可行
 * 3. 逆元法：C(n, m) = n! * (m!)^(-1) * ((n-m)!)^(-1) % p
 *    - 问题：需要预处理 O(n) 个阶乘，n 大时不可行
 * 
 * Lucas 定理优势：
 * - 只需预处理 O(p) 个阶乘（p 很小）
 * - 查询复杂度 O(log_p n)（递归深度）
 * - 支持 n, m ≤ 1e18
 * 
 * 【Lucas 定理证明（简化版）】
 * 核心：利用 p 进制分解和费马小定理
 *  
 * 1. 组合数的二项式定理：
 *    (1 + x)^n = Σ C(n, k) * x^k`  
 * 
 * 2. 在模 p 意义下：
 *    (1 + x)^n ≡ (1 + x^p)^(n/p) * (1 + x)^(n%p) (mod p)
 * 
 * 3. 比较系数得：
 *    C(n, m) ≡ C(n/p, m/p) * C(n%p, m%p) (mod p)
 * 
 * 【递归过程示例】
 * 计算 C(13, 7) % 5：
 * 
 * lucas(13, 7)
 * = lucas(13/5, 7/5) * C(13%5, 7%5) % 5
 * = lucas(2, 1) * C(3, 2) % 5
 * = [lucas(2/5, 1/5) * C(2%5, 1%5) % 5] * C(3, 2) % 5
 * = [lucas(0, 0) * C(2, 1) % 5] * C(3, 2) % 5
 * = [1 * 2 % 5] * 3 % 5
 * = 2 * 3 % 5
 * = 1
 * 
 * 【复杂度分析】
 * - 预处理：O(p)（计算 p 个阶乘和逆元）
 * - 单次查询：O(log_p n)（递归深度 = n 的 p 进制位数）
 * - 每层递归：O(1)（直接查表计算小组合数）
 * 
 * 【为什么要预处理逆元？】
 * 计算 C(n, m) = n! / (m! * (n-m)!) % p 需要除法
 * 在模运算中，除法 = 乘以逆元：
 * a / b % p = a * b^(-1) % p = a * b^(p-2) % p（费马小定理）
 * 
 * 预处理所有 i! 的逆元，避免每次都快速幂
 * 
 * 【Lucas 定理 vs 其他组合数算法】
 * 
 * | 算法 | 适用条件 | 预处理 | 查询 |
 * |------|---------|--------|------|
 * | 直接计算 | n ≤ 1e6 | O(n) | O(1) |
 * | 杨辉三角 | n, m ≤ 5000 | O(n*m) | O(1) |
 * | Lucas | p ≤ 1e5, n 任意 | O(p) | O(log n) |
 * | exLucas | p 非质数 | O(√p) | O(log n) |
 * 
 * 【常见变体】
 * 1. exLucas（扩展 Lucas）：p 不是质数时使用
 * 2. Lucas + 中国剩余定理：p 较大但可分解
 * 3. 多组询问优化：预处理后批量查询
 * 
 * 【常见错误】
 * 1. 忘记判断 m > n（返回 0）
 * 2. 预处理时 p 不够大（数组越界）
 * 3. 逆元计算错误（费马小定理要求 p 是质数）
 * 4. 递归边界错误（m = 0 返回 1）
 * 5. 每次查询忘记 init（多组测试 p 不同）
 * 
 * 【调试技巧】
 * 1. 小数据验证：C(5, 2) % 3 = 10 % 3 = 1
 * 2. 检查预处理：打印 fac[0..p-1] 和 inv[0..p-1]
 * 3. 递归过程：打印每层的 n, m, C(n%p, m%p)
 * 
 * 【提交前检查】
 * ✓ p 是质数（题目保证）
 * ✓ 数组大小 ≥ p
 * ✓ 判断 m > n 返回 0
 * ✓ 多组测试时每次 init
 * ✓ 逆元用费马小定理（p-2 次幂）
 * 
 * 【竞赛考察频率】
 * - NOI/省选：⭐⭐⭐⭐（组合数学必考）
 * - ICPC/CCPC：⭐⭐⭐（区域赛偶尔）
 * - Codeforces：⭐⭐（Div1 E/F）
 * 
 * 【推荐练习】
 * 1. 洛谷 P3807 - Lucas 定理模板
 * 2. 洛谷 P4720 - 扩展 Lucas 定理
 * 3. HDU 3037 - Saving Beans
 */
