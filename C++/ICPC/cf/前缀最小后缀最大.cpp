#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX =1e8;
const int MIN=-1;
int t,n;
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin>>t;
  //  cout<<'\n'<<t<<'\n';
    while(t--){
      cin>>n;
      vector<int> A(n),pre(n),last(n);
      for(int &x:A){ // x 是 A 中每个元素的引用，对 x 的修改会直接改变 A 中对应位置的元素
        cin>>x;
      }
      pre[0]=A[0];last[n-1]=A[n-1];
      for(int i=1;i<n;i++){
        pre[i]=min(pre[i-1],A[i]);
        
      }
      for(int i=n-2;i>=0;i--){
        last[i]=max(last[i+1],A[i]);
      }
      for(int i=0;i<n;i++){
        if(A[i]==pre[i]||A[i]==last[i]) cout<<1;
        else cout<<0;
      }
      cout<<'\n';
    }   
  return 0;
}
