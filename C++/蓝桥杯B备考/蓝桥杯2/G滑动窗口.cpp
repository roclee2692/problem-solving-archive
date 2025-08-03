#include <bits/stdc++.h>
using namespace std;
int K;
long long ans=0, c1_sum=0;
// 优先使用 long long 代替 int，避免溢出，牺牲极小内存换取更高安全性。

string S;
char c1,c2;

int main(){
    cin >> K >> S >> c1 >> c2;
    // i 从 (K-1) 开始遍历到字符串末尾
    // j = i - (K - 1)，表示当前要检查的子串最短起点
    for(int i = K - 1, j = 0; i < S.length(); i++, j++){
        // 如果下标 j 位置字符是 c1，就表示“可以从这里开始”的有效起点多了一个
        if(S[j] == c1) c1_sum++;

        // 如果下标 i 位置字符是 c2，那么
        // 以 i 为尾、且长度 >= K 的所有子串，其起点 j' 至少要满足 j' <= i - (K - 1)
        // 我们前面 c1_sum 就是统计了从 0 到 j 下标中多少个位置是 c1
        // 于是对于当前 i，如果尾字符是 c2，就加上所有这些可能起点的数量
        if(S[i] == c2) ans += c1_sum;
    }
    cout << ans;
    return 0;
}
