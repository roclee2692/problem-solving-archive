#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    long long a_count = 0;   // 可以构成的 a...a 前缀子序列的数量
    long long total_ans = 0; // 最终答案，a...ab...b 好子序列的数量

    for (char c : s) {
        if (c == 'a') {
            // 每遇到一个'a'，a...a子序列的数量翻倍（取或不取之前的），再加1（只取当前的'a'）
            a_count = (a_count * 2 + 1) % MOD;
        } else if (c == 'b') {
            // 每遇到一个'b'，都可以和之前所有的a...a子序列组合
            total_ans = (total_ans + a_count) % MOD;
        }
    }

    cout << total_ans << endl;

    return 0;
}