#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//典型模板：统计 [0..N] 中“数位和 % K == 0”的个数
int K;
vector<int> d;        // 高位到低位
ll dp[20][200];       // dp[pos][sum_mod]，仅 tight=0 时缓存，K <= 180 安全
bool vis[20][200];

ll dfs(int pos, int sum_mod, bool tight){
    if(pos == (int)d.size()) return (sum_mod % K == 0);
    if(!tight && vis[pos][sum_mod]) return dp[pos][sum_mod];

    int up = tight ? d[pos] : 9;
    ll res = 0;
    for(int x=0; x<=up; ++x){
        res += dfs(pos+1, (sum_mod + x)%K, tight && (x==up));
    }
    if(!tight){ vis[pos][sum_mod] = true; dp[pos][sum_mod] = res; }
    return res;
}

ll count_upto(long long N){
    if(N < 0) return 0;
    d.clear();
    while(N){ d.push_back(N%10); N/=10; }
    if(d.empty()) d.push_back(0);
    reverse(d.begin(), d.end());
    memset(vis, 0, sizeof(vis));
    return dfs(0, 0, true);
}

int main(){
    long long L, R; // 输入 L R 和 K
    // 示例：cin >> L >> R >> K;
    return 0;
}
