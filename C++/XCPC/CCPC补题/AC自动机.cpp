#include <bits/stdc++.h>
using namespace std;

const int SIG = 26;  // a~z
struct Node {
    int nxt[SIG];
    int fail;
    vector<int> out;     // 存该节点对应的单词编号列表
    Node() : fail(0) { memset(nxt, 0, sizeof(nxt)); }
};

struct AC {
    vector<Node> tr;
    AC() { tr.emplace_back(); }

    void insert(const string& s, int id) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!tr[u].nxt[c]) {
                tr[u].nxt[c] = tr.size();
                tr.emplace_back();
            }
            u = tr[u].nxt[c];
        }
        tr[u].out.push_back(id);   // 一条模式串的编号
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < SIG; ++c) {
            int v = tr[0].nxt[c];
            if (v) { tr[v].fail = 0; q.push(v); }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int c = 0; c < SIG; ++c) {
                int &v = tr[u].nxt[c];
                if (v) {
                    tr[v].fail = tr[ tr[u].fail ].nxt[c];
                    // 继承 fail 节点的输出列表（但不合并计数）
                    tr[v].out.insert(tr[v].out.end(),
                                     tr[ tr[v].fail ].out.begin(),
                                     tr[ tr[v].fail ].out.end());
                    q.push(v);
                } else {
                    v = tr[ tr[u].fail ].nxt[c];   // 压缩转移
                }
            }
        }
    }

    /* 返回出现过的不同模式串数量 */
    int query(const string& text, int n) {
        vector<char> vis(n, 0);
        int cnt = 0, u = 0;

        for (char ch : text) {
            u = tr[u].nxt[ch - 'a'];
            for (int id : tr[u].out) {   // 遍历所有匹配到的模式
                if (!vis[id]) {
                    vis[id] = 1;
                    ++cnt;
                }
            }
        }
        return cnt;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;  if (!(cin >> T)) return 0;
    while (T--) {
        int n; cin >> n;
        vector<string> pat(n);
        AC ac;
        for (int i = 0; i < n; ++i) {
            cin >> pat[i];
            ac.insert(pat[i], i);
        }
        ac.build();
        string article; cin >> article;
        cout << ac.query(article, n) << '\n';
    }
    return 0;
}
