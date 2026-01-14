// k 阶满树定义：
// 1. **k 阶满树** 是指树中所有 **非叶节点的度都必须是 k**，即每个非叶节点必须有 k 个子节点。
// 2. **非叶节点**：有子节点的节点。
// 3. **叶节点**：没有子节点的节点，度为 0。
// 4. **根节点**：必须是非叶节点，且度为 k。
// 5. **树的深度**：树的深度可以任意，但树的结构必须满足“每个非叶节点的度都为 k”。
// 
// 特别说明：
// 1. **二阶满树 (k = 2)**：
//    - 在 **二阶满树** 中，根节点的度为 2，根节点有 2 个子节点。
//    - 这两个子节点 **可以是叶节点**（没有子节点，度为 0），符合二阶满树的定义。
//    - 例如，根节点有 2 个子节点，且这两个子节点是叶节点，则树的深度为 2，完全符合二阶满树。
//    - 这种情况对于 k = 2 是 **允许的**，但对于 k ≥ 3 就不适用。
// 
// 2. **k ≥ 3** 满树：
//    - 对于 **k ≥ 3** 的树，**所有非叶节点的度必须是 k**，并且子节点也必须是非叶节点。
//    - **不能有叶节点作为子节点**，因为叶节点的度为 0，不符合非叶节点度为 k 的要求。
//    - 如果树的深度为 2，则根节点有 k 个子节点，且每个子节点也必须有 k 个子节点，依此类推。

// 注：这个定义适用于 **所有的 k 阶满树**，无论是 k = 2 还是 k ≥ 3。
//     k = 2 允许根节点有叶节点作为子节点，而 k ≥ 3 则不允许。
//     如果根节点的子节点是叶节点（度为 0），则树不可能是 k ≥ 3 的满树。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;
int n;
 
void preorder(int node, const vector<vector<int>>& children, vector<int>& pre_order){
    pre_order.push_back(node);
    for(auto& c:children[node]){
        preorder(c,children,pre_order);
    }
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n; // 读取树的节点数
    vector<int> parent(n+1); // 存储每个节点的父节点编号，1-based index
    vector<vector<int>> children(n+1);// 存储每个节点的子节点，1-based index
    int root=-1;
    for(int i=1;i<=n;i++){
        int p;
        cin>>p;
        parent[i]=p;
        if(p==0){
            root=i;
        }else{
            children[p].push_back(i);
        }
    }

    for(auto& child:children){
        sort(child.begin(),child.end());//确保兄弟节点升序访问
    }

    int k_max=0;
    vector<int> degrees(n+1,0);

    for(int i=1;i<=n;i++){
        degrees[i]=children[i].size();
        k_max=max(k_max,degrees[i]);
    }
    
    bool is_full=true;
    for(int i=1;i<=n;i++){
        if(degrees[i]>0&&degrees[i]!=k_max){
            is_full=0;
            break;
        }
    }
    cout<<k_max<<" "<<(is_full?"yes":"no")<<endl;
    vector<int> pre_order;
    preorder(root, children, pre_order);  // 从根节点开始递归
     // 输出前序遍历结果
     for (size_t i = 0; i < pre_order.size(); ++i) {
        if (i > 0) cout << " ";  // 每个数字之间加空格
        cout << pre_order[i];
    }
    cout << "\n";
  return 0;
}
