#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;
int N,M;
vector<int> S,E,T;
int main(){
ios::sync_with_stdio(0);cin.tie(0);
cin>>N>>M;
//N为点数 里程碑 起点加终点 M为边数 从S到E为一个任务
using P=pair<int,int>;
using VP=vector<P>;
using V=vector<int>;
vector<VP> adj(N); // 邻接表
V inDeg(N,0); // 入度数组
V dist(N,0); // 最早完成时间
for(int i=0;i<M;i++){
    int u,v,w;
    cin>>u>>v>>w;
    adj[u].emplace_back(v,w);
    //直接在容器尾部构造对象，省去一次拷贝或移动
    inDeg[v]++;//入度是被指向的那一个
}
    queue<int> q;
    for(int i=0;i<N;i++) if(inDeg[i]==0) q.push(i);
    int visited=0;
    while(!q.empty()){
        int u=q.front(); q.pop();//队列不是栈 没有top()
        visited++;
        for(auto &edge:adj[u]){
            int v=edge.first,w=edge.second;
            dist[v]=max(dist[v],dist[u]+w);
            //取从u到v 所有任务中 耗时最久的一项 
      //比较看看是之前的路径耗时久还是目前的dist u + w 耗时久
            if(--inDeg[v]==0) q.push(v);
        }
    }
    visited<N?cout<<  "Impossible\n":cout  <<  *max_element(dist.begin(),dist.end())<<'\n'  ;
    //最后输出建议加换行符（防止有的平台评测卡最后一个输出格式）
  return 0;
}
