#include <iostream>
#include <string>
using namespace std;

string bna(string s1,string s2){
    string rt="";
    int carry=0,sum=0;
    int i=s1.size()-1,j=s2.size()-1;
    while(i>=0||j>=0||carry){
        int x=(i>=0)?s1[i--]-'0':0;
        int y=(j>=0)?s2[j--]-'0':0;
        sum=x+y+carry;
        rt=char(sum%10+'0')+rt;
        carry=sum/10;
    }
    return rt;
}

long long fastpow(long long a,long long b,long long mod){
    if(b==0) return 1;
    long long half=fastpow(a,b>>1,mod);
    half=(half*half)%mod;
    if(b&1) half=(half*a)%mod;
    return half;
}

// 测试代码
int main() {
    // 测试大数加法
    string num1 = "987654321987654321987654321";
    string num2 = "123456789123456789123456789";
    cout << "大数加法：" << num1 << " + " << num2 << " = " << bna(num1, num2) << endl;

    // 测试快速幂
    long long a = 2, b = 10, mod = 1000000007;
    cout << "快速幂：" << a << "^" << b << " % " << mod << " = " << fastpow(a, b, mod) << endl;

    return 0;
}