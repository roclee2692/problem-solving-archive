#include <bits/stdc++.h>
using namespace std;

bool lunky(int n){
	 string s=to_string(n);
	 int sum1 = 0, sum2 = 0;//局部参与运算的变量一定要初始化 
	 for(int i=0;i<s.size();i++){//如果报错使用int len=s.length(); 强制转换为 int 如果字符串长度超过 INT_MAX，会出错。21亿
	 //或for (size_t i = len; i-- > 0; )  // 使用 `i-- > 0` 的写法避免负数问题 
	 //最后的长度取不到，不可写成s.size()-1,这会少算一个字符，此时从0到len-1,恰为len个 
		if(i<3)	sum1 += s[i] - '0'; //当时直接用了i不是字符s[i]呀！！！ 
		else sum2 += s[i] - '0';
	
    }
		return sum1==sum2;
	
	}
	

int main(){
	int cnt;
	cin>>cnt;//输入执行次数 
	while(cnt--){
		int n;
		cin>>n;
		if(lunky(n)) cout<<"yes\n";
		else cout<<"no\n";
	  
	}
	  return 0;
}	