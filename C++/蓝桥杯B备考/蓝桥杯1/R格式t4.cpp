#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 模拟字符串小数乘以2（支持带小数点）
// 输入：如 "3.14"
// 输出：乘2后结果，如 "6.28"
string mul2(string s){
    string r;     // 存储乘2后的结果
    int c = 0;    // 进位 carry
    int n = s.size();
    for(int i = n - 1; i >= 0; i--){  // 从后往前处理每一位
        if(s[i] == '.'){              // 如果遇到小数点，直接加进去
            r = '.' + r;
            continue;
        }
        int t = (s[i] - '0') * 2 + c; // 当前位乘2加上进位
        c = t / 10;                   // 计算新的进位
        r = char(t % 10 + '0') + r;   // 当前位结果加到结果字符串前面
    }
    if(c) r = char(c + '0') + r;      // 如果最前还有进位，补上
    return r;
}

// 四舍五入函数，只保留整数部分
// 输入：如 "12.56"
// 输出：四舍五入后结果 "13"
string round(string s){
    int p = s.find('.');             // 找到小数点的位置
    int f = s[p + 1] >= '5';         // 判断小数点后一位是否 >=5，用于是否进1
    int i = p - 1;                   // 从整数部分最后一位开始往前处理进位
    string res = s.substr(0, p);//0是子字符串截取的起点，p是截取的长度
      // 提取整数部分（不包括小数点后） 
  
    while(f && i >= 0){              // 如果需要进位，往前处理
        if(res[i] == '9')            // 如果当前位是9，进1会变成0
            res[i] = '0';
        else{
            res[i]++;                // 非9直接加1
            f = 0;                   // 进位处理完毕
        }
        i--;
    }

    if(f) res = '1' + res;           // 如果全是9，例如 999.5，最后变成 1000
    return res;
}

int main(){
    int n;          // 乘以 2 的次数（即乘以 2 的 n 次方）
    string d;       // 输入的浮点数（以字符串读入，支持高精度）
    cin >> n >> d;

    while(n--)      // 重复 n 次乘以 2
    d = mul2(d);

    cout << round(d); // 最后输出四舍五入后的整数部分
}
