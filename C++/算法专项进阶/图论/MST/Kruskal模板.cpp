#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// 并查集（Disjoint Set Union）模板
struct DSU{
    ll n;  // 元素总数
    int num;  // 连通块数
    vector<ll> p,r;  // 父节点数组 秩（树的高度）数组，用于按秩合并优化 也可以按点数
    DSU(ll n_):n(n_),p(n+1),r(n+1,0){ iota(p.begin(),p.end(),0);}     
    // iota 将 p[0..n] 赋值为 0..n  
    ll find(ll x){
        if(p[x]!=x) { p[x]=find(p[x]);}
        return  p[x];
    }
    // 合并 a 与 b 所在集合，返回是否成功合并
    bool unite(ll a,ll b){
        a=find(a);
        b=find(b);
        if(a==b) return false;
         // 按秩合并：将矮树接到高树下，保持树高度最小
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        if(r[a]==r[b]) r[a]++;  // 若两棵树高度相同，合并后根高度 +1
        num--;  // 合并成功，块数减一
        return true;
    }// 此时 dsu.cnt 就是剩余连通块数量

};
// 边结构体：用于存储图的边信息
struct Edge{
    ll u,v,w;
    bool operator<(Edge const& o)const{
        return w<o.w;// 当调用 e1 < e2 时：实际调用 e1.operator<(e2)
    }
};
// Kruskal 最小生成树函数：
// 参数：
//   n   - 图的顶点数（编号从 1 到 n）
//   E   - 输入的所有边列表
//   mst - 存放生成树边的容器
// 返回值：最小生成树的总权重
ll n,m;
vector<Edge> E;
vector<Edge> mst;
ll kruskal(bool mintree=1){//加边法
     mst.clear();          // ← 保证干净
    if(mintree)
    sort(E.begin(),E.end());// 1. 按权重升序排序所有边
    else sort(E.rbegin(),E.rend());// 降序 ⇒ 最大生成树
     // 2. 初始化并查集
     DSU dsu(n);
     ll total=0;// MST 权重累加
 // 3. 遍历每条边，若连接的两点不连通则合并并加入 MST
    for(auto &e:E){
        if(dsu.unite(e.u,e.v)){
            total+=e.w;
            mst.push_back(e);
             // 若已选满 n-1 条边，可提前结束
             if((ll)mst.size()==n-1) break;
        }
    }   
    return total;
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    E.reserve(m);
    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        E.push_back({u,v,w});
    }
    ll ans=kruskal();
    // 输出构成 MST 的每条边
    if(mst.size()==n-1) cout<<ans;//连通性判断 应该看 mst.size()
     else cout<<"orz";//不连通
    for (auto& e : mst) {
        cout << e.u << " " << e.v << " " << e.w << "\n";
    }
  return 0;
}
