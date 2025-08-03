#include <iostream>
#include <vector>
using namespace std;
int main(){
vector<int> v={1,2,3,4,5};
//遍历删除偶数
for(auto it=v.begin();it !=v.end();){
    if(*it%2==0){
        it=v.erase(it);
    }else{
        ++it;
    }
}

for(int x:v){
    cout<<x<<" ";
}

    return 0;
}