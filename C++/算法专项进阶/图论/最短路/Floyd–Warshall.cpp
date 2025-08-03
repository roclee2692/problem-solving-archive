#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=LLONG_MAX;
int main(){
ios::sync_with_stdio(0);cin.tie(0);
ll n,m;
cin>>n>>m;
 // 初始化邻接矩阵
 vector<vector<ll>> dist(n+1,vector<ll>(n+1,INF) );
 for(int i=0;i<n+1;i++) dist[i][i]=0;//0~n  初始化对角时也要从 0 到 n：
  // 读边：有向图或无向按题意
  while(m--){
    ll u,v,w;
    cin>>u>>v>>w;
    dist[u][v]=min(dist[u][v],w);
     // 若无向： dist[v][u]=min(dist[v][u],w);
  }
  /*适用：

n≤400~800、图较稠密、要回答大量任意两点最短路/可达性查询。

需要做传递闭包/最小瓶颈路/最大最小边等可用“三重循环改一行转移”的变形。

题目数据离线、一次跑完即可多次查询。*/
     // Floyd–Warshall 三重循环
      for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i)
            if(dist[i][k] != INF)
                for(int j = 1; j <= n; ++j)
                    if(dist[k][j]!=INF)
                        dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
    //所有对 (i,j) 的最短路距离
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }
  return 0;
}
