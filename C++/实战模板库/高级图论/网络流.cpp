#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int XN=1e4+5;
const int XM=2e5+5;
const ll INF=1e18;
struct Edge{
    int to;
    ll cap;
    int rev;
};

vector<Edge> adj[XN];
int n,m,s,t;
int level[XN];
int iter[XN];

void add_edge(int from,int to,ll cap){
    adj[from].push_back({to,cap,(int)adj[to].size()});
    adj[to].push_back({from,0,(int)adj[from].size()-1});
}
bool bfs(){
    fill(level,level+n+1,-1);
    queue<int> q;
    q.push(s);
    level[s]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto &e:adj[u]){
            if(e.cap>0 && level[e.to]<0){
                level[e.to]=level[u]+1;
                q.push(e.to);
            }
        }
    }
    return level[t]>=0;
}

ll dfs(int u,ll flow){
    if(u==t) return flow;
    for(int &i=iter[u];i<adj[u].size();i++){
        Edge &e=adj[u][i];
        if(e.cap>0 && level[e.to]==level[u]+1){
            ll d=dfs(e.to,min(flow,e.cap));
            if(d>0){
                e.cap-=d;
                adj[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
ll dinic(){
    ll max_flow=0;
    while(bfs()){
        fill(iter,iter+n+1,0);
        ll flow;
        while((flow=dfs(s,INF))>0){
            max_flow+=flow;
        }

    }
    return max_flow;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>s>>t;
    for(int i=0;i<m;i++){
        int u,v;
        ll cap;
        cin>>u>>v>>cap;
        add_edge(u,v,cap);
    }
    cout<<dinic()<<'\n';
    return 0;
}