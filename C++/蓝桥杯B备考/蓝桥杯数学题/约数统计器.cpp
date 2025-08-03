#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1000000;
vector<int> divisors(MAX_N + 1, 0);

// 预处理所有数的约数个数
void preprocess(int N) {
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            divisors[j]++;
        }
    }
}

int main() {
    int N = 10000; // 可修改 N
    preprocess(N);
    
    // 输出 1~N 每个数的约数个数
    for (int i = 1; i <= N; i++) { // 只展示前10个
        cout << "Number " << i << " has " << divisors[i] << " divisors.\n";
    }
    return 0;
}
