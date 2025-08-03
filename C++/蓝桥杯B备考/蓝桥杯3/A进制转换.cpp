#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// 支持最大进制为62（0-9 + A-Z + a-z）
const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

// 把字符（如'A'）转换为对应的数值（如10）
int charToValue(char ch) {
    if (isdigit(ch)) return ch - '0';
    if (isupper(ch)) return ch - 'A' + 10;
    return ch - 'a' + 36;
}

// 把数值（如10）转换为字符（如'A'）
char valueToChar(int val) {
    return digits[val];
}

// 将“任意进制的数”（字符串）转为十进制整数
int convertToDecimal(const string& numStr, int fromBase) {
    int decimalValue = 0;
    // 任意进制转十进制：从左到右每位“乘基加位值”，等价于数学上的权值展开
    for (size_t i = 0; i < numStr.length(); i++) {
        int digit = charToValue(numStr[i]);
        decimalValue = decimalValue * fromBase + digit;
    }
    return decimalValue;
}

// 将“十进制整数”转为“任意进制表示”（字符串）
string convertFromDecimal(int decimalValue, int toBase) {
    if (decimalValue == 0) return "0";
    string result = "";
    while (decimalValue > 0) {
        int remainder = decimalValue % toBase;
        // 每次取余得最低位字符，从低到高拼接，最后 reverse() 还原高位在前顺序
        result += valueToChar(remainder);
        decimalValue /= toBase;
    }// 每次插到前面,这样就不需要 reverse()，但效率稍低，因为每次都移动前缀。
    reverse(result.begin(), result.end()); // 结果需反转
    return result;
}

// 统一函数：任意进制 ? 任意进制
string convertBase(const string& numStr, int fromBase, int toBase) {
    int decimal = convertToDecimal(numStr, fromBase);    // 第一步：先转为十进制
    return convertFromDecimal(decimal, toBase);          // 第二步：再转为目标进制
}
int main() {
    string originalNum = "245";
    int fromBase = 9;
    int toBase = 16;

    string result = convertBase(originalNum, fromBase, toBase);
    cout << originalNum << " (base " << fromBase << ") ? "
         << result << " (base " << toBase << ")" << endl;

    return 0;
}
