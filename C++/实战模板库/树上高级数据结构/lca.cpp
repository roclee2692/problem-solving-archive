/*
 * 【LCA（最近公共祖先）】- 树上二分查找
 * 
 * 时间复杂度：O(n + q*log n) 使用二进制提升
 * 空间复杂度：O(n*log n)
 * 
 * 适用场景：
 *   - 树上路径长度
 *   - 两点距离
 *   - 树上位置判断
 *   - 比较节点的祖先关系
 * 
 * 模板题：
 *   - 洛谷 P3379 - 【模板】最近公共祖先（LCA）
 *   - Codeforces 519E - A and B and Lecture Rooms
 */

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const ll N=5e5+7;
const ll LOG=20;

vector<ll> adj[N];
ll up[N][LOG];
ll depth[N];
ll n,m,s;

void dfs(ll u,ll p){
    up[u][0]=p;
    for(int i=1;i<LOG;i++){ // 应该从 i=1 开始！
        up[u][i]=up[up[u][i-1]][i-1];
    }
    for(ll v:adj[u]){
        if(v!=p){  // 避免回到父节点
            depth[v]=depth[u]+1;
            dfs(v,u);
        }
    }
}

ll lca(ll u,ll v){
    if(depth[u]<depth[v]) swap(v,u);
    ll diff=depth[u]-depth[v];
    for(ll i=0;i<LOG;i++){
        if((diff>>i)&1){
            u=up[u][i];
        }
    }
    if(u==v) return u;
    for(ll i=LOG-1;i>=0;i--){
        if(up[u][i]!=up[v][i]){
            u=up[u][i];
            v=up[v][i];
        }
    }
    return up[u][0];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m>>s;
    for(ll i=0;i<n-1;i++){
        ll u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    depth[0]=-1;
    depth[s]=0;
    dfs(s,0);
     // ===== 处理 m 个 LCA 查询 =====
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";  // 输出 u 和 v 的最近公共祖先
    }
    return 0;
}
/*
 * 【关键点】
 * 1. up[i][j] 表：i 的第 2^j 个祖先（二进制跳跃）
 * 2. dfs 预处理：计算 depth 和 up 表
 * 3. lca 步骤一：对齐深度（用二进制表示差值）
 * 4. lca 步骤二：同时向上跳（不跳过LCA）
 * 5. 复杂度控制：LOG = 20（支持 2^20 > 1e6 个节点）
 * 
 * 【常见变体】
 * - 树链剖分（支持树上路径更新）
 * - 虚树（关键节点压缩）
 * - Tarjan 离线 LCA
 * 
 * 【提交前检查】
 * ✓ LOG 大小是否足够
 * ✓ up 表初始化是否完整
 * ✓ dfs 遍历是否正确（避免重复访问）
 * ✓ depth 计算是否正确
 */
