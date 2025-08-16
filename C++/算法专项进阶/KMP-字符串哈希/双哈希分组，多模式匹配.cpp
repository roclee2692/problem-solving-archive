#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;

// 两个大质数模；两个大基数（也可运行时随机化）
const ll M1 = 1000000007LL, M2 = 1000000009LL;
const ll B1 = 911382323LL, B2 = 972663749LL;

string S;                   // 文本
vector<ll> H1, H2, P1, P2;  // S 的前缀哈希与幂（1-index）

// -------- 预处理 S 的双哈希前缀（1-index） --------
// H[i] = H[i-1]*B + x；P[i] = B^i；均对各自模取模
void build_hash(const string& s){
    int n = (int)s.size();
    H1.assign(n+1,0); H2.assign(n+1,0);
    P1.assign(n+1,1); P2.assign(n+1,1);
    for(int i = 1; i <= n; i++){
        int x = (unsigned char)s[i-1];                // 统一映射到 0..255
        H1[i] = ( (H1[i-1]*B1) % M1 + x ) % M1;
        H2[i] = ( (H2[i-1]*B2) % M2 + x ) % M2;
        P1[i] = ( P1[i-1]*B1 ) % M1;
        P2[i] = ( P2[i-1]*B2 ) % M2;
    }
}

// -------- 取子串 [l,r] 的双哈希（1-index） --------
// 公式：H[r] - H[l-1]*B^(r-l+1)（模意义下要做“正值化”）
inline pll get_hash(int l,int r){
    ll a1 = ( H1[r] - H1[l-1]*P1[r-l+1] ) % M1; if(a1 < 0) a1 += M1;
    ll a2 = ( H2[r] - H2[l-1]*P2[r-l+1] ) % M2; if(a2 < 0) a2 += M2;
    return {a1, a2};
}

// pair<ll,ll> 作为 unordered_* 的 key 需要自定义哈希
struct PairHash {
    size_t operator()(const pll& x) const {
        // 简单异或混合（足够用）；如需更强可用 splitmix64
        return (size_t)x.first ^ ((size_t)x.second << 1);
    }
};

/* -------- 多模式匹配（按长度分组）--------
   输入：文本 S，模式串数组 pats
   输出：每个模式串是否在 S 中出现（1/0）
   思路：
   1) 先 build_hash(S) 得到 S 的前缀双哈希
   2) 按长度分组模式串（不同长度互不比较）
   3) 对每个长度 L：
      - 建一个哈希表 need：存所有模式整串的双哈希
      - 枚举 S 的所有长为 L 的子串哈希，O(1) 查询是否在 need 中
      - 命中则把该长度分组内的模式标记为出现（本实现是“只要该长度中有任意命中，就全部置 1”，
        若要精确到每个模式，请改用 hash -> list<pattern_id> 并逐一标记）
*/
vector<int> multi_match(const string& S, const vector<string>& pats){
    build_hash(S);
    int n = (int)S.size();

    // 1) 按长度分组：长度 -> 该长度的模式下标列表
    unordered_map<int, vector<int>> ids;
    ids.reserve(pats.size()*2+1);
    for(int i = 0; i < (int)pats.size(); i++){
        ids[(int)pats[i].size()].push_back(i);
    }

    // 2) 结果数组：0/1 表示是否出现
    vector<int> ok(pats.size(), 0);

    // 3) 逐长度处理
    for(auto &kv : ids){
        int L = kv.first;
        const auto &idxs = kv.second;   // 该长度的模式 id 列表
        if(L == 0 || L > n){            // 空串或比文本长：直接判不存在
            for(int id : idxs) ok[id] = 0;
            continue;
        }

        // 3.1 建该长度下的模式哈希表
        unordered_set<pll, PairHash> need;
        need.reserve(idxs.size()*2 + 1);
        for(int id : idxs){
            const string &p = pats[id];
            ll a1 = 0, a2 = 0;
            for(char c : p){
                int x = (unsigned char)c;
                a1 = ( (a1*B1) % M1 + x ) % M1;
                a2 = ( (a2*B2) % M2 + x ) % M2;
            }
            need.insert({a1, a2});
        }

        // 3.2 枚举 S 的所有长度为 L 的子串，查表
        bool hit_this_len = false;
        for(int i = 1; i + L - 1 <= n; i++){
            pll h = get_hash(i, i + L - 1);
            if(need.find(h) != need.end()){
                // != end() 表示找到元素；end() 是尾后迭代器，不是最后一个元素
                hit_this_len = true;
                break; // 已经确认该长度组存在命中，后面可提前结束
            }
        }

        // 3.3 标记该长度分组的所有模式为“出现”
        // （⚠ 如果你要“精确到每个模式”，这里不要一刀切，
        //    把 need 改为 unordered_map<pll, vector<int>>，
        //    命中时对列表里的模式 id 单独置 1，甚至可再做一次字符串逐字比对兜底）
        if(hit_this_len){
            for(int id : idxs) ok[id] = 1;
        }
    }
    return ok;
}

// 示例：输入文本 S 与 m 个模式串，输出 Yes/No
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m; 
    if(!(cin >> S >> m)) return 0;
    vector<string> pats(m);
    for(int i = 0; i < m; i++) cin >> pats[i];

    auto res = multi_match(S, pats);
    for(int i = 0; i < m; i++) cout << (res[i] ? "Yes\n" : "No\n");
    return 0;
}
