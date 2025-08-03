#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;

struct TreeNode{
    string val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string x):val(x),left(nullptr),right(nullptr){}
};

TreeNode* bulidexpessiontree(const string& operand1,
    const string& operand2,
    char op){
        TreeNode* root=new TreeNode(string(1,op));
        root->left=new TreeNode(operand1);
        root->right=new TreeNode(operand2);
        return root;
    }

    string printtree(TreeNode* root){
        if(!root) return "";
        if (!root->left && !root->right) return root->val;
        string nl=printtree(root->left);
        string nr=printtree(root->right);
        return "("+nl+")"+root->val+"("+nr+")";
    }
 
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    string operand1, operand2;
    char   op; 
     cin >> operand1 >> operand2 >> op;         // 读入两个操作数和运算符
    TreeNode* root=bulidexpessiontree(operand1,operand2,op);
    cout << printtree(root) << '\n';
    delete root->left;
    delete root->right;
    delete root;

  return 0;
}
