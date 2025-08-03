#include <iostream>
using namespace std;

int countDivisors(int n) {
    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            count++; // i 是约数
            if (i != n / i) count++; // n/i 也是约数
        }
    }
    return count;
}

int main() {
    int n = 12;
    cout << "Number of divisors of " << n << " is " << countDivisors(n) << endl;
    return 0;
}
