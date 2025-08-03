#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long ll;

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
int main(){
    ll len=343720,w=233333,dx=15,dy=17;
    ll A=dx*w,B=dy*len;
    ll g=gcd(A,B);
    ll k=A/g,m=B/g;//k是走过几个宽度，m对应长度
    if(k%2||m%2) k*=2,m*=2;//，将多个语句连成一句
    double dist=sqrt(dx*dx+dy*dy)*(len*m/double(dx));
     printf("%.2f",dist);
  return 0;
}