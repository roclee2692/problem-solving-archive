#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int M=1e5+5;
//有向无环图 (Directed Acyclic Graph, DAG)

// --- Tarjan 算法所需变量 ---
vector<ll> adj[N],value;
ll dfs[N],low[N];
ll scc_id[N],scc_count;
stack<ll> s;
bool in_stack[N];
ll timestamp,ans;//全局变量默认初始化为零

// --- 缩点后 DAG 所需变量 ---
vector<ll> adj_scc[N];
ll weights[N];
ll scc_weight[N];
ll indegree[N];
ll dp[N];

void tarjan(ll u){
    dfs[u]=low[u]=++timestamp;
    s.push(u);
    in_stack[u]=1;

    for(ll v:adj[u]){
        if(dfs[v]==0) {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in_stack[v]) low[u]=min(low[u],dfs[v]);
    }

    if(dfs[u]==low[u]){
        scc_count++;
        ll node;
        do{
            node=s.top(); s.pop();
            in_stack[node]=0;
            scc_id[node]=scc_count;
        }while (node!=u);
    }
}

int main(){
    ll n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){//点 从1开始
        cin >> weights[i];
    }
    for(int i=0;i<m;i++){
        ll u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    // 1. 运行 Tarjan 找 SCC
    for (int i = 1; i <= n; ++i) {
        if (!dfs[i]) {
            tarjan(i);
        }
    }
    // 2. 构建缩点后的 DAG
    for(int u=1;u<=n;u++){
        scc_weight[scc_id[u]]+=weights[u]; // 计算 SCC 的总权值
        for(ll v:adj[u]){
            if(scc_id[v]!=scc_id[u]){
                adj_scc[scc_id[u]].push_back(scc_id[v]);
                indegree[scc_id[v]]++;
            }
        }
    }
// 在建新图时，如果原图两SCC间有多条边，新图中也会被加入多条边，
// 但因为我们只关心连通性，这在拓扑排序中没有影响。如果需要严格去重，
// 可以将 adj_scc 定义为 vector<set<int>> 或在建图后对每个 adj_scc[i] 进行排序和去重。
// 对于本题，不影响结果。
    // // 去除重复边
    // for(int i=1;i<=scc_count;i++){
    //     sort(adj_scc[i].begin(), adj_scc[i].end());
    //     adj_scc[i].erase(unique(adj_scc[i].begin(), adj_scc[i].end()), adj_scc[i].end());
    // }
    
    // // 重新计算入度
    // for(int i=1;i<=scc_count;i++) indegree[i] = 0;
    // for(int u=1;u<=scc_count;u++){
    //     for(ll v : adj_scc[u]){
    //         indegree[v]++;
    //     }
    // }

     // 3. 拓扑排序与 DP
    stack<int> q; // 用 stack 代替 queue 也可以
     for (int i = 1; i <= scc_count; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
            dp[i] = scc_weight[i]; // 初始化dp值
        }
    }
     while (!q.empty()) {
        int u = q.top();
        q.pop();

        for (int v : adj_scc[u]) {
            dp[v] = max(dp[v], dp[u] + scc_weight[v]);
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
// 4. 寻找最终答案
    for(int i=1;i<=scc_count;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}

/*好的，我们来做一个全面的复盘，把状压 DP 和 Tarjan SCC 这两个强大的工具彻底掌握，并看看它们如何结合起来解决更复杂的问题。

1. 综合复盘：模板回顾与常见坑点
A. 状压 DP 模板复盘
核心模板 (TSP/路径问题)

状态: dp[mask][i] 表示访问过的节点集合为 mask，且当前停留在节点 i 时的最优值（例如最短路径、最大价值等）。

转移: dp[mask][i] = optimal_op(dp[mask ^ (1<<i)][j] + cost(j, i))

mask ^ (1<<i) 是 mask 去掉节点 i 后的上一个状态。

j 是上一个状态中，i 的前驱节点。

适用场景: 数据规模 N 极小（通常 N ≤ 20），问题涉及集合、子集、排列组合等。

常见坑点 (Pitfalls)

复杂度算错：O(2^N * N^2) 的复杂度对 N 的大小非常敏感。N=20 时约 4 * 10^8 次运算，处于超时边缘；N > 22 基本不可能通过。看到小 N 才考虑状压。

位运算与索引混淆：1 << i 代表的是集合 {i}，即第 i 位为1。在处理 1-based 和 0-based 问题时，很容易在 1 << i 和 1 << (i-1) 之间混淆，导致错误。建议：始终在内部统一为 0-based 索引处理。

边界条件错误：dp 的起点（base case）至关重要。例如 TSP 问题中，dp[1][0] = 0 (从节点0出发，访问了集合{0}，停在0，代价为0)，如果起点有代价，则需要相应修改。

转移逻辑不严谨：在从 j 转移到 i 时，忘记检查 j 是否真的属于上一个状态 mask ^ (1<<i)，导致从一个不存在的状态进行了转移。

B. Tarjan SCC 模板复盘
核心模板

组件: dfn[], low[], stack, in_stack[]。

逻辑: 通过一次 DFS，dfn 记录访问时间戳，low 记录能追溯到的最早祖先。

关键判断: 当 dfn[u] == low[u] 时，u 是一个 SCC 的根，此时栈中从 u 到栈顶的所有节点构成一个 SCC。

适用场景: 有向图中所有涉及环、节点间双向可达性的问题，或需要将图缩点成 DAG 的问题。

常见坑点 (Pitfalls)

in_stack 判断遗漏：这是 最最最常见 的错误。在更新 low[u] 时，对于已访问过的邻居 v，必须用 in_stack[v] 加以判断。low[u] = min(low[u], dfn[v]) 仅当 v 仍在栈中时才成立。如果 v 已经属于另一个已处理完的 SCC，则不能用它来更新 low 值。

图不连通：忘记在主函数中用 for 循环调用 Tarjan，for (int i=1; i<=n; ++i) if (!dfn[i]) tarjan(i);，导致只处理了图的一部分。

数组/变量未清空：在多组测试数据的题目中，忘记重置 dfn, low, in_stack, timestamp, scc_count 等全局或静态变量。

low 更新混淆：

从子节点 v 回溯更新：low[u] = min(low[u], low[v]);

遇到在栈中的邻居 v：low[u] = min(low[u], dfn[v]);

两者不要搞混。

2. 综合题：缩点 + 状压 DP
很多难题都是由多个经典算法组合而成的。缩点 + 状压 DP 就是一个常见的组合，通常用于解决一般有向图上的路径问题。

例题构想 (蓝桥杯风格)

题目：[P_Custom] 景区深度游

给定一个由 N 个景点和 M 条单向游览路线组成的景区（N ≤ 18, M ≤ 5000）。每个景点都有一个观赏价值 w_i。由于景区内存在环路，你可以多次经过同一个景点，但其观赏价值只计算一次。

请规划一条简单路径（即不重复经过缩点后的景区单元），使得路径上所有景点的总观赏价值最大。

解题思路
这道题的解法完美地结合了两个算法：

第一步：识别并处理环路 (Tarjan SCC)

题目中“可以多次经过同一个景点，但价值只计算一次”是强烈的信号。这意味着一个强连通分量 (SCC) 内的所有景点可以被看作一个整体。只要你进入了某个 SCC，你就可以获得这个 SCC 内所有景点的总价值。

操作：
a.  运行 Tarjan 算法，找出所有 SCC。
b.  缩点：将每个 SCC 看作一个“超级点”或“景区单元”。
c.  建立新图：
* 新图的节点是这些 SCC。
* 新图节点的权值 = SCC 内所有原始景点的权值之和。
* 如果原图中存在从 SCC A 的某景点到 SCC B 的某景点的边，则在新图中连一条 A -> B 的边。

结果：我们得到一个有向无环图 (DAG)，节点数量为 scc_count (一定 ≤ N)。

第二步：在 DAG 上寻找最长路径 (状压 DP)

现在问题转化为：在一个点带权 DAG 上，找一条简单路径，使其经过的节点权值和最大。

由于 N ≤ 18，缩点后的 scc_count 也 ≤ 18。这个规模是状压 DP 的完美应用场景。

操作：
a.  状态定义: dp[mask][i] 表示在新图（DAG）上，访问过的 SCC 集合为 mask，且当前停留在 SCC i 时的最大总价值。
b.  转移:
dp[mask][i] = max(dp[mask ^ (1<<i)][j] + scc_weight[i])
其中 j 是新图中能到达 i 的一个前驱 SCC。
c.  注意: DP 的转移需要按照一定的顺序。可以直接在拓扑排序的过程中进行 DP，也可以用记忆化搜索。

这个问题的本质就是：先用 Tarjan 将一般有向图“净化”成 DAG，再用状压 DP 在这个规模不大的 DAG 上解决路径问题。

3. 写短笔记：核心用法总结
Bitmask 用法速记
创建全集: (1 << n) - 1

检查第 i 位: (mask >> i) & 1

添加元素 i: mask | (1 << i)

移除元素 i: mask & ~(1 << i)

切换元素 i: mask ^ (1 << i)

最低位的1: mask & -mask (lowbit)

遍历 mask 的所有子集 s: for (int s = mask; s > 0; s = (s - 1) & mask)

Tarjan 实战细节
dfn/low 初始化: dfn[u] = low[u] = ++timestamp;

入栈: s.push(u); in_stack[u] = true;

核心更新 (两条路):

树边 (子节点 v 未访问): tarjan(v); low[u] = min(low[u], low[v]);

返祖/横叉边 (子节点 v 在栈中): low[u] = min(low[u], dfn[v]);

SCC判定: if (dfn[u] == low[u]) -> u 是根，从栈顶 pop 直到 u。

出栈: in_stack[node] = false; (千万别忘！)

主函数框架:

C++

for (int i = 1; i <= n; ++i) {
    if (!dfn[i]) {
        tarjan(i);
    }
}*/