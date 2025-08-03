#include <iostream>
using namespace std;

const int N = 10010;
int fa[N];    // fa[i] 表示元素i的父亲
int sz[N];    // sz[i] 表示以i为根的集合的大小（秩）

// 初始化：每个节点自成一个集合，大小是1
void init(int n) {
    for(int i = 1; i <= n; i++) {
        fa[i] = i; // 父亲指向自己
        sz[i] = 1; // 每个集合初始大小为1
    }
}

// 查找：带路径压缩
int find(int x) {
    if(fa[x] != x)  fa[x] = find(fa[x]); // 路径压缩：让x直接指向根节点
    return fa[x];
}

// 合并：按集合大小合并
void merge(int x, int y) {
    int fx = find(x); // 找x的根
    int fy = find(y); // 找y的根
    if(fx == fy) return; // 已经在同一个集合，无需合并

    if(sz[fx] < sz[fy]) {
        // 把小的集合接到大的集合上
        fa[fx] = fy;
        sz[fy] += sz[fx]; // 更新新的根的大小
    } else {
        fa[fy] = fx;
        sz[fx] += sz[fy];
    }
}

int main() {
    int n = 5; // 5个元素

    init(n);

    merge(1, 2); // 合并1和2
    merge(3, 4); // 合并3和4

    if(find(1) == find(2)) {
        cout << "1 和 2 属于同一个集合" << endl;
    } else {
        cout << "1 和 2 不属于同一个集合" << endl;
    }

    if(find(1) == find(3)) {
        cout << "1 和 3 属于同一个集合" << endl;
    } else {
        cout << "1 和 3 不属于同一个集合" << endl;
    }

    merge(2, 3); // 合并2和3，现在1、2、3、4都应该连在一起了

    if(find(1) == find(3)) {
        cout << "1 和 3 现在属于同一个集合了" << endl;
    } else {
        cout << "1 和 3 还是不属于同一个集合" << endl;
    }

    return 0;
}
