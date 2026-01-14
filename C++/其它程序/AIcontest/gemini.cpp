#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    // Check for impossible cases
    bool possible = true;
    if (n > 1 && s[0] == '0' && s[1] == '1') {
        possible = false;
    }
    if (n > 1 && s[n - 2] == '1' && s[n - 1] == '0') {
        possible = false;
    }
    for (int i = 0; i < n - 2; ++i) {
        if (s[i] == '1' && s[i + 1] == '0' && s[i + 2] == '1') {
            possible = false;
            break;
        }
    }

    if (!possible) {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";
    std::vector<int> p(n + 1);
    
    // Find boundaries of unstable blocks
    std::vector<int> stable_indices;
    stable_indices.push_back(0); // Boundary before start
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            stable_indices.push_back(i + 1);
        }
    }
    stable_indices.push_back(n + 1); // Boundary after end

    // Construct the permutation
    for (size_t i = 0; i < stable_indices.size() - 1; ++i) {
        int start_idx = stable_indices[i];
        int end_idx = stable_indices[i+1];
        
        // Place stable numbers
        if (start_idx > 0 && start_idx <= n) {
            p[start_idx] = start_idx;
        }
        
        // Handle unstable blocks
        // Values from start_idx+1 to end_idx-1 go into positions start_idx+1 to end_idx-1
        int block_len = (end_idx - 1) - (start_idx + 1) + 1;
        if (block_len > 0) {
            for (int j = 0; j < block_len; ++j) {
                int pos = start_idx + 1 + j;
                int val = (end_idx - 1) - j;
                p[pos] = val;
            }
        }
    }
     // Place last stable number if it exists
    if (stable_indices.back() > 0 && stable_indices.back() <= n){
         p[stable_indices.back()] = stable_indices.back();
    }


    for (int i = 1; i <= n; ++i) {
        std::cout << p[i] << (i == n ? "" : " ");
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}