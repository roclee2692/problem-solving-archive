#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int XN=1e5+5;
struct Point{
    int a,b,c;
    int cnt;
    int ans;
    bool operator<(const Point &p) const{
        if(a!=p.a) return a<p.a;
        if(b!=p.b) return b<p.b;
        return c<p.c;
    }
    bool operator==(const Point &p) const{
        return a==p.a && b==p.b && c==p.c;
    }
};

Point p[XN],tmp[XN];
int n,k;
int ans[XN];
struct BIT{
    int c[XN];
    int maxn;
    void init(int n){
        maxn=n;
        fill(c,c+n+1,0);
    }
    int lowbit(int x){
        return x&(-x);
    }
    void add(int x,int val){
        while(x<=maxn){
            c[x]+=val;
            x+=lowbit(x);
        }
    }
    int query(int x){
        int res=0;
        while(x>0){
            res+=c[x];
            x-=lowbit(x);
        }
        return res;
    }
}bit;
void cdq(int l,int r){
    if(l>=r) return;
    int mid=(l+r)/2;
    cdq(l,mid);
    cdq(mid+1,r);
    int i=l,j=mid+1,k=l;
    while(i<=mid && j<=r){//双指针
        if(p[i].b<=p[j].b){
            bit.add(p[i].c,p[i].cnt);
            tmp[k++]=p[i++];
        }else{
            p[j].ans+=bit.query(p[j].c);
            tmp[k++]=p[j++];
        }
    }
    while (j <= r) {
        p[j].ans += bit.query(p[j].c);
        tmp[k++] = p[j++];
    }
    while (i <= mid) {
        bit.add(p[i].c, p[i].cnt);
        tmp[k++] = p[i++];
    }
      for (int i = l; i <= mid; i++) {
        bit.add(p[i].c, -p[i].cnt);
    }
       for (int i = l; i <= r; i++) {
        p[i] = tmp[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
        vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].a >> points[i].b >> points[i].c;
        points[i].cnt = 1;
        points[i].ans = 0;
    }
        sort(points.begin(), points.end());
    int m = 0;
        for (int i = 0; i < n; i++) {
            if (m == 0 || !(points[i] == p[m])) {
                p[++m] = points[i];
            } else {
                p[m].cnt++;
            }
        }
        bit.init(k);
        cdq(1, m);
        for (int i = 1; i <= m; i++) {
               ans[p[i].ans + p[i].cnt - 1] += p[i].cnt;
        }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}
