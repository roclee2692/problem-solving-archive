#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
//这是暴力解法 会超时

ll t;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>t;
    while(t--){
        ll n; cin>>n; 
        string s; cin>>s;
        ll cnta=0,cntb=0,ans=n;
        for(int i=0;i<n;i++){
            if(s[i]=='a') cnta++;
            else cntb++;
        }
        ll D=cnta-cntb;
        if (D == 0) {  cout << 0 << "\n"; continue; }
        for(ll l=0;l<n;l++){
            ll a=0,b=0;
            for(ll r=l;r<n;r++){//一段连续的字母 数量可以为0
         
                if(s[r]=='a') a++;
                else b++;
                if(a-b==D) {
                  ans=min(ans,r-l+1);//窗口的右区间减去左区间
                }
            }            
        }
        if(ans==n) {
            cout<<-1<<'\n';
        }else{
            cout<<ans<<'\n';
        }
    }
    
    return 0;
}