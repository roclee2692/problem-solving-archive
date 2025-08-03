#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const double INF = 1e18;
  
 struct plane{
 	int t,d,l;	
 };
int T,n,cnt,last;
bool found;
vector<plane> planes(15);
vector<bool> visited(15);
// DFS 判断是否存在一种合法的降落顺序	
bool dfs(int n,int cnt,int last){
	if(cnt==n) return true;//递归终止条件 
	
	for(int i=0;i<n;i++){
		if(!visited[i]){//确保没有被访问过 
			int arrive=planes[i].t;
			int deadline=arrive+planes[i].d;
			int landtime=planes[i].l;
			
			if(deadline>=last){//如果最大飞行截至时间>=前一飞机的降落时间测进行循环 
				visited[i]=true;//初始last=0，第一架飞机来了即降落，
				//最终它的last=t+l;后面的飞机若早到了要等前一飞机降落后 ；若晚到，到了即可降落，此时t>l;
				bool found=dfs(n,cnt+1,max(arrive,last)+landtime); 
				if(found){
					return true; 
				}
				visited[i]=false;// 回溯  函数没有退出说明撞墙了，要换条路继续搜索直到找到一条合法路径 
			}
		}
	}
	return false; 
}
	  
 
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	 cin>>T;	
	while(T--){
		 cin>>n;//这里n必须写里面，确保每组输入的n值都能被更新 
			for(int i=0;i<n;i++){
				cin>>planes[i].t>>planes[i].d>>planes[i].l;
			}
			dfs(n, 0, 0)?cout<<"YES"<<endl:cout<<"NO"<<endl;
			  fill(visited.begin(), visited.end(), false);  // 每次开始前清空 visited 数组
			  //或者memset(visited,0,sizeof(visited)); 
		}	
    return 0;
}

