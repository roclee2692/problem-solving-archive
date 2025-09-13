#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// -------- 01-Trie （优化版本）---------
struct XORTrie{
    static const int MAXB = 60; // 作为成员常量，更清晰
    
    vector<array<int, 2>> nxt; // 使用 int 类型，节省内存
    int tot; // 节点计数器也使用 int
    
    XORTrie(int max_nodes = 0) { // 构造函数
        if(max_nodes) init(max_nodes);
    }
    
    void init(int max_nodes) { // 初始化函数
        nxt.assign(max_nodes + 2, {0, 0});
        tot = 1; // 根节点编号为1
    }
    
    inline int bit(ll x, int b) { 
        return (int)((x >> b) & 1LL); 
    }
    
    inline void insert(ll x) { // 插入一个数 x
        int u = 1; // 从根节点开始
        for(int b = MAXB; b >= 0; b--) {
            int c = bit(x, b); // 当前位是 0 还是 1
            if(!nxt[u][c]) nxt[u][c] = ++tot; // 如果没有子节点就新建
            u = nxt[u][c]; // 走到子节点
        }
    }
    
    // 返回与 x 异或值最大的"值"
    inline ll query_max_xor(ll x) {
        int u = 1;
        ll y = 0; // y 表示异或值
        for(int b = MAXB; b >= 0; b--) {
            int c = bit(x, b);
            int want = c ^ 1; // 想要的相反位
            if(nxt[u][want]) { 
                u = nxt[u][want]; 
                y |= (1LL << b); // 如果能走到相反位，答案这一位就是 1
            } else { 
                u = nxt[u][c]; // 否则只能走相同位，这一位异或结果是 0
            }
        }
        return y; // 返回的是异或值
    }
};

ll max_xor_pair(const vector<ll> &a) {
    if(a.empty()) return 0;
    if(a.size() == 1) return 0; // 只有一个元素，无法形成对
    
    // 预分配节点：每个数最多 61 位，每位可能新建一个节点
    // 最坏情况，新节点数 ≤ |a| * (MAXB+1)
    XORTrie tr((int)a.size() * (XORTrie::MAXB + 1));
    ll ans = 0;
    
    tr.insert(a[0]); // 插入第一个数
    
    // 从第二个数开始：每次先查再插
    // 要求"两两不同"的最大异或对，保证每次配对对象都是"之前的数"
    for(size_t i = 1; i < a.size(); i++) {
        ans = max(ans, tr.query_max_xor(a[i]));
        tr.insert(a[i]);
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; 
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    
    ll res = max_xor_pair(a);
    cout << res << "\n";
    
    return 0;
}
