#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX =73;
 int t,n,k;
int main(){
ios::sync_with_stdio(0);cin.tie(0);
  string s;
  cin>>t;
  while(t--){
    int cnt=0;
     cin>>n>>k;
     cin>>s;
     for(int i=0;i<n;i++){
      int temp=s[i]-'0';
      cnt+=temp;
     }
    // cout<<cnt<<"\n";
     if(cnt<=k||n<2*k)//边界情况 n==2*k时 从左右往中间 k-1 1 k-1  共2k-1可以 k 1 k-1 01交替 2k个 不行
    {
      cout<<"Alice\n";
    }else{
      cout<<"Bob\n";
    }
  }
 return 0;
}
