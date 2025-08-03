#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 高精度乘法
vector<int> bigMultiply(vector<int> &a, int b) {
    vector<int> res;
    int carry = 0;
    for (int i = 0; i < a.size() || carry; i++) {
        if (i < a.size()) carry += a[i] * b;
        res.push_back(carry % 10); // 存个位
        carry /= 10; // 进位
    }
    while (res.size() > 1 && res.back() == 0) res.pop_back(); // 去掉前导0
    return res;
}

// 高精度除法
vector<int> bigDivide(vector<int> &a, int b) {
    vector<int> res;
    int remainder = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        remainder = remainder * 10 + a[i];
        res.push_back(remainder / b);
        remainder %= b;
    }
    while (res.size() > 1 && res.back() == 0) res.pop_back(); // 去掉前导0
    reverse(res.begin(), res.end()); // 逆序存储
    return res;
}

// 打印高精度数
void printBigNum(vector<int> &num) {
    for (int i = num.size() - 1; i >= 0; i--) {
        cout << num[i];
    }
    cout << endl;
}

// 计算 C(n, m)
vector<int> comb(int n, int m) {
    vector<int> numerator = {1}; // 存 n! / (n-m)!
    for (int i = n; i > n - m; i--) {
        numerator = bigMultiply(numerator, i);
    }

    vector<int> denominator = {1}; // 存 m!
    for (int i = 1; i <= m; i++) {
        denominator = bigMultiply(denominator, i);
    }

    return bigDivide(numerator, m); // 计算组合数
}

int main() {
    int n = 1000, m = 500;
    cout << "C(1000, 500) = ";
    vector<int> result = comb(n, m);
    printBigNum(result);
    return 0;
}
