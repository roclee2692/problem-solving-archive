#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> v;
    v.reserve(100);

    for(int i=0;i<100;++i){
        v.push_back(i);
    }

    cout <<"Capacity before shrink_to_fit: "<<v.capacity()<<endl;
    v.resize(50);
    v.shrink_to_fit();
    cout<<"Capacity after shrink_to_fit: "<<v.capacity()<<endl;

    return 0;
}