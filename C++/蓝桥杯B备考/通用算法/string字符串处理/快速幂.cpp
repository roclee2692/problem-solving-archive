#include <iostream>
using namespace std;

// 迭代版快速幂（位运算优化）
long long fastpow(long long a, long long b, long long mod) {
    long long res = 1;  // 结果初始为 1
    a %= mod;  // 先取模，防止 a 过大

    while (b > 0) {
        if (b & 1) res = (res * a) % mod;  // 如果当前位是 1，累乘当前的 a
        a = (a * a) % mod;  // a 翻倍（平方）
        b >>= 1;  // 右移 b，相当于除以 2
    }

    return res;
}

// 测试代码
int main() {
    long long a = 2, b = 10, mod = 1000000007;
    cout << "优化后的快速幂：" << a << "^" << b << " % " << mod << " = " << fastpow(a, b, mod) << endl;
    return 0;
}
