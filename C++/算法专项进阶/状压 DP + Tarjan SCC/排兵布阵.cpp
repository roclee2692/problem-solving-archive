#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
// 1. 核心模型：将问题转化为分组背包。城堡是“物品组”，不同兵力策略是组内“物品”，总兵力是“背包容量”。

// 2. DP状态：dp[j] 表示用 j 的总兵力（背包容量）能获得的最大总分（价值）。

// 3. 状态转移关键：dp[j - cost] 指的是，在决策当前城堡前，用剩余兵力在前序所有城堡中能取得的最优解。

// 4. 实现技巧：预算 j 必须倒序遍历，以保证 dp[j - cost] 存储的是上一轮（处理前一个城堡）的结果，从而确保每个城堡组最多只选择一个策略。
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    ll s,n,m;
    cin>>s>>n>>m;
vector<vector<ll>> opponent_soldiers(n+1);//索引从一开始要扩大
    for(int i=1;i<=s;i++){
        for(int j=1;j<=n;j++){
            int soldiers;
            cin>>soldiers;
            opponent_soldiers[j].push_back(soldiers);// 将第i场战斗的士兵数添加到第j个城堡
            //这是一个以城编号为行 以对手编号为列的二维数组
        }
    }
    // groups[i] 存储第i个城堡的所有可选方案
    // 每个方案是一个 pair<花费, 价值>
    // 这是分组背包的"组"，每个城堡是一个组
vector<vector<pll> > groups(n+1);
for(int i=1;i<=n;i++){// 枚举第i个城堡攻占的场次数（从1场到s场）
    // 将第i个城堡的各场战斗按对方士兵数从小到大排序
        // 这样可以保证先打容易的场次，再打困难的场次
        //排序 并未改变攻占城市应获得的得分
    sort(opponent_soldiers[i].begin(),opponent_soldiers[i].end());
    // for(int k=0;k<s;k++){
    //     // 注意：push_back了s次后，vector大小为s，有效索引为[0,s-1]，不能访问索引s
    //     ll cost=2*opponent_soldiers[i][k]+1;// 攻占前k场需要的士兵数
    //     ll value=i*(k+1); // 城堡编号i × 攻占的场次数// k+1表示攻占的场次数
    //     if(cost<=m){ // 如果花费不超过总士兵数，则这是一个可行方案
    //         groups[i].push_back({cost,value});
    //     }

    // }
    for(int k=1; k<=s; k++){  // k从1开始
    ll cost=2*opponent_soldiers[i][k-1]+1;  // 使用k-1作为索引
    ll value=i*k;  // k直接表示攻占的场次数
         if(cost<=m){
        groups[i].push_back({cost,value});
         }
    }
}
 // 动态规划数组
    // dp[j] 表示使用j个士兵能获得的最大分数
    vector<ll> dp(m + 1, 0);
    // 分组背包动态规划
    // 外层循环：遍历每个城堡（每个组）
    for(int i=1;i<=n;i++){
      
            // 中层循环：逆序遍历背包容量（士兵数）
        // 逆序是为了保证 dp[j - cost] 存储的是上一轮（处理前一个城堡）的结果,保证每个组只选一个物品
        for(int j=m;j>=1;j--){
              for(const auto& item:groups[i]){
                 // 如果当前士兵数足够选择这个方案
                 if (j >= item.first) {
                    // 更新dp值：不选 vs 选择当前方案
                    // item.first 是花费（士兵数）
                    // item.second 是价值（分数）
                    dp[j] = max(dp[j], dp[j - item.first] + item.second);
                }
            }
        }
    }
    // 输出使用m个士兵能获得的最大分数
    cout << dp[m] << endl;

    return 0;
}