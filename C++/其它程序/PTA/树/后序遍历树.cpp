#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;

struct TreeNode{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* middle;
    TreeNode(int x):data(x),left(nullptr),right(nullptr),middle(nullptr){}
};
void postOrder(TreeNode* root){
    if(!root) return;
    postOrder(root->left); //递归保证输出完遍历左子树后才会输出右子树 中间 最后是根节点 后序遍历
    postOrder(root->right);
    postOrder(root->middle);
    cout<<root->data<<endl;
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int rtval,lfch,rich,mich;
    cin>>rtval>>lfch>>rich>>mich;
    TreeNode* root=new TreeNode(rtval);
    root->left=new TreeNode(lfch);
    root->right=new TreeNode(rich);
    root->middle=new TreeNode(mich);
postOrder(root);
delete root->left;
delete root->right;
delete root->middle;
delete root;

  return 0;
}
