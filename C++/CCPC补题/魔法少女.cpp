#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;
ll n,m,k,sum=0;

int main(){
ios::sync_with_stdio(0);cin.tie(0);
cin>>n>>m>>k;
    vector<ll> arr1(n+1,0),arr2(m+1,0);
    for(int i=1;i<=n;i++){//索引从一开始要特别小心的控制索引下标的偏移 1~n
        cin>>arr1[i];
    }
    for(int i=1;i<=m;i++){
        cin>>arr2[i];
    }
    sort(arr1.begin() + 1,arr1.end(),greater<ll>());//这里排序时最好不要将 不参入的索引0加入排序 
    //可能导致排序顺序错误  你只从 1~n 遍历 可能将有效值挤出此范围 引入错误顺序
    sort(arr2.begin() + 1,arr2.end(),greater<ll>()); 
    /*
?你忘写 <ll>，编译器会默认使用 greater<>，并根据容器元素类型推导出 <ll>。
? 这就是 C++14 以后的 STL 优化之一，让代码更简洁。
? 如果你使用的编译器比较老（比如 C++11），那就必须手动写出 <ll>，否则会报错。
*/
    ll MIN=min(m,n);
    //using 类型别名 = 原类型;
    for(int i=1;i<=MIN;i++){
        sum+=max(2*arr1[i]+arr2[i],arr1[i]+arr2[i]+k);
    }
    int m1=m; int n1=n;
    m-=MIN;n-=MIN;
    /*这里要考虑到 你无论是在for循环中 还是在这里直接赋值m n 
    都会改变遍历的终止条件 所以使用这种方法必须复制一份初始值*/
    if(n>0) {  
     for(int i=MIN+1;i<=n1;i++) { sum+=arr1[i]; }
    }//遍历的起始条件是从 MIN开始不是改变前后的 m n的任一个都不符合
     if(m>0) {  
     for(int i=MIN+1;i<=m1;i++) { sum+=arr2[i];}
    }
    cout<<sum<<'\n';
  return 0;
}
/*






*/