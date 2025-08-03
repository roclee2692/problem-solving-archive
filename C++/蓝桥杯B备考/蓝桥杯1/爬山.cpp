#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const double INF = 1e18;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr); 
     int n,p,m;
	 cin>>n>>p>>m;
	 
	 //我要建一个最大堆，实现自动排序,因为每次施加魔法后都要重新在所有山中找到最大值 
	 priority_queue<ll> pm;
	 ll sum=0;
	 
	 for(int i=0;i<n;i++){
	 	ll h;
	 	cin>>h;
		pm.push(h);//将输入的数据压入队列
		sum+=h; 
	 }
	 
	 while((p>0||m>0)&&!pm.empty()){
	 	ll top=pm.top();
	 	pm.pop();
	 	
	 	if(top<=0){//如果已经处理多次为0了，就压回堆不做处理 
	 		pm.push(top);
	 		break;
		 }
		 
		 ll gains=-1,news=-1; // gains:开平方收益, news: 开平方后的新高度
		 if(p>0){
		 	news=(ll)floorl(sqrtl((long double)top));
		 	gains=top-news;
		 	
		 }
		 
		 ll gainh=-1,newh=-1;
		 if(m>0){
		 	newh=top/2;//错误 
		 	gainh=top-newh;//复制偷懒导致变量名忘了换 
		 	
		 }
		 
		 if(gains < 0 && gainh < 0){
		 	pm.push(top);
		 	break;
		 	
		 }
		 
		 if(gains>=gainh){
		 	sum-=gains; // 减少总和
		 	pm.push(news);  // 压回新高度
            p--;            // 开平方次数-1
		 }else{
		 	 // 使用 "减半"
            sum -= gainh;
            pm.push(newh);
            m--;
		 }
		  
	 }
	 
    // 4) 输出最终所有山峰的总高度
    cout << sum << "\n";
    return 0;
		
}
