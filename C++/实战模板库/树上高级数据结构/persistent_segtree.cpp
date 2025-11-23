/*
 * 【主席树/可持久化线段树】- 历史版本查询
 * 
 * 时间复杂度：O((n + q) * log n) 
 * 空间复杂度：O((n + q) * log n)
 * 
 * 适用场景：
 *   - 第 k 小元素（离线）
 *   - 动态排名问题
 *   - 时间旅行查询
 *   - 持久化数据结构
 * 
 * 模板题：
 *   - 洛谷 P3834 - 【模板】可持久化线段树 1
 *   - Codeforces 1010F - Satellite
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll N=1e6+7;
struct Node{
    ll ls,rs;
    ll cnt;
};
vector<Node> tree;
ll root[N];
ll n,m;
vector<ll> a;
vector<ll> sd;

ll NewNode(){
    tree.push_back({0,0,0});
    return tree.size()-1;
}
void insert(ll &u,ll l,ll r,ll pos,ll val){
    ll v=NewNode();
    tree[v]=tree[u];
    tree[v].cnt+=val;
    u=v;

    if(l==r) return;

    ll mid=(r+l)/2;
    if(pos<=mid){
        insert(tree[u].ls,l,mid,pos,val);
    }else{
        insert(tree[u].rs,mid+1,r,pos,val);
    }
}

ll query(ll u,ll l,ll r,ll ql,ll qr){
    if(ql>qr) return 0;
    if(ql<=l && r<=qr) return tree[u].cnt;
    ll mid=(l+r)/2;
    ll res=0;
    if(ql<=mid) res+=query(tree[u].ls,l,mid,ql,qr);
    if(qr>mid) res+=query(tree[u].rs,mid+1,r,ql,qr);  // ❌ 错误已修复：原来是 ql>mid，应该是 qr>mid
    return res;
}

ll kth(ll u,ll v,ll l,ll r,ll k){
    if(l==r) return l;
    ll mid=(l+r)/2;
    ll left_cnt=tree[tree[u].ls].cnt-tree[tree[v].ls].cnt;
    if(k<=left_cnt){
        return kth(tree[u].ls,tree[v].ls,l,mid,k);
    }
    else{
        return kth(tree[u].rs,tree[v].rs,mid+1,r,k-left_cnt);
    }
}
ll main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    a.resize(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sd.push_back(a[i]);
    }
    sort(sd.begin(),sd.end());
    sd.erase(unique(sd.begin(),sd.end()),sd.end());
    tree.push_back({0,0,0});
    root[0]=0;
    for(int i=1;i<=n;i++){
        root[i]=root[i-1];
        ll pos=lower_bound(sd.begin(),sd.end(),a[i])-sd.begin()+1;  // ❌ 错误已修复：原来是 -sd.end()，应该是 -sd.begin()
        insert(root[i],1,sd.size(),pos,1);
    }
    for(int i=0;i<m;i++){
        ll l,r,k;
        cin>>l>>r>>k;
        ll u=root[r];
        ll v=root[l-1];
        ll pos=kth(u,v,1,sd.size(),k);
        cout<<sd[pos-1]<<"\n";
    }
    return 0;
}
/*
 * 【关键点】
 * 1. Node 结构：ls, rs 子指针 + cnt 计数
 * 2. newNode：动态创建新节点
 * 3. insert：修改某个版本（复制+修改）
 * 4. root 数组：每个前缀对应一个根节点
 * 5. kth 查询：在差分树中找第 k 小
 * 6. 离散化：必要处理坐标值
 * 
 * 【常见变体】
 * - 区间第 k 小
 * - 动态排名问题
 * - 持久化并查集
 * 
 * 【提交前检查】
 * ✓ 节点动态创建是否正确
 * ✓ root 数组是否初始化
 * ✓ 离散化坐标是否正确
 * ✓ kth 查询逻辑
 */
