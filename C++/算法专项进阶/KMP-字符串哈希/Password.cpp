#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;

string s;
vector<ll> nxt;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if(!(cin >> s)) return 0;
    ll n = (ll)s.size();
    nxt.assign(n, 0);

    for(int i=0,j=0;i<n;i++){
        while(j>0&&s[i]!=s[j]) j=nxt[j-1];
        if(s[i]==s[j]) j++;
        nxt[i]=j;
    }
    ll L=nxt[n-1];
    ll mx=0;
    for(int i=0;i<n-1;i++){
       mx=max(nxt[i],mx);
    }
    while(L>0&&mx<L) L=nxt[L-1];
    if(L==0) cout << "Just a legend\n";
    else cout << s.substr(0, L) << "\n";
    
    return 0;
}
