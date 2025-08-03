#include <iostream>
#include <vector>
#include <string> // 使用 string 的 size() 和 length()
#include <cstring> // 使用 memset 初始化 dp 表

typedef long long ll;
using namespace std;

string s; // 用于存储输入的数字 N 的字符串形式（便于从高位向低位访问每一位）
ll dp[20][2][2]; // 三维 dp 表：dp[pos][tight][started]
// - pos：当前处理的是第 pos 位（从高位到低位）
// - tight：是否受限于原数字 N 的对应前缀（true 表示当前构造数字必须 <= N）
// - started：是否已经开始构造有效数字（false 表示还在跳过前导 0）

// 递归函数 dfs：从 pos 位开始构造，统计合法好数的个数
ll dfs(int pos, bool tight, bool started) {
    // 递归边界：如果已经处理完所有位
    if (pos == s.size()) return started ? 1 : 0;
    // 如果已经构造出一个非前导 0 开头的完整合法数，返回 1；否则（前导 0 情况）返回 0

    // 记忆化：如果当前状态已计算过，直接返回保存的结果，避免重复计算
    if (dp[pos][tight][started] != -1) return dp[pos][tight][started];

    ll res = 0; // 当前状态的计数结果
    int up = tight ? s[pos] - '0' : 9; // 如果当前 tight 为 true，当前位最多只能选到 s[pos]；否则可以选到 9

    // 遍历当前位所有可能的数字 d（从 0 到 up）
    for (int d = 0; d <= up; d++) {
        // 更新下一个状态的 tight：只有当前 d == up 且原 tight 为真，才保持 tight
        bool newtight = tight && (d == up);
        // 更新是否已开始构造数字：如果已经 started 或当前 d > 0，就算开始了
        bool newstarted = started || (d > 0);

        if (!newstarted) {
            // 还在前导 0 阶段（比如前几位是 000...），允许跳过，不做奇偶判断
            res += dfs(pos + 1, newtight, newstarted);
        } else {
            // 已开始构造有效数字，需要判断当前位是否满足“好数”规则（奇偶位匹配）
            int pos_from_right = s.size() - pos; // 从右往左是第几位（个位是第 1 位）

            // 判断奇偶位规则：
            // - 奇数位上（个位、百位等）只能出现奇数（1,3,5,7,9）
            // - 偶数位上（十位、千位等）只能出现偶数（0,2,4,6,8）
            if ((pos_from_right % 2 == 1 && d % 2 == 1) || // 奇位必须为奇数
                (pos_from_right % 2 == 0 && d % 2 == 0)) { // 偶位必须为偶数
                // 满足规则则继续递归下一位
                res += dfs(pos + 1, newtight, newstarted);
            }
            // 否则该路径剪枝（不合法，直接跳过）
        }
    }

    // 保存当前状态的结果并返回（记忆化）
    return dp[pos][tight][started] = res;
}

int main() {
    int n;
    cin >> n; // 输入数字 N
    s = to_string(n); // 转换为字符串，便于逐位处理
    memset(dp, -1, sizeof(dp)); // 初始化 dp 数组为 -1，表示所有状态未计算过
    ll ans = dfs(0, true, false); // 从第 0 位开始，tight=true（不能超过原数），started=false（尚未开始）
    cout << ans << endl; // 输出结果
    return 0;
}
