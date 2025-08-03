#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int n=1e5+1;//n as up limit
bool ip[n];//mark whether is prime

void sieve(){
    fill(ip,ip+n,true);
    for(int i=2;i*i<n;i++){
        if(ip[i]){
            for(int j=i*i;j<n;j+=i){//遍历i的所有倍数2，3，4，5and so on
                ip[j]=false;
            }
        }
    }
}

int main(){
    sieve();
    int pc=0;
    for(int i=2;i<n;i++){
        if(ip[i]){
            pc++;
            cout<<i<<"\t";
    }
}
    cout<<"1~10^6range prime number sum up: "<<pc<<endl;
    return 0;
}