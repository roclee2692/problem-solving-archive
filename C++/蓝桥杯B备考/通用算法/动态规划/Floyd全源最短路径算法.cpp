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
        for (int i = 0; i < V; ++i) adjMatrix[i][i] = 0;  // 自己到自己的距离是0
    }

    // 添加边，u和v是节点，w是边的权重
    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;  // 无向图
    }

    // Floyd算法实现所有节点对的最短路径
    void floydWarshall() {
        vector<vector<int>> dist = adjMatrix;

        // 进行中间节点的更新
        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        // 打印所有节点对的最短路径
        printSolution(dist);
    }

private:
    // 打印所有节点对的最短路径
    void printSolution(const vector<vector<int>>& dist) {
        cout << "Shortest distances between every pair of vertices:\n";
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][j] == INT_MAX)
                    cout << "INF ";
                else
                    cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 10);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 0, 7);

    g.floydWarshall();  // 运行Floyd算法计算所有节点对的最短路径
    return 0;
}
