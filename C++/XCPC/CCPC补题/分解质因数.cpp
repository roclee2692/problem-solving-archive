#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;

int main(){
ios::sync_with_stdio(0);cin.tie(0);
int n;  cin>>n;
bool first=1;
    for(int i=2;i*i<=n;i++){
        while(n%i==0){  
            if(!first) cout<<"*";
            cout<<i;
            n/=i;
            first=0;
        }
    }

    if(n>1){
        if(!first) cout<<"*";
        cout<<n;
    }

  return 0;
}
