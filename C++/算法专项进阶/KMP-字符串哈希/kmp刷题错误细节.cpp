#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;
string S, P;           // 文本、模式
vector<ll> nxt;        
vector<ll> nxtval;      // 优化 PMT（0-based）
vector<ll> pos;        // 所有匹配起点(1-index)
ll cnt;           // 匹配次数
void build_nxt(){
    ll m=P.size();//模式串长度 
    nxt.assign(m,0);
    for(ll i=1,j=0;i<m;i++){//i 控制模式串 1对应0 从2开始计算next数组
       // ll j=0 ;//从0开始遍历字符串build_nxt()里把 j 放在了 for 循环内部重置
//这样每次 i++ 都把已匹配前缀长度清零，nxt 递推失效
        while(j>0&&P[j]!=P[i]) j=nxt[j-1];
        if(P[i]==P[j]) j++;
        nxt[i]=j;
    }
}

void build_nxtval_v1(){
    build_nxt();
    ll m=P.size();
    nxtval=nxt;
    for(int i=1;i<m;i++){
        ll t=nxtval[i];
        while(t>0&&P[i]==P[t]){
            t=nxtval[t-1];
        }
        nxtval[i]=t;
    }
}
/*不是数据在“卡”你，是**nextval 的定义和你匹配环的语义不完全一致**，
导致回退跳得过头，从而漏掉某些合法匹配；把它关掉就恢复成标准 KMP，自然就 AC 了。
nxtval 在 0-based 下的实现如果有一丝索引不严谨，就可能漏匹配
nextval 的思想是“如果回退后要比较的两个字符本来就相等，就再回退一次，省一次比较”。
你如果只改索引没改语义，很容易把**“省一次比较”变成“省了一整个候选前后缀”——就跳过了应试的长度**，从而漏解
安全做法（两条任选其一）
最稳：不用优化，kmp(true, false)，本题 1e6 完全够快。

要用优化（0-based 经过验证的版本）：
用下面这个单步压缩而不是 while 连跳——它和你的匹配环语义对齐，实践里更安全：*/
// 在 build_nxt() 之后调用
void build_nxtval() {
    ll m = (ll)P.size();
    nxtval = nxt;
    for (ll i = 1; i < m; i++) {
        ll t = nxt[i];
        if (t > 0 && P[i] == P[t]) nxtval[i] = nxtval[t - 1];
        else                       nxtval[i] = t;
    }
    /*说明：这里用单步压缩（看 P[i] == P[t] 就一次替换成 nxtval[t-1]），
    避免 while 连跳带来的过度压缩；同时它保持了“候选长度链”的完整性，因此不丢解。*/
}
void kmp(bool allowOverlap=1,bool useval=0){
    pos.clear();
     ll n = (ll)S.size(), m = (ll)P.size();
    if(m == 0 || n < m) return;  // 边界：空模式或模式长于文本 -> 无匹配
     if(useval) build_nxtval();
    else       build_nxt();
    const vector<ll> &nx = useval ? nxtval : nxt;
    for(ll i=0,j=0;i<n;i++){
        while(j>0&&S[i]!=P[j]) j=nx[j-1];
         // 相等：已匹配长度 +1
        if(S[i] == P[j]) j++;
         // 找到一次完整匹配：起点 = 当前 i - m + 2（转 1-index
        if(j==m){
            pos.push_back(i-m+2);
            cnt++;
            // 继续找下一处：重叠/不重叠两种场景
            j = allowOverlap ? nx[j-1] : 0;
        }
    }
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 示例读取（无空格用 cin；若含空格用 getline）
    if(!(cin >> S >> P)) return 0;

    // 允许重叠 + 优化回退（推荐日常刷题配置）
    kmp(true, true);

    // 打印所有出现位置（1-index）
    for(size_t i = 0; i < pos.size(); i++){
        cout << pos[i] <<"\n";
    }
  //  if(pos.empty()) cout << "\n";

    

    // 如需输出 PMT，便于自测/对拍（0-based）
    // 若做 P3375（要求输出 1-index 的 next），需把 nxt 转为 1-index 再打印
    // 这里先打印 0-based 的 nxt / nxtval：
    for(size_t i = 0; i < nxt.size(); i++){
        cout << nxt[i] << (i + 1 == nxt.size() ? '\n' : ' ');
    }
    return 0;
}

