#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const int MAXN = 100;
vector<int> post,ino,pre;
unordered_map<int,int> ino_dict;
int pre_idx=0;
void buildPreorder(int post_start, int post_end, int ino_start, int ino_end) {
    if (post_start >= post_end) return;
    int root = post[post_end - 1]; // 后序的最后一个节点是根
    pre[pre_idx++] = root;         // 根存入前序序列

    int idx = ino_dict[root];       // 中序中的位置
    int left_size = idx - ino_start; // 左子树大小
    // 递归处理左子树
    buildPreorder(post_start, post_start + left_size, ino_start, idx);//因为我们用的是左闭右开区间 [start, end)
    // 递归处理右子树                      //所以右端点本来就是不包含的，根节点的元素已经自然排除在外，
    buildPreorder(post_start + left_size, post_end - 1, idx + 1, ino_end);//不需要再额外加1。
}



    int main() {
        int n;
        cin >> n;
        post.resize(n);
        ino.resize(n);
        pre.resize(n);
    
        for (int i = 0; i < n; i++) cin >> post[i];
        for (int i = 0; i < n; i++) cin >> ino[i];
    
        for (int i = 0; i < n; i++) ino_dict[ino[i]] = i;
    
        buildPreorder(0, n, 0, n);
    
        cout << "Preorder: ";
        for (int i = 0; i < n; i++) {
            cout << pre[i];
            if (i != n - 1) cout << " ";
        }
        cout << endl;
    
        return 0;
    }