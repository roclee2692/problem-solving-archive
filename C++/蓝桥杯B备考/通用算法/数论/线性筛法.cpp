#include <iostream>
#include <vector>
using namespace std;
const int n=1e6+1;
vector<int> pr;//save all prime
int ip[n];//全局变量，自动初始化为0，标记是质数的，初始均未标记

void ls(){
    for(int i=2;i<n;i++){
        if(!ip[i]){//如果未标记就加入素数
            ip[i]=i;//让素数索引数组标记为自己
            pr.push_back(i);
        }
        for(int p:pr){
            if(p>ip[i]||i*p>=n) break;//如果已经被更小素数标记过或数组范围越界就跳出本次循环
            ip[i*p]=p;//标记倍数
            }
        }
    }

    int main(){
        ls();
        cout<<"1~10^6 renge prime number sun: "<<pr.size()<<endl;
        return 0;
    }