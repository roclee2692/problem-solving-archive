#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
const ll INF = (ll)1e18;
int n, m, src;
vector<vector<pll>> adj;
vector<ll> dist01;

// 0–1 BFS：边权仅 0 或 1
void zeroOneBFS(){
    deque<ll> dq;
    dist01.assign(n+1,INF);
    dist01[src]=0;
    dq.push_front(src);
    while(!dq.empty()){
        ll u=dq.front();dq.pop_front();
        for(auto &pr:adj[u]){
            int v = pr.first, w = pr.second;
                if(dist01[u]+w<dist01[v]){
                    dist01[v]=dist01[u]+w;
                    if(w==0) dq.push_front(v);
                    else dq.push_back(v);
                 }
            }
        }
    }
    
int main(){
ios::sync_with_stdio(0);cin.tie(0);
   // 输入：顶点数 n，边数 m，源点 src
    cin >> n >> m >> src;
    adj.assign(n+1, vector<pll>());
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;     // 0 ≤ w ≤ 1
        adj[u].emplace_back(v, w);
        // 若无向图可加： adj[v].emplace_back(u, w);
    }
      zeroOneBFS();

    // 输出 dist01[1..n]
    for (int i = 1; i <= n; ++i) {
        if (dist01[i] == INF) cout << "-1 ";
        else                  cout << dist01[i] << ' ';
    }
    cout << "\n";
  return 0;
}
