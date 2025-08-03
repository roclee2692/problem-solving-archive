#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 扩展欧几里得：解 ax + by = gcd(a,b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// 合并两个同余方程：
// x ≡ a1 (mod m1)
// x ≡ a2 (mod m2)
pair<ll, ll> merge(ll a1, ll m1, ll a2, ll m2) {
    ll x, y;
    ll d = exgcd(m1, m2, x, y);
    ll c = a2 - a1;

    if (c % d != 0) {
        return {-1, -1}; // 无解
    }

    // 模简化：
    ll mod = m2 / d;

    // 求 k：
    x = (x * (c / d)) % mod;
    if (x < 0) x += mod;

    // 新的解：
    ll new_a = a1 + m1 * x;
    ll new_m = m1 / d * m2; // lcm(m1, m2)

    new_a = (new_a % new_m + new_m) % new_m;

    return {new_a, new_m};
}

// ExCRT 解多个方程
pair<ll, ll> exCRT(vector<ll> a, vector<ll> m) {
    ll cur_a = a[0];
    ll cur_m = m[0];
    for (int i = 1; i < a.size(); i++) {
        auto res = merge(cur_a, cur_m, a[i], m[i]);
        if (res.first == -1) {
            return {-1, -1}; // 无解
        }
        cur_a = res.first;
        cur_m = res.second;
    }
    return {cur_a, cur_m};
}

int main() {
    vector<ll> a = {2, 3, 2};
    vector<ll> m = {3, 5, 7};

    auto res = exCRT(a, m);
    if (res.first == -1) {
        puts("No solution.");
    } else {
        printf("最小非负整数解 x = %lld\n", res.first);
        printf("所有解为 x ≡ %lld mod %lld\n", res.first, res.second);
    }
    return 0;
}
