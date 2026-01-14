#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> a(51,0);
int main(){
    int n,x;
     cin>>n;
   // while(cin>>x&&n--){//这里用n--&& 依然不够严谨 当n=0时 确实会跳过一次 但是如果还有数据输入 n会递减为-1使读入继续 出现错误
        // for(ll i=0;i<51;i++){
         //   if(i==x) a[i]++;
       // }
   // }

//优化后的
    for(ll i=0;i<n;i++){
        cin>>x;//依次读取n个x
        a[x]++;//因为x一定在【0，50】内也不用考虑数组越界的问题 直接哈希 让x对应的年龄加1
    }
    for(int j=0;j<51;j++){
        if(a[j]!=0){
            cout<<j<<":"<<a[j]<<'\n';
        }
    }
    return 0;
}