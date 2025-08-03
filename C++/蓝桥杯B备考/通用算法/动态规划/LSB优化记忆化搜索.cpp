#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

vector<int> memo; 
int fib(int n){
if(n<=1) return n;
if(memo[n]!=-1){
    return memo[n];
}
memo[n]=fib(n-1)+fib(n-2);
return memo[n];
}

int main(){
    int n=45;
    memo.resize(n+1,-1);
    cout<<"fibonacci of "<<n<<" is: "<<fib(n)<<endl;
    return 0;
    }