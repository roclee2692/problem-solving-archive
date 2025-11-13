#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;

struct Node {
    ll passCnt = 0;
    ll endCnt  = 0;
    unordered_map<char,ll> nxt; // 更快的查找，适合 Trie 树
    // map<char,ll> nxt; // 有序版本，内存更省但稍慢
};

vector<Node> T(2); // 下标 1 作为根
ll tot = 1;

inline void clearTrie(){
    T.assign(2, Node());
    tot = 1;
}
inline void insertStr(const string &s){
    ll u = 1;
    T[u].passCnt++;
    for(char ch: s){
        if(!T[u].nxt.count(ch)){
            T[u].nxt[ch] = ++tot;
            if((ll)T.size() <= tot) T.emplace_back();
/*动态分配节点：Trie 树的节点数量在插入过程中是动态增长的
避免越界：确保 T[tot] 是有效的访问
按需扩展：只在需要时才增加内存，节省空间*/
        }
        u = T[u].nxt[ch];
        T[u].passCnt++;
    }
    T[u].endCnt++;
}

inline ll countWord(const string &s){
    ll u = 1;
    for(char ch: s){
        if(!T[u].nxt.count(ch)) return 0;
        u = T[u].nxt[ch];
    }
    return T[u].endCnt;
}

inline ll countPrefix(const string &p){
    ll u = 1;
    for(char ch: p){
        if(!T[u].nxt.count(ch)) return 0;
        u = T[u].nxt[ch];
    }
    return T[u].passCnt;
}
inline void eraseOnce(const string &s){
    if(countWord(s)==0) return;
    ll u = 1;
    T[u].passCnt--;
    for(char ch: s){
        u = T[u].nxt[ch];
        T[u].passCnt--;
    }
    T[u].endCnt--;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    clearTrie();
    insertStr("Hello");
    insertStr("Hell");
    cout << countWord("Hello") << "\n";   // 1
    cout << countPrefix("He") << "\n";    // 2
    return 0;
}