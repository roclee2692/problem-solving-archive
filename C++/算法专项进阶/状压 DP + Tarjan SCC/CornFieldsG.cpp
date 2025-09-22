#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;
const int MOD=1e8;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M,N;
    cin>>M>>N;
     // --- 步骤 1: 读入数据，统一为0索引 ---
    // field_mask[i] 存储第 i 行 (0-indexed) 的地形状态
     vector<int> field_mask(M, 0);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            int fertility;
            cin >> fertility;
            if (fertility == 1) {
                field_mask[i] |= (1 << j);
            }
        }
    }
 // --- 步骤 2: 预处理所有“单行内合法”的状态 ---
    // “单行内合法” 指没有水平相邻的草，即 mask 中没有相邻的 1
    vector<int> legal_states;
    for(int mask=0;mask<(1<<N);mask++){
         // 检查水平限制：(mask & (mask << 1)) == 0
         if ((mask & (mask << 1)) == 0) {
            legal_states.push_back(mask);
        }
    }
    // --- 步骤 3: DP计算 ---
    // dp[i][mask] 表示处理完第 i 行，且第 i 行状态为 mask 的方案数
    vector<vector<int>> dp(M, vector<int>(1 << N, 0));
     // 3.1 初始化第一行 (i=0)
     for(int mask:legal_states){
        if((mask & field_mask[0])==mask) dp[0][mask]=1;//mask已经满足行不相邻 还好确保符合土地都为富饶
        // 检查该种植方案(mask)是否可行，即其是否为可用地形(field_mask)的一个子集。
     }
     // 3.2 递推计算第 1 到 M-1 行
     for(int i=1;i<M;i++){// 遍历当前行 i 的所有合法状态
        for(int mask:legal_states){
            // 检查地形限制
             if ((mask & field_mask[i]) != mask) {
                continue; // 当前状态在地形上不可行，跳过
            }
             // 遍历上一行 i-1 的所有合法状态
             for(int prev_mask:legal_states){
                 // 检查垂直限制：两行状态不能在同一列上有草
                if ((mask & prev_mask) == 0) {
                    // 累加方案数
                    dp[i][mask] = (dp[i][mask] + dp[i-1][prev_mask]) % MOD;
                }
             }
        }
     }
      // --- 步骤 4: 汇总结果 ---
    // 结果是最后一行的所有状态的方案数之和
    ll total=0;
     // 注意这里我们只对最后一行的合法状态求和即可
    // 但为简单起见，遍历所有 mask 也一样，因为非法 mask 的 dp 值必为0
for (int mask = 0; mask < (1 << N); ++mask) {
        total = (total + dp[M - 1][mask]) % MOD;
    }
    cout<<total<<endl;
    return 0;
}