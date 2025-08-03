#include <iostream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;
int main(){
    map<string,int> word_count;
    string text="apple banana apple orange banana apple alldg alldg ajgdg afdg aas ddfgg applr applo  applg apple applooo";
    stringstream ss(text);
    string word;
    while(ss>>word){
        word_count[word]++;
    }
    for(const auto& pair : word_count){
        cout<<pair.first<<":"<<pair.second<<endl;
    }
    return 0;
    }