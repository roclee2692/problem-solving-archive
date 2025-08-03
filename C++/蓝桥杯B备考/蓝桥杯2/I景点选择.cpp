#include <bits/stdc++.h>
using namespace std;

/*
 * 本题所需的数据结构与步骤：
 * 1. 读取输入：n(节点数), k(访问景点个数)
 * 2. 建立树的邻接表 + 权重数组
 * 3. 利用 DFS 构建：
 *      - depth[u]：节点 u 的深度
 *      - dist[u]：节点 u 到 根节点(本题默认选 1 号节点为根) 的距离
 *      - dp[u][j]：从 u 出发，向上跳 2^j 步所能到达的祖先
 * 4. 利用 dp 与 depth 数组实现 LCA(x, y) 的快速求取
 * 5. 在得到 LCA 后，可快速计算任意两节点间的距离 getDist(u, v)
 * 6. 最后对于需要跳过的节点 i，按照公式
 *      sum - dist(A_{i-1}, A_i) - dist(A_i, A_{i+1}) + dist(A_{i-1}, A_{i+1})
 *    计算新的路径长度
 */

// -------------------- 全局常量与存储 --------------------
static const int MAXN = 100000;
static const int LOGN = 20; // 2^20 > 10^5，够用

// 邻接表存储：edge[u] 中存放与 u 相邻的节点 v
// weight[u] 中存放与 u 相邻的对应边权 w
vector<int> edgeList[MAXN + 5];
vector<long long> weightList[MAXN + 5];

// dp[u][j]：从 u 节点向上走 2^j 步的祖先节点
int dp[MAXN + 5][LOGN + 1];

// depth[u]：记录节点 u 的深度 (相对于根节点)
int depthArr[MAXN + 5];

// distArr[u]：记录节点 u 到根节点的距离
long long distArr[MAXN + 5];

// -------------------- DFS 构建 LCA 所需信息 --------------------
void dfs(int u, int parent) {
    // 设置当前节点的深度与父亲 (向上 1 步)
    depthArr[u] = depthArr[parent] + 1;
    dp[u][0] = parent; // dp[u][0] 就是 u 的父亲

    // 预处理：dp[u][i] = dp[ dp[u][i-1] ][ i-1 ]
    // 即 “从 u 向上走 2^i 步” = “从 u 向上走 2^(i-1) 步” 后，再向上走 2^(i-1) 步
    for(int i = 1; i <= LOGN; i++) {
        dp[u][i] = dp[dp[u][i-1]][i-1];
    }

    // DFS 继续遍历与 u 相邻的节点
    for(int i = 0; i < (int)edgeList[u].size(); i++) {
        int v = edgeList[u][i];
        long long w = weightList[u][i];
        if(v == parent) continue; // 避免回到父亲形成环
        distArr[v] = distArr[u] + w; // v 到 根节点的距离 = u 到 根节点距离 + 边权
        dfs(v, u);
    }
}

// -------------------- 求 LCA(u, v) --------------------
int LCA(int x, int y) {
    // 1. 确保 depth[x] >= depth[y]，让 x 是更深或相等的那个
    if(depthArr[x] < depthArr[y]) {
        swap(x, y);
    }
    // 2. 将 x 向上跳到与 y 同一深度
    int diff = depthArr[x] - depthArr[y];
    for(int i = 0; i <= LOGN; i++) {
        if(diff & (1 << i)) {
            x = dp[x][i];
        }
    }
    // 此时若相等，说明 y 本身就是 x 的祖先
    if(x == y) return x;

    // 3. 继续向上跳，直到找到最低公共祖先
    //   (dp[x][i] != dp[y][i]) 表示如果在 2^i 步祖先不同，就先跳过去
    for(int i = LOGN; i >= 0; i--) {
        if(dp[x][i] != dp[y][i]) {
            x = dp[x][i];
            y = dp[y][i];
        }
    }
    // 4. 此时它们的父亲就是 LCA
    return dp[x][0];
}

// -------------------- 求两点距离 getDist(u, v) --------------------
long long getDist(int u, int v) {
    // 若有需要处理边界情况，可额外判断
    if(u == 0 || v == 0) return 0; // 根据第一份代码的特殊写法，可自行选择
    int lca = LCA(u, v);
    // distArr[u] + distArr[v] - 2 * distArr[LCA(u, v)]
    return distArr[u] + distArr[v] - 2 * distArr[lca];
}

// -------------------- 主函数 --------------------
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // 读取 n - 1 条边 (树)
    // 树：无向边 u - v，边权 w
    for(int i = 1; i < n; i++){//数据只有n-1行
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edgeList[u].push_back(v);
        edgeList[v].push_back(u);
        weightList[u].push_back(w);
        weightList[v].push_back(w);
    }

    // 读取访问路径 A[1..k]
    vector<int> A(k + 1);
    for(int i = 1; i <= k; i++){
        cin >> A[i];
    }

    // 1. 以节点 1 作为根节点进行 DFS，初始化 LCA 所需信息
    //    注意：若整棵树不一定连通，可根据题意来处理，一般题目保证连通
    //    depthArr[1] = 1 表示根的深度可为 1
    dfs(1, 0);

    // 2. 计算原访问序列的总距离 sum
    long long sumPath = 0;
    // 为了简化边界，可在 A[0], A[k+1] 赋值为 0 (或其他处理)，并在 getDist 函数里做判断
    // 或者只在 1..k-1 里累加距离
    for(int i = 1; i < k; i++){
        sumPath += getDist(A[i], A[i+1]);
    }

    // 3. 遍历每一个要被「跳过」的点 i，输出新路径长度
    //    按照： sum - dist(A[i-1], A[i]) - dist(A[i], A[i+1]) + dist(A[i-1], A[i+1])
    //    注：需要小心 i=1 或 i=k 时，A[i-1], A[i+1] 的合法性，这里我们只要保证下标别越界即可
    //    因为题目中常见做法就是 A[0] 和 A[k+1] 设为 0，再在 getDist 做 (0, x)->0 的处理
    //    或者你也可以手工判断 i=1 时就不减 A[i-1]... 视题目需要
    //    下面是直接用第一版代码的思路处理：假设 A[0] = A[k+1] = 0
    //    你也可以选择更严格的判断边界
    A[0] = 0; 
    A.push_back(0); // A[k+1] = 0

    for(int i = 1; i <= k; i++){
        long long dist1 = getDist(A[i-1], A[i]);
        long long dist2 = getDist(A[i],   A[i+1]);
        long long dist3 = getDist(A[i-1], A[i+1]);
        long long ans   = sumPath - dist1 - dist2 + dist3;
        cout << ans << " ";
    }
    cout << "\n";

    return 0;
}
