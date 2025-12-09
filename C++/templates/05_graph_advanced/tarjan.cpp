/*
 * 【Tarjan 算法】- 求强连通分量（SCC）
 * 
 * 时间复杂度：O(n + m)
 * 空间复杂度：O(n + m)
 * 
 * 适用场景：
 *   - 求强连通分量
 *   - 缩点成 DAG（求 SCC 个数的题目）
 *   - 2-SAT 问题（特殊情况）
 *   - 图的连通性分析
 * 
 * 模板题：
 *   - 洛谷 P3387 - 【模板】缩点
 *   - Codeforces 1109D - Sasha and His Friend
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

struct Tarjan {
    int n;
    vector<int> adj[MAXN];
    
    // 【WHY we need dfn[]?】
    // dfn[u] = discovery time of node u (when we first visit it)
    // Used to identify if a node has been visited and distinguish different types of edges
    int dfn[MAXN];
    
    // 【WHY we need low[]?】
    // low[u] = the smallest dfn value that u or its descendants can reach via tree edges or back edges
    // If low[u] == dfn[u], it means u cannot reach any ancestor → u is the root of an SCC
    int low[MAXN];
    
    // 【WHY we need in_stack[]?】
    // To distinguish between back edges (pointing to nodes in stack) and cross edges
    // Cross edges point to nodes in other SCCs that have already been processed
    // Only back edges can help us find SCCs
    bool in_stack[MAXN];
    
    // 【WHY we need a stack?】
    // The stack stores all nodes in the current DFS path
    // When we find an SCC root (dfn[u] == low[u]), we pop all nodes from stack until u
    // These popped nodes form one SCC
    stack<int> st;
    
    int timestamp = 0;      // Global timer for dfn values
    int scc_count = 0;      // Number of SCCs found
    vector<int> scc_id;     // scc_id[u] = which SCC node u belongs to
    
    Tarjan(int n) : n(n), scc_id(n + 1) {}
    
    void dfs(int u) {
        // 【WHY initialize both dfn[u] and low[u] to timestamp?】
        // - dfn[u] records when we discovered u
        // - low[u] starts with dfn[u] and will be updated if we find a path to an earlier node
        dfn[u] = low[u] = ++timestamp;
        
        // 【WHY push u onto stack?】
        // u might be part of an SCC that we haven't fully discovered yet
        // We keep it in the stack until we determine which SCC it belongs to
        st.push(u);
        in_stack[u] = true;
        
        // Explore all edges from u
        for (int v : adj[u]) {
            if (!dfn[v]) {
                // 【Case 1: Tree Edge - v not visited yet】
                // WHY recurse? We need to explore the subtree rooted at v
                dfs(v);
                
                // 【WHY update low[u] with low[v]?】
                // If v's subtree can reach an earlier node, then u can also reach it (through v)
                // This propagates reachability information up the DFS tree
                low[u] = min(low[u], low[v]);
                
            } else if (in_stack[v]) {
                // 【Case 2: Back Edge - v is an ancestor in current DFS path】
                // WHY check in_stack[v]? To distinguish from cross edges
                // Cross edges point to nodes in already-completed SCCs (not in stack)
                
                // 【WHY update low[u] with dfn[v] (not low[v])?】
                // Because v is an ancestor, we can directly reach v
                // Using dfn[v] is more precise - it's the actual discovery time of v
                // Using low[v] would be incorrect because v might have been updated by other paths
                low[u] = min(low[u], dfn[v]);
            }
            // 【Case 3: Cross Edge - v visited but not in stack】
            // WHY do nothing? v is in a different SCC that's already been identified
            // Cross edges don't affect the current SCC we're forming
        }
        
        // 【WHY check if dfn[u] == low[u]?】
        // This means u cannot reach any node with earlier discovery time
        // Therefore, u is the "root" of an SCC (the first node discovered in this SCC)
        // All nodes from u to stack top form one SCC
        if (dfn[u] == low[u]) {
            scc_count++;
            
            // 【WHY pop until we reach u?】
            // All nodes pushed after u (with later dfn values) that couldn't escape
            // back to earlier nodes belong to the same SCC as u
            while (true) {
                int v = st.top();
                st.pop();
                in_stack[v] = false;
                scc_id[v] = scc_count;
                if (v == u) break;
            }
        }
    }
    
    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs(i);
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    Tarjan tarjan(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        tarjan.adj[u].push_back(v);
    }
    
    tarjan.solve();
    
    cout << "SCC 个数: " << tarjan.scc_count << "\n";
    
    for (int i = 1; i <= n; i++) {
        cout << "节点 " << i << " 属于 SCC " << tarjan.scc_id[i] << "\n";
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. dfn[u]：u 的发现时间戳
 * 2. low[u]：u 及其子树能到达的最小时间戳
 * 3. dfn[u] == low[u]：u 是某个 SCC 的根
 * 4. 栈用途：存储当前 DFS 路径上的节点
 * 5. in_stack[]：判断边是否是回边（指向栈中节点）
 * 
 * 【关键性质】
 * - 回边：v 在栈中且未被弹出
 * - 前向边/横边：不影响 low 值（或者说 dfn[v] > dfn[u]）
 * 
 * 【常见变体】
 * - Kosaraju 算法（两次 DFS）
 * - 2-SAT（Tarjan 特化版本）
 * - 缩点后的 DAG
 * 
 * 【提交前检查】
 * ✓ dfn 数组初值为 0（未访问）
 * ✓ low 初始化为 dfn[u]
 * ✓ 栈操作的一致性
 * ✓ SCC 根节点识别
 */
