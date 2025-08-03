#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
		int n,mw;//先定义两个变量 记录物品的数量和背包的最大容量 
		cout<<"请输入物品数量n和背包容量w: ";
		cin>>n>>mw;
		int w[n+1],v[n+1];
		for(int i=1;i<=n;i++){
			cin>>w[i]>>v[i];//通过循环遍历输入每件的物品重量和价值 
		} 
		int dp[mw+1]={0};//存储计数后的数据
		
		for(int i=1;i<=n;i++) {//第几个物品 
			for(int j=mw;j>=w[i];j--){//从mw开始倒序遍历 ，下一个j>=当前物品的重量，继续遍历所有 重量的可能性 
				dp[j]=max(dp[j],v[i]+dp[j-w[i]]);//判断价值 
			}//当前重量所能有的最大价值 
		
		}
		
			cout<<dp[mw]<<endl;
			return 0; 
	
	
}