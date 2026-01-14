/*
 * 【位运算 DP】- 状态压缩动态规划
 * 
 * 时间复杂度：O(n * 2^n * m) 通常
 * 空间复杂度：O(2^n)
 * 
 * 适用场景：
 *   - 小范围集合状态（n ≤ 20）
 *   - 旅行商问题（TSP）
 *   - 棋盘状态压缩
 *   - 子集枚举
 * 
 * 模板题：
 *   - 洛谷 P1097 - 统计数字
 *   - Codeforces 10D - LCIS
 */

#include<bits/stdc++.h>
using namespace std;
using ll=long long;

namespace BitDP{
    int n,m;
    vector<ll> dp;
    void solve1(){//前向转移 从小求大 表示：到达状态 路径（所有可能的顺序组合
        cin>>n>>m;
        dp.assign(1<<n,0);
        dp[0]=1;

        for(int mask=0;mask<(1<<n);mask++){
            if(dp[mask]==0) continue;

            for(int i=0;i<n;i++){
                if((mask & (1<<i))==0){
                    int new_mask =mask|(1<<i);
                    dp[new_mask]+=dp[mask];
                }
            }
        }
    }
    void solve2(){//子集枚举 一般不包含空集
        for(int mask=1;mask<(1<<n);mask++){
            for(int sub=mask;sub>0;sub=(sub-1)&mask){
                dp[mask]=max(dp[mask],dp[sub]+dp[mask^sub]);
            }
        }
    }

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    BitDP::solve1();
    return 0;
}

/*
 * 【关键点】
 * 1. 状态范围：2^n（必须 n ≤ 20 左右）
 * 2. 状态转移：通常通过添加/移除元素
 * 3. 子集枚举：for (int sub = mask; sub > 0; sub = (sub-1) & mask)
 * 4. 时间复杂度：O(3^n) 枚举所有子集对
 * 5. 位操作：count, set, unset, toggle
 * 
 * 【常见变体】
 * - TSP（旅行商）：dp[mask][i] = 访问 mask 集合且在 i 的最小路径
 * - 棋盘覆盖：按行转移状态
 * - 子集 DP：计算所有子集的某个性质
 * 
 * 【提交前检查】
 * ✓ 状态定义清晰
 * ✓ 子集枚举公式正确
 * ✓ 初值设置
 * ✓ 转移逻辑
 */
