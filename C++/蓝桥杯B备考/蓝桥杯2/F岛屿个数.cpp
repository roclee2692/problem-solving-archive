#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const double INF = 1e18;
const int N = 52;  // 定义地图的最大尺寸为 60x60

char c;  // 临时存储每个输入的字符
int g[N][N], n, m, res, t;  // g 数组存储地图，n 和 m 是地图的行列数，res 存储岛屿数量，t 是测试数据组数
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};  // 定义四个方向的移动偏移量，用于上、下、左、右方向的DFS

bool st[N][N];  // st 数组用于记录每个格子是否已经被访问过

// 递归函数：dfs_1，用于标记岛屿中的格子
void dfs_1(int r,int c){
	st[r][c]=true;
	for(int k=0;k<4;k++){
		int x = dx[k] + r, y = dy[k] + c;
		if(st[x][y]||g[x][y]==0) continue;
		dfs_1(x,y);//灵活使用递归极大的简化代码 
		
	}
} 
// 递归函数：dfs_0，用于从外部海洋开始标记所有海水格子，并检查岛屿
void dfs_0(int r,int c){
	st[r][c]=1;
	for(int i=-1;i<=1;i++){//如何实现遍历8个方向，3*3即可  给出8个偏移量 
		for(int j=-1;j<=1;j++){
			int x=r+i;int y=c+j;
			 if(x<0||x>n+1||y<0||y>m+1||st[x][y]) continue;//麻烦？不麻烦，只是防止越界和以遍历重复
			 if(g[x][y]==0){
			 	dfs_0(x,y);
			 } else{
			 	dfs_1(x,y);
			 	res++;
			 }
		}
	}
} 

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	 cin>>t;
	 while(t--){
	 	memset(g,0,sizeof(g));
	 	memset(st,0,sizeof(st));
	 	res=0;
	 	cin>>n>>m;
	 	for(int i=1;i<=n;i++){
	// 为给外层预留一圈“外海”边界（0 与 n+1 / m+1），实际地图填入区间 [1..n][1..m]。
	 		for(int j=1;j<=m;j++){
	 			cin>>c;
	 			g[i][j]=c-'0';
	 // 输入数据一行是连续字符，直接读取整数会出错，因此需要先读取字符后转换为数字。

			 }
		 } 
		 dfs_0(0, 0);  // 从外海（假设坐标 (0,0) 外海）自己定义的外海 开始递归遍历
        cout << res << '\n';  // 输出岛屿数量
	 
	 }
		

  return 0;
}
