#include <iostream>
#include <vector>
using namespace std;

class Graph {
    int no_edge_val;         // 无边标记值
    int n;                   // 当前顶点数
    vector<char> V;          // 顶点信息
    vector<vector<int>> G;   // 邻接矩阵

public:
    Graph(int maxV, int noEdgeVal, int initN, const vector<char>& vertices)
        : no_edge_val(noEdgeVal), n(initN), V(vertices),
          G(maxV, vector<int>(maxV, noEdgeVal)) {}

    void addEdge(int u, int v, int w) {
        if (valid(u) && valid(v)) G[u][v] = w;
    }

    bool hasEdge(int u, int v) const {
        return valid(u) && valid(v) && G[u][v] != no_edge_val;
    }

    int firstAdj(int v) const {
        if (!valid(v)) return -1;
        for (int j = 0; j < n; ++j)
            if (G[v][j] != no_edge_val) return j;
        return -1;
    }

    void removeEdge(int u, int v) {
        if (valid(u) && valid(v)) G[u][v] = no_edge_val;
    }

    void removeVertex(int v) {
        if (!valid(v)) return;
        V[v] = V[n - 1];
        V.pop_back();
        for (int i = 0; i < n; ++i) G[i][v] = G[i][n - 1];
        for (int j = 0; j < n - 1; ++j) G[v][j] = G[n - 1][j];
        n--;
    }

    void printMatrix() const {
        cout << "邻接矩阵为：\n";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cout << G[i][j] << (j == n - 1 ? "\n" : " ");
    }

    void printVertices() const {
        for (int i = 0; i < n; ++i) cout << V[i];
        cout << "\n";
    }

    int countEdges() const {
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (G[i][j] != no_edge_val) cnt++;
        return cnt;
    }

    int vertexCount() const { return n; }
    char vertexInfo(int v) const { return valid(v) ? V[v] : '?'; }

private:
    bool valid(int x) const { return x >= 0 && x < n; }
};

int main() {
    int maxV, noEdgeVal, n, m;
    cin >> maxV >> noEdgeVal >> n >> m;
    vector<char> vertices(n);
    for (int i = 0; i < n; ++i) cin >> vertices[i];

    Graph g(maxV, noEdgeVal, n, vertices);

    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.printMatrix();
    cout << "顶点数 = " << g.vertexCount() << "\n";

    for (int i = 0; i < 2; ++i) {
        int u, v; cin >> u >> v;
        cout << "<" << u << ", " << v << "> 的存在性 = " << g.hasEdge(u, v) << "\n";
    }

    int v; cin >> v;
    cout << "顶点" << v << "的第一个邻接点 = " << g.firstAdj(v) << "\n";

    int u, w; cin >> u >> w;
    g.removeEdge(u, w);
    cout << "<" << u << ", " << w << "> 的存在性 = 0\n";

    int del; cin >> del;
    cout << "待删除的顶点信息为 " << g.vertexInfo(del) << "\n";
    g.removeVertex(del);

    cout << "当前顶点数 = " << g.vertexCount() << "\n";
    cout << "当前边数 = " << g.countEdges() << "\n";
    g.printVertices();
    g.printMatrix();

    return 0;
}
