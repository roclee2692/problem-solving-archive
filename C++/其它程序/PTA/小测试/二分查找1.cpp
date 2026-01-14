#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// 【警示1】误用排序：  
// 题目要求返回元素在「原始顺序表」中的下标，调用 sort() 后会改变元素位置，
// 导致即使能查到值，也返回了「排序后」的下标，结果必错。  

// 【警示2】不必要的二分查找：  
// 本题只是简单查找，无需二分查找（输入未保证有序）；  
// 用 O(n) 的线性扫描即可在原序列上直接返回正确下标。  

// 【警示3】值传递 vector 带来隐性开销：  
// 递归时函数签名 `myfind(ll x, vector<ll> save, ll l, ll r)`  
// 会在每次调用都拷贝整个数组，效率极低。  
// 应该改为 `const vector<ll>& save` 或直接在主函数里线性查找。  

// 【警示4】递归 vs. 迭代：  
// 二分查找用递归虽然简洁，但迭代写法更直观可靠，也避免函数调用开销和潜在的栈溢出。  

// 【警示5】mid 的计算方式：  
// 虽然 `(l + r) / 2` 对 10? 范围足够，但一般推荐 `l + (r - l) / 2` 来防止 l + r 整数溢出。  

// ——改进建议：——
// 不要对输入数组排序，完全去掉二分，将查找写成：
// for (int i = 0; i < n; ++i)
//     if (save[i] == x) { cout << i; return 0; }
// cout << -1;

ll myfind(ll x,vector<ll> save,ll l,ll r){
    if(l>r) return -1;

        ll mid=(r+l)/2;
        if(save[mid]>x){
            r=mid-1;
            return myfind(x,save,l,r);
        }else if(save[mid]<x){
            l=mid+1;
            return myfind(x,save,l,r);
        }else return mid;
    
}
int main(){
    ll n,x;
    cin>>n;
    vector<ll> save(n,0);
    for(int i=0;i<n;i++){
        cin>>save[i];
    }    
    sort(save.begin(),save.end());  
    cin>>x;
    cout<<myfind(x,save,0,n-1);
   
        
return 0;
}
