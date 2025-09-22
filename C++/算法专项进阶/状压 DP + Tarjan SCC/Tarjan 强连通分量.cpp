#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
const ll INF = (ll)4e18;      // 无穷大值
const int N  = 1e5+5; 
vector<ll> adj[N];// 邻接表存图
ll dfn[N],low[N];// 时间戳和low数组
bool in_stack[N];
stack<ll> s;
ll timestamp=0;
ll ans=0; // 最终答案：大小 > 1 的 SCC 个数

void tarjan(ll u){
    // 1. 初始化
    dfn[u] = low[u] = ++timestamp;
    s.push(u);
    in_stack[u] = true;
    // 2. 遍历邻居
    for (int v : adj[u]) {
        if (dfn[v] == 0) { // v 未被访问，是树边
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) { // v 已被访问且在栈中，是返祖边或横叉边
            low[u] = min(low[u], dfn[v]);
        }
    }
    // 3. 找到一个 SCC 的根节点
    if (dfn[u] == low[u]) {
        int current_scc_size = 0;
        while (true) {
            int node = s.top();
            s.pop();
            in_stack[node] = false;
            current_scc_size++; // 统计当前 SCC 的大小
            if (node == u) break;
        }
        
        // 4. 根据题目要求进行统计
        if (current_scc_size > 1) {
            ans++;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N,M;
    cin>>N>>M;
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);//存储出度的边
    }
    // Tarjan 算法主循环，确保能处理不连通的图
    for (int i = 1; i <= N; ++i) {
        if (dfn[i] == 0) { // 如果节点 i 还未被访问过
            tarjan(i);
        }
    }
    cout << ans << endl;
    return 0;
}