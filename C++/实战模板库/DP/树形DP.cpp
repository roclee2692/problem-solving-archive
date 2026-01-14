#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int XN=1e5+5;

vector<int> adj[XN];
ll dp[XN][2];
ll value[XN];
int n;

void dfs(int u,int p){
    dp[u][0]=0;
    dp[u][1]=value[u];

    for(int v:adj[u]){
        if(v==p) continue;
        dfs(v,u);
        dp[u][0]+=max(dp[v][0], dp[v][1]);
        dp[u][1]+=dp[v][0];
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>value[i];

    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,-1);
    cout<<max(dp[1][0],dp[1][1])<<"\n";
    return 0;
}