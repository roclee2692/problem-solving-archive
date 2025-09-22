#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int M=1e5+5;
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