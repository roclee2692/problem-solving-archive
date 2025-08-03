#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;
int n;
// 二叉树节点定义
struct TreeNode {
    int value;  // 节点的值
    TreeNode* left;   // 左子树
    TreeNode* right;  // 右子树
    TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
};
 TreeNode* buildTree(vector<string>& preorderseq, size_t& idx){
    if(idx>=preorderseq.size()) return nullptr;
    string val = preorderseq[idx++];
    if (val == "#") return nullptr;  // 如果是 #，表示空节点
    TreeNode* node = new TreeNode(stoi(val));  // 创建节点
    node->left = buildTree(preorderseq, idx);  // 构建左子树
    node->right = buildTree(preorderseq, idx);  // 构建右子树
    return node;
 }

 void preorder(TreeNode* root){
    if(!root) return;
    cout<<root->value<<endl;
    preorder(root->left);
    preorder(root->right);
 }
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    vector<string> preorderseq(n);
    for(int i=0;i<n;i++) cin>>preorderseq[i];
    size_t idx=0;
    TreeNode* root=buildTree(preorderseq,idx);
    preorder(root);

  return 0;
}
