#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

struct TreeNode{
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val):value(val),left(nullptr),right(nullptr){}

};

TreeNode* createTree(){
    TreeNode* root=new TreeNode(1);
    root->left=new TreeNode(2);
    root->right=new TreeNode(3);
    root->left->left=new TreeNode(4);
    root->left->right=new TreeNode(5);
    return root;
}

void preOrder(TreeNode* root){
    if(root==nullptr) return;
    cout<<root->value<<" "<<endl;
    preOrder(root->left);
    preOrder(root->right);
}

int main(){
    TreeNode* root=createTree();
    cout<<"preOrder traversal: ";
    preOrder(root);
    cout<<endl;
    return 0;
    }