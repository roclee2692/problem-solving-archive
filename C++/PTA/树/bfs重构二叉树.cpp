#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};
 
TreeNode* build(const vector<string>& a){
    if(a.empty()||a[0]=="#") return nullptr;
    TreeNode* root=new TreeNode(stoi(a[0]));
    queue<TreeNode*> q;
    q.push(root);
    size_t i=1;
//q.empty()：为 true 表示“是空的”，此时 不能执行。
//!q.empty()：为 true 表示“不是空的”，此时 可以执行。
    while(!q.empty()&&i<a.size()){
        TreeNode* cur=q.front();
        q.pop();
        if(a[i]!="#"){
            cur->left=new TreeNode(stoi(a[i]));
            q.push(cur->left);
        }
        if(++i==a.size()) break;
        if(a[i]!="#"){
            cur->right=new TreeNode(stoi(a[i]));
            q.push(cur->right);
        }
        i++;
    }
    return root;
}

void levelPrint(TreeNode* root){
    if(!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* node=q.front();
        q.pop();
        cout<<node->val<<endl;
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    if(!(cin>>n)) return 0;
    vector<string> seq(n);
    for (int i = 0; i < n; ++i) cin >> seq[i];
    TreeNode* root = build(seq);
    levelPrint(root);
  return 0;
}
