/*
 * 归程问题 - Kruskal重构树解法
 * 
 * 问题描述：
 * 给定一个带权无向图，每条边有长度l和海拔高度a。
 * 多次查询：从节点v出发，只能经过海拔高度大于p的边，能到达的节点中距离起点1最近的距离是多少？
 * 
 * 算法思路：
 * 1. 使用Dijkstra算法计算从起点1到所有节点的最短距离
 * 2. 构建Kruskal重构树：
 *    - 将所有边按海拔从高到低排序
 *    - 使用并查集，每当两个连通分量通过一条边连接时，创建一个新的内部节点
 *    - 新节点的海拔为这条边的海拔，左右孩子为两个连通分量的根
 *    - 新节点维护子树中所有原始节点到起点1的最小距离
 * 3. 查询时：
 *    - 从查询节点v开始，在重构树中向上跳跃
 *    - 找到海拔仍大于p的最高祖先
 *    - 返回该祖先对应子树的最小距离值
 * 
 * 时间复杂度：预处理O(m log m + m log n)，查询O(log n)
 * 空间复杂度：O(n log n)
 */

#include <bits/stdc++.h>
using namespace std;
using ll  = long long;
using pli = pair<ll,int>;

const ll INF = (ll)4e18;      // 无穷大值
const int N  = 200000 + 5;    // 原图最大节点数
const int Tm = N * 2;         // 重构树最大节点数（原节点数的2倍）
const int LG = 19;            // 用于倍增查询的最大层数

/* 原图相关 */
vector<pair<int,ll>> G[N];    // 邻接表存储原图，G[u] = {v, 长度}
ll dist1[N];                  // 从起点1到各点的最短距离

/* Kruskal重构树相关 */
int prt[Tm];                  // parent，每个节点的父节点
int L[Tm], R[Tm];             // 左右孩子节点
int fa[Tm];                   // 并查集的父节点数组
int dep[Tm];                  // 重构树中每个节点的深度
int up[LG+1][Tm];             // 倍增数组，up[k][u]表示u向上跳2^k步到达的祖先
ll  H[Tm];                    // 重构树中每个节点的海拔高度（权值）
ll  mn[Tm];                   // 重构树中每个子树的最小距离值

/* 并查集查找函数（路径压缩） */
int Find(int x){ return fa[x]==x ? x : fa[x]=Find(fa[x]); }

/* Dijkstra算法计算从节点1到所有节点的最短距离 */
void dij(int n){
    fill(dist1+1, dist1+n+1, INF);                           // 初始化距离为无穷大
    priority_queue<pli, vector<pli>, greater<pli>> pq;       // 小根堆，存储{距离, 节点}
    dist1[1]=0; pq.push({0,1});                              // 起点距离为0
    
    while(!pq.empty()){
        auto cur = pq.top(); pq.pop();
        ll d = cur.first;    // 当前距离
        ll u = cur.second;   // 当前节点
        
        if(d!=dist1[u]) continue;    // 如果已经找到更短路径，跳过
        
        // 遍历所有邻接节点
        for(auto &e:G[u]){
            int v=e.first; ll w=e.second;    // v是邻接节点，w是边长
            if(dist1[v]>d+w){                // 如果找到更短路径
                dist1[v]=d+w; 
                pq.push({dist1[v],v});       // 更新距离并加入队列
            }
        }
    }
}

/* 边的结构体：包含两个端点u,v，边长l，海拔高度a */
struct E{int u,v; ll l,a;};

/* 构建Kruskal重构树 */
void build(int n, vector<E>& e){
    int tot=n;    // 当前节点总数，初始为原图节点数
    
    // 初始化所有节点（包括原节点和新建的内部节点）
    for(int i=1;i<=2*n;i++){
        fa[i]=i;                          // 并查集初始化
        prt[i]=L[i]=R[i]=0;              // 父节点和左右孩子初始化为0
        H[i]=(i<=n?INF:0);               // 原节点海拔设为无穷大，新节点为0
        mn[i]=(i<=n?dist1[i]:INF);       // 原节点的最小值为到起点距离，新节点为无穷大
    }
    
    // 按海拔高度从大到小排序（Kruskal重构树的关键）
    sort(e.begin(),e.end(),[](E&x,E&y){return x.a>y.a;});
    
    // 按海拔从高到低处理每条边
    for(auto &ed:e){
        int ru=Find(ed.u), rv=Find(ed.v);    // 找到两个端点所在的连通分量根节点
        if(ru==rv) continue;                  // 如果已经连通，跳过这条边
        
        ++tot;                               // 创建新的内部节点
        H[tot]=ed.a;                         // 新节点的海拔为这条边的海拔
        L[tot]=ru; R[tot]=rv;                // 左右孩子为两个连通分量的根
        prt[ru]=prt[rv]=tot;                 // 设置父节点关系
        mn[tot]=min(mn[ru],mn[rv]);          // 新节点的最小值为两个孩子的最小值
        fa[ru]=fa[rv]=fa[tot]=tot;           // 更新并查集
    }
    
    // 使用BFS构建倍增数组，处理每个连通分量的根
    queue<int> q;
    for(int i=1;i<=tot;i++) if(!prt[i]){     // 找到所有根节点（没有父节点的节点）
        dep[i]=0; up[0][i]=0; q.push(i);     // 根节点深度为0，向上跳0步还是自己
        
        // BFS遍历整棵重构树
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v:{L[u],R[u]}){          // 遍历左右孩子
                if(!v) continue;             // 如果孩子不存在，跳过
                dep[v]=dep[u]+1;             // 孩子深度 = 父节点深度 + 1
                up[0][v]=u;                  // 向上跳1步到达父节点
                q.push(v);                   // 将孩子加入队列继续处理
            }
        }
    }
    
    // 构建倍增数组：up[k][i] = up[k-1][up[k-1][i]]
    // up[k][i]表示从节点i向上跳2^k步到达的祖先
    for(int k=1;k<=LG;k++)
        for(int i=1;i<=tot;i++)
            up[k][i]=up[k-1][ up[k-1][i] ];
}

/* 查询函数：在重构树中查询从节点v出发，在海拔大于p的路径上能到达的最小距离 */
ll ask(int v,ll p){
    int cur=v;    // 从节点v开始
    
    // 使用倍增法向上找到最高的祖先，使得该祖先的海拔仍然大于p
    // 这样可以确保路径上所有边的海拔都大于p
    for(int k=LG;k>=0;k--){
        int anc=up[k][cur];              // 当前节点向上跳2^k步的祖先
        if(anc && H[anc]>p) cur=anc;     // 如果祖先存在且海拔大于p，就跳到祖先
    }
    
    // 返回以cur为根的子树中的最小距离值
    return mn[cur];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin>>T;    // 测试用例数量
    while(T--){
        int n,m; cin>>n>>m;    // n个节点，m条边
        
        // 清空邻接表
        for(int i=1;i<=n;i++) G[i].clear();
        
        vector<E> ed(m);    // 存储所有边
        
        // 读入每条边的信息
        for(int i=0;i<m;i++){
            int u,v; ll l,a; cin>>u>>v>>l>>a;    // u,v是端点，l是长度，a是海拔
            G[u].push_back({v,l}); G[v].push_back({u,l});    // 无向图，双向加边
            ed[i]={u,v,l,a};    // 存储边信息
        }
        
        dij(n);        // 计算从节点1到所有节点的最短距离
        build(n,ed);   // 构建Kruskal重构树

        int Q; ll K,S; cin>>Q>>K>>S;    // Q个查询，K和S是强制在线的参数
        ll last=0;    // 上一次查询的答案，用于强制在线
        
        while(Q--){
            ll v0,p0; cin>>v0>>p0;    // 读入原始查询参数
            
            // 强制在线：根据上一次的答案来计算真实的查询参数
            int v=((v0+K*last-1)%n+n)%n+1;    // 计算真实的查询节点
            ll p=(p0+K*last)%(S+1);           // 计算真实的海拔限制
            
            ll ans=ask(v,p);    // 执行查询
            cout<<ans<<"\n";    // 输出答案
            last=ans;           // 更新last为当前答案，供下次查询使用
        }
    }
    return 0;
}
