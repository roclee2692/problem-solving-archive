/*
 * 【Tarjan 算法】- 求强连通分量（SCC）
 * 
 * 时间复杂度：O(n + m)
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 求强连通分量
 *   - 缩点成 DAG
 *   - 2-SAT 问题
 * 
 * 模板题：
 *   - 洛谷 P3387 - 【模板】缩点
 *   - Codeforces 1109D - Sasha and His Friend
 */

#include <bits/stdc++.h>
using namespace std;

const int XN = 1e5 + 5;
using ll=long long;
int n, m;
vector<int> adj[XN];
ll dfn[XN],low[XN];
bool in_st[XN];
ll stk[XN],top;
ll timestamp;
ll scc_cnt;
ll scc_id[XN];

void tarjan(int u){
    dfn[u]=low[u]=++timestamp;
    stk[++top]=u;
    in_st[u]=1;
    for(ll v:adj[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(in_st[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        scc_cnt++;
        ll v;
        do{
            v=stk[top--];
            in_st[v]=0;
            scc_id[v]=scc_cnt;
        }while(v!=u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    
    // 对所有未访问的点执行 Tarjan
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }
    
    cout << "SCC 个数: " << scc_cnt << "\n";
    
    for (int i = 1; i <= n; i++) {
        cout << "节点 " << i << " 属于 SCC " << scc_id[i] << "\n";
    }
    
    return 0;
}

/*
 * 【核心思想】
 * dfn[u]: u 第一次被访问的时间
 * low[u]: u 能够回溯到的最早的栈中节点的时间
 * 
 * 如果 dfn[u] == low[u]，说明 u 无法回溯到更早的节点，u 是 SCC 的根
 * 
 * 【三种边】
 * 1. 树边：v 未访问 → 递归访问，用 low[v] 更新 low[u]
 * 2. 回边：v 在栈中 → v 是祖先，用 dfn[v] 更新 low[u]
 * 3. 横叉边：v 已访问但不在栈中 → v 在另一个 SCC，不更新
 * 
 * 【为什么回边用 dfn[v] 而不是 low[v]？】
 * 因为 v 在栈中，v 的 low 可能还会被后续更新
 * 我们要的是 v 本身的时间戳，不是 v 子树能到达的最小时间戳
 */
