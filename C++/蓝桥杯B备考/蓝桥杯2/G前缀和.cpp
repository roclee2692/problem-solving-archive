#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    string s;
    char c1, c2;
    cin >> k >> s >> c1 >> c2;  // 读取

    int n = s.size();
    vector<long long> pre(n, 0);  // 前缀和数组
    long long res = 0;

    for(int i = 0; i < n; i++){
        // 构造前缀和：pre[i] 表示 s[0..i]（含 i）中有多少个 c1
        if(i > 0) pre[i] = pre[i-1];
        if(s[i] == c1) {
            pre[i]++;
        }

        // 若当前 s[i] == c2 并且 i+1 >= k，则子串长度可达 k
        // 以 i 为尾的子串起点可到 i-(k-1), 于是把 [0.. i-(k-1)] 之间的 c1 次数加进结果
        if(s[i] == c2 && i+1 >= k){
            res += pre[i - k + 1];
        }
    }

    cout << res << "\n";
    return 0;
}
