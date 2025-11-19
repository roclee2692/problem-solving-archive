/*
 * 【P1119 灾后重建】- 在线动态Floyd（空间优化）
 * 
 * 关键思路：
 * 1. 利用查询时间t不下降的性质
 * 2. 在线处理：逐步加入村庄，动态更新Floyd
 * 3. 只保存当前状态，节省空间
 * 
 * 时间复杂度：O(N^3)  空间复杂度：O(N^2)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int XN = 205;

int n, m, q;
int t[XN];  // 重建时间
ll dist[XN][XN];  // 当前状态下的最短路距离

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> t[i];
    }
    
    // 初始化距离矩阵
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }
    
    // 读入所有边并直接加入距离矩阵
    for(int i = 0; i < m; i++){
        int u, v;
        ll w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }
    
    cin >> q;
    int last_k = -1;  // 上次处理到的村庄编号
    
    while(q--){
        int x, y, query_t;
        cin >> x >> y >> query_t;
        
        // 找到在时间query_t能重建完成的最后一个村庄
        int k = -1;
        for(int i = 0; i < n; i++){
            if(t[i] <= query_t){
                k = i;
            } else {
                break;
            }
        }
        
        // 检查x和y是否都已重建完成
        if(k < x || k < y){
            cout << -1 << '\n';
            continue;
        }
        
        // 用村庄last_k+1到k作为中间点更新Floyd
        for(int mid = last_k + 1; mid <= k; mid++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(dist[i][mid] != INF && dist[mid][j] != INF){
                        dist[i][j] = min(dist[i][j], dist[i][mid] + dist[mid][j]);
                    }
                }
            }
        }
        last_k = k;
        
        ll ans = dist[x][y];
        if(ans >= INF){
            cout << -1 << '\n';
        } else {
            cout << ans << '\n';
        }
    }
    
    return 0;
}

/*
 * 【关键修正】
 * 1. 所有边一开始就加入距离矩阵（不是按需加入）
 * 2. Floyd算法：逐步允许更多村庄作为中间点
 * 3. 利用查询时间单调性，增量更新
 * 
 * 【核心思想】
 * - 边的存在与村庄重建无关，路径的可达性才与重建有关
 * - 通过控制Floyd的中间点来控制路径可达性
 */