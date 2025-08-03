#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;
#define NIL '-'
typedef char TElemSet;

struct BinaryTreeNode{
    vector<char> data;
    int size;
 };
void PreOrder(BinaryTreeNode* tree){
    if(tree==nullptr||tree->size==0) return;
    stack<int> s;
    s.push(1);

    while(!s.empty()){
        int curr=s.top();
        s.pop();
        if(curr<=tree->size&&tree->data[curr]!=NIL){
            cout<<tree->data[curr];
            int right=2*curr+1;
            int left=2*curr;
            if (right <= tree->size && tree->data[right] != NIL) s.push(right);
            if (left <= tree->size && tree->data[left] != NIL) s.push(left);
        }
    }

}

void InOrder(BinaryTreeNode* tree) {
    if (tree == nullptr || tree->size == 0) return
    stack<int> s;
    int curr=1;

    while((curr<=tree->size&& tree->data[curr] != NIL|| !s.empty())){
        while (curr <= tree->size && tree->data[curr] != NIL) {
            s.push(curr);  // 当前节点入栈
            curr = 2 * curr;  // 移动到左孩子
        } 
        if (!s.empty()) {
            curr= s.top();  // 弹出栈顶节点
            s.pop();
            cout << tree->data[curr];  // 访问当前节点
              // 3. 转向右子树（右孩子可能为空）
              curr = 2 * curr + 1;
        }
    }
}

// 后序遍历非递归实现（关键：记录最后访问的节点）
void PostOrder(BinaryTreeNode* tree) {
    // 空树直接返回
    if (tree == nullptr || tree->size == 0) return;

    stack<int> s;
    int curr = 1;  // 当前节点指针（初始指向根节点）
    int last_visited = 0;  // 记录最后访问的节点下标（初始无效）
    while ((curr <= tree->size && tree->data[curr] != NIL) || !s.empty()) {
        // 1. 向左走到底，将路径上的节点入栈
        if (curr <= tree->size && tree->data[curr] != NIL) {
            s.push(curr);  // 当前节点入栈
            int left = 2 * curr;  // 左孩子下标
            if (left <= tree->size && tree->data[left] != NIL) {
                curr = left;  // 继续向左
            } else {
                curr = 0;  // 无左孩子，置为无效
            }
        } else {
            // 2. 查看栈顶节点（不弹出）
            int temp = s.top();
            // 检查右孩子是否存在且未被访问
            int right = 2 * temp + 1;
            if (right <= tree->size && tree->data[right] != NIL && right != last_visited) {
                curr = right;  // 转向右孩子
            } else {
                // 右子树已处理完毕，访问当前节点
                cout << tree->data[temp];
                last_visited = temp;  // 记录最后访问的节点
                s.pop();  // 弹出栈顶
            }
        }
    }
}

// 主函数：处理输入和输出
int main() {
    int n;
    cin >> n;

    BinaryTreeNode* tree = new BinaryTreeNode;
    tree->data = vector<TElemSet>(n + 1);  // 数据顺序表
    tree->size = n;
    tree->data[0] = NIL;  // 根节点

    // 读取树的数据
    for (int i = 1; i <= n; i++) {
        cin >> tree->data[i];  // 读取字符
    }

    // 调用三种遍历并输出结果
    PreOrder(tree);
    cout << endl;
    InOrder(tree);
    cout << endl;
    PostOrder(tree);
    cout << endl;

    // 释放动态分配的内存
    delete tree;

    return 0;
}