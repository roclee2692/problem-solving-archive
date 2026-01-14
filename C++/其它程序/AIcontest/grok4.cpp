#include <bits/stdc++.h>
using namespace std;

void solve_test_case() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    // Count number of 1s
    int ones = count(s.begin(), s.end(), '1');
    int zeros = n - ones;
    
    // If all 1s or all 0s, use identity permutation
    if (ones == n) {
        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << i << (i < n ? " " : "\n");
        }
        return;
    }
    
    // For stable positions (s_i = 1), p[i] must be i
    vector<int> p(n + 1, 0);
    vector<int> zero_pos; // Positions where s_i = 0
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '1') {
            p[i] = i; // Stable positions are fixed points
        } else {
            zero_pos.push_back(i);
        }
    }
    
    // Check if we can make non-stable positions unstable
    if (zeros == 1) {
        // Single non-stable position cannot be unstable (p[i] = i would make it stable)
        cout << "NO\n";
        return;
    }
    
    // Assign values to non-stable positions
    if (zeros >= 2) {
        // Create a cycle or derangement for non-stable positions
        vector<int> available_values;
        for (int i = 1; i <= n; i++) {
            if (s[i - 1] != '1') {
                available_values.push_back(i);
            }
        }
        
        // Create a single cycle: p[zero_pos[i]] = zero_pos[(i+1)%zeros]
        for (size_t i = 0; i < zero_pos.size(); i++) {
            int curr_pos = zero_pos[i];
            int next_pos = zero_pos[(i + 1) % zero_pos.size()];
            p[curr_pos] = next_pos;
        }
    }
    
    // Output the result
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        cout << p[i] << (i < n ? " " : "\n");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve_test_case();
    }
    
    return 0;
}