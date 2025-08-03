#include <iostream>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){};
};

void preOrderTraversal(TreeNode* root){
    if(root==nullptr) return;

    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        TreeNode* node=s.top();
        s.pop();
        cout<<node->val<<" ";
        if(node->right) s.push(node->right);
        if(node->left) s.push(node->left);//后进先出，先序遍历先访问左子树
    } 
    cout<<endl;
}

void inOrderTraversal(TreeNode* root){
    if(root==nullptr) return;

    stack<TreeNode*> s;
    TreeNode* curr=root;
    while(curr!=nullptr||!s.empty()){
        while(curr!=nullptr){
            s.push(curr);
            curr=curr->left;
        }//之后curr为空，要回溯 栈是后进先出取出的第一个既是回溯的点
        curr=s.top();
        s.pop();
        cout<<curr->val<<" ";
        if(curr->right) curr=curr->right;
    }
    cout<<endl;
}

void postOrderTraversal(TreeNode* root){
    if(root==nullptr) return;
    stack<TreeNode*> s1,s2;
    s1.push(root);
    while(!s1.empty()){
        TreeNode* curr=s1.top();
        s1.pop();
        s2.push(curr);

        if(curr->left) s1.push(curr->left);//这里用了两个栈，负负得正 左右顺序
        if(curr->right) s1.push(curr->right);
        
    }
    while(!s2.empty()){
        cout<<s2.top()->val<<" ";
        s2.pop();
    }
    cout<<endl;
}

int main() {
    // 构造示例二叉树
    //          1
    //         / \
    //        2   3
    //       / \   / \
    //      4   5 6   7

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    cout << "Pre-order Traversal: ";
    preOrderTraversal(root);  // 输出: 1 2 4 5 3 6 7

    cout << "In-order Traversal: ";
    inOrderTraversal(root);  // 输出: 4 2 5 1 6 3 7

    cout << "Post-order Traversal: ";
    postOrderTraversal(root);  // 输出: 4 5 2 6 7 3 1

    return 0;
}