#include <iostream>
using namespace std;

struct TreeNode{
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x):value(x),left(nullptr),right(nullptr){}
};

TreeNode* insert(TreeNode* root,int value){
    if(root==nullptr) return new TreeNode(value);
    if(value < root->value){
        root->left=insert(root->left,value);
    }
    else {
        root->right=insert(root->right,value);
    }
    return root;
}

TreeNode* search(TreeNode* root,int value){
    if(root==nullptr||root->value==value){
        return root;
    }

    if(value<root->value){
        return search(root->left,value);
    }else{
        return search(root->right,value);
    }
}

// 获取右子树中的最小节点
TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}
TreeNode* deleteNode(TreeNode* root,int value){
if(root==nullptr) return root;

if(value<root->value){
    root->left=deleteNode(root->left,value);
}else if(value>root->value){
    root->right=deleteNode(root->right,value);
}else{
    if(root->left==nullptr){
        TreeNode* temp=root->right;
        delete root;
        return temp;
    }else if(root->right==nullptr){
        TreeNode* temp=root->left;
        delete root;
        return temp;
    }
        
      // 找到右子树中的最小节点（即后继节点）
      TreeNode* temp = minValueNode(root->right);
      root->value = temp->value;
      root->right = deleteNode(root->right, temp->value);
}
return root;
}


// 打印树的前序遍历
void preOrder(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->value << " ";
    preOrder(root->left);
    preOrder(root->right);
}
// 打印树的中序遍历
void inOrder(TreeNode* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->value << " ";
    inOrder(root->right);
}
// 打印树的后序遍历
void postOrder(TreeNode* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->value << " ";
}
// 创建一个完全二叉树
TreeNode* createCompleteBinaryTree() {
    TreeNode* root = nullptr;
    root = insert(root, 10);

    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 12);
    root = insert(root, 18);
    return root;
}

// 主函数：测试各项功能
int main() {
    TreeNode* root = createCompleteBinaryTree();  // 创建完全二叉树

    cout << "前序遍历: ";
    preOrder(root);
    cout << endl;

    cout << "中序遍历: ";
    inOrder(root);
    cout << endl;

    cout << "后序遍历: ";
    postOrder(root);
    cout << endl;

    // 查找操作
    int searchValue = 7;
    TreeNode* foundNode = search(root, searchValue);
    if (foundNode) {
        cout << "找到节点 " << searchValue << "。\n";
    } else {
        cout << "未找到节点 " << searchValue << "。\n";
    }

    // 删除操作
    int deleteValue = 7;
    cout << "删除节点 " << deleteValue << " 后，进行中序遍历：\n";
    root = deleteNode(root, deleteValue);
    inOrder(root);
    cout << endl;

    return 0;
}