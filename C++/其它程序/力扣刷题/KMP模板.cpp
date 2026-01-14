// //? 常用的 PMT (next) 数组是 0-based，存储最长公共前后缀长度，和字符串索引完全一致。
// ? 教材的“1-based next”表示失配跳转位置，主要是形式美观，实际刷题中不常用。
// ? -1 开头的 next 版也是 0-based，只是为了在失配时统一处理逻辑，避免多余 if。
// ? 如果没有明确限制，竞赛和面试中建议使用 0-based 版本，代码简洁自然。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;

class Solution {
private:
    vector<int> next;

    // 构建 next 数组（前缀函数）
    vector<int> build_next(const string& needle) {
        int n = needle.size();
        next.assign(n, 0); // 初始化 next 数组为 0
        int len = 0; // len 表示前缀长度
        for (int i = 1; i < n; ++i) {
            // 回退到上一个最长相等前后缀的位置
            while (len > 0 && needle[i] != needle[len]) {
                len = next[len - 1];
            }
            if (needle[i] == needle[len]) {
                ++len;
            }
            next[i] = len;
        }
        return next;
    }

public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0; // 特殊情况：空字符串
        int m = haystack.size();
        int n = needle.size();
        build_next(needle);

        int i = 0, j = 0; // i: 主串指针，j: 子串指针
         while(i<m){
            if(haystack[i]==needle[j]){
                i++;
                j++;
            }else if(j>0)  {//字符失衡，根据next 跳过字串前面的一些字符
                j=next[j-1];
            }else i++; //字串第一个字符就失衡
            if(j==n) return i-j;//重叠一个起始字符 刚好为开始索引
        }
        return -1;
    }
};