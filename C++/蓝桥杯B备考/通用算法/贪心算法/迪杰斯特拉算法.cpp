#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
public:
    int V;  // 图的顶点数
    vector<vector<int>> adjMatrix;  // 邻接矩阵表示图

    Graph(int V) {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, INT_MAX));  // 初始化邻接矩阵
    }

    // 添加边，u和v是节点，w是边的权重
    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;  // 无向图
    }

    // Dijkstra算法实现单源最短路径
    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);  // 存储从src到各个节点的最短距离
        vector<bool> sptSet(V, false);  // sptSet数组记录哪些节点已经被处理过

        dist[src] = 0;  // 起始节点的距离为0

        for (int count = 0; count < V - 1; ++count) {
            int u = minDistance(dist, sptSet);  // 选择一个最短的节点
            sptSet[u] = true;  // 标记为已处理

            // 更新与u相邻的节点的距离
            for (int v = 0; v < V; ++v) {
                if (!sptSet[v] && adjMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                }
            }
        }

        // 打印最短路径
        printSolution(dist);
    }

private:
    // 返回距离源节点最近的未处理节点
    int minDistance(const vector<int>& dist, const vector<bool>& sptSet) {
        int min = INT_MAX, min_index = -1;
        for (int v = 0; v < V; ++v) {
            if (!sptSet[v] && dist[v] < min) {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }

    // 打印最短路径
    void printSolution(const vector<int>& dist) {
        cout << "Vertex \tDistance from Source\n";
        for (int i = 0; i < V; ++i) {
            cout << i << " \t" << dist[i] << endl;
        }
    }
};

int main() {
    Graph g(9);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 5, 4);
    g.addEdge(2, 8, 2);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    g.dijkstra(0);  // 从节点0开始计算最短路径
    return 0;
}
