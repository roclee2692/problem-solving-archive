#include <iostream>

using namespace std;

// 计算 GCD
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 计算 LCM
int lcm(int a, int b) {
    return a / gcd(a, b) * b; // 先除再乘，防止溢出
}

int main() {
    int a, b;
    cout << "请输入两个数: ";
    cin >> a >> b;
    
    cout << "lcm(" << a << ", " << b << ") = " << lcm(a, b) << endl;
    return 0;
}
