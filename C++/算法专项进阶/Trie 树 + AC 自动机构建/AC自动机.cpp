#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;

/* ===================== 统一命名 · AC 自动机（a-z） =====================
 * 你在 Trie 里用的命名，这里保持一致，方便迁移和记忆：
 *   - nxt[u][c]：自动机从结点 u 经字符 c 的“下一结点”
 *   - tot / root / idx / clearTrie / insertStr
 * 在 AC 里多出的：
 *   - fail[u]：u 对应串的“最长真后缀”的结点（KMP 的 fail 在 Trie 上的延伸）
 *   - outCnt[u]：有多少模式在 u 处结束
 *   - outSum[u]：u 以及其 fail 祖先的 outCnt 之和（到达 u 时能匹配的模式数）
 *   - occ[u]：文本扫描时“恰好到达 u 的次数”（逐模式计数用）
 *
 * 关键思想（为什么要这样写）：
 *   1) “补 goto”：把缺失的 nxt 转移补成“沿 fail 走一次后的转移”，
 *      这样匹配阶段就可以 O(1) 写成：u = nxt[u][c]，无需 while 回退。
 *      根的缺边设成指向根：nxt[root][c] = root，含义是“在根遇到不匹配字符就原地不动”。
 *   2) outSum[u] = outCnt[u] + outSum[fail[u]]：到达 u 时，既命中 u 自己，
 *      也命中它沿 fail 链的所有祖先（这些祖先代表更短的后缀模式）。
 *      BFS 自浅到深构造保证 fail[u] 已经就绪，所以可以直接“拓扑继承”。
 *   3) 逐模式计数：扫文本只记 occ[u]++（落在谁就给谁 +1）；
 *      然后把每个点的 occ 沿 fail 链向上汇总（子加到父），
 *      最后每个模式末结点的 occ 就是该模式的出现次数。
 * ===================================================================== */

const int L = 26;         // 字母集 a..z
const int N = 1000000+5;  // 结点上限（按需调；全 ll 时注意内存）

// -------- 基础（保持与 Trie 一致） --------
ll nxt[N][L];  // goto 转移：nxt[u][c] = v（0 表示无）
ll tot = 1;    // 已用节点数（根从 1 开始）
ll root = 1;   // 根结点编号
inline ll idx(char ch){ return (ll)(ch - 'a'); }

// -------- AC 额外信息 --------
ll fail_[N];      // fail 指针
ll outCnt[N];     // 本结点直接结束的模式数
ll outSum[N];     // 本结点及其 fail 祖先的“结束数之和”
ll occ[N];        // 扫文本时到达该结点的次数（逐模式）
vector<ll> patEnd; // 可选：id -> 末结点（逐模式输出用）

// 为逐模式的“自底向上汇总”准备的 BFS 序（从浅到深）
vector<ll> bfsOrder;

// -------- 和 Trie 对齐的接口 --------
inline void clearTrie(){
    for(ll u=1; u<=tot; ++u){
        for(int c=0;c<L;++c) nxt[u][c]=0;
        fail_[u]=0; outCnt[u]=0; outSum[u]=0; occ[u]=0;
    }
    tot = root = 1;
    bfsOrder.clear();
    patEnd.clear();
}

// 插入模式串；若 id>0，则记录该模式的“末结点”，便于逐模式输出
inline void insertStr(const string& s, ll id=0){
    ll u = root;
    for(char ch : s){
        ll k = idx(ch);
        if(!nxt[u][k]) nxt[u][k] = ++tot;
        u = nxt[u][k];
    }
    outCnt[u] += 1;                 // 在 u 处有一个模式结束
    if(id > 0){
        if((ll)patEnd.size() <= id) patEnd.resize((size_t)id+1, 0);
        patEnd[(size_t)id] = u;     // 记住该模式的末结点
    }
}

/* --------------- 构造 fail，并“补 goto” ---------------
 * 根层：
 *   - 若有儿子 v，则 fail[v]=root，入队；
 *   - 若无儿子，nxt[root][c]=root（补 goto：根缺边回根）。
 * 层序（BFS）：
 *   - 弹 u 时先做 outSum[u] = outCnt[u] + outSum[fail[u]]（拓扑继承）
 *   - 对每个字符 c：
 *       若有儿子 v：fail[v] = nxt[fail[u]][c]（因为 goto 已补齐），入队
 *       否则：nxt[u][c] = nxt[fail[u]][c]（继续补 goto）
 * 最终：nxt 形成一个“闭包”转移表，匹配阶段 O(1) 转移。
 */
inline void buildFail(){
    queue<ll> q;
    // 根层
    for(int c=0;c<L;++c){
        ll v = nxt[root][c];
        if(v){ fail_[v] = root; q.push(v); }
        else  nxt[root][c] = root;          // 关键：根缺边回根
    }
    outSum[root] = outCnt[root];

    // BFS
    bfsOrder.clear();
    while(!q.empty()){
        ll u = q.front(); q.pop();
        bfsOrder.push_back(u);               // 记录自浅到深的顺序
        // 到达 u 时可匹配的模式数 = 自己 + fail 祖先
        outSum[u] = outCnt[u] + outSum[ fail_[u] ];

        for(int c=0;c<L;++c){
            ll v = nxt[u][c];
            if(v){
                fail_[v] = nxt[ fail_[u] ][c]; // 由于已补 goto，直接取
                q.push(v);
            }else{
                nxt[u][c] = nxt[ fail_[u] ][c]; // 继续补 goto
            }
        }
    }
}

/* ---------------- 匹配 · 总出现次数 ----------------
 * 由于已补 goto，匹配就一句话：u = nxt[u][idx(ch)]
 * 然后把 outSum[u] 累加即可（含 fail 祖先）。
 */
inline ll matchTotal(const string& text){
    ll ans = 0, u = root;
    for(char ch : text){
        if(ch<'a' || ch>'z'){ u = root; continue; } // 非法字符当断开
        u = nxt[u][ idx(ch) ];
        ans += outSum[u];
    }
    return ans;
}

/* --------------- 匹配 · 逐模式出现次数 ---------------
 * 步骤：
 *   1) 扫文本：每到一个状态 u，就 occ[u]++（落在谁就给谁 +1）
 *   2) 自底向上沿 fail 汇总：对 BFS 序反向遍历，
 *        occ[ fail[u] ] += occ[u]
 *      理由：落在更长后缀的次数，也算命中它的所有 fail 祖先。
 *   3) 模式 id 的答案 = 其末结点的 occ。
 */
inline void matchEach(const string& text, vector<ll>& ans, ll max_id){
    ans.assign((size_t)max_id+1, 0);
    // 1) 扫文本
    ll u = root;
    for(char ch : text){
        if(ch<'a' || ch>'z'){ u = root; continue; }
        u = nxt[u][ idx(ch) ];
        occ[u] += 1;
    }
    // 2) 反向汇总（自底向上）
    for(ll i=(ll)bfsOrder.size()-1; i>=0; --i){
        ll x = bfsOrder[(size_t)i];          // x 的 fail 父已在更前面
        occ[ fail_[x] ] += occ[x];
    }
    // 3) 取每个模式末结点的次数
    for(ll id=1; id<=max_id; ++id){
        if(id < (ll)patEnd.size() && patEnd[(size_t)id])
            ans[(size_t)id] = occ[ patEnd[(size_t)id] ];
        else
            ans[(size_t)id] = 0;             // 没插过这个 id
    }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  clearTrie();
  insertStr("he",   1);
  insertStr("she",  2);
  insertStr("his",  3);
  insertStr("hers", 4);
  buildFail();

  string text = "ushers";
  cout << matchTotal(text) << "\n";        // 总出现次数

  vector<ll> cnt; matchEach(text, cnt, 4); // 逐模式
  for(int i=1;i<=4;i++) cout << cnt[i] << " \n"[i==4];
  return 0;
}
