#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> sets(n);
        vector<int> count(m + 1, 0); // 记录每个元素被多少个集合包含
        vector<bool> covered(m + 1, false); // 记录每个元素是否被至少一个集合包含
        
        // 读取集合并初始化count和covered数组
        for (int i = 0; i < n; ++i) {
            int l;
            cin >> l;
            vector<int> s(l);
            for (int j = 0; j < l; ++j) {
                cin >> s[j];
                count[s[j]]++;
                covered[s[j]] = true;
            }
            sets[i] = s;
        }
        
        // 步骤1：检查是否所有1..m都被覆盖
        bool all_covered = true;
        for (int x = 1; x <= m; ++x) {
            if (!covered[x]) {
                all_covered = false;
                break;
            }
        }
        if (!all_covered) {
            cout << "NO\n";
            continue;
        }
        
        // 步骤2：检查是否有至少两个覆盖集
        int cover_sets = 0;
        for (auto& s : sets) {
            int l = s.size();
            if (l < m) continue; // 大小小于m的集合不可能是覆盖集
            
            // 检查是否包含1..m的所有元素
            vector<bool> has(m + 1, false);
            for (int x : s) {
                has[x] = true;
            }
            bool is_cover = true;
            for (int x = 1; x <= m; ++x) {
                if (!has[x]) {
                    is_cover = false;
                    break;
                }
            }
            if (is_cover) {
                cover_sets++;
                if (cover_sets >= 2) break; // 找到两个即可
            }
        }
        if (cover_sets >= 2) {
            cout << "YES\n";
            continue;
        }
        
        // 步骤3：检查是否有一个覆盖集且n >= 3
        if (cover_sets >= 1 && n >= 3) {
            cout << "YES\n";
            continue;
        }
        
        // 步骤4：检查是否有至少两个冗余集合
        int redundant = 0;
        for (auto& s : sets) {
            bool is_redundant = true;
            for (int x : s) {
                // 如果元素x只被当前集合包含，则当前集合不是冗余的
                if (count[x] <= 1) {
                    is_redundant = false;
                    break;
                }
            }
            if (is_redundant) {
                redundant++;
                if (redundant >= 2) break; // 找到两个即可
            }
        }
        if (redundant >= 2) {
            cout << "YES\n";
            continue;
        }
        
        // 所有条件都不满足
        cout << "NO\n";
    }
    return 0;
}
    