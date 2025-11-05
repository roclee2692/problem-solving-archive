#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;

/* --------------------------------------------
   统一口径（重要）：
   - nxt[i]  : 0-based PMT/LPS，表示 P[0..i] 的“最长相等前后缀长度”
               取值范围 [0..i]，nxt[0] = 0。
   - nxtval[i]: 在 nxt 基础上“消掉必然相等的那一步”，
                使得匹配阶段回退更少无效比较。
   - KMP 匹配阶段：文本 S 从 0 开始扫；失配回退用 nx[j-1]（nx 可选 nxt 或 nxtval）
   - 输出位置：题目常要 1-index，这里统一在 push 时 +1（i - m + 2）
   -------------------------------------------- */

string S, P;            // 文本、模式串
vector<ll> nxt;         // 标准 KMT（0-based）
vector<ll> nxtval;      // 优化 KMT（0-based）
vector<ll> pos;         // 所有匹配起点（按 1-index 存）
ll cntMatch;            // 匹配次数（允许重叠时为所有出现次数）

/* ---------- 构建标准 nxt ----------
   思想：i 是“快指针”扫 P，j 是当前“最长前后缀长度”
   当 P[i] != P[j]，尝试把 j 回退到 nxt[j-1]（更短的相等前后缀）
   当 P[i] == P[j]，可以把 j 扩到 j+1
   最终 nxt[i] = j
*/
void build_nxt(){
    ll m = (ll)P.size();
    nxt.assign(m, 0);
    for(ll i = 1, j = 0; i < m; i++){
        //这里的 j 是整个循环的一个持续状态变量，直接跨迭代延续，不用 pi[i-1] 初始化，因为它天然保存着上一次的匹配结果。
        // 若当前字符不等，沿“前后缀链”回退 j，直到相等或 j==0
        //如果没有 j > 0，下一步会访问 pi[-1]，直接越界崩溃。
        while(j > 0 && P[i] != P[j]) j = nxt[j-1];
        // 若相等，可以把相等前后缀长度 +1
        if(P[i] == P[j]) j++;
        // 记录 P[0..i] 的最长相等前后缀长度
        nxt[i] = j;
    }
}

/* ---------- 构建优化 nxtval ----------
   目的：当“回退后将要比较的字符”与“当前字符”仍相等时，
         预先继续回退，直接跳过那次“必然相等”的比较。
   做法：在 nxt 基础上，若 P[i] == P[t]（t = nxtval[i]），
         则令 t = nxtval[t-1]，重复直到不等或 t==0。
*/
void build_nxtval(){
    build_nxt();                 // 先有标准 nxt
    ll m = (ll)P.size();
    nxtval = nxt;                // 复制一份作为起点
    for(ll i = 1; i < m; i++){
        ll t = nxtval[i];
        // 只要“回退后下一比较位字符 P[t]”与“当前字符 P[i]”仍相等，就再回退
        while(t > 0 && P[i] == P[t]){
            t = nxtval[t-1];
        }
        nxtval[i] = t;           // 压缩后的回退长度
    }
}

/* ---------- KMP 主过程 ----------
   参数：
   - allowOverlap：是否允许重叠匹配（true 为标准 KMP 行为）
   - useOpt      ：是否使用 nxtval（优化 PMT）做回退
   过程：
   - i 扫 S，j 是“已匹配长度”（下一个要比的是 P[j]）
   - 失配：j = nx[j-1]（nx 为 nxt 或 nxtval）
   - 相等：j++
   - 完整匹配：j == m -> 记录起点（1-index），次数+1，然后
                j = nx[j-1]（允许重叠）或 j = 0（不允许重叠）
*/
void kmp(bool allowOverlap = true, bool useOpt = false){
    pos.clear(); cntMatch = 0;
    ll n = (ll)S.size(), m = (ll)P.size();
    if(m == 0 || n < m) return;  // 边界：空模式或模式长于文本 -> 无匹配

    if(useOpt) build_nxtval();
    else       build_nxt();
    const vector<ll> &nx = useOpt ? nxtval : nxt;

    for(ll i = 0, j = 0; i < n; i++){
        // 失配：沿 nx 回退 j，直至能比较或清零
        while(j > 0 && S[i] != P[j]) j = nx[j-1];
        // 相等：已匹配长度 +1
        if(S[i] == P[j]) j++;
        // 找到一次完整匹配：起点 = 当前 i - m + 2（转 1-index）i+1-m +1
        if(j == m){
            pos.push_back(i - m + 2);
            cntMatch++;
            // 继续找下一处：重叠/不重叠两种场景
            j = allowOverlap ? nx[j-1] : 0;
        }
    }
}

/* -------------------- 可选：演示主函数 --------------------
   用法：
   输入两行（或两串）：
     第一行 S（文本）
     第二行 P（模式）
   输出：
     匹配起点列表（1-index）
     匹配次数
     nxt / nxtval（查看构建是否正确）
*/
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 示例读取（无空格用 cin；若含空格用 getline）
    if(!(cin >> S >> P)) return 0;

    // 允许重叠 + 优化回退（推荐日常刷题配置）
    kmp(true, true);

    // 打印所有出现位置（1-index）
    for(size_t i = 0; i < pos.size(); i++){
        cout << pos[i] << (i + 1 == pos.size() ? '\n' : ' ');
    }
    if(pos.empty()) cout << "\n";

    // 统计次数
    cout << cntMatch << "\n";

    // 如需输出 PMT，便于自测/对拍（0-based）
    // 若做 P3375（要求输出 1-index 的 next），需把 nxt 转为 1-index 再打印
    // 这里先打印 0-based 的 nxt / nxtval：
    for(size_t i = 0; i < nxt.size(); i++){
        cout << nxt[i] << (i + 1 == nxt.size() ? '\n' : ' ');
    }
    for(size_t i = 0; i < nxtval.size(); i++){
        cout << nxtval[i] << (i + 1 == nxtval.size() ? '\n' : ' ');
    }
    return 0;
}
