#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const double INF = 1e18;


int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	ll n;
	cin>>n;
	ll mymax=MAX;
 	ll mymin=-MAX;

	vector<pair<ll,ll>> ans(n);	
	vector<pair<ll,ll>> ab(n);
	for(auto &x:ab){
		cin>>x.first>>x.second;
	}
	
	for(ll i=0;i<n;i++){
		ans[i].first=ab[i].first/ab[i].second;
	 	ans[i].second=ab[i].first/(ab[i].second+1)+1;
	 	mymax=min(mymax,ans[i].first);//
		mymin=max(mymin,ans[i].second); // 
	}
	
	cout<<mymin<<' '<<mymax;	

  return 0;
}
