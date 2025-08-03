#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int u, v, weight;  // 边的两个端点u、v和边的权重weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;  // 按权重排序，最小的边在前面
    }
};

// 并查集 (Union-Find) 数据结构
class UnionFind {
public:
    UnionFind(int n) {
        parent.resize(n);  // 存储每个节点的父节点
        rank.resize(n, 0);  // 用来优化的树的深度
        for (int i = 0; i < n; ++i) parent[i] = i;  // 初始化时，每个节点的父节点是它自己
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);  // 路径压缩
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;  // 合并时选择深度较小的树
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;  // 如果深度相同，合并后树的深度加1
            }
        }
    }

private:
    vector<int> parent, rank;
};

// Kruskal算法的实现   克鲁斯克尔算法
void kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());  // 按边的权重排序
    UnionFind uf(n);  // 初始化并查集
    int mstWeight = 0;  // 最小生成树的权重和
    vector<Edge> mst;  // 存储最小生成树的边

    for (auto& edge : edges) {
        // 检查这条边是否会形成环
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unionSets(edge.u, edge.v);  // 合并这两个节点
            mst.push_back(edge);  // 加入到最小生成树
            mstWeight += edge.weight;  // 更新最小生成树的权重
        }
    }

    cout << "Minimum Spanning Tree Weight: " << mstWeight << endl;
    cout << "Edges in MST:" << endl;
    for (auto& edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
}

int main() {
    int n = 4;  // 图中的节点数（编号为0, 1, 2, 3）
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}
    };

    kruskal(n, edges);  // 执行Kruskal算法
    return 0;
}
