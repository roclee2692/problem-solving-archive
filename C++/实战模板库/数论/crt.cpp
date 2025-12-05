/*
 * 【中国剩余定理 CRT】- 求解同余方程组
 * 
 * 时间复杂度：O(k log m)，k = 方程个数，m = 模数最大值
 * 空间复杂度：O(k)
 * 
 * 适用场景：
 *   - 求解 x ≡ a_i (mod m_i) 的同余方程组
 *   - 前提：所有 m_i 两两互质
 *   - 扩展 CRT：m_i 不互质时
 * 
 * 【什么是中国剩余定理？】
 * 古代问题："今有物不知其数，三三数之剩二，五五数之剩三，七七数之剩二，问物几何？"
 * 翻译：求 x 满足 x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7)
 * 答案：x = 23
 * 
 * 【核心思想】
 * 构造法：分别构造只满足一个方程、对其他方程贡献为 0 的特解，然后加起来。
 * 
 * 模板题：
 *   - 洛谷 P1495 - 【模板】中国剩余定理(CRT)/曾经沧海
 *   - Codeforces 1106F - Lunar New Year and a Recursive Sequence
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    ll x1,y1;
    ll d=exgcd(a,b,x1,y1);
    x=y1;
    y=x1-a/b*y1;
    return d;
}
pair<ll,ll>  crt(vector<ll> &a,vector<ll> &m){
    ll l=a.size();
    ll M=1,ans=0;
    for(int i=0;i<l;i++){
        M*=m[i];
    }
    for(int i=0;i<l;i++){
        ll mi=M/m[i];
        ll x,y;
        ll d=exgcd(mi,m[i],x,y);
        x=((x%m[i])+m[i])%m[i];
        ans=(ans+a[i]*mi%M*x%M)%M;
    }
    return {ans,M};
}
pair<ll,ll> extgcd_merge(ll a1,ll m1,ll a2,ll m2){
    ll x,y;
    ll d=exgcd(m1,m2,x,y);
    if((a2-a1)%d!=0) return {-1,-1};
    ll lcm=m1/d*m2;
    ll a=(a1+m1*x%lcm*((a2-a1)/d)%lcm)%lcm;
    a=(a+lcm)%lcm;
    return {a,lcm};
}
pair<ll,ll> excrt(vector<ll> &a, vector<ll> &m){
    ll cur_a = a[0], cur_m = m[0];
    for (int i = 1; i < (int)a.size(); i++) {
        auto [new_a, new_m] = extgcd_merge(cur_a, cur_m, a[i], m[i]);
        if (new_m == -1) return {-1, -1};  // 无解
        cur_a = new_a;
        cur_m = new_m;
    }
     return {cur_a, cur_m};
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    vector<ll> a(n),m(n);
    for(int i=0;i<n;i++){
        cin>>m[i]>>a[i];
    }
    auto [ans,M]=crt(a,m);
    cout<<ans<<"\n";
    return 0;
}
/*
 * ========== 中国剩余定理核心原理 ==========
 * 
 * 【问题】
 * 求 x 满足：
 * x ≡ a[0] (mod m[0])
 * x ≡ a[1] (mod m[1])
 * ...
 * x ≡ a[n-1] (mod m[n-1])
 * 
 * 【互质 CRT 公式】
 * M = m[0] * m[1] * ... * m[n-1]
 * x = Σ(a[i] * M_i * inv(M_i, m[i])) mod M
 * 
 * 其中 M_i = M / m[i]，inv(M_i, m[i]) 是 M_i 在 mod m[i] 下的逆元
 * 
 * 【手算例子】
 * x ≡ 2 (mod 3), x ≡ 3 (mod 5), x ≡ 2 (mod 7)
 * 
 * M = 3 * 5 * 7 = 105
 * M_0 = 35, inv(35, 3) = inv(2, 3) = 2  → 贡献 2 * 35 * 2 = 140
 * M_1 = 21, inv(21, 5) = inv(1, 5) = 1  → 贡献 3 * 21 * 1 = 63
 * M_2 = 15, inv(15, 7) = inv(1, 7) = 1  → 贡献 2 * 15 * 1 = 30
 * 
 * x = (140 + 63 + 30) % 105 = 233 % 105 = 23 ✓
 * 
 * 【非互质扩展 CRT】
 * 当模数不互质时，用 exgcd 逐两个合并
 * 合并 (a1, m1) 和 (a2, m2) 得到 (a_new, lcm(m1, m2))
 * 
 * 【关键点】
 * 1. 互质 CRT：M = ∏m_i, 答案 = Σ(a_i * M_i * (M_i^-1 mod m_i))
 * 2. M_i = M / m_i，需要计算其在 m_i 下的逆元
 * 3. 非互质 CRT：用扩展欧几里得逐两个合并
 * 4. 无解条件：(a2 - a1) % gcd(m1, m2) ≠ 0
 * 5. 合并后 lcm = m1 * m2 / gcd(m1, m2)
 * 
 * 【常见应用】
 * - 大数分解后分别求解再合并
 * - 求解模方程组（密码学）
 * - 区间内解计数
 * 
 * 【竞赛考察频率】
 * - NOI/省选：⭐⭐⭐⭐
 * - ICPC/CCPC：⭐⭐⭐
 * - Codeforces：⭐⭐（Div2 D/E）
 * 
 * 【提交前检查】
 * ✓ 互质性检查（或使用扩展版本）
 * ✓ 模逆元计算正确性
 * ✓ 取模防止溢出（先除后乘）
 * ✓ 无解条件判断
 * ✓ 负数取模处理
 */
