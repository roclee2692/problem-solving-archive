#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 在 0/1 背包问题中，我们通常需要一个二维的 
// DP 数组 dp[i][j]，其中 i 代表前 i 个物品，
// j 代表背包容量。但实际上，当前背包容量 j 
// 只依赖于上一行的 dp[i-1][j] 和 dp[i-1][j-weight[i]]。
// 因此，我们可以将二维数组压缩为一维数组，从而节省空间。
int knapsack(int W,vector<int>& weights,vector<int>& values,int n){
    vector<int> dp(W+1,0);
    for(int i=1;i<=n;i++){
        for(int w=W;w>=weights[i-1];w--){
            dp[w]=max(dp[w],dp[w-weights[i-1]]+values[i-1]);
        }
    } return dp[W];
}

int main(){
    int n,W;
    cout<<"请输入物品数量n和背包重量W:";
    cin>>n>>W;

    vector<int> weights(n),values(n);

    cout<<"请输入每个物品的重量：";
    for(int i=0;i<n;i++){
        cin>>weights[i];
    }

    cout<<"请输入每个物品的价值：";
    for(int i=0;i<n;i++){
        cin>>values[i];
    }

    int result=knapsack(W,weights,values,n);
    cout<<"背包能够容纳的最大价值为："<<result<<endl;

    return 0;
}

