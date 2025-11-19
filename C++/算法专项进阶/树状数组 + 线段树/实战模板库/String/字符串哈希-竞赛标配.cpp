/*
 * 【字符串哈希】- 竞赛标配模板
 * 
 * 时间复杂度：预处理 O(n)，查询 O(1)
 * 空间复杂度：O(n)
 * 
 * 适用：99% 的字符串匹配/判重/LCP 问题
 * 推荐基数：131、13331（经验值，分布均匀）
 */

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

const ull B = 131;  // 进制基数（131 或 13331）
vector<ull> H, P;   // H[i] = 前缀哈希, P[i] = B^i

// 构建字符串 S 的哈希表（1-indexed）
void build(const string &S){
    int n = S.size();
    H.assign(n+1, 0);
    P.assign(n+1, 1);
    for(int i=1;i<=n;i++){
        H[i] = H[i-1]*B + S[i-1];  // 自动 mod 2^64
        P[i] = P[i-1]*B;
    } 
}

// 获取子串 [l, r] 的哈希值（1-indexed）
ull get(int l, int r){
    return H[r] - H[l-1]*P[r-l+1];
}

// 【用法示例 1】字符串匹配
void example_match(){
    string S, T;
    cin >> S >> T;
    build(S);
    
    // 计算模式串 T 的哈希
    ull ht = 0;
    for(char c : T) ht = ht*B + c;
    
    // 在 S 中查找所有匹配位置
    int n = S.size(), m = T.size();
    for(int i=1;i+m-1<=n;i++){
        if(get(i, i+m-1) == ht){
            cout << i << "\n";  // 1-indexed
        }
    }
}

// 【用法示例 2】字符串去重
void example_dedup(){
    int n;
    cin >> n;
    set<ull> seen;
    int cnt = 0;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        ull h = 0;
        for(char c : s) h = h*B + c;
        if(seen.insert(h).second) cnt++;
    }
    cout << cnt << "\n";
}

// 【用法示例 3】最长公共前缀（LCP）
int lcp(int i1, int i2, int n){  // S[i1..] 和 S[i2..] 的 LCP
    int l = 0, r = n - max(i1, i2) + 1;
    while(l < r){
        int mid = (l + r + 1) / 2;
        if(get(i1, i1+mid-1) == get(i2, i2+mid-1)) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    
    // 根据题目选择示例
    example_match();
    
    return 0;
}

/*
 * 【核心公式】
 * hash(s[l..r]) = H[r] - H[l-1] * B^(r-l+1)
 * 
 * 【为什么用 ULL 自然溢出？】
 * - 自动 mod 2^64，无需手动取模
 * - 速度快，代码简洁
 * - 碰撞概率 ≈ 1/2^64（极低）
 * 
 * 【防卡方案】
 * 普通题：单哈希 + 131 即可
 * 防卡题：
 *   1. 随机基数：B = rand() % 1000000 + 256
 *   2. 双哈希：ULL + 单模数，或双模数
 * 
 * 【常见应用】
 * - 字符串匹配（代替 KMP）
 * - 字符串去重
 * - 最长公共子串
 * - 回文串判断
 * - 最长回文子串
 * - 字典序比较
 * 
 * 【提交前检查】
 * - [ ] 索引是 0 还是 1？
 * - [ ] 字符映射正确？（大小写、ASCII）
 * - [ ] 是否需要双哈希防卡？
 */
