#include <bits/stdc++.h>
typedef long long ll;  // 定义长整型别名 ll，方便后续使用
using namespace std;  // 使用标准命名空间
const double INF =1e18;  // 定义无穷大常量

double mdist(pair<int,int> p1,pair<int,int> p2){
	double distance=sqrt(pow(p1.first-p2.first,2)+pow(p1.second-p2.second,2));
	return distance;
}
double dijkstra(int n,int s,int t,const vector<vector<double>>& graph){
	vector<double> dist(n,INF);
	vector<bool> vis(n,false);
	dist[s] = 0;//标记起点的距离为0 
	for (int i = 0; i < n; i++) {// 每次选择一个新的节点进行“确认”并更新它的邻居。
        int u = -1;
        double minDist =INF;//遇见一个未访问且不为正无穷的值，则更新最小值，为了能够有效选出最小值 
        for (int j = 0; j < n; j++) {
            if (!vis[j] && dist[j] < minDist) {
                minDist = dist[j];//记录次最小值，直到完全遍历找到最小值 
                u = j;//遍历所有未选择的节点选择一个最小值，记录该点和最小距离 
            }
        }//第一次选出的最小值一定是起点，应为他是0，这个算法不处理负边 
        if (u == -1) break;//如果提前处理完了所有可达的节点，也会 break 跳出。
        vis[u] = true;

        for (int v = 0; v < n; v++) {//更新节点 u 的邻居的距离
            if (!vis[v] && graph[u][v] != INF) {//如果在已知图中有连接的节点中未遍历 
                dist[v] = min(dist[v], dist[u] + graph[u][v]);//则判断更新最小距离 
            }
        }
    }

    return dist[t];
} 

int main() {
	int n;
	cin>>n;
	vector<pair<int,int>> point(n);//存储点 
	    for(auto &x:point)//索引从零开始，有索引可任意调用 
	    cin>>x.first>>x.second;
	int m;
	cin>>m;
	vector<vector<double>> graph(n,vector<double>(n,INF));
	for(int k=0;k<m;k++){
		int i,j;
		cin>>i>>j;//传入有连线的点 
		i--;j--;
		double dist=mdist(point[i],point[j]); 
		graph[i][j]=dist;//无向图 
		graph[j][i]=dist;
	}
	int s,t;//起点和终点 
	cin>>s>>t;
	s--;t--;//将点的序号转化为索引，必须从0开始 
	//输入的点是从一开始的，因为没有第零个点
	double ans=dijkstra(n, s, t, graph);
	printf("%.2f",ans); 
	return 0;
}
    
