#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<char>> grid;
    vector<vector<bool>> visit;  // 访问标记数组
    int m, n;

public:
    int numIslands(vector<vector<char>>& grid) {
        this->grid = grid;
        m = grid.size();
        n = grid[0].size();
        visit = vector<vector<bool>>(m, vector<bool>(n, false));  // 初始化访问标记数组
        int count = 0;  // 岛屿计数

        // 遍历整个 grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1' && !visit[i][j]) {  // 如果是陆地且未访问过
                    cout << "Island found at: (" << i << ", " << j << ")\n";  // 调试输出
                    dfs(i, j);  // 使用 DFS 遍历该岛屿
                    count++;  // 计数器增加
                }
            }
        }

        return count;  // 返回岛屿总数
    }

    void dfs(int i, int j) {
        // 判断越界或已经访问过的格子
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != '1' || visit[i][j]) {
            return;
        }

        // 标记当前格子为已访问
        visit[i][j] = true;
        cout << "Marking (" << i << ", " << j << ") as visited\n";  // 调试输出

        // 递归访问四个方向
        dfs(i - 1, j);  // 上
        dfs(i + 1, j);  // 下
        dfs(i, j - 1);  // 左
        dfs(i, j + 1);  // 右
    }
};

int main() {
    // 测试用例
    vector<vector<char>> grid = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };

    Solution solution;
    int result = solution.numIslands(grid);
    cout << "Number of islands: " << result << endl;  // 应输出 1
    return 0;
}
