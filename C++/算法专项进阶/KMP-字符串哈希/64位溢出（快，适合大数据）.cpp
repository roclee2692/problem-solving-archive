#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

ull B; // 随机基数
vector<ull> H, P;

ull gen_base(){
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    ull b = (rng() % 1000000ULL) + 256ULL;
    if ((b & 1ULL) == 0) b++; // 奇数
    return b;
}

void build_hash(const string &S){
    int n = (int)S.size();
    H.assign(n+1, 0); P.assign(n+1, 1);
    for(int i=1;i<=n;i++){
        ull x = (unsigned char)S[i-1];
        H[i] = H[i-1]*B + x; // 自然溢出即 mod 2^64
        P[i] = P[i-1]*B;
    }
}

ull get_hash(int l, int r){ // 1-index
    return H[r] - H[l-1]*P[r-l+1];
}

// 示例：判断 P 是否 S 的子串
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S, T;
    if(!(cin>>S>>T)) return 0;
    B = gen_base();
    build_hash(S);
    ull ht = 0; for(char c: T) ht = ht*B + (unsigned char)c;

    int n = (int)S.size(), m = (int)T.size();
    bool ok = false;
    for(int i=1;i+m-1<=n;i++){
        if(get_hash(i, i+m-1) == ht){ ok = true; break; }
    }
    cout << (ok ? "Yes\n" : "No\n");
    return 0;
}
