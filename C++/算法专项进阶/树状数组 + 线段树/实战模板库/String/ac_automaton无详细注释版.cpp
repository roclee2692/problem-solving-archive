/*
 * 【AC 自动机】- 多模式字符串匹配（升级版Trie）
 * 
 * 时间复杂度：O(n + m*k) 预处理 + O(len) 匹配
 *   n = 所有模式总长度，m = 模式数，k = 字母表大小，len = 文本长度
 * 空间复杂度：O(n*k)
 * 
 * 适用场景：
 *   - 在文本中查找多个模式的所有出现位置
 *   - 敏感词过滤
 *   - 字典最长匹配（贪心）
 * 
 * 模板题：
 *   - 洛谷 P3808 - 【模板】AC 自动机（简单版）
 *   - Codeforces 754F - Robbers
 */

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const ll N=1e6+7;
const ll L=26;

ll nxt[N][L];
ll fail[N];
ll occ[N];
ll outcnt[N];
ll tot=1;
ll root=1;
ll n;
string t;

vector<ll> bfsorder;
//参数不需要引用：char &ch 改为 char ch 即可
inline ll idx(char ch){//返回类型错误：返回 char 应该改为 ll 或 int
    return ch-'a';// ❌ 错误！应该是 ch-'a'
}

void insertStr(const string &s){
    ll u=root;
    for(char ch:s){
        ll id=idx(ch);
        ll v=nxt[u][id];
        if(!v){
            nxt[u][id]=++tot;
        }
         u=nxt[u][id];
    }
    outcnt[u]++;
}

inline void buildfail(){
    queue<ll> q;
    for(int i=0;i<L;i++){
        ll v=nxt[root][i];
        if(v){
            fail[v]=root;
            q.push(v);
        }else{
            nxt[root][i]=root;
        }
    }
    while(!q.empty()){
        ll u=q.front();  q.pop();
        bfsorder.push_back(u);
        for(int i=0;i<L;i++){
            ll v=nxt[u][i];
            if(v){
                fail[v]=nxt[fail[u]][i];
                q.push(v);
            }else{
                nxt[u][i]=nxt[fail[u]][i];
            }
        }
    }
}

inline ll matchCount(const string &t){
    ll u=root;
    for(char ch:t){
        u=nxt[u][idx(ch)];
        occ[u]++;
    }
    for(int i=bfsorder.size()-1;i>=0;i--){
        ll x=bfsorder[i];
        occ[fail[x]]+=occ[x];
    }
    ll ans=0;
    for(int i=1;i<=tot;i++){
        if(occ[i]>0 && outcnt[i]>0) ans+=outcnt[i];
    }
    return ans;
}

int main() {
    // 快速 I/O 优化
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 【步骤 1】读入模式串数量
    cin >> n;
    
    // 【步骤 2】构建 Trie 树
    // 将所有模式串插入到 Trie 中
    string s;
    for (int i = 1; i <= n; ++i) {
        cin >> s;         // 读入第 i 个模式串
        insertStr(s);     // 插入到 Trie 树中
    }
    // 此时 Trie 树已构建完成，包含所有模式串
    
    // 【步骤 3】读入文本串
    cin >> t;
    
    // 【步骤 4】构建 fail 指针
    buildfail();
    // 此时 AC 自动机已完全构建完成
    // Trie 树 + fail 指针 = AC 自动机
    
    // 【步骤 5】匹配并输出结果
    cout << matchCount(t) << "\n";
    // 输出在文本串 t 中出现的不同模式串数量
    
    return 0;
}

/*
 * 【关键点】
 * 1. Trie 构建：insert 函数逐个模式字符串
 * 2. fail 链构建：BFS 按层处理，fail 指向更短的相同后缀
 * 3. go 数组完善：处理失配时的边跳转
 * 4. outcnt 累加：失配链上的匹配数要累加到当前节点
 * 5. query 流程：按文本字符逐个转移，累加 outcnt
 * 
 * 【常见变体】
 * - 记录具体匹配位置（不仅是计数）
 * - 状态压缩（bit 标记匹配模式）
 * - 带权版本（每个模式有权值）
 * 
 * 【提交前检查】
 * ✓ N 是否足够（总字符数 + 余量）
 * ✓ fail 链的构建逻辑
 * ✓ go 数组是否完全填充（不留空转移）
 * ✓ outcnt 累加位置（在 fail 链建立时进行）
 */
