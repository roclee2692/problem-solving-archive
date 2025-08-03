#include <iostream>
using namespace std;

const int N = 10010; // 假设元素个数最大是10000
int fa[N]; // fa[i] 表示元素i的父亲节点（最开始每个元素都是自己的父亲）

// 初始化：每个元素自己是自己所在集合的代表
void init(int n) {
    for(int i = 1; i <= n; i++)  fa[i] = i; // 初始化：父亲指向自己
}

// 查找：找到元素x所在集合的代表（根节点）
// 并在查找过程中进行路径压缩（让中间的点直接连到根上，加速后续查找）
int find(int x) {
    if(fa[x] == x)  return x; // 如果x是自己的父亲，说明x是根节点，返回它
     return fa[x] = find(fa[x]); 
        // 递归找父亲，顺便把fa[x]直接指向根节点，压缩路径
}

// 合并：把x和y所在的两个集合合并
void merge(int x, int y) {
    fa[find(x)] = find(y);
    // 找到x的根节点，找到y的根节点，然后让x的根节点挂到y的根节点上
    // 这样两个集合就合并了
}

int main() {
    int n = 5; // 假设有5个元素，编号1~5

    init(n); // 初始化并查集

    merge(1, 2); // 合并1号和2号元素所在的集合
    merge(3, 4); // 合并3号和4号元素所在的集合

    // 查询元素是否在同一个集合
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

    merge(2, 3); // 把2和3也合并

    if(find(1) == find(3)) {
        cout << "1 和 3 现在属于同一个集合了" << endl;
    } else {
        cout << "1 和 3 还是不属于同一个集合" << endl;
    }

    return 0;
}
