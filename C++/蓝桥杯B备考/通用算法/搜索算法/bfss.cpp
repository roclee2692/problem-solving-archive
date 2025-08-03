#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
private:
    vector<vector<char>> grid; 
    vector<vector<bool>> visit;  // 新增的访问标记数组
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
                    bfs(i, j);  // 使用 BFS 遍历该岛屿
                    count++;  // 计数器增加
                }
            }
        }

        return count;  // 返回岛屿总数
    }

    void bfs(int i, int j) {
        queue<pair<int, int>> q;
        q.push({i, j});
        visit[i][j] = true;  // 标记为已访问

        // 四个方向：上、下、左、右
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!q.empty()) {
            pair<int, int> p = q.front();
            q.pop();

            int x = p.first;
            int y = p.second;

            // 遍历四个方向
            for (int d = 0; d < 4; ++d) {
                int nx = x + directions[d][0];
                int ny = y + directions[d][1];

                // 如果新位置合法，并且是陆地（'1'），且未访问过，则加入队列并标记为已访问（水域）
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1' && !visit[nx][ny]) {
                    q.push({nx, ny});
                    visit[nx][ny] = true;  // 标记为已访问
                }
            }
        }
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
