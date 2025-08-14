#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;  // 测试用例的数量
    cin >> T;
    
    while (T--) {
        ll n, m;
        cin >> n >> m;

        // 最小神圣值和是 n，最大神圣值和是 n * (n + 1) / 2
        ll lo = n;                    // 神圣值和的最小值是 n（所有节点神圣值为 1）
        ll hi = n * (n + 1) / 2;      // 最大值是节点神圣值从 1 到 n 累加
        if (m < lo || m > hi) { 
            cout << -1 << '\n';  // 如果 m 超出了合理范围，输出 -1
            continue; 
        }

        // 枚举根节点 k，选择合适的根节点
        int k = -1;
        for (int i = 1; i <= n; ++i) {
            ll base = 1LL * i * (i + 1) / 2;  // 链 1..i 的和
            ll A = base + (n - i);            // 其余节点神圣值为 1
            ll B = base + (n - i) * 1LL * i;  // 其余节点神圣值为 i
            if (A <= m && m <= B) {  // 找到合适的根节点 k
                k = i;
                break;
            }
        }
        if (k == -1) { 
            cout << -1 << '\n';  // 如果没有找到合适的根节点，输出 -1
            continue; 
        }

        // 计算每个神圣值的出现次数
        ll base = 1LL * k * (k + 1) / 2;  // 根节点为 k 时的贡献
        ll cnt  = n - k;                   // 需要分配的节点个数
        ll extra = (m - base) - cnt;       // 需要额外再涨的贡献

        // 构造神圣值分配的数组 c[u]，表示需要 d(v)=u 的节点数
        vector<ll> c(k + 1, 0);
        c[1] = cnt;  // 初始化，所有节点的神圣值为 1

        // 分配额外的增量 extra
        if (extra) {
            ll full = extra / (k - 1);  // 可以把 full 个 节点升到 k
            ll r    = extra % (k - 1);  // 剩余 r(<k-1) 还需一次性给 1 个节点

            c[1] -= full;  // 这些节点不再是 1
            c[k] += full;  // 变成 k

            if (r) {  // 如果还需要更多的增量
                --c[1];         // 从 1 中“拿”出一个节点
                ++c[1 + r];     // 把它提升到 1+r
            }
        }

        // 输出根节点 k
        cout << k << '\n';

        // 递减链：k -> k-1 -> … -> 1
        for (int i = k; i > 1; --i) 
            cout << i << ' ' << i - 1 << '\n';

        // 其余节点根据 c[u] 直接挂在 u 之下
        int v = k + 1;  // 下一未使用的节点编号
        for (int u = 1; u <= k; ++u) {
            for (ll t = 0; t < c[u]; ++t)
                cout << v++ << ' ' << u << '\n';  // 连接 v 和 u
        }
    }
    return 0;
}
