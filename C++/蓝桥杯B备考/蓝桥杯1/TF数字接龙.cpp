#include <bits/stdc++.h>
using namespace std;

/**
 * 题意概述：
 * 1. 在 N×N 的棋盘上，每个格子含有 [0..K-1] 的整数。
 * 2. 从 (0,0) 出发到 (N-1,N-1) ，路径需访问所有 N*N 个格子“恰好一次”。
 * 3. 第 i 步访问的格子数字须为 i mod K（从起点(0,0)算起，起点是第 1 步）。
 * 4. 可以沿 8 个方向移动（水平、竖直、对角线）。
 * 5. 路径不能有任何“交叉”。
 * 6. 若有多解，输出字典序最小的方向序列，否则输出 -1。
 */

/**
 * 用于方向编号 0~7 的位移向量：
 *  假设我们定义：
 *     0: ↖ (dr=-1, dc=-1)
 *     1: ↑  (dr=-1, dc= 0)
 *     2: ↗ (dr=-1, dc=+1)
 *     3: ←  (dr= 0,  dc=-1)
 *     4: →  (dr= 0,  dc=+1)
 *     5: ↙ (dr=+1, dc=-1)
 *     6: ↓  (dr=+1, dc= 0)
 *     7: ↘ (dr=+1, dc=+1)
 * 这样从小到大顺序遍历可以保证“字典序最小”。
 */
static const vector<pair<int,int>> directions = {
    {-1, -1}, // 0
    {-1,  0}, // 1
    {-1, +1}, // 2
    { 0, -1}, // 3
    { 0, +1}, // 4
    {+1, -1}, // 5
    {+1,  0}, // 6
    {+1, +1}  // 7
};

// 输入数据
static const int MAXN = 10;
int N, K;
int grid[MAXN][MAXN];

// 访问标记
bool visited[MAXN][MAXN];

// 记录当前路径经过的坐标 (r, c)
vector<pair<int,int>> path_positions;

// 记录当前路径的方向序列（比坐标数少 1）。若长度为 L，表示已经走了 L 步
vector<int> path_directions;

/**
 * edges 用于存储当前路径上已经使用过的线段，每条线段用一对坐标 ((r1,c1),(r2,c2)) 表示。
 * 在继续走下一步时，需要判定新线段与这些线段是否会交叉。
 */
vector<pair<pair<int,int>, pair<int,int>>> edges;

/**
 * 用于保存最终找到的字典序最小可行解。若无解则保持空字符串。
 * 当找到一个可行解时，用它与全局 best_path 比较更新。
 */
string best_path = "";

/**
 * 判断两条线段是否严格相交（不含端点重合）。
 *  - p1->p2, p3->p4 均为线段在平面中的端点坐标。
 *  - 若它们仅共享端点，则不算交叉，这是路径本身相邻的情况。
 */
bool segmentsIntersect(const pair<int,int>& p1, const pair<int,int>& p2,
                      const pair<int,int>& p3, const pair<int,int>& p4) {
    // 如果有端点完全重合，则认为不构成“交叉”。
    if (p1 == p3 || p1 == p4 || p2 == p3 || p2 == p4) {
        return false;
    }

    // 定义 orientation 函数：返回向量叉积的正负结果
    // orientation(a,b,c) > 0  =>  a->b->c 是逆时针
    // orientation(a,b,c) < 0  =>  a->b->c 是顺时针
    // orientation(a,b,c) = 0  =>  三点共线
    auto orientation = [&](const pair<int,int>& A,
                           const pair<int,int>& B,
                           const pair<int,int>& C) {
        // 向量 AB = (B.x - A.x, B.y - A.y)
        // 向量 AC = (C.x - A.x, C.y - A.y)
        // cross(AB, AC) = (Bx - Ax)*(Cy - Ay) - (By - Ay)*(Cx - Ax)
        long long cross_val = 1LL*(B.first - A.first)*(C.second - A.second)
                            - 1LL*(B.second - A.second)*(C.first - A.first);
        if      (cross_val > 0)  return 1;
        else if (cross_val < 0)  return -1;
        else                     return 0;
    };

    // 计算 4 个方向
    int o1 = orientation(p1, p2, p3);
    int o2 = orientation(p1, p2, p4);
    int o3 = orientation(p3, p4, p1);
    int o4 = orientation(p3, p4, p2);

    // 普通严格相交：o1 != o2 && o3 != o4 && (各自一正一负)
    //  但要注意共线时还要判断是否重叠等情况
    if (o1 == 0 && o2 == 0 && o3 == 0 && o4 == 0) {
        // p1, p2, p3, p4 四点共线
        // 在本题由于每个格子只能访问一次，出现真正重叠的可能性极小
        // 但为保证安全，可以进行投影区间的判断。
        // 如果线段有非端点的重叠，也可以算交叉。
        // 简单处理：只要四点共线且没有共享端点（上面已排除），我们就认为交叉了。
        return true;
    }

    // 一般线段相交判定
    if (o1 * o2 < 0 && o3 * o4 < 0) {
        return true;
    }

    return false;
}

/**
 * 回溯函数：
 *  - (r, c): 当前所在坐标
 *  - step:   当前已经走过多少个格子（含起点）。若 step == N*N 则表示访问完全部格子。
 */
void dfs(int r, int c, int step) {
    // 如果已经走满 N*N 个格子，检查是否到达终点 (N-1, N-1)
    if (step == N*N) {
        if (r == N-1 && c == N-1) {
            // 构造出当前路径的方向序列（转成字符串）
            // path_directions 长度 = N*N - 1
            // 我们在 dfs 中每走一步就 push_back 了一个方向
            string candidate;
            candidate.reserve(path_directions.size());
            for (int d : path_directions) {
                candidate.push_back(char('0' + d)); 
            }
            // 若当前 best_path 为空或 candidate 字典序更小，则更新
            if (best_path.empty() || candidate < best_path) {
                best_path = candidate;
            }
        }
        return;
    }

    // 下一步需要访问的格子数字 = step % K
    int requiredDigit = step % K;

    // 依次尝试 8 个方向 d_index
    for (int d_index = 0; d_index < 8; d_index++) {
        int dr = directions[d_index].first;
        int dc = directions[d_index].second;
        int nr = r + dr;
        int nc = c + dc;
        // 判断越界
        if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
            continue;
        }
        // 判断是否已访问
        if (visited[nr][nc]) {
            continue;
        }
        // 判断数字是否符合 (step % K)
        if (grid[nr][nc] != requiredDigit) {
            continue;
        }
        // 检查是否与已有线段交叉
        // 新线段为 ( (r,c)->(nr,nc) )
        pair<int,int> p1 = make_pair(r,c);
        pair<int,int> p2 = make_pair(nr,nc);

        bool crossed = false;
        for (auto &ed : edges) {
            if (segmentsIntersect(ed.first, ed.second, p1, p2)) {
                crossed = true;
                break;
            }
        }
        if (crossed) {
            continue; // 这条路不行
        }

        // 可以走
        visited[nr][nc] = true;
        edges.push_back({p1, p2});
        path_positions.push_back({nr,nc});
        path_directions.push_back(d_index);

        // 递归
        dfs(nr, nc, step + 1);

        // 回溯
        path_directions.pop_back();
        path_positions.pop_back();
        edges.pop_back();
        visited[nr][nc] = false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            cin >> grid[r][c];
        }
    }

    // 如果起点 (0,0) 的数字 != 0，则无解
    if (grid[0][0] != 0){
        cout << -1 << "\n";
        return 0;
    }

    // 初始化访问与路径
    memset(visited, false, sizeof(visited));
    visited[0][0] = true;

    // 起点放入路径
    path_positions.push_back({0, 0});

    // 从起点开始 DFS，step=1 表示已经访问了 1 个格子
    dfs(0, 0, 1);

    // 输出结果
    if (best_path.empty()) {
        cout << -1 << "\n";
    } else {
        cout << best_path << "\n";
    }

    return 0;
}
