/*二分图最大匹配
二分图（Bipartite Graph）是一个图，它的节点可以分成两组：

一组是左侧集合（这里是正驾驶员）。

一组是右侧集合（这里是副驾驶员）。

所有边只连接左侧点和右侧点，没有边连接同一侧的点。
匈牙利算法的核心思想
1?? 基本逻辑
我们要找一组匹配，让最多的正驾驶员能有副驾驶员搭档。

先随便找一些匹配，然后看看能不能调整位置，腾出空间给新的匹配（增广路径）。

2?? 增广路径
对于左侧的一个节点（正驾驶员），尝试“占领”一个右侧节点（副驾驶员）。

如果副驾驶员还没被匹配（空闲），就直接配对。

如果副驾驶员已经有配对了，就尝试从他的配对链上“腾位置”。

这就是经典的“DFS 回溯+替换法”：

python
复制
编辑
正驾驶员 u 想配对副驾驶员 v
如果 v 空闲 -> 匹配成功
如果 v 已被别的 u' 占了，就看 u' 能不能腾出别的副驾驶员给自己。*/
#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<int> adj[110],match(110),vis(110);
//邻接表 每个行容器动态push_back 分配内存不会怕几千行匹配的情况
//match vis 只是用来记录最大能匹配的对数 不可能超过一百

bool dfs(int u){//u v 
    for( int v:adj[u] ){//遍历邻接表
        if(vis[v]) continue;
        vis[v]=1;
        if( !match[v]||dfs(match[v]) ){
            //如果该点未匹配 则直接匹配成功 若已经匹配则 根据右找左 
            //递归dfs遍历左点的邻接表 看看有没有还能匹配的 如有匹配成功
            match [v] =u;
            return true;
        }
    }
    return false;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    int v,u;
    while(cin>>u>>v){
        adj[u].push_back(v);
    }
    int ans=0;
    for(int u=1;u<=m;u++){// 枚举左侧所有节点
        vis.assign(110,0);//对每个左点依次进行dfs前 每次都要重置vis数组
        if( dfs(u) ) ans++;  // 如果找到增广路，匹配数+1
    }
    cout<<ans<<'\n';
    return 0;
}