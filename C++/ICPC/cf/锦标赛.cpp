#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX =73;
int j,n,k,t;
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    cin >> t;
   
    while(t--){
        cin >>n>> j >> k;
        vector<int> A(n+1);
        for(int i=1;i<=n;i++){
        cin >> A[i];
        }
        int my_max=0;
        for(auto &x:A){
            my_max=max(x,my_max);
        }
        
        if(k==1&&A[j]==my_max){
            cout<<"YES\n";
            continue;
        }
        if(k==1){
            cout<<"NO\n";
            continue;
        }
    
        if(k>1) cout<<"YES\n";

    }
  return 0;
}
