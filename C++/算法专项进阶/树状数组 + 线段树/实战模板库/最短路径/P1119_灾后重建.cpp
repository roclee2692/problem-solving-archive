/*
 * 【P1119 灾后重建】- 动态Floyd最短路
 * 
 * 关键思路：
 * 1. 村庄按重建时间排序：t[0] <= t[1] <= ... <= t[n-1]
 * 2. 预处理：对每个k，计算只使用村庄0~k时的最短路
 * 3. 查询时二分查找最后一个重建完成的村庄
 * 
 * 时间复杂度：O(N^3 + Q*log N)
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int XN = 205;

int n, m, q;
int t[XN];  // 重建时间
ll dist[XN][XN][XN];  // dist[k][i][j] = 只使用村庄0~k时，i到j的最短路

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> t[i];
    }
    
    // 初始化：所有状态下距离都是INF，除了自己到自己
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == j) dist[k][i][j] = 0;
                else dist[k][i][j] = INF;
            }
        }
    }
    
    // 读入边
    for(int i = 0; i < m; i++){
        int u, v;
        ll w;
        cin >> u >> v >> w;
        // 初始边只在两个端点都存在时才有效
        for(int k = max(u, v); k < n; k++){
            dist[k][u][v] = min(dist[k][u][v], w);
            dist[k][v][u] = min(dist[k][v][u], w);
        }
    }
    
    // 动态Floyd：逐步加入村庄0, 1, 2, ..., k
    for(int k = 0; k < n; k++){
        // 继承上一状态的结果
        if(k > 0){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    dist[k][i][j] = dist[k-1][i][j];
                }
            }
        }
        
        // 加入村庄k作为中间点
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dist[k][i][k] != INF && dist[k][k][j] != INF){
                    dist[k][i][j] = min(dist[k][i][j], dist[k][i][k] + dist[k][k][j]);
                }
            }
        }
    }
    
    cin >> q;
    while(q--){
        int x, y, query_t;
        cin >> x >> y >> query_t;
        
        // 找到在时间query_t能重建完成的最后一个村庄
        int last_village = -1;
        for(int i = 0; i < n; i++){
            if(t[i] <= query_t){
                last_village = i;
            } else {
                break;
            }
        }
        
        // 检查x和y是否都已重建完成
        if(last_village < x || last_village < y){
            cout << -1 << '\n';
            continue;
        }
        
        ll ans = dist[last_village][x][y];
        if(ans >= INF){
            cout << -1 << '\n';
        } else {
            cout << ans << '\n';
        }
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. dist[k][i][j] 表示只使用村庄0~k时，i到j的最短路
 * 2. 边(u,v)只在max(u,v)及以后的状态中存在
 * 3. 查询时找最后一个重建完成的村庄编号
 * 4. 检查起点终点是否都已重建
 * 
 * 【空间优化版本】
 * - 由于查询t不下降，可以在线处理，只保存当前状态
 * - 但预处理版本更稳定，避免实现错误
 */