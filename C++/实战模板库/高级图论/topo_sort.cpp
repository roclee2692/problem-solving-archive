/*
 * 【拓扑排序】- 有向无环图的线性排序
 * 
 * 时间复杂度：O(n + m) Kahn 算法
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 检测有向环
 *   - DAG 上的动态规划
 *   - 任务调度（有依赖关系）
 *   - 编译顺序
 * 
 * 模板题：
 *   - 洛谷 P1113 - 杰森的困境(拓扑排序)
 *   - Codeforces 1385F - Red-Blue Graph
 */

#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int XN=1e5+5;
int n,m;
ll in_deg[XN];
vector<ll> adj[XN];
vector<ll> topo;

ll Kahn(){
    queue<ll> q;
    for(int i=1;i<=n;i++){
        if(in_deg[i]==0){ q.push(i); }
    }
    topo.clear();
    while(!q.empty()){
        ll u=q.front(); q.pop();
        topo.push_back(u);
        for(auto v:adj[u]){
            in_deg[v]--;
            if(in_deg[v]==0) q.push(v);
        }
    }
    return topo.size()==n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_deg[v]++;
    }
    
    if (!Kahn()) {
        cout << "有环\n";
        return 0;
    }
    
    // 输出拓扑序
    for (int x : topo) {
        cout << x << " ";
    }
    cout << "\n";
    
    return 0;
}

/*
 * 【关键点】
 * 1. 入度：每个节点的前驱节点数
 * 2. 初始化：入度为 0 的节点入队
 * 3. 处理：弹出节点，更新其后继入度
 * 4. 有环检测：最后排序大小 != n
 * 5. 多个排序解：不同的初始化顺序产生不同结果
 * 
 * 【常见变体】
 * - DFS 版本拓扑排序
 * - 字典序最小的拓扑排序（优先队列）
 * - 拓扑排序 + 动态规划
 * 
 * 【提交前检查】
 * ✓ 入度数组是否正确计算
 * ✓ 有环检测逻辑
 * ✓ 输出大小验证
 * ✓ 图的表示（邻接表）
 */
