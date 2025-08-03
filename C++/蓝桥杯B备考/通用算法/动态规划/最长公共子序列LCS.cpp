#include <iostream>
#include <vector>
#include <string>
using namespace std;

int lcs(const string &X, const string &Y) {
    int m = X.length();
    int n = Y.length();
    
    // 创建一个二维dp数组来保存子问题的解
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // 动态规划填充dp数组
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {  // 字符相同，LCS长度加1
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {  // 字符不同，LCS长度取前两者的最大值
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    // dp[m][n] 存储的是LCS的长度
    return dp[m][n];
}

int main() {
    string X, Y;
    cout<<"请输入两个字符串X和Y(中间用换行隔开):"<<endl;
    cin >> X >> Y;  // 输入两个字符串
    
    // 输出LCS的长度
    cout << lcs(X, Y) << '\n';
    
    return 0;
}
