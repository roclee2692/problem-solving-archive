#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
ll t;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>t;
    while(t--){
        ll n,k;
        cin>>n>>k;
        string s;
        char ans[n];
        for(int i=0;i<n;i++){
            ans[i]='+';
        }
        cin>>s;
       if(k==n) {
        for(int i=0;i<n;i++){
            ans[i]='-';
        }
       }else{
         int p=0,q=n-1,cnt=0;
            for(int i=0;i<s.size();i++){           
                char ch=s[i];
                if(ch=='0'){
                    ans[p]='-';
                    p++;
                }else if(ch=='1'){
                    ans[q]='-';
                    q--;
                }else if(ch=='2'){
                    cnt++;
                }
            }
            while(cnt--&&p<=q){
                ans[p]='?';
                ans[q]='?';
                p++; q--;
            }
       }
       for(int i=0;i<n;i++){
        cout<<ans[i];
       }
       cout<<endl;
    }
    return 0;
}