#include <iostream>     // 标准输入输出
#include <vector>       // 动态数组 vector
#include <algorithm>    // reverse
using namespace std;

// 全局变量声明，方便在各处访问
int n, m;                              // 顶点数 n 和 边数 m
vector<vector<int>> adj;              // 正向图的邻接表
vector<vector<int>> reverse_adj;      // 反向图的邻接表
vector<bool> visited;                 // 第一次 DFS 的访问标记
vector<int> order;                    // 存放节点的“结束时间”顺序
vector<bool> visited2;                // 第二次 DFS 的访问标记
vector<vector<int>> components;       // 存放所有强连通分量

// 第一次 DFS，从 u 出发，遍历正向图，DFS 完成后将 u 加入 order
void dfs1(int u) {
    visited[u] = true;                // 标记 u 已访问
    // 遍历 u 的所有正向邻居 v
    for (int v : adj[u]) {
        if (!visited[v])              // 如果 v 尚未访问，就递归
            dfs1(v);
    }
    // 所有能从 u 到达的节点都处理完以后，把 u 放到 order 末尾
    order.push_back(u);
}

// 第二次 DFS，从 u 出发，遍历反向图，将能回到 u 的所有节点收集到 comp 中
void dfs2(int u, vector<int>& comp) {
    visited2[u] = true;              // 标记 u 已在第二次搜索中访问
    comp.push_back(u);               // 将 u 加入当前分量
    // 遍历 u 在反向图中的邻居 v
    for (int v : reverse_adj[u]) {
        if (!visited2[v])            // 如果 v 尚未访问，就递归
            dfs2(v, comp);
    }
}

int main() {
    // 读取顶点数 n 和边数 m
    cin >> n >> m;

    // 根据 n 调整邻接表大小，初始时每个都为空
    adj.resize(n);
    reverse_adj.resize(n);
    // 初始化两个访问数组，大小为 n，默认值 false
    visited.assign(n, false);
    visited2.assign(n, false);

    // 读入所有有向边 u -> v，填充正向图和反向图
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);         // 正向图边
        reverse_adj[v].push_back(u); // 反向图边
    }

    // —— 第一次 DFS：在正向图上，得到节点的后序（结束时间）序列 —— //
    for (int u = 0; u < n; ++u) {
        if (!visited[u])             // 如果 u 尚未被访问，就从 u 开始 DFS
            dfs1(u);
    }

    // 把 order 倒序，保证先处理最晚完成的节点
    reverse(order.begin(), order.end());

    // —— 第二次 DFS：在反向图上，按 order 顺序收集强连通分量 —— //
    for (int u : order) {
        if (!visited2[u]) {          // 如果 u 未被第二次搜索访问
            vector<int> comp;        // 新建一个分量容器
            dfs2(u, comp);           // 从 u 出发，收集一个 SCC
            components.push_back(comp); // 保存当前分量
        }
    }

    // —— 输出所有分量及其数量 —— //
    for (const auto& comp : components) {
        cout << "{ ";
        for (int v : comp) {
            cout << v << " ";        // 输出分量中的每个顶点
        }
        cout << "}" << endl;
    }
    // 最后一行输出分量总数
    cout << components.size() << endl;

    return 0;
}
