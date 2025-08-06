#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF=LLONG_MAX;
struct Edge {
    int u, v;
    ll w;
};
// 全局变量
int n, m;
vector<Edge> E;          // 所有边
vector<ll> used;   // MST 边在 E 中的索引

struct DSU {
    vector<int> p, r;
    DSU(int n=0): p(n+1), r(n+1,0) { iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x ? x : p[x]=find(p[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        if(r[a]==r[b]) r[a]++;
        return true;
    }
};
// Kruskal，传入 `skip_idx` 表示“跳过”那条边
// 如果 skip_idx==-1 则不跳过任何边
// 如果能组成 n-1 条边，返回总权重并填充 `used`; 否则返回 -1 
ll kruskal(int skip_idx){
    ll ok=0;
    used.clear();
    DSU dsu(n);
    ll total=0;
    // 排序只在主流程做一次
    // 假设 E 已按 w 升序排序
    for(int i=1;i<=m;i++){
        if(i==skip_idx) continue;
        auto &e=E[i];
        if(dsu.unite(e.u,e.v)){
            total+=e.w;
            used.push_back(i);
            if((ok=used.size())==n-1){break; } 
        }
    }
    return ok==n-1?total:-1;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    E.resize(m+1);
    for (int i = 1; i <=m; i++){
        cin >> E[i].u >> E[i].v >> E[i].w;
    }
      // 1. 预排序
      sort(E.begin()+1,E.end(),[](const Edge &a,const Edge &b){return a.w<b.w;});// 只排序 1…m
      //在竞赛环境下把 lambda 参数写成 const Edge& 
      //C++11 并不支持在 lambda 参数列表里用 auto 来做通用类型推导，只有从 C++14 才开始允许这种 “generic lambda”。
       // 2. 第一次 Kruskal，求 MST
       ll sum=kruskal(-1);
        // 3. 对每条 MST 边尝试跳过
       ll tmp=INF;
        for(auto &idx:used){
            ll s=kruskal(idx);
            if(s!=-1) tmp=min(tmp,s);
        }
        if(tmp==INF) cout<< "No second best MST\n";
        else cout<<tmp<<'\n';
         return 0;
}