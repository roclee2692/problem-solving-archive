#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;   // 需要修正
const int MAXA = 100000;               // 题目上限

long long mod_pow(long long x, long long e = MOD - 2) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return r;
}

long long fact[MAXA + 1], inv_fact[MAXA + 1];

long long C_mod(long long n, int k) {
    long long num = 1;
    for (int i = 0; i < k; ++i)
        num = num * ((n - i) % MOD) % MOD;
    return num * inv_fact[k] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 预处理阶乘及逆元
    fact[0] = 1;
    for (int i = 1; i <= MAXA; ++i) fact[i] = fact[i - 1] * i % MOD;
    inv_fact[MAXA] = mod_pow(fact[MAXA]);
    for (int i = MAXA; i > 0; --i)
        inv_fact[i - 1] = inv_fact[i] * i % MOD;

    int T;
    cin >> T;
    while (T--) {
        long long a, b, k;
        cin >> a >> b >> k;

        // 1. 行数 n = (a-1)*k + 1
        long long n_raw = (a - 1) * k + 1;
        long long n_mod = n_raw % MOD;

        // 2. 组合数 C(n, a) (mod MOD)
        long long comb = C_mod(n_raw, (int)a);

        // 3. m = (b-1)*k*C(n,a) + 1 (mod MOD)
        long long m_mod = (((((b - 1) % MOD) * (k % MOD)) % MOD * comb) % MOD);
        m_mod = (m_mod + 1) % MOD;

        cout << n_mod << ' ' << m_mod << '\n';
    }
    return 0;
}
