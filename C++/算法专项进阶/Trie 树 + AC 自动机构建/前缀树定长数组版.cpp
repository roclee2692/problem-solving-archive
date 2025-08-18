#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;
/*数组版极快，内存按“字符总数 × 26 × sizeof(ll)”估算，适合英文小写、数据量大、速度敏感场景。

clearTrie() 只清已用部分，避免 O(全数组)。*/

const ll MAXN = 1000000 + 5; // 估算：总字符数上界（可按题目调整）
const ll SIG = 26;          // 字母表大小

// 全局 Trie
ll nxt[MAXN][SIG]; // nxt[u][c] = 子结点索引，0 表示“无”
ll passCnt[MAXN];  // 经过 u 的单词数量
ll endCnt[MAXN];   // 以 u 结尾的单词数量
ll tot = 1;        // 结点总数，根为 1
inline ll idx(char ch){ return ch - 'a'; }
inline void clearTrie(){
      // 只清已用结点，O(tot*SIG)
    for(ll i=1;i<=tot;i++){
        passCnt[i]=endCnt[i]=0;
        for(ll c=0;c<SIG;c++) nxt[i][c]=0;
    }
    tot=1;
}

inline void insertStr(const string &s){
    ll u=1;
    passCnt[u]++;
    for(char ch:s){
        ll id=idx(ch);
        if(!nxt[u][id]) nxt[u][id]=++tot;
        u=nxt[u][id];//tot并不总是等于nxt[u][id] 仅当！nex时
        passCnt[u]++;
    }
    endCnt[u]++;
}
inline ll countWord(const string &s){
    ll u=1;
    for(char ch:s){
        ll id=idx(ch);
        if(!nxt[u][id]) return 0;
        u=nxt[u][id];
    }
    return endCnt[u];
}

inline ll countPrefix(const string &s){
    ll u=1;
    for(char ch:s){
        ll id=idx(ch);
        if(!nxt[u][id]) return 0;
        u=nxt[u][id];
    }
    return passCnt[u];
}
inline void eraseOne(const string &s){
    if(countWord(s)==0) return;
    ll u=1;
    passCnt[u]--;
    for(char ch:s){
        ll id=idx(ch);
        u=nxt[u][id];
        passCnt[u]--;
    }
    endCnt[u]--;
}

int main(){
     ios::sync_with_stdio(false);
    cin.tie(nullptr);
      // 使用示例（自行替换为你的 I/O）
    clearTrie();
    insertStr("apple");
    insertStr("app");
    insertStr("app");
    // "app" 出现 2 次，"apple" 出现 1 次
    cout << countWord("app") << "\n";    // 2
    cout << countPrefix("ap") << "\n";   // 3（app*2 + apple*1）

    return 0;
}