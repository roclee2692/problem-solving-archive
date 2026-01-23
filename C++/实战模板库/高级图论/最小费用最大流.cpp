#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int XN=5005;
const int XM=1e5+5;
const ll INF=1e18;
struct Edge{
    int to;
    ll cap;
    ll cost;
    int rev;
};
vector<Edge> adj[XN];
int n,m,s,t;
ll dis[XN];
int pre_v[XN];
int pre_e[XN];
bool inq[XN];

void add_edge(int from,int to,ll cap,ll cost){
    adj[from].push_back({to,cap,cost,(int)adj[to].size()});//正向to未有 从0开始记录索引为0
    adj[to].push_back({from,0,-cost,(int)adj[from].size()-1});//反向from已有 我们要索引 1-1=0
}
bool spfa(){
    fill(dis,dis+n+1,INF);//数组前缀直接作为地址
    fill(inq,inq+n+1,0);
    queue<int> q;
    q.push(s);
    dis[s]=0;
    inq[s]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        inq[u]=0;
        for(int i=0;i<adj[u].size();i++){
            Edge &e=adj[u][i];
            if(e.cap>0 && dis[e.to]>dis[u]+e.cost){
                dis[e.to]=dis[u]+e.cost;
                pre_v[e.to]=u;
                pre_e[e.to]=i;
                if(!inq[e.to]){
                    q.push(e.to);
                    inq[e.to]=true;
                }
            }
        }
    }
    return dis[t]!=INF;
}
pair<ll,ll> mcmf(){
    ll max_flow=0,min_cost=0;
    while(spfa()){
        ll flow=INF;
        for(int v=t;v!=s;v=pre_v[v]){
            flow=min(flow,adj[pre_v[v]][pre_e[v]].cap);
        }
        max_flow+=flow;
        min_cost+=flow*dis[t];
        for(int v=t;v!=s;v=pre_v[v]){
            Edge &e=adj[pre_v[v]][pre_e[v]];
            e.cap-=flow;
            adj[v][e.rev].cap+=flow;
        }
    }
    return {max_flow,min_cost};
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>s>>t;
    for(int i=0;i<m;i++){
        int u,v;
        ll cap,cost;
        cin>>u>>v>>cap>>cost;
        add_edge(u,v,cap,cost);
    }
    auto [flow,cost]=mcmf();
    cout<<flow<<" "<<cost<<"\n";
    return 0;
}
/*这段代码实现的是 **最小费用最大流 (Min-Cost Max-Flow, MCMF)** 算法。

这也是一个经典的模板，用一句话概括它的核心思想就是：**在保证能流过去的前提下，每次都挑最便宜的那条路走，直到没路可走。**

它和 Dinic 的区别在于：

* **Dinic (最大流)**：只在乎“快”，每次 BFS 按距离分层，只走“短”路。
* **MCMF (费用流)**：在乎“钱”，每次 SPFA 按费用找路，只走“便宜”的路。

这段代码使用的是 **基于 SPFA 的 EK (Edmonds-Karp) 增广路算法**。你可以把它看作是“魔改版”的 EK 算法。

---

### 1. 结构体与建边 (`Edge` & `add_edge`)

```cpp
struct Edge{
    int to;
    ll cap;  // 容量
    ll cost; // 单价（流过 1 单位流量花的钱）
    int rev; // 反向边索引
};

void add_edge(int from,int to,ll cap,ll cost){
    // 正向边：容量 cap，费用 cost
    adj[from].push_back({to,cap,cost,(int)adj[to].size()});
    // 反向边：容量 0，费用 -cost 【关键！】
    adj[to].push_back({from,0,-cost,(int)adj[from].size()-1});
}

```

**用人话讲：**

* **正向边**：你去买东西，花钱（`cost` 是正的）。
* **反向边**：你后悔了，退货，商家要把钱退给你（`cost` 是负的）。
* 这就是为什么要 `-cost`。当我们“退流”（走反向边）时，不仅要把流量拿回来，还要把之前算的费用减掉。

---

### 2. 寻路导航 (`spfa`)

这是核心中的核心。在 Dinic 里这里是 BFS，但在费用流里，这里变成了 **SPFA**（或者 Bellman-Ford）。

**为什么不用 Dijkstra？**
因为图里有 **负权边**（反向边的费用是负的）。Dijkstra 处理不了负权边，所以只能用 SPFA。

```cpp
bool spfa(){
    // ... 初始化距离为无穷大 ...
    // ... 标准 SPFA 模板 ...
    while(!q.empty()){
        int u=q.front(); q.pop(); inq[u]=0;
        for(int i=0;i<adj[u].size();i++){
            Edge &e=adj[u][i];
            // 只有还有剩余容量(cap>0)的路才能走
            // 松弛操作：如果你这里的花费比已知的更便宜，就更新
            if(e.cap>0 && dis[e.to]>dis[u]+e.cost){
                dis[e.to]=dis[u]+e.cost;
                // 【记录路径】你是从哪个点(u)、哪条边(i)走过来的？
                pre_v[e.to]=u;
                pre_e[e.to]=i;
                if(!inq[e.to]){ ... }
            }
        }
    }
    // 如果 dis[t] 还是无穷大，说明走不到汇点 t 了，结束
    return dis[t]!=INF;
}

```

**用人话讲：**

* **任务**：在残量网络里，找到一条从  到  的路径。
* **要求**：这条路径的总费用（`cost` 之和）必须是所有可行路径里 **最小的**。
* **面包屑导航**：`pre_v` 和 `pre_e` 就像在森林里撒面包屑。因为 SPFA 只是找路，它跑完之后，我们需要顺着面包屑从  倒着找回 ，才能知道刚才到底走了哪条路。

---

### 3. 总指挥 (`mcmf`)

有了导航找到的最便宜路径，现在开始运货。

```cpp
pair<ll,ll> mcmf(){
    ll max_flow=0,min_cost=0;
    // 只要导航还能找到路（能流过去），就一直循环
    while(spfa()){
        ll flow=INF;
        // 第一步：回溯路径，算出这条路上的瓶颈（最小容量）
        for(int v=t;v!=s;v=pre_v[v]){
            flow=min(flow,adj[pre_v[v]][pre_e[v]].cap);
        }
        
        // 第二步：累加流量和费用
        max_flow+=flow;
        min_cost+=flow*dis[t]; // 费用 = 流量 * 单价和
        
        // 第三步：真正扣除容量（正向减，反向加）
        for(int v=t;v!=s;v=pre_v[v]){
            Edge &e=adj[pre_v[v]][pre_e[v]]; // 找到正向边
            e.cap-=flow;                     // 正向容量减少
            adj[v][e.rev].cap+=flow;         // 反向容量增加（给后悔留后路）
        }
    }
    return {max_flow,min_cost};
}

```

**用人话讲：**
这是一个“贪心”的过程：

1. **问导航**：“现在去终点最便宜的路是哪条？”
2. **导航说**：“走 A->C->D->T，单价是 5 块。”
3. **计算瓶颈**：检查这条路上最细的水管能流多少水（假设是 10 吨）。
4. **发货**：运送 10 吨水。总费用增加  块。
5. **更新地图**：把这条路上的容量扣掉。如果某段路满了，下次导航就不会再选它了（或者只能走反向边退流）。
6. **重复**：回到第 1 步，直到导航说“没路了”。

---

### 总结与对比

你可能会问：**“这代码和 Dinic 怎么不像呢？没有 DFS 呀？”**

是的，这是两种不同的流派：

1. **Dinic 写法（多路增广）**：
* BFS 分层。
* DFS 一次性找**很多条**路把这层填满。
* **优点**：对于最大流问题，非常快。
* **缺点**：在费用流里，为了保证“最便宜”，DFS 不能乱跑，必须严格沿着最短路跑，实现起来比较麻烦（叫 ZKW 费用流）。


2. **EK-SPFA 写法（单路增广，就是你这段代码）**：
* SPFA 找**一条**最便宜的路。
* `mcmf` 函数沿着这条路推流。
* 然后再找下一条。
* **优点**：代码简单，逻辑清晰（找一条路 -> 推流 -> 再找一条）。
* **缺点**：理论复杂度比 Dinic 高，但在费用流问题中，因为每次只找一条路，通常跑得也不慢，完全够用。



**一句话总结这段代码：**
这是一个**基于 SPFA 寻找最短路（最小费用路）的单路增广算法**。它不做多路同时增广，而是“一次只做一单生意”，每单生意都挑当前最赚（费用最低）的做。*/