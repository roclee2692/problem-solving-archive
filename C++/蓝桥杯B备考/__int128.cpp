#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;

void p8(__int128 x){//输出函数类似cout<< 
// 定义一个输出 __int128 类型的函数
// 该函数通过递归实现逐位输出 __int128 类型的数字
	if(x<0){
		putchar('-');
// 'putchar' 接受 int 类型的参数，字符常量如 '-' 会自动转换为其对应的 ASCII 值（45），因此可以传递字符常量给 'putchar'。
		x=-x;  // 如果是负数，先输出负号，并将数字转为正数	
	}
	if(x>=10){//!!!这里注意一定是大于等于10，大于0会导致无限递归
		p8(x/10);  // 如果数字大于或等于 10，就继续递归输出高位
	}
// 'putchar' 用于向标准输出打印单个字符，接受一个 int 类型参数，输出对应的字符。
	putchar(x%10+'0'); // 输出当前位（x % 10 获取的是当前位的数字）
}

// 定义一个输入 __int128 类型的函数
// 该函数从标准输入读取一个数字并返回 __int128 类型的值
__int128 r8(){//输入函数类似cin>> 
	__int128 x=0;
	char ch;// 用来读取输入的字符
	bool negative=0;//标记输入是否为负数
	
	 // 读取输入，跳过非数字字符（如空格、换行等），直到遇到数字或负号
	 while((ch=getchar())&&(ch<'0'||ch>'9')){
	 	if(ch=='-') negative=1;
	 }
	 while(ch<='9'&&ch>='0'){
	 	x=x*10+(ch-'0');//多加了一个数字说明多了一位，原来的扩大10倍 
	    ch = getchar(); // 继续读取下一个字符
	 }
	 return negative?-x:x;
}

int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
	__int128 a = r8();
    __int128 b = r8();
	 // 进行加法运算，计算 a 和 b 的和
    __int128 sum = a + b;
     // 输出结果
    p8(sum); // 调用 printInt128 输出结果
    cout<<endl;
   // 输出换行符
  return 0;
}
