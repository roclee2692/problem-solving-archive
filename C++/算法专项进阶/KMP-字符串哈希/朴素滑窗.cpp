#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;

string S,P;
vector<ll> ansPos;// 所有出现位置(1-index)

void naiveMatch(){// 朴素匹配：窗口+逐字符
    ansPos.clear();
    ll n=S.size(),m=P.size();
    if(m==0||n<m) return;// 边界：空模式或模式更长
    for(int i=0,j=0;i+m<=n;i++){ // i: 窗口起点(0-index)
        while(j<m&&S[i+j]==P[j]) j++;
        if(j==m) ansPos.push_back(i+1);// 题目通常要1-index
    }
    
}
int main(){
     ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 示例：两行读取（含空格用getline；无空格可用cin）
    getline(cin, S);
    getline(cin, P);
      naiveMatch();

      for(size_t i=0;i<ansPos.size();i++){
        cout<< ansPos[i] << (i+1==ansPos.size()?'\n':' ');
      }
    if(ansPos.empty()) cout << "\n";
    return 0;
}