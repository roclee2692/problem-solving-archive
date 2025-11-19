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
using ull=unsigned long long;
using ll=long long;

const ull B=131;
vector<ull> H,P;

void build(const string & S){
    ll n=S.size();
    H.assign(n+1,0);
    P.assign(n+1,0);
    for(int i=1;i<=n;i++){
        H[i]=H[i-1]*B+S[i-1];
        P[i]=P[i-1]*B;
    }
}
ull get(ll l,ll r){
    return H[r]-H[l-1]*P[r-l+1];//+1 ensure index from 1 start
}

  void example_match(){
    string S, T;  // S=文本串，T=模式串
    cin >> S >> T;
    build(S);     // 预处理文本串的哈希表
    
    // 计算模式串 T 的整体哈希值（不用 build，直接算）
    ull ht = 0;
    for(char c : T) ht = ht*B + c;  // 递推：ht = ht×B + c
    
    // 滑动窗口：枚举 S 中所有长度为 m 的子串
    int n = S.size(), m = T.size();
    for(int i=1;i+m-1<=n;i++){  // i 是起点（1-indexed）
        // 比较子串 S[i..i+m-1] 的哈希值与模式串的哈希值
        if(get(i, i+m-1) == ht){
            cout << i << "\n";  // 输出匹配位置（1-indexed）
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

  
    // 根据题目选择示例
    //example_match();
    
    return 0;
}