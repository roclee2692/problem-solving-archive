#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=LLONG_MAX;

struct Edge{
    ll u,v,w;
    Edge(ll u1,ll v1,ll w1):u(u1),v(v1),w(w1){}
    };
    // 全局容器
    int n,m,src;
    vector<Edge> edges;
    vector<ll> dist;
    // Bellman–Ford 算法
// 返回 false 表示存在负环；true 表示无负环且已计算最短路
bool bellman_ford(){
    dist.assign(n,INF);
    dist[src]=0;
     // n-1 轮松弛
     for(int i=0;i<n;i++){
        bool updated=0;
        for(auto &e:edges ){
            if(dist[e.u]!=INF&&dist[e.u]+e.w<dist[e.v]){
                dist[e.v]=dist[e.u]+e.w;
                updated=1;
            }
        }
        if(updated==0) break;
     }
         // 检测负环
         for(auto &e:edges){
            if(dist[e.u]!=INF&&dist[e.u]+e.w<dist[e.v]){
                return false;
                }
    }
    return true;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>> m >>src;// 输入 顶点数 n，边数 m，源点 src
 // 若输入 1-base，执行 src--; 否则保持 0-base
    // src--;
    edges.reserve(m);
    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
         // 若输入 1-base，执行 u--, v--;
        // u--; v--;
        edges.emplace_back(u,v,w);
    }
    bool ok=bellman_ford();
    if(ok==0) cout<<"Negative cycle detected\n";
    else {
        for(auto &x:dist){
            cout<<(x==INF?INF:x)<<'\n';
        }
    }
    return 0;

}