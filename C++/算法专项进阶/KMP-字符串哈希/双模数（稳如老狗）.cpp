#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;

const ll M1 = 1000000007LL;
const ll M2 = 1000000009LL;
ll B; // 进制：随机化

// 预处理数组
vector<ll> H1, H2, P1, P2; // 前缀哈希 & B 的幂 (mod M1/M2)

// 生成随机基数（固定一次）
ll gen_base(){
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> dist(256, 1000000);
    ll b = dist(rng);
    if (b % 2 == 0) b++; // 选奇数
    return b;
}

void build_hash(const string &S){
    int n = (int)S.size();
    H1.assign(n+1, 0); H2.assign(n+1, 0);
    P1.assign(n+1, 1); P2.assign(n+1, 1);
    for(int i=1;i<=n;i++){
        ll x = (unsigned char)S[i-1]; // 保持一致的映射
        H1[i] = ( (H1[i-1]*B % M1) + x ) % M1;
        H2[i] = ( (H2[i-1]*B % M2) + x ) % M2;
        P1[i] = (P1[i-1]*B) % M1;
        P2[i] = (P2[i-1]*B) % M2;
    }
}

// 取子串 [l, r] 的双哈希（1-index）
pll get_hash(int l, int r){
    ll a1 = (H1[r] - H1[l-1]*P1[r-l+1]) % M1; if(a1<0) a1+=M1;
    ll a2 = (H2[r] - H2[l-1]*P2[r-l+1]) % M2; if(a2<0) a2+=M2;
    return {a1, a2};
}

// 用法示例：判重
// 读入 n 个串，计算整串哈希并去重
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    B = gen_base();
    int n; if(!(cin>>n)) return 0;
    vector<pll> all;
    while(n--){
        string s; cin>>s;
        build_hash(s);
        all.push_back(get_hash(1, (int)s.size()));
    }
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    cout << all.size() << "\n";
    return 0;
}
