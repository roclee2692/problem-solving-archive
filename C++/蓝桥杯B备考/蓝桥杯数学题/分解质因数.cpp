#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 质因数分解
vector<pair<int, int>> prime_factorization(int n) {
    vector<pair<int, int>> factors;
    
    // 处理 2 的因子
    int count = 0;
    while (n % 2 == 0) {
        n /= 2;
        count++;
    }
    if (count) factors.push_back({2, count});
    
    // 处理奇数因子
    for (int i = 3; i <= sqrt(n); i += 2) {
        count = 0;
        while (n % i == 0) {
            n /= i;
            count++;
        }
        if (count) factors.push_back({i, count});
    }
    
    // 处理 n 本身是质数的情况
    if (n > 1) factors.push_back({n, 1});
    
    return factors;
}

int main() {
    int n;
    cout << "请输入一个整数: ";
    cin >> n;
    
    vector<pair<int, int>> factors = prime_factorization(n);
    cout << "质因数分解: ";
    for (auto &p : factors) {
        cout << p.first << "^" << p.second << " ";
    }
    cout << endl;
    
    return 0;
}
