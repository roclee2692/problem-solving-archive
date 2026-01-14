#include <iostream>
using namespace std;

int main() {
    int x = 5;
    cout << "程序正常输出：x = " << x << endl; // 会被题目评测系统看到
    cerr << "调试信息：变量 x = " << x << endl; // 评测系统看不到，只是你自己看

    return 0;
}
