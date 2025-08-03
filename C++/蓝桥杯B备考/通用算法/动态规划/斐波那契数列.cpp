#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

int fibonacci(int n){
   vector<int> dp(n+1);
   dp[0] = 0;
   dp[1] = 1;

   for(int i=2;i<n+1;i++){
    dp[i]=dp[i-1]+dp[i-2];

   }
return dp[n];
}
int main(){
    int a;
    cout<<"请输入数据n= ";
    cin>>a;
    cout<<fibonacci(a);
    return 0;
    }