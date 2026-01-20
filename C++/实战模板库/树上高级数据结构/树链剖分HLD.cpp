#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int XN=1e5+7;
ll mod;
vector<int> adj[XN];
int n,m,root;

int fa[XN];
int dep[XN];
int siz[XN];
int son[XN];

int top[XN];
int dfn[XN];
int rnk[XN];
int cnt_dfn;

ll a[XN];
ll w[XN];

struct SegmentTree{
    ll tree[XN*4];
    ll lazy[XN*4];
    void push_up(int u){
        tree[u]=(tree[u*2]+tree[u*2+1])%mod;
    }
    void push_down(int u,int len){
        if(!lazy[u]) return;
         lazy[u * 2] = (lazy[u * 2] + lazy[u]) % mod;
        lazy[u * 2 + 1] = (lazy[u * 2 + 1] + lazy[u]) % mod;
        tree[u * 2] = (tree[u * 2] + lazy[u] * (len / 2)) % mod;
        tree[u * 2 + 1] = (tree[u * 2 + 1] + lazy[u] * (len - len / 2)) % mod;
        lazy[u]=0;
    }
    void build(int u,int l,int r){
        lazy[u]=0;
        if(l==r){
            tree[u]=w[l]%mod;
            return;
        }
        int mid=(l+r)/2;
        build(u*2,l,mid);
        build(u*2+1,mid+1,r);
        push_up(u);
    }
    void update(int u,int l,int r,int ql,int qr,ll val){
        val%=mod;
        if(ql<=l && r<=qr){
            lazy[u] = (lazy[u] + val) % mod;
            tree[u] = (tree[u] + val * (r - l + 1)) % mod;
            return;
        }
        push_down(u,r-l+1);
        int mid=(l+r)/2;
        if(ql<=mid) update(u*2,l,mid,ql,qr,val);
        if(qr>mid) update(u*2+1,mid+1,r,ql,qr,val);
        push_up(u);
    }
    ll query(int u,int l,int r,int ql,int qr){
        if(ql<=l && r<=qr) return tree[u];
        push_down(u,r-l+1);
        int mid=(l+r)/2;
        ll res=0;
        if (ql <= mid) res = (res + query(u * 2, l, mid, ql, qr)) % mod;
        if (qr > mid) res = (res + query(u * 2 + 1, mid + 1, r, ql, qr)) % mod;
        return res;
    }
} seg;

void dfs1(int u,int f,int d){
    fa[u]=f;
    dep[u]=d;
    siz[u]=1;
    son[u]=0;

    int max_siz=0;
    for(int v:adj[u]){
        if(v==f) continue;
        dfs1(v,u,d+1);
        siz[u]+=siz[v];
        if(siz[v]>max_siz){
            max_siz=siz[v];
            son[u]=v;
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++cnt_dfn;
    rnk[cnt_dfn]=u;
    w[cnt_dfn]=a[u];
    if(!son[u]) return;
    dfs2(son[u],t);
    for(int v:adj[u]){
        if(v==fa[u] || v==son[u]) continue;
        dfs2(v,v);
    }
}

ll query_path(int u,int v){
    ll res=0;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        res+=seg.query(1,1,n,dfn[top[u]],dfn[u]);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    res = (res + seg.query(1, 1, n, dfn[top[u]], dfn[u])) % mod;
    return res;
}
void update_path(int u,int v,ll val){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        seg.update(1,1,n,dfn[top[u]],dfn[u],val);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    seg.update(1,1,n,dfn[u],dfn[v],val);
}

ll query_subtree(int u){
    return seg.query(1,1,n,dfn[u],dfn[u]+siz[u]-1);
}
void update_subtree(int u,ll val){
    seg.update(1,1,n,dfn[u],dfn[u]+siz[u]-1,val);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>root>>mod;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(root,0,1);
    dfs2(root,root);
    seg.build(1,1,n);
    while(m--){
        int op;
        cin>>op;
        if(op==1){
            int x,y;
            ll z;
            cin>>x>>y>>z;
            update_path(x,y,z);
        }else if (op == 2) {
            // 路径查询
            int x, y;
            cin >> x >> y;
            cout << query_path(x, y) % mod << "\n";
        } else if (op == 3) {
            // 子树加
            int x;
            ll z;
            cin >> x >> z;
            update_subtree(x, z);
        } else {
            // 子树查询
            int x;
            cin >> x;
            cout << query_subtree(x) % mod << "\n";
        }
    }
     return 0;
}