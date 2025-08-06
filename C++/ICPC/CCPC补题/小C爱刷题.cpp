#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;

int main(){
ios::sync_with_stdio(0);cin.tie(0);
ll n,q;
cin>>n>>q;
//int save=n+1;//C++不支持变长数组初始化 不能对变量+1 扩容数组 但容器可以
vector<ll> a(n+1,0),sum(n+1,0),xo(n+1,0);//索引从1开始到n 
for(int i=1;i<n+1;i++){
    cin>>a[i];
}
//using P=pair<ll,ll>;
//vector<P> pair(q);//我也可以不用pair 边输入数据 便处理 每次询问独立可以这么做
   // for(ll j=0;j<q;j++) {
    //    cin>>pair[j].first>>pair[j].second;
   // }
//for(ll j=0;j<q;j++){
 // 双重循环：O(n*q) = O((10^6)*(10^6)) = 10^12 次运算
// 一秒约能做 10^8 次，2 秒约能做 2×10^8 次
// 10^12 ? 2×10^8，必然超时 考虑前缀和优化
for(ll k=1;k<=n;k++){//一个for 构造前缀和
  //  ll res1=0,res2=0,res=0; 前缀和会存储之前的和 也不需要 记录结果了
       sum[k]=sum[k-1]+a[k];
       xo[k]=xo[k-1]^a[k];  
   }
while(q--){
int l,r;
    cin>>l>>r;
    ll s=sum[r]-sum[l-1];
    ll x=xo[r]^xo[l-1];
    cout<<  ( s^x ) <<'\n';//是因为 C++ 里 <<（流插入）和 ^（异或）的优先级问题：加（） 双目位运算>>的优先级高于单目的……
    /*表达式类型内容长度（含终止符）
'\n' char（字符字面量） 单个换行字符 
"\n" const char[2]（字符串字面量） 第一个字符是 '\n'，第二个是终止符 '\0' 2 */
}/*小结
非交互式比赛题，用 cout << x << '\n'; 完全安全，
程序结束时缓冲区会自动刷新，答案不会丢失。
只有在交互式场景下，才需要在关键点用 cout << ... << endl;、
 或手动 cout.flush(); 来确保裁判端能立刻收到你的输出。*/
  return 0;
}