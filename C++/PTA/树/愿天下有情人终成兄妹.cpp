#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define endl "\n"
#define int long long
#define fi first
#define se second
const int N = 1e6+10, INF = 0x3f3f3f3f;
int n,k,flag=0; //flag判断询问中的第一个人还是第二个人 
char sex[N]; //记录性别 
vector<int> e[N]; //记录关系图 
set<int> s1,s2; //保存五代以内的亲戚
void dfs(int u,int dep){
	if(dep>5) return; //超过五代，过界
	if(!flag)  s1.insert(u); //记录第一个人所有的亲戚 
	else s2.insert(u); //记录第二个人所有的亲戚 

	for(auto j:e[u]){
		if(j==-1) continue; //无效ID
		dfs(j,dep+1);
	}
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++){
		int a,b,c;
		char gender; 
		cin >> a >> gender >> b >> c;
		sex[a]=gender;
		sex[b]='M'; sex[c]='F'; //父母性别直接补上
		e[a].push_back(b);
		e[a].push_back(c);
	}
	cin>>k;
	while(k--){
		int a,b; cin>>a>>b;
		flag=0; s1.clear(); //重置 
		dfs(a,1); //找a的五代以内亲戚 
		flag=1; s2.clear(); //重置 
		dfs(b,1); //找b的五代以内亲戚 
		
		bool f=false; //开始假设关系超过了五服 
		for(auto i:s2) if(s1.count(i)) f=true; //有共同祖先，五服以内
		  
		if(sex[a]==sex[b]) cout<<"Never Mind"<<endl; //同性
		else if(f) cout<<"No"<<endl; //异性但五服以内，有共同祖先
		else cout<<"Yes"<<endl; //异性且超过五服
	}
}
signed main() {
    //	IOS;
        int T=1;
    //	cin>>T;
        while(T--) {
            solve();
        }
        return 0;    
    }
    
