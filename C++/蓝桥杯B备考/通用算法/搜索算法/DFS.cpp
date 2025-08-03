#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
private:
    int V;  // 图的节点数
    vector<vector<int>> adj;  // 邻接表

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // 添加边
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // DFS递归实现
    void DFS(int start) {
        vector<bool> visited(V, false);  // 记录节点是否访问过
        DFSUtil(start, visited);
    }

private:
    // 辅助函数：DFS的递归实现
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;  // 标记当前节点为已访问
        cout << v << " ";  // 访问节点
        
        // 访问当前节点的所有邻接节点
        for (int i = 0; i < adj[v].size(); i++) {
            int neighbor = adj[v][i];
            if (!visited[neighbor]) {  // 如果邻接节点没有被访问
                DFSUtil(neighbor, visited);  // 递归访问
            }
        }
    }
};

int main() {
    Graph g(5);  // 创建一个含5个节点的图
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    cout << "DFS traversal starting from node 0: ";
    g.DFS(0);  // 从节点0开始DFS遍历

    return 0;
}
