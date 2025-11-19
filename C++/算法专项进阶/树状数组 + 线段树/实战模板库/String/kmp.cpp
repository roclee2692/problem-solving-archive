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
void build(){
    ll m=P.size();
    nxt.assign(m+1,0);
    for(int i=1,j=0;i<m;i++){
        while(j>0 && P[i]!=P[j]) j=nxt[j-1];
        if(P[i]==P[j]) j++; // ✅ 使用比较运算符
        nxt[i]=j;  // ✅ 记录 i 位置的最长前后缀长度
        //next数组装的始终时j 指针的前面相同位置索引 i代表当前位置 有相等匹配就使得当前nxt[i]=j 方便下次模式串回退找到过去的自己 
    }
}

void kmp(){

    ll n=T.size(),m=P.size();
    for(int i=0,j=0;i<n;i++){ //✅ i 从 0 开始扫描文本
        while(j>0 && T[i]!=P[j]) j=nxt[j-1];
        if(T[i]==P[j]) j++;
        if(j==m){
            cnt++;
            pos.push_back(i-m+1);
            j=nxt[j-1];
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
