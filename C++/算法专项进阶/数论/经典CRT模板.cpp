#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 快速幂：a^b mod m
ll qpow(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = res * a % m;
        a=a*a%m;
        b>>= 1;
    }
    return res;
}

int main() {
    // 方程组
    vector<ll> a = {2, 3, 2};
    vector<ll> m = {3, 5, 7};
    int n = a.size();

    // 计算 M = m1 * m2 * m3 ...
    ll M = 1;
    for (ll mi : m) M *= mi;

    cout << "总模数 M = " << M << endl;

    vector<ll> Mi(n);
    vector<ll> ti(n);

    ll x = 0;
    for (int i = 0; i < n; i++) {
        Mi[i] = M / m[i];
        cout << "M" << i+1 << " = " << Mi[i] << endl;

        // 计算 Mi 的逆元 mod mi
        // Mi^{-1} ≡ Mi^(mi-2) mod mi
        ti[i] = qpow(Mi[i], m[i] - 2, m[i]);
        cout << "M" << i+1 << " 在 mod " << m[i] << " 下的逆元 ti = " << ti[i] << endl;

        ll term = a[i] * Mi[i] % M * ti[i] % M;
        cout << "第 " << i+1 << " 项贡献 = " << term << endl;
        x = (x + term) % M;
    }

    cout << "最小非负整数解 x = " << x << endl;
    cout << "所有解为 x ≡ " << x << " mod " << M << endl;

    return 0;
}
