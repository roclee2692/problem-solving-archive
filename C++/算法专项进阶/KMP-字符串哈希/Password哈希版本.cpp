#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;
using ull = unsigned long long;

string s;
ll n;
const ull B = 131;

vector<ull> H, P; // 1-index
inline void build_hash(const string &S){
    ll m = (ll)S.size();
    H.assign(m+1, 0); P.assign(m+1, 1);
    for(ll i = 1; i <= m; ++i){
        ull x = (unsigned char)S[i-1];
        H[i] = H[i-1] * B + x;   // 自然溢出 => mod 2^64
        P[i] = P[i-1] * B;
    }
}
inline ull get_hash(ll l, ll r){ // 1-index, l<=r
    return H[r] - H[l-1] * P[r-l+1];
}
inline bool equal_sub(ll l1, ll r1, ll l2, ll r2){
    return get_hash(l1,r1) == get_hash(l2,r2);
}

// 计算从位置 i 开始与前缀的 LCP，i ∈ [2..n-1]
inline ll lcp_with_prefix(ll i){
    ll lo = 0, hi = n - i + 1, ans = 0; // 不能越界
    while(lo <= hi){
        ll mid = (lo + hi) >> 1;
        if(mid == 0){ ans = 0; lo = 1; continue; }
        if(equal_sub(1, mid, i, i+mid-1)){
            ans = mid; lo = mid + 1;
        }else{
            hi = mid - 1;
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if(!(cin >> s)) return 0;
    n = (ll)s.size();
    if(n <= 2){ cout << "Just a legend\n"; return 0; }

    build_hash(s);

    // A[i] = 与前缀的 LCP 长度（仅中间位置 i=2..n-1）
    vector<ll> A(n+1, 0);
    ll V1 = 0, V2 = 0; // 最大与次大
    ll idx1 = -1;      // 最大值出现的位置
    for(ll i = 2; i <= n-1; ++i){
        A[i] = lcp_with_prefix(i);
        if(A[i] > V1){
            V2 = V1;
            V1 = A[i];
            idx1 = i;
        }else if(A[i] > V2){
            V2 = A[i];
        }
    }

    // 从大到小找满足：既是前缀又是后缀，且在中间出现
    for(ll L = n-1; L >= 1; --L){
        // 前后缀相等？
        if(!equal_sub(1, L, n-L+1, n)) continue;

        // 中间是否出现（排除唯一的后缀起点 i = n-L+1）
        ll suffix_start = n - L + 1;
        bool ok = false;
        if(idx1 != suffix_start){
            ok = (V1 >= L);
        }else{
            ok = (V2 >= L);
        }
        if(ok){
            cout << s.substr(0, (size_t)L) << "\n";
            return 0;
        }
    }
    cout << "Just a legend\n";
    return 0;
}
