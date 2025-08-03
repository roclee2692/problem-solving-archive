#include <iostream>
#include <vector>
#include <string> // 使用 string 的 size() 和 length()
#include <cstring> // 使用 memset 初始化 dp 表

typedef long long ll;
using namespace std;
string s;
ll dp[20][2][2];
ll dfs(int pos, bool tight,bool star){
    if(pos==s.size()) return star? 1 : 0;//排除前缀全为0的
    if(dp[pos][tight][star]!=-1) return dp[pos][tight][star];//dp记忆
    int up=tight?s[pos]-'0':9;
    ll res=0;
    for(int d=0;d<=up;d++){
        bool newtight=tight&&(d==up);
        bool newstar=star||(d>0);
        if(d!=4 && !(d==6&&  pos + 1 < s.size() && s[pos+1]=='2')) 
        res+=dfs(pos+1,newtight,newstar);
    }
   return dp[pos][tight][star]=res;
}

int main(){
    int n;
    cin>>n;
    s=to_string(n);
    memset(dp,-1,sizeof(dp));
    ll ans=dfs(0,true,false);
    cout<<ans<<endl;
    return 0;
}