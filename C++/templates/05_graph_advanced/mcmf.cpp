/*
 * 【最小费用最大流 MCMF】- 在最大流基础上优化费用
 * 
 * 时间复杂度：O(n * m * f)，f 为最大流
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 最小费用流问题
 *   - 二分图最优匹配
 *   - 任务分配优化
 *   - 物流运输成本
 * 
 * 模板题：
 *   - 洛谷 P3381 - 【模板】最小费用最大流
 *   - Codeforces 362E - Petya and Pipes
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;
const int MAXM = 1e5 + 5;
const ll INF = 1e18;

// ===== MCMF 核心数据结构 =====
struct Edge {
    int to;      // 终点
    ll cap;      // 容量
    ll cost;     // 单位流量的费用
    int rev;     // 反向边的位置
};

vector<Edge> adj[MAXN];
int n, m, s, t;
ll dis[MAXN];      // dis[i] = 从源点到 i 的最短费用
int pre_v[MAXN];   // pre_v[i] = 最短路中 i 的前驱节点
int pre_e[MAXN];   // pre_e[i] = 最短路中到达 i 的边的编号
bool inq[MAXN];    // SPFA 中是否在队列中

// ===== 添加边 =====
// 同时添加正向边和反向边
// 反向边的费用是负的（用于退流时退回费用）
void add_edge(int from, int to, ll cap, ll cost) {
    // 正向边：from → to，容量 cap，费用 cost
    adj[from].push_back({to, cap, cost, (int)adj[to].size()});
    
    // 反向边：to → from，容量 0，费用 -cost
    // 为什么费用是负的？退流时要退回之前的费用
    adj[to].push_back({from, 0, -cost, (int)adj[from].size() - 1});
}

// ===== SPFA 寻找最短费用的增广路 =====
// 返回：是否存在增广路
// 核心：找从 s 到 t 的最小费用路径（允许有负权边，但不能有负环）
bool spfa() {
    fill(dis, dis + n + 1, INF);
    fill(inq, inq + n + 1, false);
    
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    inq[s] = true;
    
    // ===== SPFA 算法 =====
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        
        for (int i = 0; i < adj[u].size(); i++) {
            Edge &e = adj[u][i];
            
            // 只考虑还有容量的边
            if (e.cap > 0 && dis[e.to] > dis[u] + e.cost) {
                dis[e.to] = dis[u] + e.cost;
                pre_v[e.to] = u;
                pre_e[e.to] = i;
                
                if (!inq[e.to]) {
                    q.push(e.to);
                    inq[e.to] = true;
                }
            }
        }
    }
    
    // 返回是否能到达汇点
    return dis[t] != INF;
}

// ===== 最小费用最大流主函数 =====
// 返回：{最大流，最小费用}
// 核心思想：每次找最小费用的增广路，直到没有增广路
pair<ll, ll> mcmf() {
    ll max_flow = 0, min_cost = 0;
    
    // ===== 主循环：不断找最小费用增广路 =====
    while (spfa()) {
        // ===== 找瓶颈容量（增广路上的最小容量）=====
        ll flow = INF;
        for (int v = t; v != s; v = pre_v[v]) {
            flow = min(flow, adj[pre_v[v]][pre_e[v]].cap);
        }
        
        // ===== 更新流量和费用 =====
        max_flow += flow;
        min_cost += flow * dis[t];
        
        // ===== 更新边的容量 =====
        for (int v = t; v != s; v = pre_v[v]) {
            Edge &e = adj[pre_v[v]][pre_e[v]];
            e.cap -= flow;                      // 正向边减少容量
            adj[v][e.rev].cap += flow;          // 反向边增加容量
        }
    }
    
    return {max_flow, min_cost};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> s >> t;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        ll cap, cost;
        cin >> u >> v >> cap >> cost;
        add_edge(u, v, cap, cost);
    }
    
    auto [flow, cost] = mcmf();
    cout << flow << " " << cost << "\n";
    
    return 0;
}

/*
 * ========== MCMF 核心原理 ==========
 * 
 * 【什么是最小费用最大流？】
 * - 在最大流的基础上，每条边有单位费用
 * - 目标：在流量最大的前提下，总费用最小
 * - 应用：物流、任务分配、二分图最优匹配
 * 
 * 【MCMF vs 最大流】
 * | 算法 | 目标 | 边属性 | 复杂度 |
 * |------|------|--------|--------|
 * | Dinic | 最大流 | 容量 | O(n²m) |
 * | MCMF | 最小费用最大流 | 容量+费用 | O(nmf) |
 * 
 * 【核心思想】
 * 1. 每次找最小费用的增广路（SPFA 最短路）
 * 2. 沿着这条路增广
 * 3. 重复直到没有增广路
 * 
 * 【为什么用 SPFA 而不是 Dijkstra？】
 * - 反向边的费用是负的，可能有负权边
 * - SPFA 可以处理负权边（但不能有负环）
 * - 如果保证没有负权边，可以用 Dijkstra（更快）
 * 
 * 【为什么反向边的费用是负的？】
 * 退流时要退回之前的费用：
 * - 正向边：流量 f，费用 f * cost
 * - 退流：减少正向边流量 f，相当于增加反向边流量 f
 * - 费用变化：-f * cost = f * (-cost)
 * 
 * 【复杂度分析】
 * - 单次 SPFA：O(nm)
 * - 增广次数：最多 f 次（f 为最大流）
 * - 总复杂度：O(nmf)
 * 
 * 实际表现：
 * - 如果流量小，很快
 * - 如果流量大，会很慢（可以用 Dinic + 费用流）
 * 
 * 【经典应用】
 * 
 * 1. **二分图最大权匹配**
 *    - 边权取负，转化为最小费用流
 *    - 最大权 = -最小费用
 * 
 * 2. **任务分配问题**
 *    - n 个人，m 个任务
 *    - 每个人做每个任务有费用
 *    - 求最小费用分配方案
 * 
 * 3. **物流运输**
 *    - 多个仓库、多个客户
 *    - 运输有成本
 *    - 求最小成本满足需求
 * 
 * 4. **K 短路**
 *    - 转化为最小费用流
 *    - 流量 = K，费用 = 路径长度
 * 
 * 【建图技巧】
 * 
 * 1. **拆点**
 *    - 点有容量限制：拆成两个点，中间连边（容量 = 限制）
 * 
 * 2. **多源多汇**
 *    - 超级源点连所有源点（容量 = 供应量，费用 = 0）
 *    - 所有汇点连超级汇点（容量 = 需求量，费用 = 0）
 * 
 * 3. **费用转化**
 *    - 最大权 → 最小费用：边权取负
 *    - 必须经过：设置高费用强制选择
 * 
 * 【常见变体】
 * 
 * 1. **最大费用最大流**
 *    - 所有边的费用取负
 *    - 答案再取负
 * 
 * 2. **固定流量的最小费用**
 *    - 限制最大流 ≤ K
 *    - 在 SPFA 中判断流量
 * 
 * 3. **上下界费用流**
 *    - 每条边流量 [L, R]
 *    - 转化为无下界问题
 * 
 * 【优化技巧】
 * 
 * 1. **势函数优化（Johnson 算法）**
 *    - 消除负权边，用 Dijkstra 代替 SPFA
 *    - 时间复杂度优化到 O(f * m * log n)
 * 
 * 2. **zkw 费用流**
 *    - 原始对偶算法
 *    - 实践中非常快
 * 
 * 3. **Dinic + 费用流**
 *    - 先用 Dinic 找最大流
 *    - 再优化费用
 * 
 * 【常见错误】
 * 1. 反向边费用忘记取负
 * 2. SPFA 忘记判断 cap > 0
 * 3. 增广时忘记更新反向边
 * 4. pre_v 和 pre_e 没有正确记录
 * 5. 费用溢出（用 ll）
 * 
 * 【调试技巧】
 * 1. 检查费用是否正确（打印每次增广的费用）
 * 2. 验证流量守恒
 * 3. 检查反向边费用是否为负
 * 4. 小数据手模增广过程
 * 
 * 【提交前检查】
 * ✓ 反向边费用为负
 * ✓ SPFA 判断 cap > 0
 * ✓ pre_v 和 pre_e 正确记录
 * ✓ 费用和流量用 ll
 * ✓ 数组大小足够
 * ✓ 源点和汇点不搞反
 * 
 * 【MCMF vs 其他算法】
 * 
 * | 问题 | 算法 | 复杂度 |
 * |------|------|--------|
 * | 二分图最大匹配 | 匈牙利 | O(nm) |
 * | 二分图最大权匹配 | KM | O(n³) |
 * | 二分图最大权匹配 | MCMF | O(nmf) |
 * | 任务分配 | 贪心 | O(n log n) |
 * | 任务分配（带约束）| MCMF | O(nmf) |
 * 
 * 【竞赛考察频率】
 * - NOI/省选：⭐⭐⭐⭐（网络流专题）
 * - ICPC/CCPC：⭐⭐⭐（区域赛及以上）
 * - Codeforces：⭐⭐（Div1 E/F）
 * 
 * 【推荐练习】
 * 1. 洛谷 P3381 - 最小费用最大流模板
 * 2. 洛谷 P4014 - 分配问题
 * 3. HDU 1533 - Going Home
 * 4. POJ 2195 - Going Home
 */
