#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX =73;
int t;
bool ok(int dx,int dy,int xi,int yi,ll s){
    int res=0;
    if(xi==s/2&&yi==s/2) return true; // 中心点
    if (!(xi == yi || xi + yi == s)) return false;
    if (xi==yi) {if(dx==1&&dy==1||dx==-1&&dy==-1) res++;}
    else if (xi + yi == s) {if(dx==1&&dy==-1||dx==-1&&dy==1) res++;}
    return res==1;
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
cin>>t;//组数
while(t--){
ll n,s,res=0;//每组的测试用例数量 台球桌边长
cin>>n>>s;
    for(int i=1;i<=n;i++){
    int dx,dy,xi,yi;
    cin>>dx>>dy>>xi>>yi;
    if(ok(dx,dy,xi,yi,s)) res++;

    }
    cout<<res<<'\n';
}
  return 0;
}
