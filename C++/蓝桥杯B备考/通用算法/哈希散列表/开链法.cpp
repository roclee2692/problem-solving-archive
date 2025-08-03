#include <iostream>
#include <vector>
#include <list>
using namespace std;

class mh{
    private:
        static const int size=10007;
        vector<list<int>> ta;
        int hash(int key){
            return key%size;
        }
    public:
        mh():ta(size){}

    void add(int key){
        int index=hash(key);
        for(int num:ta[index]){
            if(num==key) return;
        }
        ta[index].push_back(key);
    }

    void remove(int key){
        int ix=hash(key);
        ta[ix].remove(key);
    }

    bool contains(int key){
        int ix=hash(key);
        for(int num:ta[ix]){
            if(num==key) return true;
        }
        return false;
    }
};

int main(){
    mh hs;
    hs.add(1);
    hs.add(2);
    cout<<hs.contains(1)<<"\n";
    std::cout << hs.contains(3) << "\n"; // 输出 0（false）
    hs.add(2);
    std::cout << hs.contains(2) << "\n"; // 输出 1（true）
    hs.remove(2);
    std::cout << hs.contains(2) << "\n"; // 输出 0（false）
    return 0;
}