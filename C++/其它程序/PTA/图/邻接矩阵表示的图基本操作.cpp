#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;

struct Graph{
    int max_vertex;// 最大顶点数
    int no_edge; // 无边标记值
    int n; // 当前顶点数
    vector<char> vertices;// 顶点信息数组（存储每个顶点的字符信息）
    vector<vector<int>> adj;// 邻接矩阵（存储边的权重）
    // 构造函数 初始化图的最大顶点数、无边标记值、当前顶点数、顶点信息
    Graph(int kMax,int noEdge,int curN,const vector<char>& v)
    : max_vertex(kMax), no_edge(noEdge), n(curN), vertices(v) {
        adj.resize(max_vertex, vector<int>(max_vertex, noEdge));  // 初始化邻接矩阵，默认无边
    }
   //const 修饰函数 成员函数，表示该成员函数 不会修改 类的任何成员变量。
// 判断边是否存在（带越界检查）
    bool edgeExists(int u, int v) const {
        // 判断 u, v 是否在有效范围内，并且检查 adj[u][v] 是否为无边标记
        return (u >= 0 && u < n && v >= 0 && v < n) 
            ? (adj[u][v] != no_edge) 
            : false;
    }

     // 查找顶点的第一个邻接点
     int firstAdjacent(int v) const {
        if (v < 0 || v >= n) return -1;  // 如果顶点 v 不在有效范围内，返回 -1
        for (int j = 0; j < n; ++j) {
            if (adj[v][j] != no_edge) return j;  // 找到第一个与 v 相邻的顶点
        }
        return -1;  // 如果没有邻接点，返回 -1
    }

    // 删除边
    void removeEdge(int u, int v) {
        if (u >= 0 && u < n && v >= 0 && v < n) {
            adj[u][v] = no_edge;  // 将边的权重设置为无边标记
        }
    }

    void removeVertex(int v){
        if(v<0||v>=n) return;
         // 1. 用最后一个顶点覆盖被删除顶点的信息
         vertices[v] = vertices.back();
         vertices.pop_back();
          // 2. 覆盖行：将最后一行复制到被删除行 出度//第?v?行?=?顶点?v?发出的所有边（出度）。
        for (int j = 0; j < n; ++j) {
            adj[v][j] = adj[n-1][j];
        }

        // 3. 覆盖列：将最后一列复制到被删除列  入度  第?v?列?=?指向顶点?v?的所有边（入度）。
        for (int i = 0; i < n; ++i) {
            adj[i][v] = adj[i][n-1];
        }

        // 4. 调整顶点数（最后一行/列不再使用）
        n--;
    }

     // 统计当前边数
     int countEdges() const {
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adj[i][j] != no_edge) cnt++;  // 统计边的个数
            }
        }
        return cnt;
    }
};
 
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
 // 输入处理
 int kMax, noEdge, n, m;
 cin >> kMax >> noEdge >> n >> m;  // 读取最大顶点数、无边标记、当前顶点数和边数
 
 vector<char> vertices(n);  // 顶点信息
 for (int i = 0; i < n; ++i) {
     cin >> vertices[i];  // 读取每个顶点的字符信息
 }
 // 初始化图
 Graph g(kMax, noEdge, n, vertices);
  
    // 插入边
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;  // 读取每条边的起点、终点和权重
        if (u >= 0 && u < n && v >= 0 && v < n) {
            g.adj[u][v] = w;  // 在邻接矩阵中插入边
        }
    }
  // 读取操作参数
  int checkEdges[2][2];  // 存储待检查的两条边
  cin >> checkEdges[0][0] >> checkEdges[0][1];
  cin >> checkEdges[1][0] >> checkEdges[1][1];
     
  int checkAdj;  // 存储待检查的顶点
  cin >> checkAdj;
  
  int delEdgeU, delEdgeV;  // 待删除的边
  cin >> delEdgeU >> delEdgeV;
  
  int delVertex;  // 待删除的顶点
  cin >> delVertex;

  // 输出初始邻接矩阵
  cout << "邻接矩阵为：\n";
  for (int i = 0; i < g.n; ++i) {
      for (int j = 0; j < g.n; ++j) {
          cout << g.adj[i][j] << " ";
      }
      cout << "\n";
  }
    // 输出顶点数
    cout << "顶点数 = " << g.n << "\n";

    // 检查边存在性
    for (auto& e : checkEdges) {
        int u = e[0], v = e[1];
        cout << "<" << u << ", " << v << "> 的存在性 = " 
             << (g.edgeExists(u, v) ? 1 : 0) << "\n";
    }

      // 查找第一个邻接点
      cout << "顶点" << checkAdj << "的第一个邻接点 = " 
      << g.firstAdjacent(checkAdj) << "\n";

    // 删除边并检查
    g.removeEdge(delEdgeU, delEdgeV);
    cout << "<" << delEdgeU << ", " << delEdgeV << "> 的存在性 = " 
         << (g.edgeExists(delEdgeU, delEdgeV) ? 1 : 0) << "\n";
  // 删除顶点并输出
  cout << "待删除的顶点信息为 " << g.vertices[delVertex] << "\n";
  g.removeVertex(delVertex);
  // 输出最终状态
  cout << "当前顶点数 = " << g.n << "\n";
  cout << "当前边数 = " << g.countEdges() << "\n";
  for (char c : g.vertices) cout << c;
  cout << "\n邻接矩阵为：\n";
  for (int i = 0; i < g.n; ++i) {
      for (int j = 0; j < g.n; ++j) {
          cout << g.adj[i][j] << " ";
      }
      cout << "\n";
  }
  return 0;
}
