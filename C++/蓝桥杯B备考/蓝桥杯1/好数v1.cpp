#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;
int c=0;

bool ih(int n){
	string s=to_string(n);
	int len=s.length();
	int ind=len-1;

	//如果报错        1——len,字符一个不少
	// for (size_t i = len; i-- > 0; ) { // 使用 `i-- > 0` 的写法避免负数问题
	// 	if (s[i] - '0' & 1) {
	// 		if (i == 0) break; // 避免 i-- 导致的溢出
	// 		i--;
	// 	}
	// }

	for(int i=ind;i>=0;){
		if(s[i]-'0'&1) i--;//是奇数 
		else 
			return false;
		if(i>=0 &&!(s[i]-'0'&1)) i--;//是偶数 
		 	//i-=2;//这里可能导致数组越界，i=1时会变成负一 
		else if(i==-1) return true;//如果前面的都通过了说明完全符合条件直接通过 
		else return false;
	}
	return true;
}

int main(){
    ll num;
    cin>>num;
    for(int i=1;i<=num;i++){
    	if(i&1&&ih(i)) c++; 
	}
	cout<<c<<endl;
    return 0;
    }