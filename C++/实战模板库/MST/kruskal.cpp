/*
 * 【Kruskal 算法】- 最小生成树（依赖并查集）
 * 
 * 时间复杂度：O(E log E)（边排序主导）
 * 空间复杂度：O(V + E)
 * 
 * 适用场景：
 *   - 求最小生成树（权值最小）
 *   - 稀疏图更优
 *   - 边权较小（容易排序）
 * 
 * 模板题：洛谷 P3366 - 【模板】最小生成树
 */
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll n,m;
struct DSU{
    vector<ll> p,r;
    DSU(ll n):p(n+1),r(n+1){ iota(p.begin(),p.end(),0); };
    ll find(ll x){
        if(p[x]!=x) p[x]=find(p[x]);  // ✅ 修正：应该递归find(p[x]) 若为find(x)会无限递归
        return p[x];
    }
    bool unite(ll a,ll b){
        a=find(a);
        b=find(b);
        if(a==b) return 0;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;  // ✅ 修正：应该是p[b]=a，让b指向a  谁大 是母树 写后面
        if(r[a]==r[b]) r[a]++;
        return 1;
    }
};
struct Edge{
    ll u,v,w;
    bool operator<(Edge const& o)const{
        return w<o.w;
    }
};
vector<Edge> E;
vector<Edge> mst;

ll kruskal(bool mintree=1){
    mst.clear();
    if(mintree) sort(E.begin(),E.end());
    else sort(E.rbegin(),E.rend());
    DSU dsu(n);
    ll total=0;
    for(auto &e:E){
        if(dsu.unite(e.u,e.v)){
            total+=e.w;
            mst.push_back(e);
            if(mst.size()==n-1) break;
        }
    }
    return total;
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    E.reserve(m);
    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        E.push_back({u,v,w});
    }
    ll ans=kruskal();
     if(mst.size()==n-1){//可能少于n-1条边 无法输出
        cout<<ans<<'\n';  // 连通，输出总权重
        // 可选：输出每条边
        // for (auto& e : mst) {
        //     cout << e.u << " " << e.v << " " << e.w << "\n";
        // }
    }else{
        cout<<"orz\n";  // 不连通
    }
  return 0;

}
/*
 * 【Kruskal 算法步骤】
 * 1. 将所有边按权值从小到大排序
 * 2. 依次考虑每条边：
 *    - 如果两端点不连通，加入这条边
 *    - 否则跳过（会形成环）
 * 3. 直到加入 n-1 条边（形成树）
 * 
 * 【为什么贪心有效？】
 * - 最小生成树的关键性质：
 *   "最小权值的边一定在某个 MST 中"
 * - 每次加入最小的未加入边，最终得到全局最优
 * 
 * 【与 Prim 的对比】
 * Kruskal:
 *   - 时间：O(E log E)
 *   - 空间：O(E)
 *   - 适合：稀疏图
 * Prim:
 *   - 时间：O((V + E) log V)（堆优化）
 *   - 空间：O(V)
 *   - 适合：稠密图
 * 
 * 【常见变体】
 * - 第 k 小生成树：需要特殊处理
 * - 带约束的 MST：限制某些边是否使用
 * - 最大生成树：改为降序排列
 * 
 * 【提交前检查】
 * - [ ] 并查集是否正确实现？
 * - [ ] 边是否按权值排序？
 * - [ ] 是否检查了连通性？
 * - [ ] 是否处理了重边和自环？
 * - [ ] 最终是否有 n-1 条边？
 */
