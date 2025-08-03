#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll myfind(ll x, const vector<ll> &save,ll l,ll r){//该数组拷贝为引用 提高效率
    if(l>r) return -1;
    ll len=save.size();
  //  for(ll i=0;i<len;i++){//这里误用for 循环 你都递归了用什么for循环呀！ 只会导致查找错误
        ll mid=(r+l)/2;
        if(save[mid]>x){
            r=mid-1;
           return  myfind(x,save,l,r);//这里递归之后呢，查找的值直接丢失了 ！！rutun !
        }else if(save[mid]<x){
            l=mid+1;
           return  myfind(x,save,l,r);//这里递归之后呢，查找的值直接丢失了 ！！rutun !
        }else return mid;
    //}
}
int main(){
    ll n,x;
    cin>>n;
    vector<ll> save(n,0);
    for(int i=0;i<n;i++){
        cin>>save[i];//确保符合二分查找使用条件 数组已经有序
    }      
    
    while(cin>>x){
        if(x==-1) break;
        ll res=myfind(x,save,0,n-1)+1;//索引+1
        cout<<( res!=-1 ? res: 0)<<" ";
    }
        
return 0;
}
// 快速输入多个整数直到 -1
int x;
while (cin >> x && x != -1) {
    // ...
}

// 条件输出
cout << (flag ? "YES" : "NO") << endl;

// 一行输出数组
for (int i = 0; i < n; cout << arr[i++] << ' ');
