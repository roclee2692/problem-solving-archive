#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LCS(string x,string y){
    int m=x.size(),n=y.size();
    vector<int> prev(n+1,0),curr(m+1,0);
    
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
        if(x[i-1]==y[j-1]){
            curr[j]=prev[j-1]+1;}
        else{
            curr[j]=max(prev[j],curr[j-1]);
        }
        }
        swap(prev,curr);
    }

    return prev[n];
}


int main(){
    string X = "ABCBDAB", Y = "BDCABB";
    cout << "Length of LCS: " << LCS(X, Y) << endl;
    return 0;
}