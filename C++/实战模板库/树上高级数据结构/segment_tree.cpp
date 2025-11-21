/*
 * 【线段树】- 区间查询与范围更新（带懒标记）
 * 
 * 时间复杂度：O(log n) 单点/区间操作
 * 空间复杂度：O(n)
 * 
 * 适用场景：
 *   - 区间求和/最值
 *   - 区间更新（加法）
 *   - 复杂区间查询
 *   - 比树状数组灵活
 * 
 * 模板题：
 *   - 洛谷 P3372 - 【模板】线段树 1
 *   - Codeforces 1303E - Triangle
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

struct SegmentTree{
       ll tree[N*4];
       ll lazy[N*4];
       ll n;
       void push_up(ll u){
        tree[u]= tree[2*u]+tree[2*u+1];
       }
       void push_down(ll u,ll len){
        if(!lazy[u]) return;
        lazy[2*u]+=lazy[u];
        lazy[2*u+1]+=lazy[u];
        tree[2*u]+=lazy[u]*(len/2);
        tree[2*u+1]+=lazy[u]*(len-len/2);
        lazy[u]=0;
       }
       void build(ll u,ll l,ll r,vector<ll> &arr){
        if(l==r){
            tree[u]=arr[l];
            return;
        }
        ll mid=(l+r)/2;
        build(u,l,mid,arr);
        build(u,mid+1,r,arr);
        push_up(u);
       }
        //   u - 当前节点编号
    //   l, r - 当前节点管辖的区间
    //   ql, qr - 要修改的查询区间
    //   val - 要加的值
       void update(ll u,ll l,ll r,ll ql,ll qr,ll val){
        if(ql>qr) return;
        if(ql<=l && r<=qr){
            lazy[u]+=val;
            tree[u]+=val*(r-l+1);
            return;
        }
        push_down(u,r-l+1);
        ll mid=(r+l)/2;
        if(ql<=mid){
            update(2*u,l,mid,ql,qr,val);
        }
        if(qr>mid){
            update(2*u+1,mid+1,r,ql,qr,val);
        }
        push_up(u);
       }

       ll query(ll u,ll l,ll r,ll ql,ll qr){
        if(ql>qr) return 0;
        if(ql<=l && r<=qr){
            return tree[u];
        }
        push_down(u,r-l+1);
        ll mid=(r+l)/2;
        ll res=0;
        if(ql<=mid){
            res+=query(u*2,l,mid,ql,qr);
        }
        if(qr>mid){
            res+=query(u*2+1,mid+1,r,ql,qr);
        }
        return res;
       }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<ll> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    
    SegmentTree st;
    st.n = n;
    st.build(1, 1, n, arr);
    
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        
        if (op == 1) {
            // 区间更新
            int l, r;
            ll val;
            cin >> l >> r >> val;
            st.update(1, 1, n, l, r, val);
        } else {
            // 区间查询
            int l, r;
            cin >> l >> r;
            cout << st.query(1, 1, n, l, r) << "\n";
        }
    }
    
    return 0;
}

/*
 * 【关键点】
 * 1. push_up：子节点合并为父节点
 * 2. push_down：懒标记下推（处理待更新）
 * 3. update：区间更新时打标记，不立即更新子节点
 * 4. query：查询前下推标记，确保数据一致
 * 5. 位置是 1-indexed
 * 
 * 【常见变体】
 * - 区间最值（max/min）
 * - 区间乘法更新
 * - 动态开点线段树（稀疏坐标）
 * 
 * 【提交前检查】
 * ✓ push_down 逻辑是否正确处理区间长度
 * ✓ build 是否初始化树
 * ✓ MAXN 是否足够
 * ✓ 边界条件 ql > qr
 */
