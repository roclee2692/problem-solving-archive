#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n;
int gcd1(int a,int b){
  return b?gcd1(b,a%b):a;
}
int gcd2(int a,int b){
  while(b!=0){
    int t=a%b;
    a=b;
    b=t;
  }
  return a;
}
int gcd3(int a,int b){
  return b==0?a:gcd3(b,a%b);
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin>>t>>n;
    cout<<gcd1(t,n)<<"\n";
    cout<<gcd2(t,n)<<'\n';
    cout<<gcd3(t,n)<<"\n";
  return 0;
}
