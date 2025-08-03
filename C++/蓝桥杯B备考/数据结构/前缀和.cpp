#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<vector<int>> arr = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    int m = arr.size();
    int n = arr[0].size();
    
    // 构建二维前缀和数组
    vector<vector<int>> prefix_sum(m, vector<int>(n));
    prefix_sum[0][0] = arr[0][0];
    
    // 第一行
    for (int j = 1; j < n; ++j) {
        prefix_sum[0][j] = prefix_sum[0][j-1] + arr[0][j];
    }
    
    // 第一列
    for (int i = 1; i < m; ++i) {
        prefix_sum[i][0] = prefix_sum[i-1][0] + arr[i][0];
    }
    
    // 填充其余位置
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            prefix_sum[i][j] = arr[i][j] + prefix_sum[i-1][j] + prefix_sum[i][j-1] - prefix_sum[i-1][j-1];
        }
    }
    
    // 查询从 (1, 1) 到 (2, 2) 的和
    int x1 = 1, y1 = 1, x2 = 2, y2 = 2;
    int result = prefix_sum[x2][y2];
    if (x1 > 0) result -= prefix_sum[x1-1][y2];
    if (y1 > 0) result -= prefix_sum[x2][y1-1];
    if (x1 > 0 && y1 > 0) result += prefix_sum[x1-1][y1-1];
    
    cout << "Sum of the submatrix from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ") is: " << result << endl;
    
    return 0;
}
