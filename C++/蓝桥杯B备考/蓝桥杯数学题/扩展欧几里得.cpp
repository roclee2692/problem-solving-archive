#include <iostream>

using namespace std;

/**
 * 扩展欧几里得算法 (Extended Euclidean Algorithm)
 * 计算 ax + by = gcd(a, b) 的整数解 (x, y)
 *
 * @param a: 整数 a
 * @param b: 整数 b
 * @param x: 用于存储解 x
 * @param y: 用于存储解 y
 * @return  返回 gcd(a, b)
 */
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {  // 递归终止条件：gcd(a, 0) = a
        x = 1, y = 0;
        return a;  // gcd(a, 0) = a
    }

    int x1, y1;  // 用于存储子问题的解
    int gcd = exgcd(b, a % b, x1, y1);  // 递归求解 gcd(b, a % b)

    // 根据递归返回的解 (x1,y1 ) 计算当前 (x, y)    
    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;  // 返回 gcd(a, b)
}

int main() {
    int a, b, x, y;
    cout << "请输入 a 和 b: ";
    cin >> a >> b;

    // 调用扩展欧几里得算法，求解 ax + by = gcd(a, b)
    int gcd = exgcd(a, b, x, y);

    // 输出结果
    cout << "gcd(" << a << ", " << b << ") = " << gcd << endl;
    cout << "方程解: x = " << x << ", y = " << y << endl;

    // 验证: ax + by 是否等于 gcd(a, b)
    cout << "验证: " << a << " * " << x << " + " << b << " * " << y << " = " << gcd << endl;
    
    return 0;
}
