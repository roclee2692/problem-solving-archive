#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
using de=double;
using ld=long double;
const ll INF = (ll)4e18;      // 无穷大值
const int N  = 200000 + 5;    // 原图最大节点数
const int Tm = N * 2;         // 重构树最大节点数（原节点数的2倍）
const int LG = 19;            // 用于倍增查询的最大层数

struct edge{ll u,v,w;};
// 全局变量
ll n, m;
vector<ll> indegree;
vector<pll> adj[N];
vector<ll> save;
vector<ll>  dp;
 vector<int> timeCost;
bool kahn(){
    save.clear();
    dp.assign(n+1, 0);  // 分配n+1大小，索引从1开始
    queue<ll> q;
    for(ll i=1;i<=n;i++){
        if(indegree[i]==0) q.push(i);
        dp[i]=timeCost[i];    // <- 初始化为自身耗时
          // 项目排期：对所有节点都要赋值，OK
        // 如果你想要从adj[i]中获取某个值，需要这样写：
        // if(!adj[i].empty()) dp[i] = adj[i][0].second;  // 获取第一个邻接节点的索引
        // 或者
        // dp[i] = 某个初始值;  // 根据你的算法逻辑设置
    }
    
    while(!q.empty()){
        ll u=q.front(); q.pop();
        save.push_back(u);

        for(auto &x:adj[u]){
            ll v=x.second,len=x.first;
            dp[v]=max(dp[v],dp[u]+len);
            if(--indegree[v]==0){
                q.push(v);
            } 
        }
    }
    return save.size()==n;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n ;
    timeCost.assign(n+1,0);
    dp.assign(n+1,0);
    indegree.assign(n+1,0);
    for(ll i=1;i<=n;i++) {
        ll idx,len,pre=1;
        cin>>idx>>len;
        timeCost[idx] = len;  
        while(pre){
            cin>>pre;
        if(pre==0) break;
        indegree[idx]++;
        adj[pre].push_back({len,idx});//出度
        //邻接表 adj 只是存依赖关系 当 adj[i] 为空时（即 i 没有后续依赖），adj[i][0] 根本就不存在——访问它会越界、导致段错误。
        }
    }
    // 拓扑 + DP
    bool ok=kahn();
     if(!ok) cout<<"有环\n";
    else {
        ll ans=0;
        for(ll &u:save) ans=max(ans,dp[u]);
        //遍历所有 dp[i]、取它们的最大值，才是整个项目（所有 n 项杂务）最早完成的时刻：
        cout<<ans<<'\n';
    }
      return 0;
}