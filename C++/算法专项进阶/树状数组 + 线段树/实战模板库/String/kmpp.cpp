/*
 * 【KMP 算法】- 字符串模式匹配
 * 
 * 时间复杂度：O(n + m)，其中 n = 文本长度，m = 模式长度
 * 空间复杂度：O(m)
 * 
 * 适用场景：
 *   - 在文本中查找所有模式出现位置
 *   - 不允许回溯（相比朴素算法更高效）
 * 
 * 模板题：洛谷 P3375 - 【模板】KMP字符串匹配
 */

#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;

string T,P;
vector<ll> nxt,pos;
ll cnt;

// 构建 next 数组：nxt[i] = P[0..i] 的最长相等前后缀长度
void build(){
    ll m=P.size();
    nxt.assign(m,0);  // ✅ 大小为 m
    // i 必须从 1 开始，nxt[0]=0
    for(int i=1,j=0;i<m;i++){
        // 失配时回退 j
        while(j>0 && P[i]!=P[j]) j=nxt[j-1];
        // 匹配时扩展前后缀长度
        if(P[i]==P[j]) j++;  // ✅ 使用 == 比较
        nxt[i]=j;            // ✅ 记录 P[0..i] 的最长前后缀长度
    }
}

// KMP 匹配：在文本 T 中查找模式 P
void kmp(){
    ll n=T.size(),m=P.size();
    cnt=0;
    pos.clear();
    // i 从 0 开始扫描文本 T
    for(int i=0,j=0;i<n;i++){  // ✅ i 从 0 开始
        // 失配时回退 j
        while(j>0 && T[i]!=P[j]) j=nxt[j-1];
        // 匹配时扩展
        if(T[i]==P[j]) j++;
        // 完整匹配
        if(j==m){
            cnt++;
            pos.push_back(i-m+1);  // ✅ 0-indexed 存储
            j=nxt[j-1];            // 允许重叠匹配
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    cin>>P;
    build();
    kmp();
    for(auto &e:pos){
        cout<<e<<" ";
    }
    cout<<"\n";
    return 0;
}
/*
 * 【使用说明】
 * S = 文本串，P = 模式串
 * build() 构建 next 数组
 * kmp() 查找所有匹配，结果存在 pos 中（0-indexed）
 * 
 * 【next 数组】
 * nxt[i] = P[0..i] 的最长相等前后缀长度
 * 
 * 【提交前检查】
 * - [ ] 输出是 0-indexed 还是 1-indexed？
 * - [ ] 是否需要输出 next 数组？
 */
