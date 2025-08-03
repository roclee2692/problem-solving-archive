#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int main(){
    int n,m,ans=0;
    cin>>n>>m;
    vector<int> curr(n,0),up(n);
    for(int i=0;i<n;i++){
        cin>>up[i];
    }
    vector<pair<int,int>> bf(m);//编号 分值
    for(auto &x:bf){
        cin>>x.first>>x.second;
    }
    for(auto &x:bf){
    	int t=x.first-1;
       curr[t]=min(curr[t]+x.second,up[t]);//每一小项素质分累加 必须开一个新数组 
    }
    for(auto &x:curr){
        ans+=x;
    }
    cout<<ans;
    return 0;
}