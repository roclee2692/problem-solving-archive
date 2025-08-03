#include <iostream>
using namespace std;
typedef long long ll;
bool isgood(ll n){
    while(n>0){//257689
       int curr=n%10;n/=10;
       if(curr%2==0) return false;//保证奇数位为奇数
       else if(n==0) return true;
       else curr=n%10;
       
       if(curr%2==1) return false;//保证偶数位为偶数
       else n/=10; 
    }return true;//C++中不能接else
   
}

int main(){
    ll n,cnt=0;
    cin>>n;
    for(ll i=1;i<=n;i++){
        if( i%2==1 &&isgood(i)) cnt++;//每次判断一个索引代表的数是否是素数
    }
    cout<<cnt<<endl;
    return 0;
    }
