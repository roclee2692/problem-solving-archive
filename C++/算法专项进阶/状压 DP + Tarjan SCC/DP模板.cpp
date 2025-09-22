#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // 用于 memset

using namespace std;

// --- 配置与全局变量 ---

// N 的最大值，根据题目调整。状压DP通常 N <= 20
const int N = 20; 
// 状态数量，2^N
const int STATE_COUNT = 1 << N; 
// 表示无穷大，用于求最小值
const int INF = 0x3f3f3f3f; 

int n; // 城市数量
int dist[N][N]; // dist[i][j] 表示从城市 i 到城市 j 的距离

// --- DP 核心 ---

// dp[mask][i] 的定义：
// mask: 一个二进制数，表示已经访问过的城市集合。
//       例如 mask = 0...1011 表示访问了城市 0, 1, 3。
// i:    当前所在的城市 (必须是 mask 集合中的一员)。
// 值:   从起点出发，访问了 mask 所代表的城市集合，并最终停在城市 i 的最短路径长度。
int dp[STATE_COUNT][N];


int main() {
    // --- 输入与初始化 ---
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "请输入城市数量 n: ";
    cin >> n;

    cout << "请输入 " << n << "x" << n << " 的距离矩阵:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dist[i][j];
        }
    }

    // 1. 初始化 DP 数组为无穷大
    // memset 的 0x3f 是一个常用技巧，它设置的int值足够大，
    // 且两个 INF 相加不会溢出 int。
    memset(dp, 0x3f, sizeof(dp));

    // 2. 设置 DP 边界条件（起点）
    // 假设我们从城市 0 出发。
    // "只访问了城市 0" 这个集合的 mask 是 1 (二进制 0...0001)。
    // 此时停留在城市 0，路径长度为 0。
    dp[1][0] = 0;

    // --- 状态转移 ---

    // 3. 按 mask 从小到大遍历所有状态
    // mask 从 1 开始，因为我们已经处理了起点状态，且空集没有意义。
    for (int mask = 1; mask < (1 << n); ++mask) {
        // 4. 遍历当前状态 mask 可能的最后一个城市 i
        for (int i = 0; i < n; ++i) {
            // 检查城市 i 是否在 mask 集合中
            if ((mask >> i) & 1) {
                // 5. 遍历上一个状态可能在的城市 j
                for (int j = 0; j < n; ++j) {
                    // 检查城市 j 是否也在 mask 集合中，并且 j 不能是 i
                    // 我们要从 j 转移到 i
                    if (i != j && ((mask >> j) & 1)) {
                        
                        // 状态转移的核心：
                        // 要到达 `dp[mask][i]` 这个状态，
                        // 必然是从一个“少访问了城市i”的状态转移过来的。
                        // 这个“上一个状态”的集合是 `mask` 去掉 `i`，即 `mask ^ (1 << i)`
                        // 在那个状态下，我们停留在某个城市 `j`。
                        // 所以，我们尝试用 `dp[mask ^ (1 << i)][j] + dist[j][i]` 来更新 `dp[mask][i]`
                        
                        int prev_mask = mask ^ (1 << i); // 上一个状态的 mask
                        
                        // 确保上一个状态是可达的
                        if (dp[prev_mask][j] != INF) {
                           dp[mask][i] = min(dp[mask][i], dp[prev_mask][j] + dist[j][i]);
                        }
                    }
                }
            }
        }
    }

    // --- 计算最终结果 ---

    // 6. 找到最终答案
    // 此时，`dp[(1 << n) - 1][i]` 存储了“走遍所有城市，并停在城市i”的最短路径。
    // (1 << n) - 1 是全集，例如 n=4 时，是 1111 (二进制)。
    int final_mask = (1 << n) - 1;
    int min_total_dist = INF;

    // 遍历所有可能的终点 i，并加上回到起点 0 的距离
    for (int i = 0; i < n; ++i) {
        if (dp[final_mask][i] != INF) {
            min_total_dist = min(min_total_dist, dp[final_mask][i] + dist[i][0]);
        }
    }

    cout << "走遍所有城市并返回起点的最短路径长度是: " << min_total_dist << endl;

    return 0;
}