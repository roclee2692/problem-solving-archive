#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdint>
using namespace std;

// 计算最大公约数（欧几里得算法）
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// 计算最小公倍数
long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

int main() {
    // 给定矩形尺寸和速度分量
    const long long W = 233333;
    const long long H = 343720;
    const long long dx = 15;
    const long long dy = 17;

    // 计算水平方向的辅助值：lcm_x = (W * dx) / gcd(W, dx)
    long long g1 = gcd(W, dx);
    long long lcm_x = (W * dx) / g1;

    // 计算竖直方向的辅助值：lcm_y = (H * dy) / gcd(H, dy)
    long long g2 = gcd(H, dy);
    long long lcm_y = (H * dy) / g2;

    // 分别计算 a = lcm_x/dx 和 b = lcm_y/dy
    long long a = lcm_x / dx;
    long long b = lcm_y / dy;

    // k 为 a 和 b 的最小公倍数，即完整周期所需的“步数”
    long long k = lcm(a, b);

    // 每一步（从一次“碰撞”到下一次）的位移长度
    double step_length = sqrt(dx * dx + dy * dy);
    // 总路径长度（保留两位小数输出）
    double path_length = k * step_length;

    cout << "辅助计算：\n";
    cout << "  a = lcm_x/dx = " << a << "\n";
    cout << "  b = lcm_y/dy = " << b << "\n";
    cout << "  k = lcm(a, b) = " << k << "\n";
    cout << "\n小球完整周期内的总路径长度 = " 
         << fixed << setprecision(2) << path_length << "\n\n";

    // 下面模拟输出前 10 个碰撞点（即小球与边界碰撞后的反射位置）
    // 注意：完整周期内碰撞次数可能非常巨大，故这里只演示部分轨迹。
    cout << "前10个碰撞点坐标（单位坐标系）：\n";
    double x = 0.0, y = 0.0;
    double vx = dx, vy = dy;
    cout << fixed << setprecision(2);
    cout << "(0.00, 0.00)" << "\n"; // 初始点

    int count = 0;
    while (count < 10) {
        double x_next = x + vx;
        double y_next = y + vy;

        // 检查水平边界碰撞
        if (x_next > W || x_next < 0) {
            vx = -vx; // 反转水平速度
            if (x_next > W)
                x_next = W - (x_next - W);
            else if (x_next < 0)
                x_next = -x_next;
        }
        // 检查竖直边界碰撞
        if (y_next > H || y_next < 0) {
            vy = -vy; // 反转竖直速度
            if (y_next > H)
                y_next = H - (y_next - H);
            else if (y_next < 0)
                y_next = -y_next;
        }

        x = x_next;
        y = y_next;
        cout << "(" << x << ", " << y << ")" << "\n";
        count++;
    }

    return 0;
}
