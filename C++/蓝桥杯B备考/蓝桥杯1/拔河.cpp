#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const double INF = 1e18;

const int N=1010;//这里人数最多只有1000已知          // 定义常量 N，最大数组大小为 1010
ll a[N], sum[N];            // a 数组存储输入的力量值，sum 数组存储前缀和
int n;                       // n 为同学的数量
//变量的声明直接声明在外自动初始化为0，以防后患 

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	vector<ll> ans;
	
// 输入力量值并计算前缀和
for(int i=1;i<=n;i++){//前缀和从1开始，表示前i个学生的力量总和 
	cin>>a[i];
	sum[i]=sum[i-1]+a[i];//全局数组自动初始化为0，累加得到前缀和 
}	    
		
	//双层for循环遍历所有前缀和的差
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			ans.push_back(sum[j]-sum[i-1]);//第二层从j=i开始遍历，确保不重不漏 
			 
		} 
		
	} 
	ll t=1e9; 
	sort(ans.begin(),ans.end());
	   // 寻找相邻两个子数组和的最小差值
	 int  l=ans.size();
	 //这里很容易出错，i要从1开始，因为你用了ans[i-1];从零开始会为负值
	for(int i=1;i<l;i++){//上面的是构造所有可能队伍组合，现在要挑出，队伍之间差值最小的 
		t=min(t,ans[i]-ans[i-1]);//此处已经排序，直接相邻相减找最小差值 
	}
	cout<<t; 
	

  return 0;
}
