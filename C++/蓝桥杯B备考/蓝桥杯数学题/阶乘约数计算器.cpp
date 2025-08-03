#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

// 计算 n! 的约数个数
ll cd(int n){
    vector<int> cnt(n+1,0);
    for(int i=2;i<=n;i++){ // 计算 n! 的质因数分解
        for(int j=i;j<=n;j+=i){
            cnt[i]++;//储存有多少质因数,即质因数的指数
         }//countDivisors：计算并返回 n! 的约数个数。
        // cnt：保存从 1 到 n 的每个数的质因数分解的计数。
        }
     // res：保存最终的 n! 的约数个数。result
    ll res=1;
    for(int i=2;i<=n;i++){
        if(cnt[i]>0){
            res*=(cnt[i]+1);//就是将每个质因数的选择数相乘，
            //从而计算 n! 的总约数个数。
        }
   }
    return res;
}

int main(){
    int n;
    cout<<"请输入：";
    cin>>n;
    cout<<cd(n)<<endl;
    return 0;
}