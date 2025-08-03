#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const double INF = 1e18;
 int dp[10];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	 int n,res=0;
	 cin>>n;
	 vector<string> str(n);
	 for(int i=0;i<n;i++){
	 	cin>>str[i];
	 }
	 for(int i=0;i<n;i++){
	 	int left=str[i].front()-'0';
	 	int right=str[i].back()-'0';
	 	dp[right]=max(dp[right],dp[left]+1);
	 	res=max(res,dp[right]);
	 }
		cout<<n-res<<endl;

  return 0;
}
