#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int xn=100000;
//时间复杂度为O(n^2),数据在10^5左右会超时
// int main(){
//     int n,g=0;
//     cin>>n;
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=n;j++){
//             g+=__gcd(i,j);
//         }
//     }
//     cout<<g<<endl;
// // }
// 优化代码
// C++ 代码（O(N log N) 复杂度）

vector<int> phi(xn+1);

void cp(int n){//手写欧拉函数，to save 比自身索引小的数中有多少与其索引本身互质的素数
    for(int i=0;i<=n;i++) phi[i]=i;//第一次遍历，使每个欧拉函数的值为自身索引
    for(int i=2;i<=n;i++){//二次遍历，从2开始，由于1之前没有与其互质的素数
 if(phi[i]==i){//如果遍历到的值与自身索引相同，说明没有被素数的倍数影响，其本身是素数
            for(int j=i;j<=n;j+=i){ //从i开始遍历，让之后素数的倍数被标记，j为i及其倍数
                                //同时保障时间复杂度，后面的每个合数只被最小的质数标记
                phi[j]=phi[j]/i*(i-1);//=phi[j]*(i-1)/i 累乘 使用了欧拉公式计算公式
            }
        }
    }
}
int main(){
    int n;
    cin>>n;
    cp(n);
    ll sum=0;
    for(int d=1;d<=n;d++){//遍历n
        ll cnt=n/d;//目的：计算 d 的倍数在 1 到 n 范围内有多少个。
        sum+=phi[d]*(cnt*(cnt+1)/2);//计算当 GCD(i, j) = d 时，所有数对 (i, j) 的贡献。
    }//  等差数列的求和公式   这个和的含义是，cnt 个数可以组成多少对数对
    //(a,a)也有最大公约数，就是a本身 多了三个，比不不按顺序的组合数多了
    //对于 d = 3，我们已经知道与 3 互质的数有 phi[3] = 2 个（即 1 和 2），
    //它们与 3 和 6 的组合都应该计入最终的贡献。3,3/3,6/1,3/2,3/2,6
    //  /6,6 两个互质的数 2,2 相乘d得到的
    cout<<sum<<endl;
    return 0;
}