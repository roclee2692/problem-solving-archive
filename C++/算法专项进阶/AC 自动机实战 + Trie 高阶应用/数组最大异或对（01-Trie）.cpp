#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const int MAXB=60;
// -------- 01-Trie （全 ll，节点索引也用 ll）---------
struct XORTrie{

    vector<array<ll,2>> nxt;
     // 每个节点有两个出口：0 和 1
    // nxt[u][0] 表示节点 u 的“0 儿子”，nxt[u][1] 表示“1 儿子”
    // 0 表示“还没有这个儿子”
    ll tot;
    XORTrie(ll max_nodes=0){ // 构造函数：预分配 max_nodes 个节点（上界）
        if(max_nodes) init(max_nodes);
    }
    void init(ll max_nodes){ // 构造函数：预分配 max_nodes 个节点（上界）
        nxt.assign(max_nodes+2,{0,0});
        tot=1;
    }
    inline int bit(ll x,ll b){return  (int)((x>>b)&1LL); }  // 取出整数 x 的第 b 位（二进制，0/1）
    inline void insert(ll x){   // 插入一个数 x（从最高位到最低位）
        ll u=1;// 从根节点开始
        for(int b=MAXB;b>=0;b--){
            int c=bit(x,b); // 当前位是 0 还是 1
            if(!nxt[u][c]) nxt[u][c]=++tot;// 如果没有子节点就新建
            u=nxt[u][c]; // 走到子节点
        }
     }
    // 返回与 x 异或值最大的“值”   看上去像累加，但本质上是“逐位点亮”。
    inline ll query_max_xor(ll x){
        ll u=1,y=0;// y 表示异或值
        for(int b=MAXB;b>=0;b--){
            int c=bit(x,b),want=c^1; // 当前位  // 想要的相反位
            if(nxt[u][want]) { u=nxt[u][want]; y|=(1LL<<b);} // 如果能走到相反位，就走它，答案这一位就是 1
            else { u=nxt[u][c]; }  // 否则只能走相同位，这一位异或结果是 0
        }
        return y; // 返回的是异或值（不是配对的那个数）
    }
};

ll max_xor_pair(const vector<ll> &a){
    if(a.empty()) return 0;
     // 预估节点：|a|*(MAXB+1)

    // 预分配节点：每个数最多 61 位，每位可能新建一个节点
    //最坏情况，新节点数 ≤ |a| * (MAXB+1)。预分配到这个上界，可避免反复扩容，常数更小、更稳。
    XORTrie tr(a.size()*(MAXB+1));
    ll ans=0;
    tr.insert(a[0]); // 插入第一个数
     // 从第二个数开始：每次先查再插 要求“两两不同”的最大异或对。 这样保证每次配对对象都是“之前的数”，不会自配。
     //Trie 允许“自己和自己异或”，就产生了伪答案 0。
     /*最大异或对要求的是“数组里两个不同元素”的最大异或值。
所以流程必须是：
一边扫数组，一边维护 Trie。
每次要查找时，只能和 之前已经插入过的数 配对。
查完再把自己插入，供后面的数使用。*/
     for(size_t i=1;i<a.size();i++){
        ans=max(ans,tr.query_max_xor(a[i]));
        tr.insert(a[i]);
     }
    return ans;
    /*如果 MAXB 是定义在 struct XORTrie { ... }; 里面的 static const int MAXB = 60;，
那么它属于 XORTrie 的成员常量，必须写成 XORTrie::MAXB 才能访问。*/
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector<ll> a(n);
    for(int i=0;i<n;i++){ cin>>a[i]; }
    ll res=max_xor_pair(a);
    cout<<res<<"\n";
    return 0;
}