// ========== 头文件 ==========
#include <bits/stdc++.h>
using namespace std;

// ========== 基本宏定义 ==========
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define endl "\n"

// 保证int默认是long long，防止爆int
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

// 快速最大最小函数（可选）
template<typename T> inline T Max(T a, T b) { return a > b ? a : b; }
template<typename T> inline T Min(T a, T b) { return a < b ? a : b; }

// 常用常量
const int INF = 0x3f3f3f3f; // int型无穷大
const ll LINF = 1e18;       // long long型无穷大
const int MOD = 1e9+7;      // 模运算常用模数
const int N = 2e5+10;       // 数据范围（可以按题目调整）

// 快速读入模板（大数据量必备）
inline int read() {
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9'){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); }
    return x*f;
}

// 快速输出（有时也能用）
inline void write(int x){
    if(x<0){ putchar('-'); x=-x; }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

// ========== 主要代码从这里开始 ==========
void solve() {
    // 这里写每一组数据的处理逻辑
}

int main() {
    IOS; // 加速输入输出

    int T = 1; 
    // cin >> T; // 如果题目是多组数据，取消注释
    while(T--) solve();

    return 0;
}

#define endl "\n"

cout << "数据输出完了" << endl;
cout.flush();  // 手动刷新
