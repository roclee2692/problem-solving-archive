#include <iostream>
#include <vector>
#include <queue>
#include <climits>//使用INT_MAX INT_MAX

using namespace std;

class Graph{
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

void BFS(int start){
    vector<bool> visited(V,false);
    queue<int> q;

    visited[start]=true;
    q.push(start);

    while(!q.empty()){
        int node=q.front();
        q.pop();
        cout<<node<<" ";
    for(int neighbor:adj[node]){
        if(!visited[neighbor]) {
            visited[neighbor]=true;
            q.push(neighbor);
        }
    }
 }
}
// 查找从起始节点到其他所有节点的最短路径
    void shortestPath(int start) {
        vector<int> dist(V, INT_MAX);  // 存储到各节点的最短距离
        queue<int> q;
        
        dist[start] = 0;  // 起始节点的距离为0
        q.push(start);  // 将起始节点加入队列
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            // 访问当前节点的所有邻接节点
            for (int neighbor : adj[node]) {
                if (dist[neighbor] == INT_MAX) {  // 如果该节点尚未访问
                    dist[neighbor] = dist[node] + 1;  // 更新距离
                    q.push(neighbor);  // 将邻接节点加入队列
                }
            }
        }
        
        // 输出从起始节点到其他节点的最短距离
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX) {
                cout << "No path from " << start << " to " << i << endl;
            } else {
                cout << "Shortest path from " << start << " to " << i << " is " << dist[i] << endl;
            }
        }
    }
};

int main() {
    Graph g(6);  // 创建一个含6个节点的图
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    
    cout << "BFS traversal starting from node 0: ";
    g.BFS(0);  // 从节点0开始BFS遍历
    cout << endl;
    
    cout << "Shortest paths from node 0:" << endl;
    g.shortestPath(0);  // 查找从节点0到所有其他节点的最短路径
    
    return 0;
}