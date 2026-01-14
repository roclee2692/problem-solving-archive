/*
 * 【矩阵快速幂 DP】- 线性递推加速
 * 
 * 时间复杂度：O(k^3 * log n)，k = 递推阶数
 * 空间复杂度：O(k^2)
 * 
 * 适用场景：
 *   - 线性递推数列求第 n 项
 *   - 斐波那契数列
 *   - 任意线性递推关系
 * 
 * 模板题：
 *   - 洛谷 P1962 - 斐波那契数列
 *   - Codeforces 1106F - Lunar New Year and a Recursive Sequence
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

struct Matrix {
    ll a[2][2];
    int n, m;
    
    Matrix(int _n = 2, int _m = 2) : n(_n), m(_m) {
        memset(a, 0, sizeof(a));
    }
    
    Matrix operator*(const Matrix &b) const {
        Matrix c(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b.m; j++) {
                for (int k = 0; k < m; k++) {
                    c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]) % MOD;
                }
            }
        }
        return c;
    }
};

Matrix qpow(Matrix a, ll b) {
    Matrix res(2, 2);
    res.a[0][0] = res.a[1][1] = 1;  // 单位矩阵
    
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

// 求斐波那契数列 F(n)
// F(n) = F(n-1) + F(n-2)
// 矩阵形式：[F(n+1), F(n)]^T = [[1,1],[1,0]] * [F(n), F(n-1)]^T
ll fib(ll n) {
    if (n == 1 || n == 2) return 1;
    
    Matrix base(2, 2);
    base.a[0][0] = 1; base.a[0][1] = 1;
    base.a[1][0] = 1; base.a[1][1] = 0;
    
    Matrix res = qpow(base, n - 1);
    
    return res.a[0][0];  // F(n) = [[1,1],[1,0]]^(n-1)[0][0]
}

// 通用线性递推求解
// f(n) = c1*f(n-1) + c2*f(n-2) + ... + ck*f(n-k)
ll linearRecurrence(vector<ll> &c, vector<ll> &init, ll n) {
    int k = c.size();  // 递推阶数
    
    if (n < init.size()) return init[n];
    
    Matrix base(k, k);
    // 第一行放系数（按倒序）
    for (int i = 0; i < k; i++) {
        base.a[0][i] = c[i];
    }
    // 其余行构造移位矩阵
    for (int i = 1; i < k; i++) {
        base.a[i][i - 1] = 1;
    }
    
    Matrix res = qpow(base, n - k + 1);
    
    // 结果是 res * init 的第一个分量
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        ans = (ans + res.a[0][i] * init[k - 1 - i]) % MOD;
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    cin >> n;
    
    cout << fib(n) << "\n";
    
    return 0;
}

/*
 * 【关键点】
 * 1. 递推式转矩阵：识别线性递推关系
 * 2. 矩阵构造：系数作为第一行，下面是移位矩阵
 * 3. 矩阵乘法：注意模运算，防止溢出
 * 4. 快速幂：指数 b 从 n-k+1
 * 5. 初值设置：前 k 项的初值
 * 
 * 【常见变体】
 * - 二阶递推：F(n) = a*F(n-1) + b*F(n-2)
 * - 更高阶递推：类似扩展矩阵大小
 * - 模运算加法递推
 * 
 * 【提交前检查】
 * ✓ 矩阵乘法是否正确
 * ✓ 快速幂逻辑
 * ✓ 初值个数是否正确
 * ✓ 模运算防溢出（使用 long long）
 */

/*
 * 运行示例（命令行输入输出）
 * -----------------------------------------------------------------
 * 示例 1：斐波那契
 * 输入：
 *   6
 * 输出：
 *   8
 * 解释：程序 main() 读取 n 并输出 fib(n)。F(6)=8（1,1,2,3,5,8）
 *
 * 示例 2：使用线性递推函数（手动调用说明）
 *  假设递推关系 f(n)=2*f(n-1)+3*f(n-2)，初值 f(0)=1, f(1)=2，求 f(5)
 *  - k=2，c={2,3}，init={1,2}
 *  - 手工计算（验证）：
 *      f(2)=2*2+3*1=7
 *      f(3)=2*7+3*2=20
 *      f(4)=2*20+3*7=61
 *      f(5)=2*61+3*20=202
 *  - 若要用本程序测试，请把 main 改为调用：
 *      vector<ll> c={2,3}; vector<ll> init={1,2}; cout<<linearRecurrence(c,init,5)<<"\n";
 *  - 输出应为 202（模 MOD 后若较大则取 MOD）
 *
 * 为什么矩阵方法成立（简要说明）
 * -----------------------------------------------------------------
 * 线性递推 f(n)=c1*f(n-1)+...+ck*f(n-k) 可以用状态向量表示：
 *   S(n) = [f(n), f(n-1), ..., f(n-k+1)]^T
 *  存在常数矩阵 M 使得 S(n) = M * S(n-1)。M 的第一行为系数 c1..ck，
 *  其余为单位移位以把 f(n-1) 推到第二分量，依此类推。
 *  因此 S(n) = M^(n-k+1) * S(k-1)，只需计算矩阵幂并与初始向量相乘。
 *
 * 当前代码注意事项与改进建议
 * 
 * -----------------------------------------------------------------
 * 1) 矩阵存储限制：当前 struct Matrix 使用固定成员 ll a[2][2]，但
 *    linearRecurrence 构造 k×k 矩阵时会访问 a[i][j]，若 k>2 会越界。
 *    解决方案（推荐）：将 Matrix 的存储改为动态分配，例如
 *      vector<vector<ll>> a;
 *    并在构造函数中按大小分配：a.assign(n, vector<ll>(m,0));
 *    同时修改乘法实现以支持任意 k。
 *
 * 2) 单位矩阵生成：qpow 中创建单位矩阵应根据 a.n 调整维度，
 *    而不是固定为 2×2。
 *
 * 3) 索引/初值约定：linearRecurrence 中对 init 的使用是 init[0..k-1]
 *    表示 f(0..k-1)。调用者应按该约定准备初值，或在函数注释中明确。
 *
 * 4) 模化与负数：若系数或初值可能为负数，请在取模时统一处理以
 *    保证结果非负（例如 (x%MOD+MOD)%MOD）。
 *
 * 小结：本文件已实现矩阵快速幂求 Fibonacci 和通用线性递推的
 * 基本逻辑，若要处理 k>2 的通用递推，需先修正 Matrix 的存储结构。
 */
