#include <vector>
#include <queue>
#include <iostream>
using namespace std;

bool canFinish(int n, vector<vector<int>>& p) {
    // deg[i] 存储课程 i 的入度，初始化为 0
    vector<int> deg(n, 0);
    
    // g[i] 存储课程 i 的后继课程，即依赖于课程 i 的课程
    vector<vector<int>> g(n);

    // 构建图和计算每个课程的入度
    for (auto& e : p) {
        // 课程 e[0] 依赖于课程 e[1]，将课程 e[0] 放入课程 e[1] 的后继课程列表中
        g[e[1]].push_back(e[0]);
        
        // 课程 e[0] 的入度增加，表示有一个课程依赖于它
        deg[e[0]]++;
    }

    // 使用队列存储可以立即学习的课程（即入度为 0 的课程）
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            // 入度为 0 的课程加入队列，表示这些课程没有前置课程，可以立即学习
            q.push(i);
        }
    }

    int cnt = 0; // 用于记录已学习的课程数量
    
    // 拓扑排序
    while (!q.empty()) {
        int c = q.front(); q.pop(); // 从队列中取出一个课程
        cnt++; // 计数已学习的课程
        
        // 对课程 c 的所有后继课程减少入度
        for (int nxt : g[c]) {
            // 如果某后继课程的入度减为 0，表示可以学习该课程，加入队列
            if (--deg[nxt] == 0) {
                q.push(nxt);
            }
        }
    }

    // 如果已学习的课程数量等于总课程数量，返回 true，否则返回 false
    return cnt == n;
}

int main() {
    // 示例：共有 4 门课程，课程依赖关系如下
    vector<vector<int>> prerequisites = {{1, 0}, {2, 1}, {3, 2}};  // 课程 1 依赖课程 0，课程 2 依赖课程 1，课程 3 依赖课程 2
    
    int numCourses = 4;  // 总课程数
    
    // 调用 canFinish 函数判断是否能完成所有课程
    if (canFinish(numCourses, prerequisites)) {
        cout << "可以完成所有课程。" << endl;
    } else {
        cout << "无法完成所有课程。" << endl;
    }

    return 0;
}
