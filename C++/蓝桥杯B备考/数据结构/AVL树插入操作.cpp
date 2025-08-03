#include <iostream>
#include <algorithm> // 用于std::max
using namespace std;

// 定义AVL树节点结构
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int d):data(d),left(nullptr),right(nullptr),height(1){}
};

int height(Node* node){
    return node?node->height:0;
}

int getbalancefactor(Node* node){
    return node?height(node->left)-height(node->right):0;
}

Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    // 更新高度
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // 返回新的根节点
}

// 左旋操作
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // 进行旋转
    y->left = x;
    x->right = T2;

    // 更新高度
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // 返回新的根节点
}
// 插入操作
Node* insert(Node* node, int key) {
    // 1. 普通的二叉搜索树插入
    if (!node) {
        return new Node(key);
    }

    if (key < node->data) {
        node->left = insert(node->left, key);
    } else if (key > node->data) {
        node->right = insert(node->right, key);
    } else {
        return node; // 不允许插入重复的值
    }
     // 2. 更新节点的高度
     node->height = 1 + max(height(node->left), height(node->right));

     // 3. 检查该节点是否失衡，如果失衡，进行旋转操作
     int balanceFactor = getbalancefactor(node);
 
     // 左子树比右子树高，且左子树的左子树更高，进行右旋
     if (balanceFactor > 1 && key < node->left->data) {
         return rightRotate(node); 
     }
 
     // 右子树比左子树高，且右子树的右子树更高，进行左旋
     if (balanceFactor < -1 && key > node->right->data) {
         return leftRotate(node);
     }
 
     // 左子树比右子树高，且右子树的左子树更高，先左旋再右旋
     if (balanceFactor > 1 && key > node->left->data) {
         node->left = leftRotate(node->left);
         return rightRotate(node);
     }
 
     // 右子树比左子树高，且左子树的右子树更高，先右旋再左旋
     if (balanceFactor < -1 && key < node->right->data) {
         node->right = rightRotate(node->right);
         return leftRotate(node);
     }
 
     return node; // 如果没有失衡，直接返回当前节点
 }
 // 中序遍历（用于打印树）
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    // 插入一些节点
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 25);
    root = insert(root, 5);

    // 打印中序遍历结果
    cout << "In-order traversal of the constructed AVL tree is: ";
    inOrder(root);

    return 0;
}