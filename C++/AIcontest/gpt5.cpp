#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if(!(cin >> T)) return 0;
    while(T--){
        int n; 
        cin >> n;
        string s; 
        cin >> s; // length n, chars '0'/'1'

        // 找连续0段
        vector<pair<int,int>> zeroRuns; // [L,R], 1-indexed
        for(int i=0;i<n;){
            if(s[i]=='0'){
                int j=i;
                while(j<n && s[j]=='0') j++;
                zeroRuns.push_back({i+1, j}); // inclusive
                i=j;
            }else i++;
        }

        bool ok = true;
        for(auto seg: zeroRuns){
            if(seg.second - seg.first + 1 == 1){ ok = false; break; }
        }
        if(!ok){
            cout << "NO\n";
            continue;
        }

        // 构造
        vector<int> p(n+1, 0); // 1..n
        for(int i=1;i<=n;i++) if(s[i-1]=='1') p[i]=i; // 锚点

        for(auto seg: zeroRuns){
            int L = seg.first, R = seg.second;
            if(L<=R){
                // 环形右移一格（同区间内置换）
                for(int i=L;i<R;i++) p[i] = i+1;
                p[R] = L;
            }
        }

        cout << "YES\n";
        for(int i=1;i<=n;i++){
            cout << p[i] << (i==n?'\n':' ');
        }
    }
    return 0;
}
