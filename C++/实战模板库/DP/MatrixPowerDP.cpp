#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll MOD=1e9+7;
struct Matrix{
    vector<vector<ll>> a;
    int n,m;
    Matrix(int n0=2,int m0=2):n(n0),m(m0){
        a.assign(n0, vector<ll>(m0, 0));
    }
    Matrix operator*(const Matrix &b)const{
        Matrix c(n,b.m);
        for(int i=0;i<n;i++){
            for(int j=0;j<b.m;j++){
                for(int k=0;k<m;k++){
                    c.a[i][j]=(c.a[i][j]+a[i][k]*b.a[k][j])%MOD;
                }
            }
        }
        return c;
    }
};

Matrix qpow(Matrix a,ll b){
    Matrix res(2,2);
    res.a[0][0]=res.a[1][1]=1;
    while(b>0){
        if(b&1) res=res*a;
        a=a*a;
        b>>=1;
    }
    return res;
}

ll fib(ll n){
    if(n==1 || n==2){ return 1; }
    Matrix base(2,2);
    base.a[0][0]=1; base.a[0][1]=1;
    base.a[1][0]=1; base.a[1][1]=0;
    Matrix res=qpow(base,n-1);
    return res.a[0][0];
}

ll linearRecurrence(vector<ll> &c, vector<ll> &init, ll n){
    int k=c.size();
    if(n<init.size()) return init[n];
    Matrix base(k,k);
    for(int i=0;i<k; i++) {
        base.a[0][i]=c[i];
    }
    for(int i=1;i<k;i++){
        base.a[i][i-1]=1;
    }
    Matrix res=qpow(base, n-k+1);
    ll ans=0;
    for(int i=0;i<k;i++){
        ans=(ans+res.a[0][i]*init[k-1-i])%MOD;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin>>n;
    cout<<fib(n)<<"\n";
    return 0;
}