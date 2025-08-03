#include <iostream>
#include <vector>
#include <cmath>
typedef long long ll;
using namespace std;
int main(){
    long double d;
    ll n;
    cin >> n >> d;
    long double res = d*pow(2, n);
    int mod = (int)(res*10) % 10;//C风格
    if(mod >= 5)  mod=res/1+1;
    else  mod=res/1;
    cout<<(int)(res+mod*0.1)<<endl;
    return 0;
}

