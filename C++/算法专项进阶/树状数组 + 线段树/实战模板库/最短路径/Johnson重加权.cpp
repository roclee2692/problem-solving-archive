/*
 * 【Johnson 算法】- 多源最短路径（支持负权边）
 * 
 * 时间复杂度：O(V*E + V^2*log V) ≈ O(VE + V^2*log V)
 * 空间复杂度：O(V^2)
 * 
 * 适用场景：
 *   - 稀疏图多源最短路
 *   - 支持负权边（无负环）
 *   - n 不超过 500
 * 
 * 模板题：洛谷 P1119 - 灾后重建
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=(ll)1e18;
using pll=pair<ll,ll>;
const int XN=1e3+7;
int n,m;
vector<pll> adj[XN];
ll dist[XN][XN];
ll h[XN];
bool bellmanFord(){
    vector<ll> d(n+2,INF);
    d[0]=0;
    for(int i=1;i<=n;i++){  // ✅ 修正：应该到n，不是n-1
        adj[0].push_back({i,0});
    }
    for(int i=0;i<n;i++){
        for(int u=0;u<=n;u++){
            for(auto [v,w]:adj[u]){
                if(d[u]!=INF && d[u]+w<d[v]){
                    d[v]=d[u]+w;
                }
            }
        }
    }
        for(int u=0;u<=n;u++){
            for(auto [v,w]:adj[u]){
                if(d[u]!=INF && d[u]+w<d[v]){
                    return 0;
                }
            }
        }
        for(int i=1;i<=n;i++) h[i]=d[i];  // ✅ 修正：只赋值1到n
    return 1;
}

void dijkstra(int src){  // ✅ 修正：去掉默认参数和多余参数
    priority_queue< pll,vector<pll>,greater<pll> > pq;
    vector<ll> d(n+1,INF);
    d[src]=0;
    pq.emplace(0,src);
    while(!pq.empty()){
        auto [du,u]=pq.top(); pq.pop();
        if(du>d[u]) continue;
        for(auto [v,w]:adj[u]){
            if(d[u]+w<d[v]){
                //既有 d[u]-d[v]+w>=0
                //将其作为新的边权
                // 转化边权：w' = w + h[u] - h[v]
                ll w=w+h[u]-h[v];//不用nw 直接写w 对吗？✅ 技术可行性：每次循环w都会重新赋值
                d[v]=d[u]+w;
                pq.emplace(d[v],v);
                // 循环结束，局部变量w被销毁
                // 下一次循环，又创建新的解构变量w
            }
        }
    }
    for(int i=1;i<=n;i++) {  // ✅ 修正：从1到n，不包括虚拟点0
        dist[src][i]=(d[i]==INF?INF:d[i]+h[i]-h[src]);
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v;ll w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    
    if(!bellmanFord()){
        cout<<"YES\n";  // 存在负环
        return 0;
    }
    
    for(int i=1;i<=n;i++) dijkstra(i);
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<(dist[i][j]==INF?-1:dist[i][j]);
            if(j<n) cout<<' ';
        }
        cout<<'\n';
    }
    
    return 0;
}
/*
 * 【关键点】
 * 1. 第一步：使用 Bellman-Ford 计算势函数 h[]
 * 2. 第二步：对每个源点使用 Dijkstra（用势函数重新标号）
 * 3. 转化公式：w' = w + h[u] - h[v]（保证非负）
 * 4. 最终距离需要转化回原始值：dist = d + h[v] - h[src]
 * 
 * 【原理】
 * - Bellman-Ford 检测负环并计算势函数
 * - 势函数使得所有边权变非负
 * - 再用 Dijkstra 计算最短路
 * 
 * 【注意事项】
 * - [ ] 虚拟源点 0 必须连向所有点，权重为 0
 * - [ ] 势函数转化公式不能错
 * - [ ] 最终距离转化时 h[src] 的符号
 * - [ ] 检查是否存在负环（返回）
 * - [ ] adj[0] 在 Bellman-Ford 中才添加（避免重复）
 * - [ ] 时间复杂度：O(VE + V^2 log V)，适合稀疏图
 */