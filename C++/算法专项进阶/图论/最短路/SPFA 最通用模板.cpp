#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
const int INF = INT_MAX;
int n,m;
vector<vector<pii>> adj;
vector<int> dist, cnt;// dist: 最短距离；cnt: 入队次数
vector<int> inq; // inq[u] 标记 u 是否在队列中
void init(int N){
    n=N;
    adj.assign(n, vector<pii>());
    dist.assign(n,INF);//若输入是 1-base，需n+1;
    cnt.assign(n,0);
    inq.assign(n,0);//把所有容器都开成 n+1 大小，直接用 1…n 编号，无需每次 --u;--v;：
}
void addEdge(int u,int v,int w){
    adj[u].emplace_back(v,w);// 加边（有向图）
}
// SPFA 主函数
// 返回 false 表示检测到负权环；true 表示成功
bool spfa(int src){
    queue<int> q;
    dist[src]=0;
    inq[src]=1;
    q.push(src);
    cnt[src]=1;
    while(!q.empty()){
        int u=q.front(); q.pop();
        inq[u]=0;
        for(auto &x:adj[u]){
            int v=x.first;
            int w=x.second;
            if(dist[u]!=INF &&dist[u]+w<dist[v]){//松弛判断写反 应 if(dist[u]!=INF && dist[u]+w<dist[v])。
                dist[v]=dist[u]+w;
                if(!inq[v]){
                    q.push(v);
                    inq[v]=1;
                    cnt[v]++;
                    if(cnt[v]>n) return false;
                }
            }
        }
    }
    return true;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
      init(n);//没调用 init(n)，导致 adj、dist 等未初始化。
    int u,v,w;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        addEdge(u,v,w);
    }
    bool ok=spfa(0);
    if(ok==0){
          cout << "Negative cycle detected\n";
    }else{
        for(int i=0;i<n;i++){
           cout << (dist[i] == INF ? -1 : dist[i]) << ' ';
        }
    }
}