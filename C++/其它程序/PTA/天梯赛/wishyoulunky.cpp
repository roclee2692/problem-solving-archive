#include <bits/stdc++.h>
using namespace std;

bool lunky(int n){
    string s=to_string(n);
    int sum1=0,sum2=0;
   		int i=0;
        while(i<3){
            sum1+=(s[i]-'0');
            i++;
        }
        while(i>=3&&i<6){
            sum2+=(s[i]-'0');
            i++;
        }
		return sum1==sum2;
}

int main(){
    int c;
    cin>>c;
    vector<int> num(c);
    for(auto &x:num){
        cin>>x;
 }
    for(auto &x:num){
        if(lunky(x)) cout<<"You are lucky!"<<endl;
    else cout<<"Wish you good luck."<<endl;
    }
    
    return 0;
}