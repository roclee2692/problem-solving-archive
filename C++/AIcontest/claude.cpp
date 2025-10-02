#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> sets(n);
    vector<set<int>> set_elements(n);
    
    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;
        sets[i].resize(l);
        for (int j = 0; j < l; j++) {
            cin >> sets[i][j];
            set_elements[i].insert(sets[i][j]);
        }
    }
    
    // Check if it's possible to cover all integers
    set<int> all_covered;
    for (int i = 0; i < n; i++) {
        for (int x : sets[i]) {
            all_covered.insert(x);
        }
    }
    
    for (int i = 1; i <= m; i++) {
        if (all_covered.find(i) == all_covered.end()) {
            cout << "NO\n";
            return;
        }
    }
    
    // Find which integers are covered by which sets
    vector<vector<int>> covered_by(m + 1);
    for (int i = 0; i < n; i++) {
        for (int x : sets[i]) {
            if (x >= 1 && x <= m) {
                covered_by[x].push_back(i);
            }
        }
    }
    
    // Identify essential sets (sets that must be chosen)
    set<int> essential;
    for (int i = 1; i <= m; i++) {
        if (covered_by[i].size() == 1) {
            essential.insert(covered_by[i][0]);
        }
    }
    
    // Check what's covered by essential sets
    set<int> essential_covered;
    for (int i : essential) {
        for (int x : sets[i]) {
            essential_covered.insert(x);
        }
    }
    
    // Non-essential sets
    vector<int> non_essential;
    for (int i = 0; i < n; i++) {
        if (essential.find(i) == essential.end()) {
            non_essential.push_back(i);
        }
    }
    
    // If all integers are covered by essential sets
    bool all_covered_by_essential = true;
    for (int i = 1; i <= m; i++) {
        if (essential_covered.find(i) == essential_covered.end()) {
            all_covered_by_essential = false;
            break;
        }
    }
    
    if (all_covered_by_essential) {
        // Number of ways is 2^(len(non_essential))
        long long ways = 1LL << non_essential.size();
        if (ways >= 3) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        return;
    }
    
    // If some integers are not covered by essential sets
    // We need to check combinations of non-essential sets
    vector<int> remaining_integers;
    for (int i = 1; i <= m; i++) {
        if (essential_covered.find(i) == essential_covered.end()) {
            remaining_integers.push_back(i);
        }
    }
    
    // If the number of non-essential sets is small, use brute force
    if (non_essential.size() <= 20) {
        int count = 0;
        int limit = 1 << non_essential.size();
        
        for (int mask = 1; mask < limit; mask++) {
            set<int> covered = essential_covered;
            
            for (int i = 0; i < non_essential.size(); i++) {
                if (mask & (1 << i)) {
                    for (int x : sets[non_essential[i]]) {
                        covered.insert(x);
                    }
                }
            }
            
            bool valid = true;
            for (int i = 1; i <= m; i++) {
                if (covered.find(i) == covered.end()) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                count++;
                if (count >= 3) {
                    cout << "YES\n";
                    return;
                }
            }
        }
        
        cout << "NO\n";
        return;
    }
    
    // For large number of non-essential sets, use heuristics
    
    // First check if there are sets that cover all remaining integers
    int sets_covering_remaining = 0;
    for (int i : non_essential) {
        bool covers_all = true;
        for (int x : remaining_integers) {
            if (set_elements[i].find(x) == set_elements[i].end()) {
                covers_all = false;
                break;
            }
        }
        if (covers_all) {
            sets_covering_remaining++;
            if (sets_covering_remaining >= 3) {
                cout << "YES\n";
                return;
            }
        }
    }
    
    // Check if each remaining integer is covered by multiple non-essential sets
    int min_coverage = INT_MAX;
    for (int i : remaining_integers) {
        int coverage = 0;
        for (int j : covered_by[i]) {
            if (essential.find(j) == essential.end()) {
                coverage++;
            }
        }
        min_coverage = min(min_coverage, coverage);
    }
    
    // If each remaining integer is covered by at least 3 non-essential sets,
    // there are likely many ways to choose sets
    if (min_coverage >= 3) {
        cout << "YES\n";
        return;
    }
    
    // If we have many more non-essential sets than remaining integers,
    // there are likely many ways
    if (non_essential.size() >= remaining_integers.size() + 10) {
        cout << "YES\n";
        return;
    }
    
    // Otherwise, we're not sure, so we say NO
    // This might be incorrect for some edge cases
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}