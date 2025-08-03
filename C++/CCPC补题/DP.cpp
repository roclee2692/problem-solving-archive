#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

void print_dp_table(const string& A, const string& B, const vector<vector<int>>& dp) {
    int n = A.size(), m = B.size();
    const int W = 8; // 格子宽度

    // 表头
    cout << left << setw(W) << "A\\B";
    cout << left << setw(W) << "\"\"";
    for (int j = 0; j < m; ++j)
        cout << left << setw(W) << ("\"" + B.substr(0, j + 1) + "\"");
    cout << "\n";

    for (int i = 0; i <= n; ++i) {
        if (i == 0)
            cout << left << setw(W) << "\"\"";
        else
            cout << left << setw(W) << ("\"" + A.substr(0, i) + "\"");
        for (int j = 0; j <= m; ++j)
            cout << left << setw(W) << dp[i][j];
        cout << "\n";
    }
}

int main() {
    string A = "aabbabb";
    string B = "abb";
    int n = A.size(), m = B.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; ++i) dp[i][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = dp[i-1][j];
            if (A[i-1] == B[j-1]) dp[i][j] += dp[i-1][j-1];
        }
    }

    print_dp_table(A, B, dp);
    cout << "\n最终结果 dp[" << n << "][" << m << "] = " << dp[n][m] << endl;
    return 0;
}
