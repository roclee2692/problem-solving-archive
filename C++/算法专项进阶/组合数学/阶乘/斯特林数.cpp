#include <iostream>
#include <vector>
#include <numeric>
#include <map>

using namespace std;

using ll = long long;

const int MAXN = 2005; // 题目数据范围 n <= 2000
const int MOD = 1e9 + 7;

ll S[MAXN][MAXN]; // 第二类斯特林数 S(i, j)
ll B[MAXN];     // 贝尔数 B(i)

// 欧几里得算法求最大公约数
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 预处理斯特林数和贝尔数
void precompute(int n) {
    S[0][0] = 1;
    B[0] = 1;
    for (int i = 1; i <= n; ++i) {
        S[i][1] = 1; // n个球放1个盒子，1种
        for (int j = 2; j <= i; ++j) {
            S[i][j] = (S[i - 1][j - 1] + (ll)j * S[i - 1][j]) % MOD;
        }
        // 计算贝尔数 B[i]
        for (int j = 1; j <= i; ++j) {
            B[i] = (B[i] + S[i][j]) % MOD;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll L;
    cin >> n >> L;

    precompute(n);

    // map<pair<ll, ll>, int> counts;
    // 使用 map 统计每个最简时间类别的选手数量
    map<pair<ll, ll>, int> counts;
    for (int i = 0; i < n; ++i) {
        ll v;
        cin >> v;
        ll common = gcd(L, v);
        ll num = L / common; // 分子
        ll den = v / common; // 分母
        counts[{num, den}]++;
    }

    ll ans = 1;
    // 遍历所有类别，将每个类别的贝尔数相乘
    for (auto const& [time, count] : counts) {
        ans = (ans * B[count]) % MOD;
    }

    cout << ans << endl;

    return 0;
}