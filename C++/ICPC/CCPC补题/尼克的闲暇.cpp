#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    
    // 存储每个开始时间的任务持续时间
    vector<vector<int>> tasks(n + 2);  // 索引0不使用
    
    // 读取任务数据
    for (int i = 0; i < k; i++) {
        int p, t;
        cin >> p >> t;
        tasks[p].push_back(t);  // 将任务持续时间添加到开始时间p处
    }
    
    // dp[i]: 从第i分钟开始到结束的最大空闲时间
    vector<int> dp(n + 2, 0);  // 多分配空间避免边界检查
    dp[n + 1] = 0;  // 边界条件：工作结束后无时间
    
    // 从后向前遍历每一分钟
    for (int i = n; i >= 1; i--) {
        if (tasks[i].empty()) {
            // 当前时间无任务：尼克可以休息一分钟
            dp[i] = dp[i + 1] + 1;
        } else {
            // 当前时间有任务：选择能带来最大后续空闲的任务
            int best = -1;
            for (int t : tasks[i]) {
                int next = i + t;  // 任务结束时间
                if (next > n + 1) next = n + 1;  // 处理越界
                best = max(dp[next],best) ;  // 更新最优解
            }
            dp[i] = best;
        }
    }
    
    // 输出从第1分钟开始的最大空闲时间
    cout << dp[1] << endl;
    
    return 0;
}