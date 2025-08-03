#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n;
// 返回 g = gcd(a, b)，并通过 x, y 输出 Bézout 系数，满足 a·x + b·y = g
int exgcd1(int a, int b, int &x, int &y) {
    if (b == 0) {
        // 当 b=0 时，gcd(a,0)=a，对应解 (x,y)=(1,0)
        x = 1;
        y = 0;
        return a;
    }
    // 递归计算 gcd(b, a%b) 及其 Bézout 解 (x1,y1)
    int x1, y1;
    int gcd = exgcd1(b, a % b, x1, y1);
    // 根据递推关系更新本层的 (x,y)
    // a·y1 + b·(x1 - (a/b)*y1) = g
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// 返回 g = gcd(a, b)，并通过 x, y 输出 Bézout 系数，满足 a·x + b·y = g
int exgcd2(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    // 递归：先算出 gcd(b, a%b) 及其 Bézout 解 (x1, y1)
    int g = exgcd2(b, a % b, y, x);
    // 根据 a%b = a - (a/b)*b 推导出本层解
    y -= (a / b) * x;
    return g;
}
ll modinv(ll a,ll m){
    int x,y;
    int g=exgcd1(a,m,x,y);//x就是咱们要的结果 这里引用调用函数 会直接对原值进行修改赋值
    // 此时 g==1，且 a*x + m*y = 1
    // 所以 a*x ≡ 1 (mod m)
    // 将 x 归一到 [0, m)
    x%=m;
   // if(x<0) x+=m;
    return x;
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
    int a=6,b=15,x=0,y=0;
    cout<<exgcd1(a,b,x,y)<<'\n';
    cout<<exgcd2(a,b,x,y);
  return 0;
}
