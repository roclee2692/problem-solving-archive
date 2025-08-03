#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// 扩展欧几里得
i64 extgcd(i64 a, i64 b, i64 &x, i64 &y){
    if(b==0){ x=1; y=0; return a; }
    i64 x1,y1;
    i64 g=extgcd(b,a%b,x1,y1);
    x=y1; y=x1-(a/b)*y1;
    return g;
}

// CRT 逐条合并
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin>>n;
    i64 x=0, M=1;
    for(int i=0;i<n;i++){
        i64 a,r; 
        cin>>a>>r;
        // solve x ≡ r (mod a), x ≡ old x (mod M)
        // M*x1 + a*y1 = gcd(M,a)==1
        i64 s,t; 
        extgcd(M,a,s,t);
        i64 c = (r - x % a + a) % a;
        i64 k = (s % a + a) % a * c % a;
        x = x + k * M;
        M *= a;
        x = (x % M + M) % M;
    }
    cout<<x<<"\n";
    return 0;
}
