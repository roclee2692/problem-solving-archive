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
bool kahn(){
    queue<ll> q;
    for(ll i=1;i<=n;i++){
        if(indegree[i]==0) q.push(i);
    }
    while(!q.empty()){
        ll u=q.front(); q.pop();
        save.push_back(u);
        for(auto &v:adj[u]){
            indegree[v]--;
            if(indegree[v]==0){
                q.push(v);
                //save.push_back(v);
            } 
        }
    }
    return save.size()==n;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n ;
    indegree.assign(n+1,0);
    while(n--){
        ll NO,len,pre;
        cin>>NO>>len>>pre;
        indegree[NO]++;
        adj[NO].push_back({len,pre});//出度
    }
    if(kahn()) cout<<"无环\n";
    else cout<<"有环\n";
    return 0;
}