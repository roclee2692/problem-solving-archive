/*  7-6  邮递员最小疲劳
 *  解法：枚举高度区间 + BFS 判断可达
 *  兼容 C++11
 */

#include <bits/stdc++.h>
using namespace std;

/*---------------------------------*
 *          全局数据结构           *
 *---------------------------------*/
struct Pos { int x, y; };          // 网格坐标

/*---------------------------------*
 *            主程序入口           *
 *---------------------------------*/
int main() {
    ios::sync_with_stdio(false);  cin.tie(nullptr);
    /* -------- 读入地图 & 寻找 P/K -------- */
    int N;
    if (!(cin >> N)) return 0;

    vector<string> g(N);           // 字符地图：P/K/ .
    for (int i = 0; i < N; ++i) cin >> g[i];

    vector<vector<int>> h(N, vector<int>(N));  // 高度矩阵
    vector<int> allHeights; allHeights.reserve(N * N);

    Pos post;                      // 邮局坐标
    vector<Pos> houses;            // 所有房屋 K 坐标

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            cin >> h[i][j];
            allHeights.push_back(h[i][j]);

            if (g[i][j] == 'P') post = {i, j};
            if (g[i][j] == 'K') houses.push_back({i, j});
        }

    /* -------- 对高度去重并排序 -------- */
    sort(allHeights.begin(), allHeights.end());
    allHeights.erase(unique(allHeights.begin(), allHeights.end()), allHeights.end());
    const int M = static_cast<int>(allHeights.size());

    const int postH = h[post.x][post.y];
    const int postIdx = lower_bound(allHeights.begin(), allHeights.end(), postH) - allHeights.begin();
    const int need = static_cast<int>(houses.size());

    /* -------- 预生成 8 个方向增量 -------- */
    vector<pair<int,int>> dirs;
    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy)
            if (dx || dy) dirs.push_back({dx, dy});   // 排除 (0,0)

    /* -------- 可行性判定：BFS -------- */
    auto reachable = [&](int lo, int hi) -> bool {
        if (postH < lo || postH > hi) return false;   // 邮局本身必须落区间

        vector<vector<char>> vis(N, vector<char>(N, 0));
        queue<Pos> q;
        q.push(post); vis[post.x][post.y] = 1;

        int delivered = 0;
        while (!q.empty()) {
            Pos cur = q.front(); q.pop();
            if (g[cur.x][cur.y] == 'K') ++delivered;

            for (const auto& d : dirs) {
                int nx = cur.x + d.first, ny = cur.y + d.second;
                if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                if (vis[nx][ny]) continue;
                int hh = h[nx][ny];
                if (hh < lo || hh > hi) continue;     // 高度不在区间 ? 不可走
                vis[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
        return delivered == need;
    };

    /* -------- 双指针滑窗枚举 [lo, hi] -------- */
    int ans = INT_MAX;
    for (int l = 0, r = postIdx; l <= postIdx; ++l) {
        /* 移动 r 直到当前区间能覆盖所有房屋或 r 超界 */
        while (r < M && !reachable(allHeights[l], allHeights[r])) ++r;
        if (r == M) break;                     // 已经不能再扩大 ? 结束
        ans = min(ans, allHeights[r] - allHeights[l]);
    }

    cout << ans << '\n';
    return 0;
}
