#include <bits/stdc++.h>
using namespace std;

/*
 * 本题涉及的核心数据结构与算法包括：
 * 
 * 1. 树的存储：
 *    - 使用邻接表 + 边权数组存储无向带权树（n 个节点，n-1 条边）。
 * 
 * 2. 深度优先搜索（DFS）初始化：
 *    - depth[u]：记录节点 u 的深度（相对于根节点）。
 *    - dist[u]：节点 u 到根节点的距离。
 *    - dp[u][j]：从 u 向上跳 2^j 步所能到达的祖先节点（倍增法预处理）。
 * 
 * 3. 倍增求 LCA（最近公共祖先）：
 *    - 通过二进制分解深度差 diff，将深度较深的节点跳到同一层。
 *    - 然后同时上跳直到找到最近公共祖先。
 * 
 * 4. 求两点间路径长度：
 *    - 公式：dist[u] + dist[v] - 2 * dist[LCA(u, v)]
 *    - 利用 dfs 中记录的 dist 数组和 lca() 函数实现。
 * 
 * 5. 访问路径最短替代：
 *    - 给定访问路径 A[1..k]，原始路径为 A1 -> A2 -> A3 -> ... -> Ak。
 *    - 总路径和为 getDist(A1,A2) + getDist(A2,A3) + ...。
 *    - 若跳过第 i 个点 A[i]，新路径长度为：
 *        sum - getDist(A[i-1], A[i]) - getDist(A[i], A[i+1]) + getDist(A[i-1], A[i+1])
 *    - 可高效计算出每次跳过某点后的最短路径长度。
 * 
 * 6. 边界处理技巧：
 *    - 设置 A[0] = 0，A[k+1] = 0，并在 getDist 中约定 getDist(0, x) = 0
 *    - 避免边界判断，代码更加整洁。
 */

// -------------------- 常量与全局变量 --------------------
const int MAXN = 100000 + 5;
const int LOGN = 20;

vector<int> edgeList[MAXN];         // edgeList[u]：节点 u 相邻的所有节点
vector<long long> weightList[MAXN]; // weightList[u]：对应边权

int dp[MAXN][LOGN + 1];             // dp[u][j]：从 u 向上跳 2^j 层到的祖先
int depth[MAXN];                    // depth[u]：节点 u 的深度
long long dist[MAXN];              // dist[u]：u 到根节点的距离

// -------------------- DFS 初始化 --------------------
void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    dp[u][0] = p;

    // 倍增跳跃预处理
    for (int i = 1; i <= LOGN; i++) {
        dp[u][i] = dp[dp[u][i-1]][i-1];
    }

    // 遍历邻接边，更新子节点信息
    for (size_t i = 0; i < edgeList[u].size(); i++) {
        int v = edgeList[u][i];
        long long w = weightList[u][i];
        if (v == p) continue; // 避免走回父亲
        dist[v] = dist[u] + w;
        dfs(v, u);
    }
}

// -------------------- LCA（最近公共祖先） --------------------
int lca(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);

    int diff = depth[x] - depth[y];
    // 用二进制跳跃，将 x 向上跳到与 y 同一层
    for (int i = 0; i <= LOGN; i++) {
        if (diff & (1 << i)) {//这里必须是&！！
            x = dp[x][i];
        }
    }

    if (x == y) return x; // y 是 x 的祖先

    // 双指针同时跳跃，直到找到最近公共祖先
    for (int i = LOGN; i >= 0; i--) {
        if (dp[x][i] != dp[y][i]) {
            x = dp[x][i];
            y = dp[y][i];
        }
    }
    return dp[x][0];
}

// -------------------- 两点间距离计算 --------------------
long long getDist(int u, int v) {
    if (u == 0 || v == 0) return 0; // 边界处理
    int anc = lca(u, v);
    return dist[u] + dist[v] - 2 * dist[anc];
}

// -------------------- 主函数 --------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // 构建无向图（树）
    for (int i = 1; i < n; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edgeList[u].push_back(v);
        edgeList[v].push_back(u);
        weightList[u].push_back(w);
        weightList[v].push_back(w);
    }

    vector<int> A(k + 2); // A[1..k] 是访问路径，A[0] 和 A[k+1] 补零处理
    for (int i = 1; i <= k; i++) {
        cin >> A[i];
    }

    dfs(1, 0); // 初始化：从根节点 1 开始 DFS

    // 求原始路径的总长度
    long long total = 0;
    for (int i = 1; i < k; i++) {
        total += getDist(A[i], A[i+1]);
    }

    A[0] = 0;
    A[k+1] = 0;

    // 枚举跳过每一个点 A[i]
    for (int i = 1; i <= k; i++) {
        long long d1 = getDist(A[i-1], A[i]);
        long long d2 = getDist(A[i], A[i+1]);
        long long d3 = getDist(A[i-1], A[i+1]);
        long long ans = total - d1 - d2 + d3;
        cout << ans << " ";
    }
    cout << "\n";

    return 0;
}
